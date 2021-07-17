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


#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_AGENTTRANSFERMANAGERTRANSFORMER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_AGENTTRANSFERMANAGERTRANSFORMER_H_

#include <memory>

#include <MultiAgentExperience/Agent/AgentTransferManagerInterface.h>
#include <MultiAgentExperience/Actor/ActorId.h>

#include "Agent/AgentTransferManager.h"
#include "AgentStoreInterface.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

class AgentTransferManagerTransformer : public multiAgentExperience::agent::AgentTransferManagerInterface {
public:
    AgentTransferManagerTransformer(
        const multiAgentExperience::actor::ActorId id,
        std::shared_ptr<multiAgentExperience::library::agent::AgentTransferManager> agentTransferManager,
        std::shared_ptr<AgentStoreInterface> agentStore);

    void invokeAgent(const actor::ActorId& agentId) override;

private:
    const multiAgentExperience::actor::ActorId m_id;
    std::shared_ptr<multiAgentExperience::library::agent::AgentTransferManager> m_agentTransferManager;
    std::shared_ptr<AgentStoreInterface> m_agentStore;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_AGENTTRANSFERMANAGERTRANSFORMER_H_
