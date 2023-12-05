/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#include "MultiAgentExperience/IPC/gRPC/Utils/FunctionToMessageType.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

namespace multiAgentExperience {
namespace ipc {
namespace grpc {
namespace utils {

const std::string MODULE_TAG("FunctionToMessageType");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

MultiAgentExperience::Rpc::ActivityControllerMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::activity::ActivityControllerFunctions function) {
    switch (function) {
        case models::activity::ActivityControllerFunctions::STOP:
            return MultiAgentExperience::Rpc::ActivityControllerMessageType::CONTROLLER_STOP;

        default:
            return MultiAgentExperience::Rpc::ActivityControllerMessageType();
    }
}

MultiAgentExperience::Rpc::ActivityManagerMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::activity::ActivityManagerFunctions function) {
    switch (function) {
        case models::activity::ActivityManagerFunctions::REQUEST:
            return MultiAgentExperience::Rpc::ActivityManagerMessageType::ACTIVITY_MANAGER_REQUEST;
        case models::activity::ActivityManagerFunctions::STOP:
            return MultiAgentExperience::Rpc::ActivityManagerMessageType::ACTIVITY_MANAGER_STOP;

        default:
            return MultiAgentExperience::Rpc::ActivityManagerMessageType();
    }
}

MultiAgentExperience::Rpc::ActivityRequestReturnMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::activity::ActivityRequestFunctionReturns function) {
    switch (function) {
        case models::activity::ActivityRequestFunctionReturns::GET_TYPE:
            return MultiAgentExperience::Rpc::ActivityRequestReturnMessageType::GET_TYPE;
        case models::activity::ActivityRequestFunctionReturns::GET_HANDLER:
            return MultiAgentExperience::Rpc::ActivityRequestReturnMessageType::GET_HANDLER;
        case models::activity::ActivityRequestFunctionReturns::GET_MIXABILITY_TYPE:
            return MultiAgentExperience::Rpc::ActivityRequestReturnMessageType::GET_MIXABILITY_TYPE;

        default:
            return MultiAgentExperience::Rpc::ActivityRequestReturnMessageType();
    }
}

MultiAgentExperience::Rpc::ActivityHandlerMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::activity::ActivityHandlerFunctions function) {
    switch (function) {
        case models::activity::ActivityHandlerFunctions::ON_DENIED:
            return MultiAgentExperience::Rpc::ActivityHandlerMessageType::ON_DENIED;
        case models::activity::ActivityHandlerFunctions::ON_GRANTED:
            return MultiAgentExperience::Rpc::ActivityHandlerMessageType::ON_GRANTED;
        case models::activity::ActivityHandlerFunctions::ON_FOCUS_CHANGED:
            return MultiAgentExperience::Rpc::ActivityHandlerMessageType::ON_FOCUS_CHANGED;
        case models::activity::ActivityHandlerFunctions::ON_STOP:
            return MultiAgentExperience::Rpc::ActivityHandlerMessageType::ON_STOP;

        default:
            return MultiAgentExperience::Rpc::ActivityHandlerMessageType();
    }
}

MultiAgentExperience::Rpc::DialogControllerMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::dialog::DialogControllerFunctions function) {

    switch(function) {
        case models::dialog::DialogControllerFunctions::START_LISTENING:
            return MultiAgentExperience::Rpc::DialogControllerMessageType::DIALOG_CONTROLLER_START_LISTENING;

        case models::dialog::DialogControllerFunctions::START_THINKING:
            return MultiAgentExperience::Rpc::DialogControllerMessageType::DIALOG_CONTROLLER_START_THINKING;

        case models::dialog::DialogControllerFunctions::START_SPEAKING:
            return MultiAgentExperience::Rpc::DialogControllerMessageType::DIALOG_CONTROLLER_START_SPEAKING;

        case models::dialog::DialogControllerFunctions::INVOKE_CONTROL_AND_START_SPEAKING:
            return MultiAgentExperience::Rpc::DialogControllerMessageType::DIALOG_CONTROLLER_INVOKE_CONTROL_AND_START_SPEAKING;

        case models::dialog::DialogControllerFunctions::STOP:
            return MultiAgentExperience::Rpc::DialogControllerMessageType::DIALOG_CONTROLLER_STOP;

        case models::dialog::DialogControllerFunctions::STOP_AND_INVOKE_CONTROL:
            return MultiAgentExperience::Rpc::DialogControllerMessageType::DIALOG_CONTROLLER_STOP_AND_INVOKE_CONTROL;

        default:
            return MultiAgentExperience::Rpc::DialogControllerMessageType();
    }
}

