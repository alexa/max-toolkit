/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#include "MultiAgentExperience/IPC/Proxy/Dialog/DialogControllerMessageHandler.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "MultiAgentExperience/IPC/Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace dialog {

static const std::string MODULE_TAG("DialogControllerMessageHandler");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

DialogControllerMessageHandler::DialogControllerMessageHandler(
    multiAgentExperience::ipc::messaging::Reference reference,
    std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> controller):
        multiAgentExperience::ipc::transport::MessageHandler(std::move(reference)),
        m_controller{std::move(controller)} {
}

void DialogControllerMessageHandler::handle(
    const multiAgentExperience::ipc::messaging::Message<
        models::dialog::DialogControllerFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message) {

    LX(DEBUG0, ipc::utils::toString(message.getFunction()));

    switch (message.getFunction()) {
        case models::dialog::DialogControllerFunctions::START_LISTENING:
            m_controller->startListening();
            break;
        case models::dialog::DialogControllerFunctions::START_THINKING:
            m_controller->startThinking();
            break;
        case models::dialog::DialogControllerFunctions::START_SPEAKING:
            m_controller->startSpeaking();
            break;
        case models::dialog::DialogControllerFunctions::STOP:
            m_controller->stop();
            break;
        default:
            /// For those cases (enums) where we don't expect a @c VoidPayload to be passed, we report an error.
            LX(ERROR, "Wrong function passed: " + ipc::utils::toString(message.getFunction()));
    }
}

void DialogControllerMessageHandler::handle(
    const multiAgentExperience::ipc::messaging::Message<
        models::dialog::DialogControllerFunctions,
        multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::control::ControlType>>& message) {

    LX(DEBUG0, ipc::utils::toString(message.getFunction()));

    switch (message.getFunction()) {
        case models::dialog::DialogControllerFunctions::INVOKE_CONTROL_AND_START_SPEAKING:
            m_controller->invokeControlAndStartSpeaking(message.getPayload().m_value);
            break;
        case models::dialog::DialogControllerFunctions::STOP_AND_INVOKE_CONTROL:
            m_controller->stopAndInvokeControl(message.getPayload().m_value);
            break;
        default:
            LX(ERROR, "Wrong function passed: " + ipc::utils::toString(message.getFunction()));
    }
}

} // namespace dialog
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience