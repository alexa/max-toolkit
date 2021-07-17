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


#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_AGENTSTOREINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_AGENTSTOREINTERFACE_H_

#include <memory>

#include <MultiAgentExperience/Actor/ActorId.h>
#include <MultiAgentExperience/Agent/Agent.h>

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
    virtual std::shared_ptr<multiAgentExperience::agent::Agent> getAgentById(
        const multiAgentExperience::actor::ActorId& actorId) = 0;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_AGENTSTOREINTERFACE_H_