MultiAgentExperience::Rpc::DialogManagerMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::dialog::DialogManagerFunctions function) {

    switch(function) {
        case models::dialog::DialogManagerFunctions::REQUEST:
            return MultiAgentExperience::Rpc::DialogManagerMessageType::DIALOG_MANAGER_REQUEST;

        case models::dialog::DialogManagerFunctions::STOP:
            return MultiAgentExperience::Rpc::DialogManagerMessageType::DIALOG_MANAGER_STOP;

        case models::dialog::DialogManagerFunctions::SET_ALL_HANDLERS:
            return MultiAgentExperience::Rpc::DialogManagerMessageType::DIALOG_MANAGER_SET_ALL_HANDLERS;

        case models::dialog::DialogManagerFunctions::REMOVE_ALL_HANDLERS:
            return MultiAgentExperience::Rpc::DialogManagerMessageType::DIALOG_MANAGER_REMOVE_ALL_HANDLERS;

        case models::dialog::DialogManagerFunctions::SET_CONTROL_RECEIVER:
            return MultiAgentExperience::Rpc::DialogManagerMessageType::DIALOG_MANAGER_SET_CONTROL_RECEIVER;

        case models::dialog::DialogManagerFunctions::REMOVE_CONTROL_RECEIVER:
            return MultiAgentExperience::Rpc::DialogManagerMessageType::DIALOG_MANAGER_REMOVE_CONTROL_RECEIVER;

        case models::dialog::DialogManagerFunctions::SET_LISTENING_HANDLER:
            return MultiAgentExperience::Rpc::DialogManagerMessageType::DIALOG_MANAGER_SET_LISTENING_HANDLER;

        case models::dialog::DialogManagerFunctions::REMOVE_LISTENING_HANDLER:
            return MultiAgentExperience::Rpc::DialogManagerMessageType::DIALOG_MANAGER_REMOVE_LISTENING_HANDLER;

        case models::dialog::DialogManagerFunctions::SET_THINKING_HANDLER:
            return MultiAgentExperience::Rpc::DialogManagerMessageType::DIALOG_MANAGER_SET_THINKING_HANDLER;

        case models::dialog::DialogManagerFunctions::REMOVE_THINKING_HANDLER:
            return MultiAgentExperience::Rpc::DialogManagerMessageType::DIALOG_MANAGER_REMOVE_THINKING_HANDLER;

        case models::dialog::DialogManagerFunctions::SET_SPEAKING_HANDLER:
            return MultiAgentExperience::Rpc::DialogManagerMessageType::DIALOG_MANAGER_SET_SPEAKING_HANDLER;

        case models::dialog::DialogManagerFunctions::REMOVE_SPEAKING_HANDLER:
            return MultiAgentExperience::Rpc::DialogManagerMessageType::DIALOG_MANAGER_REMOVE_SPEAKING_HANDLER;

        default:
            return MultiAgentExperience::Rpc::DialogManagerMessageType();
    }
}

