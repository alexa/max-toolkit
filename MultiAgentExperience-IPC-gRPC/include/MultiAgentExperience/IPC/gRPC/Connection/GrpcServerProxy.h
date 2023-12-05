/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_GRPC_GRPCSERVERPROXY_H
#define MULTIAGENTEXPERIENCE_IPC_GRPC_GRPCSERVERPROXY_H

#include <grpcpp/server.h>

#include "maxrpc.grpc.pb.h"
#include "MultiAgentExperience/IPC/gRPC/Transport/GrpcReceiverInterface.h"

namespace multiAgentExperience {
namespace ipc {
namespace grpc {
namespace connection {

class GrpcServerProxyInterface {
public:
    virtual ~GrpcServerProxyInterface() = default;
    virtual bool BuildAndStart() = 0;
    virtual void Shutdown() = 0;
    virtual void Wait() = 0;
};

/// This is a wrapper to the ::grpc::Server class present in the gRPC library, and only exposes important APIs from it.
/// This class was introduced in order to make IPC components more testable.
class GrpcServerProxy
    : public GrpcServerProxyInterface
    , public MultiAgentExperience::Rpc::MultiAgentExperienceService::Service {

public:
    explicit GrpcServerProxy(
        const std::string& serverUri,
        const std::shared_ptr<multiAgentExperience::ipc::grpc::transport::GrpcReceiverInterface>& grpcReceiver);

    bool BuildAndStart() override;
    void Shutdown() override;
    void Wait() override;
    ::grpc::Status handle(
        ::grpc::ServerContext* context,
        const ::MultiAgentExperience::Rpc::Message* request,
        ::MultiAgentExperience::Rpc::VoidPayload* response) override;

private:
    std::string m_serverUri;
    std::shared_ptr<multiAgentExperience::ipc::grpc::transport::GrpcReceiverInterface> m_grpcReceiver;
    std::unique_ptr<::grpc::Server> m_server;
};

} // namespace connection
} // namespace grpc
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_GRPC_GRPCSERVERPROXY_H
