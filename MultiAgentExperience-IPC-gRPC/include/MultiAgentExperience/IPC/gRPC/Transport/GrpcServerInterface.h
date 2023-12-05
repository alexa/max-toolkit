/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_GRPC_GRPCSERVERINTERFACE_H
#define MULTIAGENTEXPERIENCE_IPC_GRPC_GRPCSERVERINTERFACE_H

#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

namespace multiAgentExperience {
namespace ipc {
namespace grpc {
namespace transport {
class GrpcServerInterface {
public:
    virtual ~GrpcServerInterface() = default;
    virtual void shutdown() = 0;
    virtual bool startServer() = 0;
};
} // namespace transport
} // namespace grpc
} // namespace ipc
} // namespace multiAgentExperience
#endif //MULTIAGENTEXPERIENCE_IPC_GRPC_GRPCSERVERINTERFACE_H
