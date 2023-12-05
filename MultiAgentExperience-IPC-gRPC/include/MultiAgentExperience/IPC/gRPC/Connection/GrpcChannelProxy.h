/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_GRPC_GRPCCHANNELPROXY_H
#define MULTIAGENTEXPERIENCE_IPC_GRPC_GRPCCHANNELPROXY_H

#include <grpcpp/create_channel.h>

#include <maxrpc.grpc.pb.h>

namespace multiAgentExperience {
namespace ipc {
namespace grpc {
namespace connection {

class GrpcChannelProxyInterface {
public:
    virtual ~GrpcChannelProxyInterface() = default;
    virtual bool WaitForConnected(int timeoutInMilliSeconds) = 0;
    virtual grpc_connectivity_state GetState() = 0;
    virtual ::grpc::Status send(MultiAgentExperience::Rpc::Message message) = 0;
};

/// This is a wrapper to the ::grpc::Channel class present in the gRPC library, and only exposes important APIs from it.
/// This class was introduced in order to make IPC components more testable.
class GrpcChannelProxy : public GrpcChannelProxyInterface {
public:

    /**
     * Constructor
     * @param targetUri The host:port string that represents the URI of the gRPC server in the other process.
     */
    explicit GrpcChannelProxy(const std::string& targetUri);
    bool WaitForConnected(int timeoutInMilliSeconds) override;
    grpc_connectivity_state GetState() override;
    ::grpc::Status send(MultiAgentExperience::Rpc::Message message) override;

private:
    std::shared_ptr<::grpc::Channel> m_channel;
    std::unique_ptr<MultiAgentExperience::Rpc::MultiAgentExperienceService::Stub> m_stub;
};

} // namespace connection
} // namespace grpc
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_GRPC_GRPCCHANNELPROXY_H
