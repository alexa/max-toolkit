/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_AGENT_AGENTMANAGERINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_AGENT_AGENTMANAGERINTERFACE_H_

#include "MultiAgentExperience/Agent/AgentRegistrationInterface.h"

#include <memory>
#include <set>

namespace multiAgentExperience {
namespace agent {

class AgentManagerInterface {
public:
    /**
     * Destructor.
     */
    virtual ~AgentManagerInterface() = default;

    /**
     * Registers all agents with the manager. All agents are required to be registered at the same time.
     *
     * @param agentRegistrations The set of agents to be registered
     * @return true On success
     * @return false On failure
     */
    virtual bool registerAgents(
        std::set<std::shared_ptr<multiAgentExperience::agent::AgentRegistrationInterface>> agentRegistrations) = 0;

    /**
     * Registers an agent with the manager, if it is not registered already.
     *
     * @param agentRegistration The agent to be registered
     * @return true On success
     * @return false On failure
     */
    virtual bool registerAgent(
        std::shared_ptr<multiAgentExperience::agent::AgentRegistrationInterface> agentRegistration) = 0;

    /**
     * @brief De-register an agent
     *
     * @param agent
     */
    virtual void deregisterAgent(std::shared_ptr<multiAgentExperience::agent::AgentRegistrationInterface> agentRegistration) = 0;
};

}  // namespace agent
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_APPLICATION_AGENTMANAGERINTERFACE_H_