MultiAgentExperience::Rpc::DialogRequestMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::dialog::DialogRequestFunctions function) {

    switch(function) {
        case models::dialog::DialogRequestFunctions::ON_DENIED:
            return MultiAgentExperience::Rpc::DialogRequestMessageType::DIALOG_REQUEST_ON_DENIED;

        case models::dialog::DialogRequestFunctions::ON_DIALOG_STARTED:
            return MultiAgentExperience::Rpc::DialogRequestMessageType::DIALOG_REQUEST_ON_DIALOG_STARTED;

        case models::dialog::DialogRequestFunctions::ON_ERROR:
            return MultiAgentExperience::Rpc::DialogRequestMessageType::DIALOG_REQUEST_ON_ERROR;

        case models::dialog::DialogRequestFunctions::ON_DIALOG_STOPPED:
            return MultiAgentExperience::Rpc::DialogRequestMessageType::DIALOG_REQUEST_ON_DIALOG_STOPPED;

        default:
            return MultiAgentExperience::Rpc::DialogRequestMessageType();
    }
}

MultiAgentExperience::Rpc::ListeningHandlerMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::dialog::ListeningHandlerFunctions function) {

    switch(function) {
        case models::dialog::ListeningHandlerFunctions::ON_START_LISTENING:
            return MultiAgentExperience::Rpc::ListeningHandlerMessageType::ON_START_LISTENING;

        case models::dialog::ListeningHandlerFunctions::ON_STOP_LISTENING:
            return MultiAgentExperience::Rpc::ListeningHandlerMessageType::ON_STOP_LISTENING;

        default:
            return MultiAgentExperience::Rpc::ListeningHandlerMessageType();
    }
}

MultiAgentExperience::Rpc::ThinkingHandlerMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::dialog::ThinkingHandlerFunctions function) {

    switch(function) {
        case models::dialog::ThinkingHandlerFunctions::ON_START_THINKING:
            return MultiAgentExperience::Rpc::ThinkingHandlerMessageType::ON_START_THINKING;

        case models::dialog::ThinkingHandlerFunctions::ON_STOP_THINKING:
            return MultiAgentExperience::Rpc::ThinkingHandlerMessageType::ON_STOP_THINKING;

        default:
            return MultiAgentExperience::Rpc::ThinkingHandlerMessageType();
    }
}

MultiAgentExperience::Rpc::SpeakingHandlerMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::dialog::SpeakingHandlerFunctions function) {

    switch(function) {
        case models::dialog::SpeakingHandlerFunctions::ON_START_SPEAKING:
            return MultiAgentExperience::Rpc::SpeakingHandlerMessageType::ON_START_SPEAKING;

        case models::dialog::SpeakingHandlerFunctions::ON_STOP_SPEAKING:
            return MultiAgentExperience::Rpc::SpeakingHandlerMessageType::ON_STOP_SPEAKING;

        default:
            return MultiAgentExperience::Rpc::SpeakingHandlerMessageType();
    }
}

MultiAgentExperience::Rpc::StartListeningCallbackMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::dialog::StartListeningCallbackFunctions function) {

    switch(function) {
        case models::dialog::StartListeningCallbackFunctions::START_LISTENING:
            return MultiAgentExperience::Rpc::StartListeningCallbackMessageType::START_LISTENING;

        default:
            return MultiAgentExperience::Rpc::StartListeningCallbackMessageType();
    }
}

MultiAgentExperience::Rpc::ControlRegistryMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::control::ControlRegistryFunctions function) {

    switch(function) {
        case models::control::ControlRegistryFunctions::UPDATE:
            return MultiAgentExperience::Rpc::ControlRegistryMessageType::UPDATE;

        default:
            return MultiAgentExperience::Rpc::ControlRegistryMessageType();
    }
}

MultiAgentExperience::Rpc::ControlMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::control::ControlFunctions function) {

    switch(function) {
        case models::control::ControlFunctions::CONTROL_TASK:
            return MultiAgentExperience::Rpc::ControlMessageType::CONTROL_TASK;

        default:
            return MultiAgentExperience::Rpc::ControlMessageType();
    }
}

