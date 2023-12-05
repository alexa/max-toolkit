/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <MultiAgentExperience/IPC/gRPC/Transport/GrpcServer.h>

#include <utility>

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "MultiAgentExperience/IPC/gRPC/Connection/GrpcServerProxy.h"

namespace multiAgentExperience {
namespace ipc {
namespace grpc {
namespace transport {

static const std::string MODULE_TAG("GrpcServer");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

GrpcServer::GrpcServer(
    std::shared_ptr<connection::GrpcServerProxyInterface> grpcServerProxy,
    std::shared_ptr<multiAgentExperience::ipc::grpc::transport::GrpcReceiverInterface> grpcReceiver):
        m_grpcServerProxy{std::move(grpcServerProxy)},
        m_grpcReceiver{std::move(grpcReceiver)} {
}

void GrpcServer::shutdown() {
    LX(INFO, "Executing GrpcServer Shutdown...");
    m_grpcServerProxy->Shutdown();
}

bool GrpcServer::startServer() {
    LX(DEBUG3, "");

    /// Create and start the gRPC Server
    return m_grpcServerProxy->BuildAndStart();
}

} // namespace transport
} // namespace grpc
} // namespace ipc
} // namespace multiAgentExperience