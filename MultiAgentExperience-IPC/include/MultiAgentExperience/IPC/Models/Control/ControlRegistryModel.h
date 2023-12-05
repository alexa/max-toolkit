/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_CONTROLREGISTRYMODEL_H
#define MULTIAGENTEXPERIENCE_IPC_CONTROLREGISTRYMODEL_H

#include <MultiAgentExperience/IPC/Messaging/Types/TypeUtils.h>
#include <MultiAgentExperience/Control/ControlRegistryInterface.h>
#include <string>

namespace multiAgentExperience {
namespace ipc {
namespace models {
namespace control {
enum class ControlRegistryFunctions {
    UPDATE
};
} // namespace control
} // namespace models
} // namespace ipc
} // namespace multiAgentExperience

template<>
inline std::string multiAgentExperience::ipc::messaging::types::getNamespace(const std::shared_ptr<::multiAgentExperience::control::ControlRegistryInterface> &t) {
    return "multiAgentExperience::control";
}

template<>
inline std::string multiAgentExperience::ipc::messaging::types::getName(const std::shared_ptr<::multiAgentExperience::control::ControlRegistryInterface> &t) {
    return "ControlRegistry";
}
#endif //MULTIAGENTEXPERIENCE_IPC_CONTROLREGISTRYMODEL_H
