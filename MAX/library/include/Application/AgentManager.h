/*
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_APPLICATION_AGENTMANAGER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_APPLICATION_AGENTMANAGER_H_

#include <set>
#include <memory>
#include <string>

#include <MultiAgentExperience/Agent/Agent.h>
#include <MultiAgentExperience/Agent/AgentManagerInterface.h>
#include <MultiAgentExperience/Application/WakeWordObserverInterface.h>

#include "Core/Transformer/AgentTransferManagerTransformerFactory.h"
#include "Core/Transformer/ActivityManagerTransformerFactory.h"
#include "Core/Transformer/DialogManagerTransformerFactory.h"

namespace multiAgentExperience {
namespace library {
namespace application {

class AgentManager
        : public multiAgentExperience::agent::AgentManagerInterface
        , public multiAgentExperience::application::WakeWordObserverInterface
        , public std::enable_shared_from_this<AgentManager> {
public:
    /**
     * Create an instance.
     *
     * @param core The core VII object
     * @return std::shared_ptr<AgentManager> An instance of agent manager.
     */
    static std::shared_ptr<AgentManager> create(
        std::shared_ptr<multiAgentExperience::library::core::transformer::AgentTransferManagerTransformerFactory>
            agentTransferManagerTransformerFactory,
        std::shared_ptr<multiAgentExperience::library::core::transformer::ActivityManagerTransformerFactory>
            activityManagerTransformerFactory,
        std::shared_ptr<multiAgentExperience::library::core::transformer::DialogManagerTransformerFactory>
            dialogManagerTransformerFactory);

    /// @name AgentManagerInterface method overrides.
    /// @{
    bool registerAgent(std::shared_ptr<multiAgentExperience::agent::Agent> agent) override;
    void deregisterAgent(std::shared_ptr<multiAgentExperience::agent::Agent> agent) override;
    /// @}

    /// @name WakeWordObserverInterface method overrides.
    /// @{
    void onWakeWordDetected(const std::string& wakeWord) override;
    /// @}

    /**
     * Get the Agent by its id
     *
     * @param The id of the agent
     * @return std::shared_ptr<agent::Agent> The matching agent or nullptr
     */
    std::shared_ptr<multiAgentExperience::agent::Agent> getAgentById(const multiAgentExperience::actor::ActorId& id);

private:
    AgentManager(
        std::shared_ptr<multiAgentExperience::library::core::transformer::AgentTransferManagerTransformerFactory>
            agentTransferManagerTransformerFactory,
        std::shared_ptr<multiAgentExperience::library::core::transformer::ActivityManagerTransformerFactory>
            activityManagerTransformerFactory,
        std::shared_ptr<multiAgentExperience::library::core::transformer::DialogManagerTransformerFactory>
            dialogManagerTransformerFactory);

    bool wakewordExists(const std::string& wakeword);

    std::set<std::shared_ptr<multiAgentExperience::agent::Agent>> m_agents;
    std::shared_ptr<multiAgentExperience::library::core::transformer::AgentTransferManagerTransformerFactory>
        m_agentTransferManagerTransformerFactory;
    std::shared_ptr<multiAgentExperience::library::core::transformer::ActivityManagerTransformerFactory>
        m_activityManagerTransformerFactory;
    std::shared_ptr<multiAgentExperience::library::core::transformer::DialogManagerTransformerFactory>
        m_dialogManagerTransformerFactory;
};

}  // namespace application
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_APPLICATION_AGENTMANAGER_H_
