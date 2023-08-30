/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_TRANSFORMERUTILS_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_TRANSFORMERUTILS_H_

#include <unordered_set>
#include <set>

#include <MultiAgentExperience/Activity/ActivityType.h>
#include <MultiAgentExperience/Activity/MixabilityType.h>
#include <MultiAgentExperience/Activity/MixingBehavior.h>
#include <MultiAgentExperience/Control/Control.h>

#include "Activity/ActivityType.h"
#include "Activity/FocusManager/MixabilityType.h"
#include "Activity/FocusManager/MixingBehavior.h"
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
            case multiAgentExperience::activity::ActivityType::NOTIFICATIONS:
                return multiAgentExperience::library::activity::ActivityType::NOTIFICATIONS;
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

    static std::string convertControlNameToString(
        const library::control::ControlName& name) {
        switch (name) {
            case library::control::ControlName::STOP:
                return "STOP";
            case library::control::ControlName::UNDEFINED:
                return "UNDEFINED";
            default:
                return "";
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

    static multiAgentExperience::activity::MixingBehavior convertInternalMixingBehaviorToPublicMixingBehavior(
        const multiAgentExperience::library::activity::MixingBehavior mixingBehavior) {
        switch (mixingBehavior) {
            case multiAgentExperience::library::activity::MixingBehavior::MUST_ATTENUATE:
                return multiAgentExperience::activity::MixingBehavior::MUST_ATTENUATE;
            case multiAgentExperience::library::activity::MixingBehavior::MUST_PAUSE:
                return multiAgentExperience::activity::MixingBehavior::MUST_PAUSE;
            case multiAgentExperience::library::activity::MixingBehavior::UNRESTRICTED:
                return multiAgentExperience::activity::MixingBehavior::UNRESTRICTED;
            default:
                return multiAgentExperience::activity::MixingBehavior::UNRESTRICTED;
        }
    }

    static multiAgentExperience::library::activity::MixabilityType convertPublicMixabilityTypeToInternalMixabilityType(
        const multiAgentExperience::activity::MixabilityType type) {
        switch (type) {
            case multiAgentExperience::activity::MixabilityType::MIXABLE_RESTRICTED:
                return multiAgentExperience::library::activity::MixabilityType::MIXABLE_RESTRICTED;
            case multiAgentExperience::activity::MixabilityType::NONMIXABLE:
                return multiAgentExperience::library::activity::MixabilityType::NONMIXABLE;
            case multiAgentExperience::activity::MixabilityType::MIXABLE_UNRESTRICTED:
                return multiAgentExperience::library::activity::MixabilityType::MIXABLE_UNRESTRICTED;
            default:
                return multiAgentExperience::library::activity::MixabilityType::MIXABLE_RESTRICTED;
        }
    }
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_TRANSFORMERUTILS_H_
