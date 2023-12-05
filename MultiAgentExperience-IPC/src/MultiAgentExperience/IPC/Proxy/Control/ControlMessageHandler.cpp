/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/IPC/Proxy/Control/ControlMessageHandler.h"

#include <sstream>

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "MultiAgentExperience/IPC/Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace control {

static const std::string MODULE_TAG("ControlMessageHandler");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ControlMessageHandler::ControlMessageHandler(
    const multiAgentExperience::ipc::messaging::Reference& reference,
    std::shared_ptr<multiAgentExperience::control::Control> control) :
    multiAgentExperience::ipc::transport::MessageHandler(reference),
    m_control{std::move(control)}{
}

void ControlMessageHandler::handle(
    const multiAgentExperience::ipc::messaging::Message<models::control::ControlFunctions,
    multiAgentExperience::ipc::messaging::VoidPayload>& message) {

    LX(DEBUG0, ipc::utils::toString(message.getFunction()));

    switch (message.getFunction()) {
        case models::control::ControlFunctions::CONTROL_TASK:
            invokeTask();
            break;
        default:
            LX(ERROR, "Wrong function passed: " + ipc::utils::toString(message.getFunction()));
    }
}

void ControlMessageHandler::invokeTask() {
    std::stringstream ss;
    ss << "Call to Control::task. details:"
       << " controlType=" << multiAgentExperience::ipc::utils::toString(m_control->type);
    LX(DEBUG0, ss.str());
    m_control->task();
}

} // namespace control
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience
