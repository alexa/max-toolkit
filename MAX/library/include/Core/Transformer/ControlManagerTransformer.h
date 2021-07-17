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


#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_CONTROLMANAGERTRANSFORMER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_CONTROLMANAGERTRANSFORMER_H_

#include "MultiAgentExperience/Control/ControlManagerInterface.h"
#include "MultiAgentExperience/Actor/ActorId.h"

#include "Control/ControlStore.h"

#include <memory>

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

class ControlManagerTransformer : public multiAgentExperience::control::ControlManagerInterface {
public:
    ControlManagerTransformer(
        const multiAgentExperience::actor::ActorId id,
        std::shared_ptr<multiAgentExperience::library::control::ControlStore> controlStore);

    void addObserver(std::weak_ptr<multiAgentExperience::control::ControlObserverInterface> observer) override;

    void clearObservers() override;

private:
    const multiAgentExperience::actor::ActorId m_id;
    std::shared_ptr<multiAgentExperience::library::control::ControlStore> m_controlStore;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_CONTROLMANAGERTRANSFORMER_H_