MultiAgentExperience::Rpc::ControlReceiverMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::dialog::ControlReceiverFunctions function) {

    switch (function) {
        case models::dialog::ControlReceiverFunctions::ON_CONTROLS_RECEIVED:
            return MultiAgentExperience::Rpc::ControlReceiverMessageType::ON_CONTROLS_RECEIVED;

        default:
            return MultiAgentExperience::Rpc::ControlReceiverMessageType();
    }
}

MultiAgentExperience::Rpc::ExperienceControllerMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::experience::ExperienceControllerFunctions function) {

    switch(function) {
        case models::experience::ExperienceControllerFunctions::START_EXPERIENCE:
            return MultiAgentExperience::Rpc::ExperienceControllerMessageType::START_EXPERIENCE;

        case models::experience::ExperienceControllerFunctions::END_EXPERIENCE:
            return MultiAgentExperience::Rpc::ExperienceControllerMessageType::END_EXPERIENCE;

        case models::experience::ExperienceControllerFunctions::INVALIDATE:
            return MultiAgentExperience::Rpc::ExperienceControllerMessageType::INVALIDATE;

        default:
            return MultiAgentExperience::Rpc::ExperienceControllerMessageType();
    }
}

MultiAgentExperience::Rpc::StaticExperienceManagerMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::experience::StaticExperienceManagerFunctions function) {

    switch(function) {
        case models::experience::StaticExperienceManagerFunctions::ADD_STATIC_EXPERIENCE:
            return MultiAgentExperience::Rpc::StaticExperienceManagerMessageType::ADD_STATIC_EXPERIENCE;

        case models::experience::StaticExperienceManagerFunctions::REMOVE_STATIC_EXPERIENCE:
            return MultiAgentExperience::Rpc::StaticExperienceManagerMessageType::REMOVE_STATIC_EXPERIENCE;

        case models::experience::StaticExperienceManagerFunctions::REMOVE_ALL_STATIC_EXPERIENCES:
            return MultiAgentExperience::Rpc::StaticExperienceManagerMessageType::REMOVE_ALL_STATIC_EXPERIENCES;

        default:
            return MultiAgentExperience::Rpc::StaticExperienceManagerMessageType();
    }
}

MultiAgentExperience::Rpc::OnCompletionCallbackMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::common::OnCompletionCallbackFunctions function) {

    switch(function) {
        case models::common::OnCompletionCallbackFunctions::COMPLETED:
            return MultiAgentExperience::Rpc::OnCompletionCallbackMessageType::COMPLETED;

        default:
            return MultiAgentExperience::Rpc::OnCompletionCallbackMessageType();
    }
}

MultiAgentExperience::Rpc::AgentRegistrationReturnMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::agent::AgentRegistrationFunctionReturns function) {

    switch(function) {
        case multiAgentExperience::ipc::models::agent::AgentRegistrationFunctionReturns::GET_ID:
            return MultiAgentExperience::Rpc::AgentRegistrationReturnMessageType::GET_ID;

        case multiAgentExperience::ipc::models::agent::AgentRegistrationFunctionReturns::GET_NAME:
            return MultiAgentExperience::Rpc::AgentRegistrationReturnMessageType::GET_NAME;

        default:
            return MultiAgentExperience::Rpc::AgentRegistrationReturnMessageType();
    }
}

MultiAgentExperience::Rpc::AgentRegistrationMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::agent::AgentRegistrationFunctions function) {

    switch(function) {
        case multiAgentExperience::ipc::models::agent::AgentRegistrationFunctions::ON_READY:
            return MultiAgentExperience::Rpc::AgentRegistrationMessageType::AGENT_REGISTRATION_ON_READY;

        default:
            return MultiAgentExperience::Rpc::AgentRegistrationMessageType::AGENT_REGISTRATION_ON_READY;
    }
}

