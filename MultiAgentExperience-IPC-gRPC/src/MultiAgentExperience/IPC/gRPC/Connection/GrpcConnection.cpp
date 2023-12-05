/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/IPC/gRPC/Connection/GrpcConnection.h"

#include <utility>

namespace multiAgentExperience {
namespace ipc {
namespace grpc {
namespace connection {

static const std::string MODULE_TAG("GrpcConnection");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

GrpcConnection::GrpcConnection(
    const GrpcConnectionConfiguration& grpcConnectionConfiguration,
    std::set<std::shared_ptr<maxIpcNamespace::transport::IpcConnectionListenerInterface>> connectionListeners,
    std::shared_ptr<maxIpcNamespace::transport::TransportFutureResponseStore> transportFutureResponseStore,
    std::shared_ptr<maxGrpcNamespace::transport::GrpcClientInterface> grpcClient,
    std::shared_ptr<maxIpcNamespace::transport::TransportSenderInterface> grpcTransportSender,
    std::shared_ptr<maxIpcNamespace::transport::MessageSender> messageSender,
    std::shared_ptr<maxIpcNamespace::proxy::MessageHandlerStore> messageHandlerStore,
    std::shared_ptr<maxIpcNamespace::transport::TransportHandlerInterface> messageRouter,
    std::shared_ptr<transport::GrpcReceiverInterface> grpcTransportReceiver,
    std::shared_ptr<transport::GrpcServerInterface> grpcServer,
    const GrpcConnection::ConnectionInitiator& connectionInitiator,
    std::shared_ptr<thread::executor::threading::Executor> executor)
        : m_grpcConnectionConfiguration{grpcConnectionConfiguration}
        , m_connectionListeners{std::move(connectionListeners)}
        , m_transportFutureResponseStore{std::move(transportFutureResponseStore)}
        , m_grpcClient{std::move(grpcClient)}
        , m_grpcTransportSender{std::move(grpcTransportSender)}
        , m_messageSender{std::move(messageSender)}
        , m_messageHandlerStore{std::move(messageHandlerStore)}
        , m_messageRouter{std::move(messageRouter)}
        , m_grpcTransportReceiver{std::move(grpcTransportReceiver)}
        , m_grpcServer{std::move(grpcServer)}
        , m_connectionInitiator(connectionInitiator)
        , m_executor{std::move(executor)} {
}

bool GrpcConnection::establishConnection() {
    LX(DEBUG3, "")

    LX(DEBUG3, "Starting the server")
    auto isServerStarted = m_grpcServer->startServer();
    if (!isServerStarted) {
        LX(ERROR, "startServer failed, invoking onConnectionDisruption");
        notifyConnectionListeners();
        return false;
    }

    LX(DEBUG3, "Waiting for connection to the remote server to be established")
    auto isConnectionEstablished = m_grpcClient->waitForConnectionEstablished(connection::CONNECTION_TIMEOUT_MILLISECONDS);
    if (!isConnectionEstablished) {
        LX(ERROR, "waitForConnectionEstablished failed, invoking onConnectionDisruption");
        notifyConnectionListeners();
        return false;
    }

    LX(DEBUG3, "Setting up the connection monitoring")
    auto isConnectionMonitoringSetup = m_grpcClient->setupConnectionMonitoring();
    if (!isConnectionMonitoringSetup) {
        LX(ERROR, "setupConnectionMonitoring failed, invoking onConnectionDisruption");
        notifyConnectionListeners();
        return false;
    }

    /**
     * Here, we ensure that MAX waits for the client in the agent process to send a CONNECTED_TO_MAX message. We want
     * to ensure that the client in the agent process has successfully connected to the MAX server.
     * For example, when MAX registers the agent, and invokes sync APIs like getId, it will fail to get a response if
     * the agent's client has not yet connected to the MAX server.
     */
    switch (m_connectionInitiator) {
        case ConnectionInitiator::AGENT:
            LX(DEBUG3, "Agent initiated connection. Sending CONNECTED_TO_MAX")
            // The agent process sends the CONNECTED_TO_MAX message
            m_grpcTransportSender->sendConnectedToMaxMessage();
            break;

        case ConnectionInitiator::MAX: {
            LX(DEBUG3, "MAX initiated connection. Waiting for incoming CONNECTED_TO_MAX")
            // The MAX process waits for the agent to send the CONNECTED_TO_MAX message
            auto isReady = m_grpcTransportReceiver->waitForReady();
            if (!isReady) {
                LX(ERROR, "waitForReady failed, invoking onConnectionDisruption");
                notifyConnectionListeners();
                return false;
            }
            break;
        }

        default: break;
    }

    return true;
}

void GrpcConnection::shutdownServer() {
    LX(DEBUG3, "")
    m_grpcServer->shutdown();
}

std::shared_ptr<maxIpcNamespace::transport::MessageSender> GrpcConnection::getMessageSender(){
    return m_messageSender;
}

std::shared_ptr<maxIpcNamespace::proxy::MessageHandlerStore> GrpcConnection::getMessageHandlerStore(){
    return m_messageHandlerStore;
}

void GrpcConnection::notifyConnectionListeners() {
    LX(DEBUG3, "")

    m_executor->submit([this]() {
        LX(DEBUG3, "Calling connection disruption for each listener");
        for (const auto& connectionListener: m_connectionListeners) {
            connectionListener->onConnectionDisruption();
        }
    });
}

} // namespace connection
} // namespace grpc
} // namespace ipc
} // namespace multiAgentExperience