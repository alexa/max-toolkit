/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_APPLICATION_AGENTMANAGER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_APPLICATION_AGENTMANAGER_H_

#include <set>
#include <memory>
#include <string>

#include <MultiAgentExperience/Agent/AgentRegistrationInterface.h>
#include <MultiAgentExperience/Agent/AgentManagerInterface.h>

#include "Application/MAXLifecycle.h"
#include "Common/OnCompletionCallback.h"
#include "Core/Transformer/ActivityManagerTransformerFactory.h"
#include "Core/Transformer/DialogManagerTransformerFactory.h"
#include "Core/Transformer/StaticExperienceManagerTransformerFactory.h"

namespace multiAgentExperience {
namespace library {
namespace application {

class AgentManager: public multiAgentExperience::agent::AgentManagerInterface {
public:
    /**
     * Create an instance.
     *
     * @param core The core VII object
     * @return std::shared_ptr<AgentManager> An instance of agent manager.
     */
    static std::shared_ptr<AgentManager> create(
        std::shared_ptr<multiAgentExperience::library::core::transformer::ActivityManagerTransformerFactory>
            activityManagerTransformerFactory,
        std::shared_ptr<multiAgentExperience::library::core::transformer::DialogManagerTransformerFactory>
            dialogManagerTransformerFactory,
        std::shared_ptr<multiAgentExperience::library::core::transformer ::StaticExperienceManagerTransformerFactory>
            staticExperienceManagerTransformerFactory,
        std::shared_ptr<MAXLifecycle> maxLifecycle);

    /// @name AgentManagerInterface method overrides.
    /// @{
    bool registerAgents(
        std::set<std::shared_ptr<multiAgentExperience::agent::AgentRegistrationInterface>> agentRegistrations) override;
    bool registerAgent(
        std::shared_ptr<multiAgentExperience::agent::AgentRegistrationInterface> agentRegistration) override;
    void deregisterAgent(std::shared_ptr<multiAgentExperience::agent::AgentRegistrationInterface> agentRegistration) override;
    /// @}

private:
    AgentManager(
        std::shared_ptr<multiAgentExperience::library::core::transformer::ActivityManagerTransformerFactory>
            activityManagerTransformerFactory,
        std::shared_ptr<multiAgentExperience::library::core::transformer::DialogManagerTransformerFactory>
            dialogManagerTransformerFactory,
        std::shared_ptr<multiAgentExperience::library::core::transformer ::StaticExperienceManagerTransformerFactory>
            staticExperienceManagerTransformerFactory,
        std::shared_ptr<MAXLifecycle> maxLifecycle,
        std::shared_ptr<multiAgentExperience::library::utils::threading::Executor> executor =
            std::make_shared<multiAgentExperience::library::utils::threading::Executor>());

    /**
     * Executes the AgentRegistrationInterface::onReady() for all agents, and returns the OnCompletionCallback
     * in order to wait for the agent to trigger it. This is an asynchronous call, since we are invoking agent code
     * while holding a lock.
     */
    std::shared_ptr<common::OnCompletionCallback> executeOnReady(
        std::shared_ptr<multiAgentExperience::agent::AgentRegistrationInterface> agentRegistration);

    std::shared_ptr<multiAgentExperience::library::core::transformer::ActivityManagerTransformerFactory>
        m_activityManagerTransformerFactory;
    std::shared_ptr<multiAgentExperience::library::core::transformer::DialogManagerTransformerFactory>
        m_dialogManagerTransformerFactory;
    std::shared_ptr<multiAgentExperience::library::core::transformer ::StaticExperienceManagerTransformerFactory>
        m_staticExperienceManagerTransformerFactory;
    std::shared_ptr<MAXLifecycle> m_maxLifecycle;
    std::shared_ptr<multiAgentExperience::library::utils::threading::Executor> m_executor;

    std::set<std::shared_ptr<multiAgentExperience::agent::AgentRegistrationInterface>> m_agentRegistrations;

    /// Mutex to serialize access to m_agentRegistrations and other shared members
    std::mutex m_mutex;
};

}  // namespace application
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_APPLICATION_AGENTMANAGER_H_
