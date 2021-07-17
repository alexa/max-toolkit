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

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_AGENT_AGENTTRANSFERMANAGERINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_AGENT_AGENTTRANSFERMANAGERINTERFACE_H_

#include <MultiAgentExperience/Actor/ActorId.h>

namespace multiAgentExperience {
namespace agent {

/**
 * The AgentTransferManagerInterface is used when transferring which Agent is interacting with the user.
 */
class AgentTransferManagerInterface {
public:
    virtual ~AgentTransferManagerInterface() = default;

    /**
     * Transfers interaction control to the other agent by invoking a new dialog with the agent.
     * @param agentId The id of the agent to invoke.
     */
    virtual void invokeAgent(const actor::ActorId& agentId) = 0;
};

}  // namespace agent
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_AGENT_AGENTTRANSFERMANAGER_H_
