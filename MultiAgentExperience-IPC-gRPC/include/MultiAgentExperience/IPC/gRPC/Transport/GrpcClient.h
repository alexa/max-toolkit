/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_GRPC_GRPCCLIENT_H
#define MULTIAGENTEXPERIENCE_IPC_GRPC_GRPCCLIENT_H

#include "MultiAgentExperience/IPC/gRPC/Transport/GrpcClientInterface.h"
#include "MultiAgentExperience/IPC/gRPC/Connection/GrpcChannelProxy.h"

#include <mutex>
#include <condition_variable>

#include <MultiAgentExperience/IPC/Transport/IpcConnectionListenerInterface.h>
#include <MultiAgentExperience/Thread/Executor/Threading/Executor.h>

namespace multiAgentExperience {
namespace ipc {
namespace grpc {
namespace transport {

/**
 * The GrpcClient uses the Grpc Stub to send the message
 */
class GrpcClient: public GrpcClientInterface {
public:
    explicit GrpcClient(
        std::shared_ptr<connection::GrpcChannelProxyInterface> grpcChannelProxy,
        std::set<std::shared_ptr<multiAgentExperience::ipc::transport::IpcConnectionListenerInterface>> connectionListeners,
        std::shared_ptr<thread::executor::threading::Executor> connectionStatusExecutor =
            std::make_shared<thread::executor::threading::Executor>());

    void send(MultiAgentExperience::Rpc::Message message) override;
    bool isConnected() override;

    /// Waits until the gRPC channel has connected to the gRPC server in the other process
    bool waitForConnectionEstablished(int timeoutInMilliSeconds) override;

    /// Sets up connection monitoring by frequently polling the gRPC channel state.
    bool setupConnectionMonitoring() override;

private:
    /**
     * Continuously checks the connection state of the gRPC channel. If the connection is in a bad state, then it
     * notifies listeners of the connection disruption, so that they may take actions like restarting the server/client.
     *
     * @note This needs to be executed in a separate thread
     */
    void monitorConnection();

    void notifyConnectionListeners();

    std::shared_ptr<connection::GrpcChannelProxyInterface> m_grpcChannelProxy;
    std::set<std::shared_ptr<multiAgentExperience::ipc::transport::IpcConnectionListenerInterface>> m_connectionListeners;
    std::shared_ptr<thread::executor::threading::Executor> m_connectionStatusExecutor;
};

} // namespace transport
} // namespace grpc
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_GRPC_GRPCCLIENT_H
