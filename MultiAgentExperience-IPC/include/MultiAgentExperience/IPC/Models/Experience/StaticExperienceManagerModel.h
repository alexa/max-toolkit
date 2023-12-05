/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_STATICEXPERIENCEMANAGERMODEL_H
#define MULTIAGENTEXPERIENCE_IPC_STATICEXPERIENCEMANAGERMODEL_H

#include <memory>

#include <MultiAgentExperience/IPC/Messaging/Types/TypeUtils.h>
#include <MultiAgentExperience/Experience/StaticExperienceManagerInterface.h>

namespace multiAgentExperience {
namespace ipc {
namespace models {
namespace experience {
enum class StaticExperienceManagerFunctions {
  ADD_STATIC_EXPERIENCE, REMOVE_STATIC_EXPERIENCE, REMOVE_ALL_STATIC_EXPERIENCES
};
} // namespace experience
} // namespace models
} // namespace ipc
} // namespace multiAgentExperience

template<>
inline std::string multiAgentExperience::ipc::messaging::types::getNamespace(const
std::shared_ptr<::multiAgentExperience::experience::StaticExperienceManagerInterface> &t) {
  return "multiAgentExperience::experience";
}

template<>
inline std::string multiAgentExperience::ipc::messaging::types::getName(const
std::shared_ptr<::multiAgentExperience::experience::StaticExperienceManagerInterface> &t) {
  return "StaticExperienceManager";
}

#endif // MULTIAGENTEXPERIENCE_IPC_STATICEXPERIENCEMANAGERMODEL_H