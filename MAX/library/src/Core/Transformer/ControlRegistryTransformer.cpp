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

#include <unordered_set>

#include "Control/Control.h"
#include "Control/ControlRegistry.h"
#include "Core/Transformer/ControlRegistryTransformer.h"
#include "Core/Transformer/TransformerUtils.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

static bool isValidControlType(const multiAgentExperience::control::ControlType type) {
    return type == multiAgentExperience::control::ControlType::STOP;
}

ControlRegistryTransformer::ControlRegistryTransformer(std::shared_ptr<control::ControlRegistry> controlRegistry) :
        m_controlRegistry{controlRegistry} {
}

void ControlRegistryTransformer::update(std::set<std::shared_ptr<multiAgentExperience::control::Control>> controls) {
    std::unordered_set<std::shared_ptr<library::control::Control>> transformedControls;

    for (const auto& externalControl : controls) {
        if (isValidControlType(externalControl->type)) {
            auto convertedControlType = TransformerUtils::convertControlTypeToControlName(externalControl->type);
            auto control = library::control::Control::create(
                convertedControlType, [externalControl]() { externalControl->task(); });
            transformedControls.insert(control);
        }
    }

    m_controlRegistry->update(transformedControls);
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
