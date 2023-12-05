/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#include "MultiAgentExperience/IPC/Proxy/Dialog/ThinkingHandlerMessageHandler.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "MultiAgentExperience/IPC/Proxy/Dialog/DialogControllerProxy.h"
#include "MultiAgentExperience/IPC/Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace dialog {

static const std::string MODULE_TAG("ThinkingHandlerMessageHandler");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ThinkingHandlerMessageHandler::ThinkingHandlerMessageHandler(
    multiAgentExperience::ipc::messaging::Reference reference,
    std::shared_ptr<transport::MessageSender> sender,
    std::shared_ptr<multiAgentExperience::dialog::ThinkingHandlerInterface> handler):
        multiAgentExperience::ipc::transport::MessageHandler(std::move(reference)),
        m_sender{std::move(sender)},
        m_handler{std::move(handler)} {
}

void ThinkingHandlerMessageHandler::handle(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::ThinkingHandlerFunctions,
    multiAgentExperience::ipc::messaging::ReferencePayload>& message) {
    LX(DEBUG0, ipc::utils::toString(message.getFunction()));

    switch (message.getFunction()) {
        case models::dialog::ThinkingHandlerFunctions::ON_START_THINKING: {

            /**
             * An agent expects @c DialogControllerInterface object to be received in @c ThinkingHandlerInterface::onStartThinking.
             * In the IPC scenario, the handler receives a Reference for the controller, from the MAX library.
             * Hence, we create a proxy object for the controller using the Reference provided to us. The agent can
             * then use this proxy to invoke any @c DialogControllerInterface methods.
             */
            auto controller = std::make_shared<DialogControllerProxy>(message.getPayload().m_reference, m_sender);

            /// Pass the proxy object to the agent
            m_handler->onStartThinking(controller);

            break;
        }
        default:
            LX(ERROR, "Wrong function passed: " + ipc::utils::toString(message.getFunction()));
    }
}

void ThinkingHandlerMessageHandler::handle(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::ThinkingHandlerFunctions,
    multiAgentExperience::ipc::messaging::VoidPayload>& message) {
    LX(DEBUG0, ipc::utils::toString(message.getFunction()));

    switch (message.getFunction()) {
        case models::dialog::ThinkingHandlerFunctions::ON_STOP_THINKING:
            m_handler->onStopThinking();
            break;
        default:
            LX(ERROR, "Wrong function passed: " + ipc::utils::toString(message.getFunction()));
    }
}

} // namespace dialog
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience
