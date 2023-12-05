/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#include "MultiAgentExperience/IPC/gRPC/Connection/GrpcServerProxy.h"

#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server_builder.h>
#include <MultiAgentExperience/Utils/Logger/Logger.h>

namespace multiAgentExperience {
namespace ipc {
namespace grpc {
namespace connection {

static const std::string MODULE_TAG("GrpcServerProxy");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

GrpcServerProxy::GrpcServerProxy(
    const std::string& serverUri,
    const std::shared_ptr<multiAgentExperience::ipc::grpc::transport::GrpcReceiverInterface>& grpcReceiver):
        m_serverUri{serverUri},
        m_grpcReceiver{grpcReceiver} {
}

bool GrpcServerProxy::BuildAndStart() {
    LX(DEBUG3, "");

    // Start the gRPC server with the given details
    ::grpc::ServerBuilder serverBuilder;
    m_server = serverBuilder
        .AddListeningPort(m_serverUri, ::grpc::InsecureServerCredentials())
        .RegisterService(this)
        .BuildAndStart();

    if (m_server) {
        LX(INFO, "gRPC server started on: " + m_serverUri);
        return true;
    } else {
        // ServerBuilder::BuildAndStart returns a nullptr if an error occurs when building or starting a gRPC server
        LX(ERROR, "gRPC server was not created/started due to an error");
        return false;
    }
}

void GrpcServerProxy::Shutdown() {
    LX(DEBUG3, "");

    if (m_server) {
        m_server->Shutdown();
    } else {
        LX(WARN, "Server was not created");
    }
}

void GrpcServerProxy::Wait() {
    LX(DEBUG3, "");

    if (m_server) {
        m_server->Wait();
    } else {
        LX(WARN, "Server was not created");
    }
}

::grpc::Status GrpcServerProxy::handle(
    ::grpc::ServerContext* context,
    const ::MultiAgentExperience::Rpc::Message* request,
    ::MultiAgentExperience::Rpc::VoidPayload* response) {
    LX(DEBUG3, "");

    m_grpcReceiver->receiveAndHandle(request);
    return ::grpc::Status::OK;
}

} // namespace connection
} // namespace grpc
} // namespace ipc
} // namespace multiAgentExperience