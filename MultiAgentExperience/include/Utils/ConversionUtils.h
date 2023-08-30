/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_UTILS_CONVERSIONUTILS_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_UTILS_CONVERSIONUTILS_H_

#include <functional>
#include <string>

#include <MultiAgentExperience/Activity/ActivityFocus.h>
#include <MultiAgentExperience/Activity/ActivityType.h>
#include <MultiAgentExperience/Activity/MixabilityType.h>
#include <MultiAgentExperience/Activity/MixingBehavior.h>
#include <MultiAgentExperience/Actor/ActorId.h>
#include <MultiAgentExperience/Application/MAXPolicies.h>
#include <MultiAgentExperience/Control/Control.h>
#include <MultiAgentExperience/Dialog/DialogBargeInPriority.h>
#include <MultiAgentExperience/Experience/ExperienceId.h>

#include "Activity/ActivityType.h"
#include "Activity/FocusManager/MixabilityType.h"
#include "Activity/FocusManager/MixingBehavior.h"

namespace multiAgentExperience {
namespace library {
namespace utils {

inline std::string toString(multiAgentExperience::activity::MixabilityType value) {
    switch (value) {
        case multiAgentExperience::activity::MixabilityType::MIXABLE_RESTRICTED:
            return "MIXABLE_RESTRICTED";
        case multiAgentExperience::activity::MixabilityType::MIXABLE_UNRESTRICTED:
            return "MIXABLE_UNRESTRICTED";
        case multiAgentExperience::activity::MixabilityType::NONMIXABLE:
            return "NONMIXABLE";
        default:
            return "NONE";
    }
}

inline std::string toString(multiAgentExperience::activity::MixingBehavior value) {
    switch (value) {
        case multiAgentExperience::activity::MixingBehavior::UNRESTRICTED:
            return "UNRESTRICTED";
        case multiAgentExperience::activity::MixingBehavior::MUST_ATTENUATE:
            return "MUST_ATTENUATE";
        case multiAgentExperience::activity::MixingBehavior::MUST_PAUSE:
            return "MUST_PAUSE";
        default:
            return "NONE";
    }
}

inline std::string toString(multiAgentExperience::application::ActivitySchedulingPolicy value) {
    switch (value) {
        case multiAgentExperience::application::ActivitySchedulingPolicy::STACK:
            return "STACK";
        case multiAgentExperience::application::ActivitySchedulingPolicy::REPLACE:
            return "REPLACE";
        default:
            return "NONE";
    }
}

inline std::string toString(multiAgentExperience::dialog::DialogBargeInPriority value) {
    switch (value) {
        case multiAgentExperience::dialog::DialogBargeInPriority::HIGH:
            return "HIGH";
        case multiAgentExperience::dialog::DialogBargeInPriority::NORMAL:
            return "NORMAL";
        default:
            return "NONE";
    }
}

inline std::string toString(multiAgentExperience::activity::ActivityType value) {
    switch (value) {
        case multiAgentExperience::activity::ActivityType::COMMUNICATION:
            return "COMMUNICATIONS";
        case multiAgentExperience::activity::ActivityType::ALERTS:
            return "ALERTS";
        case multiAgentExperience::activity::ActivityType::NOTIFICATIONS:
            return "NOTIFICATIONS";
        case multiAgentExperience::activity::ActivityType::CONTENT:
            return "CONTENT";
        default:
            return "NONE";
    }
}

inline std::string toString(multiAgentExperience::library::activity::ActivityType value) {
    switch (value) {
        case multiAgentExperience::library::activity::ActivityType::DIALOG:
            return "DIALOG";
        case multiAgentExperience::library::activity::ActivityType::COMMUNICATIONS:
            return "COMMUNICATIONS";
        case multiAgentExperience::library::activity::ActivityType::ALERTS:
            return "ALERTS";
        case multiAgentExperience::library::activity::ActivityType::NOTIFICATIONS:
            return "NOTIFICATIONS";
        case multiAgentExperience::library::activity::ActivityType::CONTENT:
            return "CONTENT";
        default:
            return "NONE";
    }
}

inline std::string toString(multiAgentExperience::library::activity::MixabilityType value) {
    switch (value) {
        case multiAgentExperience::library::activity::MixabilityType::MIXABLE_RESTRICTED:
            return "MIXABLE_RESTRICTED";
        case multiAgentExperience::library::activity::MixabilityType::MIXABLE_UNRESTRICTED:
            return "MIXABLE_UNRESTRICTED";
        case multiAgentExperience::library::activity::MixabilityType::NONMIXABLE:
            return "NONMIXABLE";
        default:
            return "NONE";
    }
}

inline std::string toString(multiAgentExperience::library::activity::MixingBehavior value) {
    switch (value) {
        case multiAgentExperience::library::activity::MixingBehavior::UNRESTRICTED:
            return "UNRESTRICTED";
        case multiAgentExperience::library::activity::MixingBehavior::MUST_ATTENUATE:
            return "MUST_ATTENUATE";
        case multiAgentExperience::library::activity::MixingBehavior::MUST_PAUSE:
            return "MUST_PAUSE";
        default:
            return "NONE";
    }
}

inline std::string toString(multiAgentExperience::control::ControlType value) {
    switch (value) {
        case multiAgentExperience::control::ControlType::STOP:
            return "STOP";
        default:
            return "NONE";
    }
}

inline std::string toString(multiAgentExperience::activity::ActivityFocus value) {
    switch (value) {
        case multiAgentExperience::activity::ActivityFocus::BACKGROUND:
            return "BACKGROUND";
        case multiAgentExperience::activity::ActivityFocus::FOREGROUND:
            return "FOREGROUND";
        default:
            return "NONE";
    }
}

inline std::string toString(std::set<std::shared_ptr<multiAgentExperience::control::Control>> value) {
    std::string output = "{";

    for(auto control : value) {
        output = toString(control->type) + ",";
    }

    output += "}";
    return output;
}

inline std::string toString(std::set<multiAgentExperience::control::ControlType> value) {
    std::string output = "{";

    for(auto controlType : value) {
        output = toString(controlType) + ",";
    }

    output += "}";
    return output;
}

inline std::string getObfuscatedActorId(const multiAgentExperience::actor::ActorId& actorId) {
    return std::to_string(std::hash<std::string>{}(actorId.get()));
}

inline std::string getObfuscatedExperienceId(const multiAgentExperience::experience::ExperienceId& experienceId) {
    return std::to_string(std::hash<std::string>{}(experienceId.get()));
}

}  // namespace utils
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_UTILS_CONVERSIONUTILS_H_
