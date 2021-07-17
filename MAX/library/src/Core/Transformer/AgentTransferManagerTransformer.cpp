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


#include "Core/Transformer/AgentTransferManagerTransformer.h"
#include "Utils/Logger/Logger.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

static const std::string MODULE_TAG("AgentTransferManagerTransformer");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

AgentTransferManagerTransformer::AgentTransferManagerTransformer(
    multiAgentExperience::actor::ActorId id,
    std::shared_ptr<multiAgentExperience::library::agent::AgentTransferManager> agentTransferManager,
    std::shared_ptr<AgentStoreInterface> agentStore) :
        m_id{id},
        m_agentTransferManager{agentTransferManager},
        m_agentStore{agentStore} {
}

void AgentTransferManagerTransformer::invokeAgent(const actor::ActorId& agentId) {
    auto agent = m_agentStore->getAgentById(agentId);
    if (agent) {
        m_agentTransferManager->invokeAgent(agent);
    } else {
        LX(ERROR, "Attempted to transfer to " + agentId.get() + " but it is not registered.");
    }
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
