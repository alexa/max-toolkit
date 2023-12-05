/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_GRPC_MAXCONNECTIONADAPTER_H
#define MULTIAGENTEXPERIENCE_IPC_GRPC_MAXCONNECTIONADAPTER_H

#include <MultiAgentExperience/Agent/AgentManagerInterface.h>
#include <MultiAgentExperience/IPC/Transport/IpcConnectionListenerInterface.h>
#include <MultiAgentExperience/IPC/Transport/MAXServiceAvailabilityObserverInterface.h>

#include "GrpcConnectionBuilder.h"

namespace multiAgentExperience {
namespace ipc {
namespace grpc {
namespace connection {

/// The Agent will use this class to connect to the MAX process
class MaxConnectionAdapter
    : public multiAgentExperience::ipc::transport::IpcConnectionListenerInterface
    , public std::enable_shared_from_this<MaxConnectionAdapter> {

public:
    MaxConnectionAdapter(
            const std::shared_ptr<agent::AgentRegistrationInterface>& agentRegistration,
            const GrpcConnectionConfiguration& grpcConnectionConfiguration,
            const std::shared_ptr<GrpcConnectionBuilderInterface>& grpcConnectionBuilder = std::make_shared<GrpcConnectionBuilder>(),
            std::shared_ptr<thread::executor::threading::Executor> executor = std::make_shared<thread::executor::threading::Executor>());

    void onConnectionDisruption() override;
    bool connect();
    void disconnect();

    /**
     * To receive notifications by the IPC layer if the MAX service is unavailable.
     *
     * The MaxConnectionAdapter has the ability to notify the agent when the MAX service is down. The agent that uses
     * the MaxConnectionAdapter can also optionally register an observer using this method. This is so that the agent
     * can take remediation measures when the MAX service is unavailable, like resetting activities/dialogs etc.
     */
    void setServiceAvailabilityObserver(
        std::shared_ptr<multiAgentExperience::ipc::transport::MAXServiceAvailabilityObserverInterface> serviceAvailabilityObserver);

private:
    /// Mutex to serialize access to m_isConnectionDisrupted.
    std::mutex m_mutex;
    std::shared_ptr<GrpcConnectionInterface> m_grpcConnection;
    std::shared_ptr<agent::AgentRegistrationInterface> m_agentRegistration;
    GrpcConnectionConfiguration m_grpcConnectionConfiguration;
    std::shared_ptr<GrpcConnectionBuilderInterface> m_grpcConnectionBuilder;
    std::shared_ptr<multiAgentExperience::ipc::transport::MAXServiceAvailabilityObserverInterface> m_serviceAvailabilityObserver;
    std::shared_ptr<thread::executor::threading::Executor> m_executor;
};

} // namespace connection
} // namespace grpc
} // namespace ipc
} // namespace multiAgentExperience

#endif // MULTIAGENTEXPERIENCE_IPC_GRPC_MAXCONNECTIONADAPTER_H