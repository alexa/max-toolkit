/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/IPC/gRPC/Connection/GrpcChannelProxy.h"

#include "MultiAgentExperience/IPC/gRPC/Connection/GrpcConnectionConfiguration.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

namespace multiAgentExperience {
namespace ipc {
namespace grpc {
namespace connection {

static const std::string MODULE_TAG("GrpcChannelProxy");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

GrpcChannelProxy::GrpcChannelProxy(const std::string& targetUri) {
    m_channel = ::grpc::CreateChannel(targetUri, ::grpc::InsecureChannelCredentials());
    m_stub = MultiAgentExperience::Rpc::MultiAgentExperienceService::NewStub(m_channel);
}

bool GrpcChannelProxy::WaitForConnected(int timeoutInMilliSeconds) {
    LX(DEBUG3, "")

    std::chrono::system_clock::time_point deadline = std::chrono::system_clock::now() +
        std::chrono::milliseconds(timeoutInMilliSeconds);

    auto isConnected = m_channel->WaitForConnected(deadline);
    LX(DEBUG3, "isConnected: " + std::to_string(isConnected));

    return isConnected;
}

grpc_connectivity_state GrpcChannelProxy::GetState() {
    return m_channel->GetState(false);
}

::grpc::Status GrpcChannelProxy::send(MultiAgentExperience::Rpc::Message message) {
    ::grpc::ClientContext context;
    MultiAgentExperience::Rpc::VoidPayload voidPayload;
    return m_stub->handle(&context, message, &voidPayload);
}

} // namespace connection
} // namespace grpc
} // namespace ipc
} // namespace multiAgentExperience