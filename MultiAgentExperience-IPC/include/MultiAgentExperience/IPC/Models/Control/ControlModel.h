/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_IPC_MODELS_CONTROL_CONTROLMODEL_H
#define MULTIAGENTEXPERIENCE_IPC_MODELS_CONTROL_CONTROLMODEL_H

#include <string>

#include <MultiAgentExperience/IPC/Messaging/Types/TypeUtils.h>
#include <MultiAgentExperience/Control/ControlRegistryInterface.h>

namespace multiAgentExperience {
namespace ipc {
namespace models {
namespace control {

enum class ControlFunctions {
    CONTROL_TASK
};

} // namespace control
} // namespace models
} // namespace ipc
} // namespace multiAgentExperience

template<>
inline std::string multiAgentExperience::ipc::messaging::types::getNamespace(const std::shared_ptr<::multiAgentExperience::control::Control> &t) {
    return "multiAgentExperience::control";
}

template<>
inline std::string multiAgentExperience::ipc::messaging::types::getName(const std::shared_ptr<::multiAgentExperience::control::Control> &t) {
    return "Control";
}

#endif //MULTIAGENTEXPERIENCE_IPC_MODELS_CONTROL_CONTROLMODEL_H