MultiAgentExperience::Rpc::MaxApiType getMessageTypeForFunction(
        multiAgentExperience::ipc::transport::MaxApiType function) {

    switch(function) {
        case  multiAgentExperience::ipc::transport::MaxApiType::ACTIVITY_CONTROLLER:
            return MultiAgentExperience::Rpc::MaxApiType::ACTIVITY_CONTROLLER;
        case  multiAgentExperience::ipc::transport::MaxApiType::ACTIVITY_HANDLER:
            return MultiAgentExperience::Rpc::MaxApiType::ACTIVITY_HANDLER;
        case  multiAgentExperience::ipc::transport::MaxApiType::ACTIVITY_MANAGER:
            return MultiAgentExperience::Rpc::MaxApiType::ACTIVITY_MANAGER;
        case  multiAgentExperience::ipc::transport::MaxApiType::ACTIVITY_REQUEST:
            return MultiAgentExperience::Rpc::MaxApiType::ACTIVITY_REQUEST;
        case  multiAgentExperience::ipc::transport::MaxApiType::AGENT_REGISTRATION:
            return MultiAgentExperience::Rpc::MaxApiType::AGENT_REGISTRATION;
        case  multiAgentExperience::ipc::transport::MaxApiType::ON_COMPLETION_CALLBACK:
            return MultiAgentExperience::Rpc::MaxApiType::ON_COMPLETION_CALLBACK;
        case  multiAgentExperience::ipc::transport::MaxApiType::CONTROL:
            return MultiAgentExperience::Rpc::MaxApiType::CONTROL;
        case  multiAgentExperience::ipc::transport::MaxApiType::CONTROL_REGISTRY:
            return MultiAgentExperience::Rpc::MaxApiType::CONTROL_REGISTRY;
        case  multiAgentExperience::ipc::transport::MaxApiType::EXPERIENCE_CONTROLLER:
            return MultiAgentExperience::Rpc::MaxApiType::EXPERIENCE_CONTROLLER;
        case  multiAgentExperience::ipc::transport::MaxApiType::STATIC_EXPERIENCE_MANAGER:
            return MultiAgentExperience::Rpc::MaxApiType::STATIC_EXPERIENCE_MANAGER;

        default:
            return MultiAgentExperience::Rpc::MaxApiType();
    }
}

multiAgentExperience::control::ControlType getControlTypeForMessageType(
    MultiAgentExperience::Rpc::ControlType controlType) {

    switch (controlType) {
        case MultiAgentExperience::Rpc::ControlType::STOP:
            return multiAgentExperience::control::ControlType::STOP;

        default:
            LX(ERROR, "Incorrect value provided. Using default ControlType::STOP");
            return multiAgentExperience::control::ControlType::STOP;
    }
}

MultiAgentExperience::Rpc::ControlType getMessageTypeForControlType(
    multiAgentExperience::control::ControlType controlType) {

    switch (controlType) {
        case multiAgentExperience::control::ControlType::STOP:
            return MultiAgentExperience::Rpc::ControlType::STOP;

        default:
            LX(ERROR, "Incorrect value provided. Using default ControlType::STOP");
            return MultiAgentExperience::Rpc::ControlType::STOP;
    }
}

MultiAgentExperience::Rpc::DialogBargeInPriority getMessageTypeForDialogBargePriority(
    multiAgentExperience::dialog::DialogBargeInPriority dialogBargeInPriority) {

    switch(dialogBargeInPriority) {
        case multiAgentExperience::dialog::DialogBargeInPriority::HIGH:
            return MultiAgentExperience::Rpc::DialogBargeInPriority::HIGH;

        case multiAgentExperience::dialog::DialogBargeInPriority::NORMAL:
            return MultiAgentExperience::Rpc::DialogBargeInPriority::NORMAL;

        default:
            LX(ERROR, "Incorrect value provided. Using default DialogBargeInPriority::NORMAL");
            return MultiAgentExperience::Rpc::DialogBargeInPriority::NORMAL;
    }
}

