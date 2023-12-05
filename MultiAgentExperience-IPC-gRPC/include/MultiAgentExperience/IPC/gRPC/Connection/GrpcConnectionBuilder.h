/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_GRPC_GRPCCONNECTIONBUILDER_H
#define MULTIAGENTEXPERIENCE_IPC_GRPC_GRPCCONNECTIONBUILDER_H

#include <memory>

#include "MultiAgentExperience/IPC/gRPC/Connection/GrpcConnection.h"

namespace multiAgentExperience {
namespace ipc {
namespace grpc {
namespace connection {

class GrpcConnectionBuilderInterface {
public:
    virtual ~GrpcConnectionBuilderInterface() = default;

    virtual std::shared_ptr<GrpcConnectionInterface> build() = 0;

    virtual void setGrpcConnectionConfiguration(
        const GrpcConnectionConfiguration& grpcConnectionConfiguration) = 0;

    virtual void setIpcConnectionListeners(
        std::set<std::shared_ptr<maxIpcNamespace::transport::IpcConnectionListenerInterface>> connectionListeners) = 0;

    virtual void setConnectionInitiator(GrpcConnection::ConnectionInitiator connectionInitiator) = 0;
};

class GrpcConnectionBuilder : public GrpcConnectionBuilderInterface {
public:
    std::shared_ptr<GrpcConnectionInterface> build() override;

    void setGrpcConnectionConfiguration(
        const GrpcConnectionConfiguration& grpcConnectionConfiguration) override;

    void setIpcConnectionListeners(
        std::set<std::shared_ptr<maxIpcNamespace::transport::IpcConnectionListenerInterface>> connectionListeners) override;

    void setConnectionInitiator(GrpcConnection::ConnectionInitiator connectionInitiator) override;

    /**
     * When we re-establish the IPC connection on connection disruption, all IPC objects are reset. However, this does
     * not apply to the MessageSender. This is because, when an old Proxy (like the DialogManagerProxy) gets destructed,
     * it makes an asynchronous send() call using the MessageSender. Since, this Proxy is the last Proxy that holds a
     * strong reference to the IPC objects, after its destruction, all IPC objects get destructed. The send() call made
     * by the old DialogManagerProxy segfaults.
     *
     * To solve this, instead of creating a new MessageSender, we simply update the TransportSender stored in the
     * MessageSender, with the new TransportSender. Thus, the old DialogManagerProxy's send() call will succeed. Please
     * note that, this old send() call itself may be ignored by the other process.
     */
    void createOrUpdateMessageSender(std::shared_ptr<ipc::transport::TransportSenderInterface> transportSender);

private:
    GrpcConnectionConfiguration m_grpcConnectionConfiguration;
    std::set<std::shared_ptr<maxIpcNamespace::transport::IpcConnectionListenerInterface>> m_connectionListeners;
    GrpcConnection::ConnectionInitiator m_connectionInitiator;
    std::shared_ptr<maxIpcNamespace::transport::MessageSender> m_messageSender;
};

} // namespace connection
} // namespace grpc
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_GRPC_GRPCCONNECTIONBUILDER_H
