/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/


#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_AGENTSTORE_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_AGENTSTORE_H_

#include <memory>

#include <MultiAgentExperience/Actor/ActorId.h>
#include <MultiAgentExperience/Agent/AgentRegistrationInterface.h>

#include "AgentStoreInterface.h"
#include "Application/AgentManager.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

/**
 * The AgentStore decouples the AgentManager from its storage use case.
 */
class AgentStore : public AgentStoreInterface {
public:
    AgentStore(std::shared_ptr<multiAgentExperience::library::application::AgentManager> agentManager);

    std::shared_ptr<multiAgentExperience::agent::AgentRegistrationInterface> getAgentById(
        const multiAgentExperience::actor::ActorId& actorId) override;

private:
    std::shared_ptr<multiAgentExperience::library::application::AgentManager> m_agentManager;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_AGENTSTORE_H_
