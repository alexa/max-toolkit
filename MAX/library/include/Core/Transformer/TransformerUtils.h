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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_TRANSFORERUTILS_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_TRANSFORERUTILS_H_

#include <unordered_set>
#include <set>

#include <MultiAgentExperience/Activity/ActivityType.h>
#include <MultiAgentExperience/Control/Control.h>

#include "Activity/ActivityType.h"
#include "Control/Control.h"
#include "Control/ControlName.h"
#include "Dialog/DialogState.h"
#include "DialogState.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

class TransformerUtils {
public:
    static library::activity::ActivityType convertPublicActivityTypeToInternalActivityType(
        const multiAgentExperience::activity::ActivityType& type) {
        switch (type) {
            case multiAgentExperience::activity::ActivityType::COMMUNICATION:
                return multiAgentExperience::library::activity::ActivityType::COMMUNICATIONS;
            case multiAgentExperience::activity::ActivityType::ALERTS:
                return multiAgentExperience::library::activity::ActivityType::ALERTS;
            case multiAgentExperience::activity::ActivityType::CONTENT:
            default:
                return multiAgentExperience::library::activity::ActivityType::CONTENT;
        }
    }

    static library::control::ControlName convertControlTypeToControlName(
        const multiAgentExperience::control::ControlType& type) {
        switch (type) {
            case multiAgentExperience::control::ControlType::STOP:
            default:
                return library::control::ControlName::STOP;
        }
    }

    static multiAgentExperience::control::ControlType convertControlNameToControlType(
        const library::control::ControlName& type) {
        switch (type) {
            case library::control::ControlName::STOP:
                return multiAgentExperience::control::ControlType::STOP;
            case library::control::ControlName::UNDEFINED:
            default:
                return multiAgentExperience::control::ControlType::STOP;
        }
    }

    static std::set<multiAgentExperience::control::ControlType> convertSetOfControlNamesToControlTypes(
        std::unordered_set<library::control::ControlName> controlNames) {
        std::set<multiAgentExperience::control::ControlType> controlTypes;
        for (auto& controlName : controlNames) {
            controlTypes.insert(convertControlNameToControlType(controlName));
        }
        return controlTypes;
    }

    static library::core::transformer::DialogState convertDialogStatesToDialogState(
        const library::dialog::DialogState& dialogState) {
        return library::core::transformer::DialogState::create(dialogState);
    }
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_TRANSFORERUTILS_H_
