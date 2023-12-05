/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/IPC/gRPC/Transport/GrpcClient.h"

#include <chrono>
#include <thread>
#include <sstream>

#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "MultiAgentExperience/IPC/gRPC/Connection/GrpcConnectionConfiguration.h"
#include "MultiAgentExperience/IPC/gRPC/Utils/MessageUtils.h"

namespace multiAgentExperience {
namespace ipc {
namespace grpc {
namespace transport {

static const std::string MODULE_TAG("GrpcClient");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

GrpcClient::GrpcClient(
    std::shared_ptr<connection::GrpcChannelProxyInterface> grpcChannelProxy,
    std::set<std::shared_ptr<multiAgentExperience::ipc::transport::IpcConnectionListenerInterface>> connectionListeners,
    std::shared_ptr<thread::executor::threading::Executor> connectionStatusExecutor):
        m_grpcChannelProxy{grpcChannelProxy},
        m_connectionListeners{connectionListeners},
        m_connectionStatusExecutor{connectionStatusExecutor} {
}

void GrpcClient::send(MultiAgentExperience::Rpc::Message message) {
    LX(DEBUG3, "");

    auto status = m_grpcChannelProxy->send(message);

    // If status is not OK, signal IpcConnectionListenerInterface about disruption, to take remediation measures.
    if(!status.ok()) {
        std::stringstream logValue;
        logValue << "send failed"
                 << ": errorCode=" << std::to_string(status.error_code())
                 << ", errorMessage=" << status.error_message()
                 << ", errorDetails=" << status.error_details();
        LX(ERROR, logValue.str());

        notifyConnectionListeners();
    }
}

bool GrpcClient::isConnected() {
    auto grpcState = m_grpcChannelProxy->GetState();
    // GRPC_CHANNEL_READY indicates that communication has been established. Any other state indicates otherwise.
    return grpcState == ::grpc_connectivity_state::GRPC_CHANNEL_READY;
}

bool GrpcClient::waitForConnectionEstablished(const int timeoutInMilliSeconds) {
    LX(DEBUG1, "");

    if (isConnected()) {
        LX(DEBUG3, "Client is already connected");
        return true;
    }

    return m_grpcChannelProxy->WaitForConnected(timeoutInMilliSeconds);
}

bool GrpcClient::setupConnectionMonitoring()  {
    LX(DEBUG1, "");

    if (!isConnected()) {
        // Don't want to set up connection monitoring if the client has not been connected to the
        LX(ERROR, "Client is not connected. Connection monitoring is not set up");
        return false;
    }

    // Connection needs to be monitored in a separate thread, so as not to block the current thread.
    m_connectionStatusExecutor->submit([this]() {
        this->monitorConnection();
    });

    return true;
}

void GrpcClient::monitorConnection() {
    LX(DEBUG1, "");

    /**
     * Continue to monitor the connection until there is a disruption.
     *
     * Once connection is established the gRPC channel state changes to READY, which we consider as a "good" state. When
     * the channel state changes to IDLE, we will execute connection disruption logic and reset the IPC objects. The
     * gRPC channel state changes to IDLE on two occasions:
     *   1. When there is an explicit disconnection by the other process
     *   2. When there has been no RPC activity on the channel for over IDLE_TIMEOUT ms. By default the IDLE_TIMEOUT
     *      value is INT64_MAX ms (infinite) or INT32_MAX ms (24 days).
     */
    while (isConnected()) {
        // Sleep before checking for the Channel status again.
        std::this_thread::sleep_for(std::chrono::milliseconds(connection::CONNECTION_STATUS_CHECK_INTERVAL_MILLISECONDS));
    }

    LX(ERROR, "Connection check failed. Notifying observers about connection disruption");
    // Signal IpcConnectionListenerInterface about disruption.
    notifyConnectionListeners();
}

void GrpcClient::notifyConnectionListeners() {
    LX(DEBUG3, "");
    for (const auto& connectionListener: m_connectionListeners) {
        connectionListener->onConnectionDisruption();
    }
}

} // namespace transport
} // namespace grpc
} // namespace ipc
} // namespace multiAgentExperience