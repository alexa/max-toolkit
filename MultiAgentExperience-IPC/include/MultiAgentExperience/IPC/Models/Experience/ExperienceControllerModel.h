/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_EXPERIENCECONTROLLERMODEL_H
#define MULTIAGENTEXPERIENCE_IPC_EXPERIENCECONTROLLERMODEL_H

#include <memory>

#include <MultiAgentExperience/IPC/Messaging/Types/TypeUtils.h>
#include <MultiAgentExperience/Experience/ExperienceControllerInterface.h>

namespace multiAgentExperience {
namespace ipc {
namespace models {
namespace experience {
enum class ExperienceControllerFunctions {
    START_EXPERIENCE, END_EXPERIENCE, INVALIDATE
};
} // namespace experience
} // namespace models
} // namespace ipc
} // namespace multiAgentExperience

template<>
inline std::string multiAgentExperience::ipc::messaging::types::getNamespace(const std::shared_ptr<::multiAgentExperience::experience::ExperienceControllerInterface> &t) {
    return "multiAgentExperience::experience";
}

template<>
inline std::string multiAgentExperience::ipc::messaging::types::getName(const std::shared_ptr<::multiAgentExperience::experience::ExperienceControllerInterface> &t) {
    return "ExperienceController";
}

#endif //MULTIAGENTEXPERIENCE_IPC_EXPERIENCECONTROLLERMODEL_H
