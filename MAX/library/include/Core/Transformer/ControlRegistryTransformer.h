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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_CONTROLREGISTRYTRANSFORMER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_CONTROLREGISTRYTRANSFORMER_H_

#include <memory>
#include <set>

#include <MultiAgentExperience/Control/ControlRegistryInterface.h>

#include "Control/ControlRegistry.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

class ControlRegistryTransformer : public multiAgentExperience::control::ControlRegistryInterface {
public:
    ControlRegistryTransformer(std::shared_ptr<control::ControlRegistry> controlRegistry);

    /// @name ControlRegistryInterface method overrides.
    /// @{
    void update(std::set<std::shared_ptr<multiAgentExperience::control::Control>> controls) override;
    /// @}

private:
    std::shared_ptr<control::ControlRegistry> m_controlRegistry;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_CONTROLREGISTRYTRANSFORMER_H_
