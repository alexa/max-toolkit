/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_AGENT_REGISTRATION_ADAPTER_H
#define MULTIAGENTEXPERIENCE_IPC_AGENT_REGISTRATION_ADAPTER_H

#include <MultiAgentExperience/Agent/AgentManagerInterface.h>
#include <MultiAgentExperience/IPC/Transport/IpcConnectionListenerInterface.h>

#include "MultiAgentExperience/IPC/gRPC/Connection/GrpcConnectionConfiguration.h"
#include "MultiAgentExperience/IPC/gRPC/Connection/GrpcConnectionBuilder.h"

namespace multiAgentExperience {
namespace ipc {
namespace grpc {
namespace connection {

/// This is used by MAX to connect to the Agent process. When connection disruption occurs, this class automatically
/// re-registers the Agent to MAX.
class AgentRegistrationAdapter
    : public agent::AgentRegistrationInterface
    , public multiAgentExperience::ipc::transport::IpcConnectionListenerInterface
    , public std::enable_shared_from_this<AgentRegistrationAdapter> {

public:
    AgentRegistrationAdapter(
            std::shared_ptr<agent::AgentManagerInterface> agentManagerInterface,
            GrpcConnectionConfiguration grpcConnectionConfiguration,
            std::shared_ptr<GrpcConnectionBuilderInterface> connectionBuilder = std::make_shared<GrpcConnectionBuilder>(),
            std::shared_ptr<multiAgentExperience::thread::executor::threading::Executor> executor = std::make_shared<multiAgentExperience::thread::executor::threading::Executor>());

    /// @name AgentRegistrationInterface method overrides.
    /// @{
    void onReady(
        std::shared_ptr<multiAgentExperience::common::OnCompletionCallbackInterface> onCompletionCallback,
        std::shared_ptr<multiAgentExperience::activity::ActivityManagerInterface> activityManager,
        std::shared_ptr<multiAgentExperience::dialog::DialogManagerInterface> dialogManager,
        std::shared_ptr<multiAgentExperience::experience::StaticExperienceManagerInterface> staticExperienceManager) override;
    actor::ActorId getId() override;
    std::string getName() override;
    /// @}

    /// @name IpcConnectionListenerInterface method overrides.
    /// @{
    void onConnectionDisruption() override;
    /// @}

    bool connect();
    void disconnect();

private:
    /// Mutex to serialize access to m_isConnectionDisrupted.
    std::mutex m_mutex;
    std::shared_ptr<agent::AgentManagerInterface> m_agentManager;
    std::shared_ptr<GrpcConnectionInterface> m_grpcConnection;
    std::shared_ptr<agent::AgentRegistrationInterface> m_agentRegistration;
    GrpcConnectionConfiguration m_grpcConnectionConfiguration;
    std::shared_ptr<GrpcConnectionBuilderInterface> m_grpcConnectionBuilder;
    std::shared_ptr<multiAgentExperience::thread::executor::threading::Executor> m_executor;

    /// To store the OnCompletionCallback received in onReady
    std::shared_ptr<multiAgentExperience::common::OnCompletionCallbackInterface> m_onReadyCompletionCallback;
};

} // namespace connection
} // namespace grpc
} // namespace ipc
} // namespace multiAgentExperience

#endif // MULTIAGENTEXPERIENCE_IPC_AGENT_REGISTRATION_ADAPTER_H