multiAgentExperience::dialog::DialogBargeInPriority getDialogBargePriorityForMessageType(
    MultiAgentExperience::Rpc::DialogBargeInPriority dialogBargeInPriority) {

    switch(dialogBargeInPriority) {
        case MultiAgentExperience::Rpc::DialogBargeInPriority::HIGH:
            return multiAgentExperience::dialog::DialogBargeInPriority::HIGH;

        case MultiAgentExperience::Rpc::DialogBargeInPriority::NORMAL:
            return multiAgentExperience::dialog::DialogBargeInPriority::NORMAL;

        default:
            LX(ERROR, "Incorrect value provided. Using default DialogBargeInPriority::NORMAL");
            return multiAgentExperience::dialog::DialogBargeInPriority::NORMAL;
    }
}

MultiAgentExperience::Rpc::ActivityType getMessageTypeForActivityType(
    multiAgentExperience::activity::ActivityType activityType) {

    switch(activityType) {
        case ::multiAgentExperience::activity::ActivityType::ALERTS:
            return MultiAgentExperience::Rpc::ActivityType::ALERTS;

        case ::multiAgentExperience::activity::ActivityType::NOTIFICATIONS:
            return MultiAgentExperience::Rpc::ActivityType::NOTIFICATIONS;

        case ::multiAgentExperience::activity::ActivityType::CONTENT:
            return MultiAgentExperience::Rpc::ActivityType::CONTENT;

        case ::multiAgentExperience::activity::ActivityType::COMMUNICATION:
            return MultiAgentExperience::Rpc::ActivityType::COMMUNICATION;

        default:
            LX(ERROR, "Incorrect value provided. Using default ActivityType::CONTENT");
            return MultiAgentExperience::Rpc::ActivityType::CONTENT;
    }
}

multiAgentExperience::activity::ActivityType getActivityTypeForMessageType(
    MultiAgentExperience::Rpc::ActivityType activityType) {

    switch(activityType) {
        case MultiAgentExperience::Rpc::ActivityType::ALERTS:
            return multiAgentExperience::activity::ActivityType::ALERTS;

        case MultiAgentExperience::Rpc::ActivityType::NOTIFICATIONS:
            return multiAgentExperience::activity::ActivityType::NOTIFICATIONS;

        case MultiAgentExperience::Rpc::ActivityType::CONTENT:
            return multiAgentExperience::activity::ActivityType::CONTENT;

        case MultiAgentExperience::Rpc::ActivityType::COMMUNICATION:
            return multiAgentExperience::activity::ActivityType::COMMUNICATION;

        default:
            LX(ERROR, "Incorrect value provided. Using default ActivityType::CONTENT");
            return multiAgentExperience::activity::ActivityType::CONTENT;
    }
}

MultiAgentExperience::Rpc::MixabilityType getMessageTypeForMixabilityType(
    multiAgentExperience::activity::MixabilityType mixabilityType) {

    switch(mixabilityType) {
        case ::multiAgentExperience::activity::MixabilityType::MIXABLE_RESTRICTED:
            return MultiAgentExperience::Rpc::MixabilityType::MIXABLE_RESTRICTED;

        case ::multiAgentExperience::activity::MixabilityType::NONMIXABLE:
            return MultiAgentExperience::Rpc::MixabilityType::NONMIXABLE;

        case ::multiAgentExperience::activity::MixabilityType::MIXABLE_UNRESTRICTED:
            return MultiAgentExperience::Rpc::MixabilityType::MIXABLE_UNRESTRICTED;

        default:
            LX(ERROR, "Incorrect value provided. Using default MixabilityType::MIXABLE_RESTRICTED");
            return MultiAgentExperience::Rpc::MixabilityType::MIXABLE_RESTRICTED;
    }
}

