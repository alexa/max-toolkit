/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#include "MultiAgentExperience/IPC/Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace ipc {
namespace utils {

std::string toString(models::activity::ActivityControllerFunctions value) {
    switch (value) {
        case models::activity::ActivityControllerFunctions::STOP:
            return "ActivityControllerFunctions::STOP";
        default:
            return "NONE";
    }
}

std::string toString(models::activity::ActivityHandlerFunctions value) {
    switch (value) {
        case models::activity::ActivityHandlerFunctions::ON_DENIED:
            return "ActivityHandlerFunctions::ON_DENIED";
        case models::activity::ActivityHandlerFunctions::ON_FOCUS_CHANGED:
            return "ActivityHandlerFunctions::ON_FOCUS_CHANGED";
        case models::activity::ActivityHandlerFunctions::ON_GRANTED:
            return "ActivityHandlerFunctions::ON_GRANTED";
        case models::activity::ActivityHandlerFunctions::ON_STOP:
            return "ActivityHandlerFunctions::ON_STOP";
        default:
            return "NONE";
    }
}

std::string toString(models::activity::ActivityManagerFunctions value) {
    switch (value) {
        case models::activity::ActivityManagerFunctions::REQUEST:
            return "ActivityManagerFunctions::REQUEST";
        case models::activity::ActivityManagerFunctions::STOP:
            return "ActivityManagerFunctions::STOP";
        default:
            return "NONE";
    }
}

std::string toString(models::agent::AgentRegistrationFunctions value) {
    switch (value) {
        case models::agent::AgentRegistrationFunctions::ON_READY:
            return "AgentRegistrationFunctions::::ON_READY";
        default: return "NONE";
    }
}

std::string toString(models::common::OnCompletionCallbackFunctions value) {
    switch (value) {
        case models::common::OnCompletionCallbackFunctions::COMPLETED:
            return "OnCompletionCallbackFunctions::COMPLETED";
        default: return "NONE";
    }
}

std::string toString(models::control::ControlFunctions value) {
    switch (value) {
        case models::control::ControlFunctions::CONTROL_TASK:
            return "ControlFunctions::CONTROL_TASK";
        default: return "NONE";
    }
}

std::string toString(models::control::ControlRegistryFunctions value) {
    switch (value) {
        case models::control::ControlRegistryFunctions::UPDATE:
            return "ControlRegistryFunctions::UPDATE";
        default: return "NONE";
    }
}

std::string toString(models::dialog::ControlReceiverFunctions value) {
    switch (value) {
        case models::dialog::ControlReceiverFunctions::ON_CONTROLS_RECEIVED:
            return "ControlReceiverFunctions::ON_CONTROLS_RECEIVED";
        default: return "NONE";
    }
}

std::string toString(models::dialog::DialogControllerFunctions value) {
    switch (value) {
        case models::dialog::DialogControllerFunctions::START_LISTENING:
            return "DialogControllerFunctions::START_LISTENING";
        case models::dialog::DialogControllerFunctions::START_THINKING:
            return "DialogControllerFunctions::START_THINKING";
        case models::dialog::DialogControllerFunctions::START_SPEAKING:
            return "DialogControllerFunctions::START_SPEAKING";
        case models::dialog::DialogControllerFunctions::INVOKE_CONTROL_AND_START_SPEAKING:
            return "DialogControllerFunctions::INVOKE_CONTROL_AND_START_SPEAKING";
        case models::dialog::DialogControllerFunctions::STOP:
            return "DialogControllerFunctions::STOP";
        case models::dialog::DialogControllerFunctions::STOP_AND_INVOKE_CONTROL:
            return "DialogControllerFunctions::STOP_AND_INVOKE_CONTROL";
        default: return "NONE";
    }
}

std::string toString(models::dialog::DialogManagerFunctions value) {
    switch (value) {
        case models::dialog::DialogManagerFunctions::REQUEST:
            return "DialogManagerFunctions::REQUEST";
        case models::dialog::DialogManagerFunctions::STOP:
            return "DialogManagerFunctions::STOP";
        case models::dialog::DialogManagerFunctions::SET_ALL_HANDLERS:
            return "DialogManagerFunctions::SET_ALL_HANDLERS";
        case models::dialog::DialogManagerFunctions::REMOVE_ALL_HANDLERS:
            return "DialogManagerFunctions::REMOVE_ALL_HANDLERS";
        case models::dialog::DialogManagerFunctions::SET_CONTROL_RECEIVER:
            return "DialogManagerFunctions::SET_CONTROL_RECEIVER";
        case models::dialog::DialogManagerFunctions::REMOVE_CONTROL_RECEIVER:
            return "DialogManagerFunctions::REMOVE_CONTROL_RECEIVER";
        case models::dialog::DialogManagerFunctions::SET_LISTENING_HANDLER:
            return "DialogManagerFunctions::SET_LISTENING_HANDLER";
        case models::dialog::DialogManagerFunctions::REMOVE_LISTENING_HANDLER:
            return "DialogManagerFunctions::REMOVE_LISTENING_HANDLER";
        case models::dialog::DialogManagerFunctions::SET_THINKING_HANDLER:
            return "DialogManagerFunctions::SET_THINKING_HANDLER";
        case models::dialog::DialogManagerFunctions::REMOVE_THINKING_HANDLER:
            return "DialogManagerFunctions::REMOVE_THINKING_HANDLER";
        case models::dialog::DialogManagerFunctions::SET_SPEAKING_HANDLER:
            return "DialogManagerFunctions::SET_SPEAKING_HANDLER";
        case models::dialog::DialogManagerFunctions::REMOVE_SPEAKING_HANDLER:
            return "DialogManagerFunctions::REMOVE_SPEAKING_HANDLER";
        default: return "NONE";
    }
}

std::string toString(models::dialog::DialogRequestFunctions value) {
    switch (value) {
        case models::dialog::DialogRequestFunctions::ON_DENIED:
            return "DialogRequestFunctions::ON_DENIED";
        case models::dialog::DialogRequestFunctions::ON_DIALOG_STARTED:
            return "DialogRequestFunctions::ON_DIALOG_STARTED";
        case models::dialog::DialogRequestFunctions::ON_ERROR:
            return "DialogRequestFunctions::ON_ERROR";
        case models::dialog::DialogRequestFunctions::ON_DIALOG_STOPPED:
            return "DialogRequestFunctions::ON_DIALOG_STOPPED";
        default: return "NONE";
    }
}

std::string toString(models::dialog::ListeningHandlerFunctions value) {
    switch (value) {
        case models::dialog::ListeningHandlerFunctions::ON_START_LISTENING:
            return "ListeningHandlerFunctions::ON_START_LISTENING";
        case models::dialog::ListeningHandlerFunctions::ON_STOP_LISTENING:
            return "ListeningHandlerFunctions::ON_STOP_LISTENING";
        default: return "NONE";
    }
}

std::string toString(models::dialog::SpeakingHandlerFunctions value) {
    switch (value) {
        case models::dialog::SpeakingHandlerFunctions::ON_START_SPEAKING:
            return "SpeakingHandlerFunctions::ON_START_SPEAKING";
        case models::dialog::SpeakingHandlerFunctions::ON_STOP_SPEAKING:
            return "SpeakingHandlerFunctions::ON_STOP_SPEAKING";
        default: return "NONE";
    }
}

std::string toString(models::dialog::StartListeningCallbackFunctions value) {
    switch (value) {
        case models::dialog::StartListeningCallbackFunctions::START_LISTENING:
            return "StartListeningCallbackFunctions::START_LISTENING";
        default: return "NONE";
    }
}

std::string toString(models::dialog::ThinkingHandlerFunctions value) {
    switch (value) {
        case models::dialog::ThinkingHandlerFunctions::ON_START_THINKING:
            return "ThinkingHandlerFunctions::ON_START_THINKING";
        case models::dialog::ThinkingHandlerFunctions::ON_STOP_THINKING:
            return "ThinkingHandlerFunctions::ON_STOP_THINKING";
        default: return "NONE";
    }
}

std::string toString(models::experience::ExperienceControllerFunctions value) {
    switch (value) {
        case models::experience::ExperienceControllerFunctions::START_EXPERIENCE:
            return "ExperienceControllerFunctions::START_EXPERIENCE";
        case models::experience::ExperienceControllerFunctions::END_EXPERIENCE:
            return "ExperienceControllerFunctions::END_EXPERIENCE";
        case models::experience::ExperienceControllerFunctions::INVALIDATE:
            return "ExperienceControllerFunctions::INVALIDATE";
        default: return "NONE";
    }
}

std::string toString(models::experience::StaticExperienceManagerFunctions value) {
    switch (value) {
        case models::experience::StaticExperienceManagerFunctions::ADD_STATIC_EXPERIENCE:
            return "StaticExperienceManagerFunctions::ADD_STATIC_EXPERIENCE";
        case models::experience::StaticExperienceManagerFunctions::REMOVE_STATIC_EXPERIENCE:
            return "StaticExperienceManagerFunctions::REMOVE_STATIC_EXPERIENCE";
        case models::experience::StaticExperienceManagerFunctions::REMOVE_ALL_STATIC_EXPERIENCES:
            return "StaticExperienceManagerFunctions::REMOVE_ALL_STATIC_EXPERIENCES";
        default: return "NONE";
    }
}


std::string toString(multiAgentExperience::activity::MixabilityType value) {
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

std::string toString(multiAgentExperience::activity::MixingBehavior value) {
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

std::string toString(multiAgentExperience::application::ActivitySchedulingPolicy value) {
    switch (value) {
        case multiAgentExperience::application::ActivitySchedulingPolicy::STACK:
            return "STACK";
        case multiAgentExperience::application::ActivitySchedulingPolicy::REPLACE:
            return "REPLACE";
        default:
            return "NONE";
    }
}

std::string toString(multiAgentExperience::dialog::DialogBargeInPriority value) {
    switch (value) {
        case multiAgentExperience::dialog::DialogBargeInPriority::HIGH:
            return "HIGH";
        case multiAgentExperience::dialog::DialogBargeInPriority::NORMAL:
            return "NORMAL";
        default:
            return "NONE";
    }
}

std::string toString(multiAgentExperience::activity::ActivityType value) {
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

std::string toString(multiAgentExperience::control::ControlType value) {
    switch (value) {
        case multiAgentExperience::control::ControlType::STOP:
            return "STOP";
        default:
            return "NONE";
    }
}

std::string toString(multiAgentExperience::activity::ActivityFocus value) {
    switch (value) {
        case multiAgentExperience::activity::ActivityFocus::BACKGROUND:
            return "BACKGROUND";
        case multiAgentExperience::activity::ActivityFocus::FOREGROUND:
            return "FOREGROUND";
        default:
            return "NONE";
    }
}

std::string toString(std::set<std::shared_ptr<multiAgentExperience::control::Control>> value) {
    std::string output = "{";

    for(auto control : value) {
        output = toString(control->type) + ",";
    }

    output += "}";
    return output;
}

std::string toString(std::set<multiAgentExperience::control::ControlType> value) {
    std::string output = "{";

    for(auto controlType : value) {
        output = toString(controlType) + ",";
    }

    output += "}";
    return output;
}

std::string getObfuscatedActorId(const multiAgentExperience::actor::ActorId& actorId) {
    return std::to_string(std::hash<std::string>{}(actorId.get()));
}

std::string getObfuscatedExperienceId(const multiAgentExperience::experience::ExperienceId& experienceId) {
    return std::to_string(std::hash<std::string>{}(experienceId.get()));
}

} // namespace utils
} // namespace ipc
} // namespace multiAgentExperience
