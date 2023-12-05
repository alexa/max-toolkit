/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_IPC_UTILS_CONVERSIONUTILS_H_
#define MULTIAGENTEXPERIENCE_IPC_UTILS_CONVERSIONUTILS_H_

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

#include "MultiAgentExperience/IPC/Models/Activity/ActivityControllerModel.h"
#include "MultiAgentExperience/IPC/Models/Activity/ActivityHandlerModel.h"
#include "MultiAgentExperience/IPC/Models/Activity/ActivityManagerModel.h"
#include "MultiAgentExperience/IPC/Models/Activity/ActivityRequestModel.h"
#include "MultiAgentExperience/IPC/Models/Agent/AgentRegistrationModel.h"
#include "MultiAgentExperience/IPC/Models/Common/OnCompletionCallbackModel.h"
#include "MultiAgentExperience/IPC/Models/Control/ControlModel.h"
#include "MultiAgentExperience/IPC/Models/Control/ControlRegistryModel.h"
#include "MultiAgentExperience/IPC/Models/Dialog/ControlReceiverModel.h"
#include "MultiAgentExperience/IPC/Models/Dialog/DialogControllerModel.h"
#include "MultiAgentExperience/IPC/Models/Dialog/DialogManagerModel.h"
#include "MultiAgentExperience/IPC/Models/Dialog/DialogRequestModel.h"
#include "MultiAgentExperience/IPC/Models/Dialog/ListeningHandlerModel.h"
#include "MultiAgentExperience/IPC/Models/Dialog/SpeakingHandlerModel.h"
#include "MultiAgentExperience/IPC/Models/Dialog/StartListeningCallbackModel.h"
#include "MultiAgentExperience/IPC/Models/Dialog/ThinkingHandlerModel.h"
#include "MultiAgentExperience/IPC/Models/Experience/ExperienceControllerModel.h"
#include "MultiAgentExperience/IPC/Models/Experience/StaticExperienceManagerModel.h"



namespace multiAgentExperience {
namespace ipc {
namespace utils {

std::string toString(models::activity::ActivityControllerFunctions value);
std::string toString(models::activity::ActivityHandlerFunctions value);
std::string toString(models::activity::ActivityManagerFunctions value);
std::string toString(models::agent::AgentRegistrationFunctions value);
std::string toString(models::common::OnCompletionCallbackFunctions value);
std::string toString(models::control::ControlFunctions value);
std::string toString(models::control::ControlRegistryFunctions value);
std::string toString(models::dialog::ControlReceiverFunctions value);
std::string toString(models::dialog::DialogControllerFunctions value);
std::string toString(models::dialog::DialogManagerFunctions value);
std::string toString(models::dialog::DialogRequestFunctions value);
std::string toString(models::dialog::ListeningHandlerFunctions value);
std::string toString(models::dialog::SpeakingHandlerFunctions value);
std::string toString(models::dialog::StartListeningCallbackFunctions value);
std::string toString(models::dialog::ThinkingHandlerFunctions value);
std::string toString(models::experience::ExperienceControllerFunctions value);
std::string toString(models::experience::StaticExperienceManagerFunctions value);

std::string toString(multiAgentExperience::activity::MixabilityType value);
std::string toString(multiAgentExperience::activity::MixingBehavior value);
std::string toString(multiAgentExperience::application::ActivitySchedulingPolicy value);
std::string toString(multiAgentExperience::dialog::DialogBargeInPriority value);
std::string toString(multiAgentExperience::activity::ActivityType value);
std::string toString(multiAgentExperience::control::ControlType value);
std::string toString(multiAgentExperience::activity::ActivityFocus value);
std::string toString(std::set<std::shared_ptr<multiAgentExperience::control::Control>> value);
std::string toString(std::set<multiAgentExperience::control::ControlType> value);

std::string getObfuscatedActorId(const multiAgentExperience::actor::ActorId& actorId);
std::string getObfuscatedExperienceId(const multiAgentExperience::experience::ExperienceId& experienceId) ;

} // namespace utils
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_UTILS_CONVERSIONUTILS_H_
