/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_CONTROLRECEIVERMODEL_H
#define MULTIAGENTEXPERIENCE_IPC_CONTROLRECEIVERMODEL_H

#include <MultiAgentExperience/IPC/Messaging/Types/TypeUtils.h>
#include <MultiAgentExperience/Dialog/ControlReceiverInterface.h>
#include <string>

namespace multiAgentExperience {
namespace ipc {
namespace models {
namespace dialog {
    enum class ControlReceiverFunctions {
        ON_CONTROLS_RECEIVED
    };
} // namespace dialog
} // namespace models
} // namespace ipc
} // namespace multiAgentExperience

template<>
inline std::string multiAgentExperience::ipc::messaging::types::getNamespace(const std::shared_ptr<::multiAgentExperience::dialog::ControlReceiverInterface> &t) {
    return "multiAgentExperience::dialog";
}

template<>
inline std::string multiAgentExperience::ipc::messaging::types::getName(const std::shared_ptr<::multiAgentExperience::dialog::ControlReceiverInterface> &t) {
    return "ControlReceiver";
}

#endif //MULTIAGENTEXPERIENCE_IPC_CONTROLRECEIVERMODEL_H
