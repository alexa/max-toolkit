/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <utility>

#include "MultiAgentExperience/IPC/gRPC/Connection/MaxConnectionAdapter.h"

namespace multiAgentExperience {
namespace ipc {
namespace grpc {
namespace connection {

static const std::string MODULE_TAG("MaxConnectionAdapter");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

MaxConnectionAdapter::MaxConnectionAdapter(
    const std::shared_ptr<agent::AgentRegistrationInterface>& agentRegistration,
    const GrpcConnectionConfiguration& grpcConnectionConfiguration,
    const std::shared_ptr<GrpcConnectionBuilderInterface>& grpcConnectionBuilder,
    std::shared_ptr<thread::executor::threading::Executor> executor):
        m_agentRegistration{agentRegistration},
        m_grpcConnectionConfiguration{grpcConnectionConfiguration},
        m_grpcConnectionBuilder{grpcConnectionBuilder},
        m_executor{std::move(executor)} {
}

bool MaxConnectionAdapter::connect() {
    LX(DEBUG3, "");

    m_grpcConnectionBuilder->setGrpcConnectionConfiguration(m_grpcConnectionConfiguration);
    // The MaxConnectionAdapter is a connection listener since it needs to reset the IPC connection.
    m_grpcConnectionBuilder->setIpcConnectionListeners({shared_from_this()});
    // This connection is initiated in the agent process
    m_grpcConnectionBuilder->setConnectionInitiator(GrpcConnection::ConnectionInitiator::AGENT);
    LX(DEBUG3, "Creating gRPC connection");
    m_grpcConnection = m_grpcConnectionBuilder->build();

    LX(DEBUG3, "Creating AgentRegistrationMessageHandler and storing it in the MessageHandlerStore");
    /*
     * Important to create and store the agent registration object before instantiating IPC components. This is because
     * once the IPC connection is set up, the MAX process will immediately attempt to call AgentRegistrationInterface
     * APIs on the other process.
     */
    LX(DEBUG3, "Creating AgentRegistration message handler");
    m_grpcConnection->getMessageHandlerStore()->createOrGet(m_agentRegistration);

    return m_grpcConnection->establishConnection();
}

void MaxConnectionAdapter::disconnect() {
    LX(DEBUG3, "");
    if (m_grpcConnection) {
        // TODO: instead of manually clearing the MessageHandlerStore, we should change the MessageHandlers to hold
        //  weak references of the MessageHandlerStore, so that it gets destructed automatically.
        m_grpcConnection->getMessageHandlerStore()->clearStores();
        m_grpcConnection->shutdownServer();
        m_grpcConnection.reset();
    }
}

void MaxConnectionAdapter::onConnectionDisruption(){
    if (!m_mutex.try_lock()) {
        LX(DEBUG3, "Re-connection ongoing.");
        return;
    }

    m_executor->submit([this]() {
        LX(ERROR, "Connection is disrupted. Trying to establish connection again. ");

        if (m_serviceAvailabilityObserver) {
            LX(DEBUG3, "Notifying observers that MAX service is unavailable");
            m_serviceAvailabilityObserver->onServiceUnavailable();
        }

        disconnect();
        if (!connect()) {
            LX(DEBUG3, "Connection unsuccessful");
        } else {
            LX(DEBUG3, "Connection successful")
        }

        m_mutex.unlock();
    });
}

void MaxConnectionAdapter::setServiceAvailabilityObserver(
    std::shared_ptr<multiAgentExperience::ipc::transport::MAXServiceAvailabilityObserverInterface> serviceAvailabilityObserver) {
    LX(DEBUG3, "");
    m_serviceAvailabilityObserver = std::move(serviceAvailabilityObserver);
}

} // namespace connection
} // namespace grpc
} // namespace ipc
} // namespace multiAgentExperience