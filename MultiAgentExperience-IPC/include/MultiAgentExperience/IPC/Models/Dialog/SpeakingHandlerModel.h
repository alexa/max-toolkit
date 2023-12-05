/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_IPC_MODELS_DIALOG_SPEAKINGHANDLERMODEL_H
#define MULTIAGENTEXPERIENCE_IPC_MODELS_DIALOG_SPEAKINGHANDLERMODEL_H

#include <memory>
#include <string>

#include <MultiAgentExperience/IPC/Messaging/Types/TypeUtils.h>
#include <MultiAgentExperience/Dialog/SpeakingHandlerInterface.h>

namespace multiAgentExperience {
namespace ipc {
namespace models {
namespace dialog {

enum class SpeakingHandlerFunctions {
    ON_START_SPEAKING,
    ON_STOP_SPEAKING
};

} // namespace dialog
} // namespace models
} // namespace ipc
} // namespace multiAgentExperience

template<>
inline std::string multiAgentExperience::ipc::messaging::types::getNamespace(const std::shared_ptr<multiAgentExperience::dialog::SpeakingHandlerInterface> &t) {
    return "multiAgentExperience::dialog";
}

template<>
inline std::string multiAgentExperience::ipc::messaging::types::getName(const std::shared_ptr<multiAgentExperience::dialog::SpeakingHandlerInterface> &t) {
    return "SpeakingHandlerInterface";
}

#endif //MULTIAGENTEXPERIENCE_IPC_MODELS_DIALOG_SPEAKINGHANDLERMODEL_H
