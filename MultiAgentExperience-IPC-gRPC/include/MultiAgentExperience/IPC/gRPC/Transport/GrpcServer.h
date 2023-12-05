/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_GRPC_GRPCSERVER_H
#define MULTIAGENTEXPERIENCE_IPC_GRPC_GRPCSERVER_H

#include "GrpcServerInterface.h"

#include <maxrpc.grpc.pb.h>
#include <MultiAgentExperience/Thread/Executor/Threading/Executor.h>

#include "MultiAgentExperience/IPC/gRPC/Connection/GrpcServerProxy.h"
#include "MultiAgentExperience/IPC/gRPC/Transport/GrpcReceiverInterface.h"

namespace multiAgentExperience {
namespace ipc {
namespace grpc {
namespace transport {

/**
 * The GrpcServer implements the Grpc Service which is generated from the proto file. It needs to implement the
 * methods in the proto file. It also receives the message and uses the GrpcReceiverInterface to provide it to the
 * messaging layer in MultiAgentExperience-IPC.
 */
class GrpcServer: public GrpcServerInterface {
public:
    /**
     * Constructor.
     *
     * @param grpcServerProxy A proxy to the ::grpc::Server object
     * @param grpcReceiver The GrpcReceiverInterface object which contains the logic to process gRPC requests.
     */
    GrpcServer(
        std::shared_ptr<connection::GrpcServerProxyInterface> grpcServerProxy,
        std::shared_ptr<multiAgentExperience::ipc::grpc::transport::GrpcReceiverInterface> grpcReceiver);

    /**
     * Shuts down the gRPC server using the grpcServerProxy
     */
    void shutdown() override;

    /**
     * Builds and starts the gRPC server using the grpcServerProxy
     *
     * @return true if the server was successfully started. False, otherwise.
     */
    bool startServer() override;

private:
    std::shared_ptr<connection::GrpcServerProxyInterface> m_grpcServerProxy;
    std::shared_ptr<multiAgentExperience::ipc::grpc::transport::GrpcReceiverInterface> m_grpcReceiver;
};

} // namespace transport
} // namespace grpc
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_GRPC_GRPCSERVER_H
