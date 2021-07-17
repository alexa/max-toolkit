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

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_AGENT_AGENTMANAGERINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_AGENT_AGENTMANAGERINTERFACE_H_

#include "MultiAgentExperience/Agent/Agent.h"

#include <memory>

namespace multiAgentExperience {
namespace agent {

class AgentManagerInterface {
public:
    /**
     * Destructor.
     */
    virtual ~AgentManagerInterface() = default;

    /**
     * @brief Register an agent with the manager
     *
     * @param agent The agent to register
     * @return true On success
     * @return false On failure
     */
    virtual bool registerAgent(std::shared_ptr<multiAgentExperience::agent::Agent> agent) = 0;

    /**
     * @brief De-register an agent
     *
     * @param agent
     */
    virtual void deregisterAgent(std::shared_ptr<multiAgentExperience::agent::Agent> agent) = 0;
};

}  // namespace agent
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_APPLICATION_AGENTMANAGERINTERFACE_H_
