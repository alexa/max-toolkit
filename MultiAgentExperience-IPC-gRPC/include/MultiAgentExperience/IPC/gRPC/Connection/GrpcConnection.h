/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_MAXCONNECTION_H
#define MULTIAGENTEXPERIENCE_IPC_MAXCONNECTION_H

#include <MultiAgentExperience/IPC/Proxy/Agent/AgentRegistrationMessageHandler.h>
#include <MultiAgentExperience/IPC/Proxy/MessageHandlerStore.h>
#include <MultiAgentExperience/IPC/Proxy/MessageRouter.h>
#include <MultiAgentExperience/IPC/Transport/IpcConnectionListenerInterface.h>
#include <MultiAgentExperience/IPC/Transport/MessageSender.h>
#include <MultiAgentExperience/IPC/Transport/TransportFutureResponseStore.h>

#include "MultiAgentExperience/IPC/gRPC/Adaptor/GrpcTransportReceiver.h"
#include "MultiAgentExperience/IPC/gRPC/Adaptor/GrpcTransportSender.h"
#include "MultiAgentExperience/IPC/gRPC/Connection/GrpcConnectionConfiguration.h"
#include "MultiAgentExperience/IPC/gRPC/Transport/GrpcClient.h"
#include "MultiAgentExperience/IPC/gRPC/Transport/GrpcServer.h"

namespace multiAgentExperience {
namespace ipc {
namespace grpc {
namespace connection {

/// Create namespace aliases for MAX-IPC & MAX-Grpc namespaces
namespace maxIpcNamespace = multiAgentExperience::ipc;
namespace maxGrpcNamespace = multiAgentExperience::ipc::grpc;

class GrpcConnectionInterface {
public:
    virtual ~GrpcConnectionInterface() = default;
    virtual bool establishConnection() = 0;
    virtual void shutdownServer() = 0;
    virtual std::shared_ptr<maxIpcNamespace::transport::MessageSender> getMessageSender() = 0;
    virtual std::shared_ptr<maxIpcNamespace::proxy::MessageHandlerStore> getMessageHandlerStore() = 0;
};

class GrpcConnection : public GrpcConnectionInterface {
public:

    /// Describes who initiates and creates this GrpcConnection object
    enum class ConnectionInitiator {
        /// Initiated by an agent
        AGENT,

        /// Initiated by MAX
        MAX
    };

    /// Constructor
    GrpcConnection(
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
        std::shared_ptr<thread::executor::threading::Executor> executor = std::make_shared<thread::executor::threading::Executor>());

    /// Any component that creates a GrpcConnection object will likely want to start the gRPC server using this method.
    bool establishConnection() override;

    /// Required for shutting down the grpc server. Useful for testing.
    void shutdownServer() override;

    std::shared_ptr<maxIpcNamespace::transport::MessageSender> getMessageSender() override;

    std::shared_ptr<maxIpcNamespace::proxy::MessageHandlerStore> getMessageHandlerStore() override;

private:
    void notifyConnectionListeners();

    std::set<std::shared_ptr<maxIpcNamespace::transport::IpcConnectionListenerInterface>> m_connectionListeners;
    GrpcConnectionConfiguration m_grpcConnectionConfiguration;
    std::shared_ptr<maxIpcNamespace::transport::TransportFutureResponseStore> m_transportFutureResponseStore;
    std::shared_ptr<maxGrpcNamespace::transport::GrpcClientInterface> m_grpcClient;
    std::shared_ptr<maxIpcNamespace::transport::TransportSenderInterface> m_grpcTransportSender;
    std::shared_ptr<maxIpcNamespace::transport::MessageSender> m_messageSender;
    std::shared_ptr<maxIpcNamespace::proxy::MessageHandlerStore> m_messageHandlerStore;
    std::shared_ptr<maxIpcNamespace::transport::TransportHandlerInterface> m_messageRouter;
    std::shared_ptr<transport::GrpcReceiverInterface> m_grpcTransportReceiver;
    std::shared_ptr<transport::GrpcServerInterface> m_grpcServer;
    GrpcConnection::ConnectionInitiator m_connectionInitiator;
    std::shared_ptr<thread::executor::threading::Executor> m_executor;
};

} // namespace connection
} // namespace grpc
} // namespace ipc
} // namespace multiAgentExperience

#endif // MULTIAGENTEXPERIENCE_IPC_MAXCONNECTION_H