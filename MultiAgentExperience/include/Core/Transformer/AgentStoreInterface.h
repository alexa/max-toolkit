/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/


#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_AGENTSTOREINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_AGENTSTOREINTERFACE_H_

#include <memory>

#include <MultiAgentExperience/Actor/ActorId.h>
#include <MultiAgentExperience/Agent/AgentRegistrationInterface.h>

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

/**
 * The AgentStore decouples the AgentManager from its storage use case.
 */
class AgentStoreInterface {
public:
    virtual ~AgentStoreInterface() = default;
    virtual std::shared_ptr<multiAgentExperience::agent::AgentRegistrationInterface> getAgentById(
        const multiAgentExperience::actor::ActorId& actorId) = 0;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_AGENTSTOREINTERFACE_H_
