/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_IPC_GRPC_UTILS_FUNCTIONTOMESSAGETYPE_H
#define MULTIAGENTEXPERIENCE_IPC_GRPC_UTILS_FUNCTIONTOMESSAGETYPE_H

#include <MultiAgentExperience/Activity/ActivityFocus.h>
#include <MultiAgentExperience/Activity/MixingBehavior.h>
#include <MultiAgentExperience/IPC/Models/Activity/ActivityControllerModel.h>
#include <MultiAgentExperience/IPC/Models/Activity/ActivityHandlerModel.h>
#include <MultiAgentExperience/IPC/Models/Activity/ActivityManagerModel.h>
#include <MultiAgentExperience/IPC/Models/Activity/ActivityRequestModel.h>
#include <MultiAgentExperience/IPC/Models/Agent/AgentRegistrationModel.h>
#include <MultiAgentExperience/IPC/Models/Common/OnCompletionCallbackModel.h>
#include <MultiAgentExperience/IPC/Models/Control/ControlRegistryModel.h>
#include <MultiAgentExperience/IPC/Models/Control/ControlModel.h>
#include <MultiAgentExperience/IPC/Models/Dialog/ControlReceiverModel.h>
#include <MultiAgentExperience/IPC/Models/Dialog/DialogControllerModel.h>
#include <MultiAgentExperience/IPC/Models/Dialog/DialogManagerModel.h>
#include <MultiAgentExperience/IPC/Models/Dialog/DialogRequestModel.h>
#include <MultiAgentExperience/IPC/Models/Dialog/ListeningHandlerModel.h>
#include <MultiAgentExperience/IPC/Models/Dialog/SpeakingHandlerModel.h>
#include <MultiAgentExperience/IPC/Models/Dialog/StartListeningCallbackModel.h>
#include <MultiAgentExperience/IPC/Models/Dialog/ThinkingHandlerModel.h>
#include <MultiAgentExperience/IPC/Models/Experience/ExperienceControllerModel.h>
#include <MultiAgentExperience/IPC/Models/Experience/StaticExperienceManagerModel.h>
#include <MultiAgentExperience/IPC/Transport/MaxApiTypes.h>

#include <maxrpc.grpc.pb.h>

namespace multiAgentExperience {
namespace ipc {
namespace grpc {
namespace utils {

MultiAgentExperience::Rpc::ActivityControllerMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::activity::ActivityControllerFunctions function);

MultiAgentExperience::Rpc::ActivityManagerMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::activity::ActivityManagerFunctions function);

MultiAgentExperience::Rpc::ActivityRequestReturnMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::activity::ActivityRequestFunctionReturns function);

MultiAgentExperience::Rpc::ActivityHandlerMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::activity::ActivityHandlerFunctions function);

MultiAgentExperience::Rpc::DialogControllerMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::dialog::DialogControllerFunctions function);

MultiAgentExperience::Rpc::DialogManagerMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::dialog::DialogManagerFunctions function);

MultiAgentExperience::Rpc::DialogRequestMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::dialog::DialogRequestFunctions function);

MultiAgentExperience::Rpc::ListeningHandlerMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::dialog::ListeningHandlerFunctions function);

MultiAgentExperience::Rpc::ThinkingHandlerMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::dialog::ThinkingHandlerFunctions function);

MultiAgentExperience::Rpc::SpeakingHandlerMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::dialog::SpeakingHandlerFunctions function);

MultiAgentExperience::Rpc::StartListeningCallbackMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::dialog::StartListeningCallbackFunctions function);

MultiAgentExperience::Rpc::ControlRegistryMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::control::ControlRegistryFunctions function);

MultiAgentExperience::Rpc::ControlMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::control::ControlFunctions function);

MultiAgentExperience::Rpc::ControlReceiverMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::dialog::ControlReceiverFunctions function);

MultiAgentExperience::Rpc::ExperienceControllerMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::experience::ExperienceControllerFunctions function);

MultiAgentExperience::Rpc::StaticExperienceManagerMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::experience::StaticExperienceManagerFunctions function);

MultiAgentExperience::Rpc::OnCompletionCallbackMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::common::OnCompletionCallbackFunctions function);

MultiAgentExperience::Rpc::AgentRegistrationReturnMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::agent::AgentRegistrationFunctionReturns function);

MultiAgentExperience::Rpc::AgentRegistrationMessageType getMessageTypeForFunction(
    multiAgentExperience::ipc::models::agent::AgentRegistrationFunctions function);

MultiAgentExperience::Rpc::MaxApiType getMessageTypeForFunction(
        multiAgentExperience::ipc::transport::MaxApiType function);

multiAgentExperience::control::ControlType getControlTypeForMessageType(
    MultiAgentExperience::Rpc::ControlType controlType);

MultiAgentExperience::Rpc::ControlType getMessageTypeForControlType(
    multiAgentExperience::control::ControlType controlType);

MultiAgentExperience::Rpc::DialogBargeInPriority getMessageTypeForDialogBargePriority(
    multiAgentExperience::dialog::DialogBargeInPriority dialogBargeInPriority);

multiAgentExperience::dialog::DialogBargeInPriority getDialogBargePriorityForMessageType(
    MultiAgentExperience::Rpc::DialogBargeInPriority dialogBargeInPriority);

MultiAgentExperience::Rpc::ActivityType getMessageTypeForActivityType(
    multiAgentExperience::activity::ActivityType activityType);

multiAgentExperience::activity::ActivityType getActivityTypeForMessageType(
    MultiAgentExperience::Rpc::ActivityType activityType);

MultiAgentExperience::Rpc::MixabilityType getMessageTypeForMixabilityType(
    multiAgentExperience::activity::MixabilityType mixabilityType);

multiAgentExperience::activity::MixabilityType getMixabilityTypeForMessageType(
    MultiAgentExperience::Rpc::MixabilityType mixabilityType);

MultiAgentExperience::Rpc::ActivityFocus convertActivityFocus(multiAgentExperience::activity::ActivityFocus focus);

multiAgentExperience::activity::ActivityFocus convertActivityFocus(MultiAgentExperience::Rpc::ActivityFocus focus);

MultiAgentExperience::Rpc::MixingBehavior convertMixingBehavior(multiAgentExperience::activity::MixingBehavior behavior);

multiAgentExperience::activity::MixingBehavior convertMixingBehavior(
    MultiAgentExperience::Rpc::MixingBehavior mixingBehavior);

} // namespace utils
} // namespace grpc
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_GRPC_UTILS_FUNCTIONTOMESSAGETYPE_H