multiAgentExperience::activity::MixabilityType getMixabilityTypeForMessageType(
    MultiAgentExperience::Rpc::MixabilityType mixabilityType) {

    switch(mixabilityType) {
        case MultiAgentExperience::Rpc::MixabilityType::MIXABLE_RESTRICTED:
            return multiAgentExperience::activity::MixabilityType::MIXABLE_RESTRICTED;

        case MultiAgentExperience::Rpc::MixabilityType::NONMIXABLE:
            return multiAgentExperience::activity::MixabilityType::NONMIXABLE;

        case MultiAgentExperience::Rpc::MixabilityType::MIXABLE_UNRESTRICTED:
            return multiAgentExperience::activity::MixabilityType::MIXABLE_UNRESTRICTED;

        default:
            LX(ERROR, "Incorrect value provided. Using default MixabilityType::MIXABLE_RESTRICTED");
            return multiAgentExperience::activity::MixabilityType::MIXABLE_RESTRICTED;
    }
}

MultiAgentExperience::Rpc::ActivityFocus convertActivityFocus(multiAgentExperience::activity::ActivityFocus focus) {
    switch (focus) {
        case multiAgentExperience::activity::ActivityFocus::BACKGROUND:
            return MultiAgentExperience::Rpc::ActivityFocus::BACKGROUND;

        case multiAgentExperience::activity::ActivityFocus::FOREGROUND:
            return MultiAgentExperience::Rpc::ActivityFocus::FOREGROUND;

        default:
            LX(ERROR, "Incorrect value provided. Using default ActivityFocus::FOREGROUND");
            return MultiAgentExperience::Rpc::ActivityFocus::FOREGROUND;
    }
}

multiAgentExperience::activity::ActivityFocus convertActivityFocus(MultiAgentExperience::Rpc::ActivityFocus focus) {
    switch (focus) {
        case MultiAgentExperience::Rpc::ActivityFocus::BACKGROUND:
            return multiAgentExperience::activity::ActivityFocus::BACKGROUND;

        case MultiAgentExperience::Rpc::ActivityFocus::FOREGROUND:
            return multiAgentExperience::activity::ActivityFocus::FOREGROUND;

        default:
            LX(ERROR, "Incorrect value provided. Using default ActivityFocus::BACKGROUND");
            return multiAgentExperience::activity::ActivityFocus::BACKGROUND;
    }
}

MultiAgentExperience::Rpc::MixingBehavior convertMixingBehavior(multiAgentExperience::activity::MixingBehavior behavior) {
    switch (behavior) {
        case multiAgentExperience::activity::MixingBehavior::MUST_ATTENUATE:
            return MultiAgentExperience::Rpc::MixingBehavior::MUST_ATTENUATE;

        case multiAgentExperience::activity::MixingBehavior::MUST_PAUSE:
            return MultiAgentExperience::Rpc::MixingBehavior::MUST_PAUSE;

        case multiAgentExperience::activity::MixingBehavior::UNRESTRICTED:
            return MultiAgentExperience::Rpc::MixingBehavior::UNRESTRICTED;

        default:
            LX(ERROR, "Incorrect value provided. Using default MixingBehavior::UNRESTRICTED");
            return MultiAgentExperience::Rpc::MixingBehavior::UNRESTRICTED;
    }
}

multiAgentExperience::activity::MixingBehavior convertMixingBehavior(MultiAgentExperience::Rpc::MixingBehavior mixingBehavior) {
    switch (mixingBehavior) {
        case MultiAgentExperience::Rpc::MixingBehavior::MUST_ATTENUATE:
            return multiAgentExperience::activity::MixingBehavior::MUST_ATTENUATE;

        case MultiAgentExperience::Rpc::MixingBehavior::MUST_PAUSE:
            return multiAgentExperience::activity::MixingBehavior::MUST_PAUSE;

        case MultiAgentExperience::Rpc::MixingBehavior::UNRESTRICTED:
            return multiAgentExperience::activity::MixingBehavior::UNRESTRICTED;

        default:
            LX(ERROR, "Incorrect value provided. Using default MixingBehavior::UNRESTRICTED");
            return multiAgentExperience::activity::MixingBehavior::UNRESTRICTED;
    }
}

} // namespace utils
} // namespace grpc
} // namespace ipc
} // namespace multiAgentExperience