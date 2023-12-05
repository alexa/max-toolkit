/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_IPC_MODELS_DIALOG_DIALOGMANAGERMODEL_H
#define MULTIAGENTEXPERIENCE_IPC_MODELS_DIALOG_DIALOGMANAGERMODEL_H

#include <memory>
#include <string>

#include <MultiAgentExperience/IPC/Messaging/Types/TypeUtils.h>
#include <MultiAgentExperience/Dialog/DialogManagerInterface.h>

namespace multiAgentExperience {
namespace ipc {
namespace models {
namespace dialog {

enum class DialogManagerFunctions {
    REQUEST,
    STOP,
    SET_ALL_HANDLERS,
    REMOVE_ALL_HANDLERS,
    SET_CONTROL_RECEIVER,
    REMOVE_CONTROL_RECEIVER,
    SET_LISTENING_HANDLER,
    REMOVE_LISTENING_HANDLER,
    SET_THINKING_HANDLER,
    REMOVE_THINKING_HANDLER,
    SET_SPEAKING_HANDLER,
    REMOVE_SPEAKING_HANDLER
};

} // namespace dialog
} // namespace models
} // namespace ipc
} // namespace multiAgentExperience

template<>
inline std::string multiAgentExperience::ipc::messaging::types::getNamespace(const std::shared_ptr<multiAgentExperience::dialog::DialogManagerInterface> &t) {
    return "multiAgentExperience::dialog";
}

template<>
inline std::string multiAgentExperience::ipc::messaging::types::getName(const std::shared_ptr<multiAgentExperience::dialog::DialogManagerInterface> &t) {
    return "DialogManagerInterface";
}

#endif //MULTIAGENTEXPERIENCE_IPC_MODELS_DIALOG_DIALOGMANAGERMODEL_H
