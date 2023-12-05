/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#include "MultiAgentExperience/IPC/Proxy/Dialog/ListeningHandlerMessageHandler.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "MultiAgentExperience/IPC/Proxy/Dialog/DialogControllerProxy.h"
#include "MultiAgentExperience/IPC/Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace dialog {

static const std::string MODULE_TAG("ListeningHandlerMessageHandler");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ListeningHandlerMessageHandler::ListeningHandlerMessageHandler(
    multiAgentExperience::ipc::messaging::Reference reference,
    std::shared_ptr<transport::MessageSender> sender,
    std::shared_ptr<multiAgentExperience::dialog::ListeningHandlerInterface> handler):
        multiAgentExperience::ipc::transport::MessageHandler(std::move(reference)),
        m_sender{std::move(sender)},
        m_handler{std::move(handler)} {
}

void ListeningHandlerMessageHandler::handle(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::ListeningHandlerFunctions,
    multiAgentExperience::ipc::messaging::ReferencePayload>& message) {
    LX(DEBUG0, ipc::utils::toString(message.getFunction()));

    switch (message.getFunction()) {
        case models::dialog::ListeningHandlerFunctions::ON_START_LISTENING: {

            /**
             * An agent expects @c DialogControllerInterface object to be received in @c ListeningHandlerInterface::onStartListening.
             * In the IPC scenario, the handler receives a Reference for the controller, from the MAX library.
             * Hence, we create a proxy object for the controller using the Reference provided to us. The agent can
             * then use this proxy to invoke any @c DialogControllerInterface methods.
             */
            auto controller = std::make_shared<DialogControllerProxy>(message.getPayload().m_reference, m_sender);

            /// Pass the proxy object to the agent
            m_handler->onStartListening(controller);

            break;
        }
        default:
            LX(ERROR, "Wrong function passed: " + ipc::utils::toString(message.getFunction()));
    }
}

void ListeningHandlerMessageHandler::handle(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::ListeningHandlerFunctions,
    multiAgentExperience::ipc::messaging::VoidPayload>& message) {
    LX(DEBUG0, ipc::utils::toString(message.getFunction()));

    switch (message.getFunction()) {
        case models::dialog::ListeningHandlerFunctions::ON_STOP_LISTENING:
            m_handler->onStopListening();
            break;
        default:
            LX(ERROR, "Wrong function passed: " + ipc::utils::toString(message.getFunction()));
    }
}


} // namespace dialog
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience
