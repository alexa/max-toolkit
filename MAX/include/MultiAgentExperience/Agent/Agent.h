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

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_AGENT_AGENT_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_AGENT_AGENT_H_

#include <memory>
#include <set>
#include <string>

#include "MultiAgentExperience/Activity/ActivityManagerInterface.h"
#include "MultiAgentExperience/Agent/AgentTransferManagerInterface.h"
#include "MultiAgentExperience/Dialog/DialogManagerInterface.h"
#include "MultiAgentExperience/Actor/ActorId.h"

namespace multiAgentExperience {
namespace agent {

/**
 * The Agent is an actor which handles input from the user to participate in the multi-agent experience.
 *
 * The Agent is not initialized until it is registered. Be aware the MAX ActivityManagerInterface,
 * DialogManagerInterface, and AgentTransferManagerInterface are not usable until onInitialized is called.
 */
class Agent : public std::enable_shared_from_this<Agent> {
public:
    /**
     * Constructs an Agent.
     * @param id The unique actor identifier for the agent.
     * @param wakeword The wakeword for the agent. The value should be empty string if there is no wakeword.
     */
    Agent(const actor::ActorId& id, const std::string& wakeword);

    /**
     * Destructor
     */
    virtual ~Agent() = default;

    /**
     * Provides access to the core MAX APIs required by the Agent when they are available.
     *
     * @param activityManager The manager for scheduling Activities
     * @param dialogManager The manager for scheduling Dialogs
     * @param agentTransferManager The manager for transferring interaction to other Agents.
     */
    void initializeCoreInterfaces(
        std::shared_ptr<multiAgentExperience::activity::ActivityManagerInterface> activityManager,
        std::shared_ptr<multiAgentExperience::dialog::DialogManagerInterface> dialogManager,
        std::shared_ptr<AgentTransferManagerInterface> agentTransferManager);

    /** @brief Get the ActorId of the agent.
     *
     * @return the ActorId of the agent
     */
    actor::ActorId getId();

    /** @brief Get the customer facing name of the agent.
     *
     * @return the Name of the agent
     */
    virtual std::string getName() {
        return m_id.get();
    };

    /**
     * Returns the wakeword for the agent, or empty string if it does not support one.
     * @return The wakeword for the agent, or empty string if it does not support one.
     */
    std::string getWakeword();

    /**
     * Called when the wakeword for this agent is detected.
     */
    void onWakeWordDetected();

    /**
     * Called when a tap for this agent is received.
     */
    void onTapDetected();

    /**
     * Called when another agent transfers interaction to this agent.
     */
    void onAgentTransfer();

protected:
    /**
     * Handles wakeword detection invocations.
     */
    virtual void handleOnWakeWordDetected() = 0;

    /**
     * Handles tap detection invocations.
     */
    virtual void handleOnTapDetected() = 0;

    /**
     * Handles transfers of interaction from another agent.
     */
    virtual void handleOnAgentTransfer() = 0;

    /**
     * Called when the Agent has been initialized with all MAX APIs available for use.
     */
    virtual void onInitialized() = 0;

    /// The manager for scheduling Activities.
    std::shared_ptr<multiAgentExperience::activity::ActivityManagerInterface> m_activityManager;

    /// The manager for scheduling Dialogs.
    std::shared_ptr<multiAgentExperience::dialog::DialogManagerInterface> m_dialogManager;

    /// The manager for transferring to other Agents.
    std::shared_ptr<AgentTransferManagerInterface> m_agentTransferManager;

private:
    /// The unique actor identifier for the agent.
    actor::ActorId m_id;
    /// The wakeword for the agent.
    std::string m_wakeword;
};

}  // namespace agent
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_AGENT_AGENT_H_
