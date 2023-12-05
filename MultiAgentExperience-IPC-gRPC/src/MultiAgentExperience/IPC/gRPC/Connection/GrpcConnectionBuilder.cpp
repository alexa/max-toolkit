/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/IPC/gRPC/Connection/GrpcConnectionBuilder.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

namespace multiAgentExperience {
namespace ipc {
namespace grpc {
namespace connection {

static const std::string MODULE_TAG("GrpcConnectionBuilder");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

std::shared_ptr<GrpcConnectionInterface> GrpcConnectionBuilder::build() {
    //Check if all parameters are set
    if(m_grpcConnectionConfiguration.getClientUri().empty()) {
        LX(ERROR, "ClientUri not set!");
        return nullptr;
    }
    if(m_grpcConnectionConfiguration.getServerUri().empty()) {
        LX(ERROR, "ServerUri not set!");
        return nullptr;
    }
    if(m_connectionListeners.empty()) {
        LX(ERROR, "ConnectionListeners are not set!");
        return nullptr;
    }
    if(m_connectionInitiator == GrpcConnection::ConnectionInitiator::AGENT) {
        LX(DEBUG3, "ConnectionInitiator is set to AGENT!");
    } else if (m_connectionInitiator == GrpcConnection::ConnectionInitiator::MAX) {
        LX(DEBUG3, "ConnectionInitiator is set to MAX!");
    }

    /// Create all objects necessary for a successful gRPC connection
    auto transportFutureResponseStore = std::make_shared<maxIpcNamespace::transport::TransportFutureResponseStore>();

    // Create the gRPC channel that connects to the gRPC server on the other process
    auto grpcChannelProxy = std::make_shared<connection::GrpcChannelProxy>(m_grpcConnectionConfiguration.getClientUri());
    auto grpcClient = std::make_shared<maxGrpcNamespace::transport::GrpcClient>(grpcChannelProxy, m_connectionListeners);

    auto grpcTransportSender = std::make_shared<maxGrpcNamespace::adaptor::GrpcTransportSender>(
        grpcClient, transportFutureResponseStore);

    createOrUpdateMessageSender(grpcTransportSender);

    auto messageHandlerStore = std::make_shared<maxIpcNamespace::proxy::MessageHandlerStore>(m_messageSender);

    auto messageRouter = std::make_shared<maxIpcNamespace::proxy::MessageRouter>(
        messageHandlerStore, transportFutureResponseStore);

    auto grpcTransportReceiver = std::make_shared<maxGrpcNamespace::adaptor::GrpcTransportReceiver>(
        messageRouter, grpcTransportSender);

    // Create the gRPC server for this process
    auto grpcServerProxy = std::make_shared<connection::GrpcServerProxy>(
        m_grpcConnectionConfiguration.getServerUri(), grpcTransportReceiver);
    auto grpcServer = std::make_shared<maxGrpcNamespace::transport::GrpcServer>(grpcServerProxy, grpcTransportReceiver);

    return std::make_shared<GrpcConnection>(
        m_grpcConnectionConfiguration,
        m_connectionListeners,
        transportFutureResponseStore,
        grpcClient,
        grpcTransportSender,
        m_messageSender,
        messageHandlerStore,
        messageRouter,
        grpcTransportReceiver,
        grpcServer,
        m_connectionInitiator);
}

void GrpcConnectionBuilder::setGrpcConnectionConfiguration(
    const GrpcConnectionConfiguration& grpcConnectionConfiguration) {
    m_grpcConnectionConfiguration = grpcConnectionConfiguration;
}

void GrpcConnectionBuilder::setIpcConnectionListeners(
    std::set<std::shared_ptr<maxIpcNamespace::transport::IpcConnectionListenerInterface>> connectionListeners) {
    LX(DEBUG3, "Total number of connection listeners set is: " + std::to_string(connectionListeners.size()));
    m_connectionListeners = connectionListeners;
}

void GrpcConnectionBuilder::setConnectionInitiator(GrpcConnection::ConnectionInitiator connectionInitiator) {
    m_connectionInitiator = connectionInitiator;
}

void GrpcConnectionBuilder::createOrUpdateMessageSender(
    std::shared_ptr<ipc::transport::TransportSenderInterface> transportSender) {

    if (m_messageSender) {
        LX(DEBUG3, "Updating message sender");
        m_messageSender->updateTransportSender(transportSender);
    } else {
        LX(DEBUG3, "Creating a new message sender");
        m_messageSender = std::make_shared<maxIpcNamespace::transport::MessageSender>(transportSender);
    }
}

} // namespace connection
} // namespace grpc
} // namespace ipc
} // namespace multiAgentExperience