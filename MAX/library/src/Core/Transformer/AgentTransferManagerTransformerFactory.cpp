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


#include "Core/Transformer/AgentTransferManagerTransformerFactory.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

AgentTransferManagerTransformerFactory::AgentTransferManagerTransformerFactory(
    std::shared_ptr<multiAgentExperience::library::agent::AgentTransferManager> agentTransferManager) :
        m_agentTransferManager{agentTransferManager} {
}

std::shared_ptr<multiAgentExperience::library::core::transformer::AgentTransferManagerTransformer>
AgentTransferManagerTransformerFactory::create(
    multiAgentExperience::actor::ActorId actorId,
    std::shared_ptr<AgentStoreInterface> agentStore) {
    return std::make_shared<AgentTransferManagerTransformer>(actorId, m_agentTransferManager, agentStore);
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience