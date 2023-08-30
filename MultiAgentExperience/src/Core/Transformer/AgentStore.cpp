/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/


#include "Core/Transformer/AgentStore.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

AgentStore::AgentStore(std::shared_ptr<multiAgentExperience::library::application::AgentManager> agentManager) :
        m_agentManager{agentManager} {
}

std::shared_ptr<multiAgentExperience::agent::AgentRegistrationInterface> AgentStore::getAgentById(const actor::ActorId& actorId) {
    return m_agentManager->getAgentById(actorId);
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
