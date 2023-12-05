/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#include "MultiAgentExperience/IPC/Proxy/Dialog/DialogManagerMessageHandler.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "MultiAgentExperience/IPC/Proxy/Dialog/ControlReceiverProxy.h"
#include "MultiAgentExperience/IPC/Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace dialog {

static const std::string MODULE_TAG("DialogManagerMessageHandler");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

DialogManagerMessageHandler::DialogManagerMessageHandler(
    multiAgentExperience::ipc::messaging::Reference reference,
    std::shared_ptr<transport::MessageSender> sender,
    std::shared_ptr<proxy::MessageHandlerStore> messageHandlerStore,
    std::shared_ptr<::multiAgentExperience::dialog::DialogManagerInterface> dialogManager) :
        multiAgentExperience::ipc::transport::MessageHandler(std::move(reference)),
        m_sender{std::move(sender)},
        m_messageHandlerStore{std::move(messageHandlerStore)},
        m_dialogManager{std::move(dialogManager)} {
}

/// For @c request, @c stop, @c setControlReceiver, @c setListeningHandler, @c setThinkingHandler, @c setSpeakingHandler
void DialogManagerMessageHandler::handle(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogManagerFunctions,
    multiAgentExperience::ipc::messaging::ReferencePayload>& message) {
    LX(DEBUG0, ipc::utils::toString(message.getFunction()));

    switch (message.getFunction()) {
        case models::dialog::DialogManagerFunctions::REQUEST: {
            /**
             * The MAX library's @c DialogManagerInterface::request expects a @c DialogRequestInterface object.
             * In the IPC scenario, the handler receives a Reference for the dialog request, from the agent.
             * Hence, we create a proxy object for the dialog request using the Reference provided to us. The MAX library can
             * then use this proxy to invoke any @c DialogRequestInterface methods.
             */
            auto request = std::make_shared<DialogRequestProxy>(
                message.getPayload().m_reference, m_sender, m_messageHandlerStore);

            /// Pass the proxy object to the agent
            m_dialogManager->request(request);

            break;
        }

        case models::dialog::DialogManagerFunctions::STOP: {

            auto request = std::make_shared<DialogRequestProxy>(
                message.getPayload().m_reference, m_sender, m_messageHandlerStore);

            m_dialogManager->stop(request);

            break;
        }

        case models::dialog::DialogManagerFunctions::SET_CONTROL_RECEIVER: {

            auto receiver = std::make_shared<ControlReceiverProxy>(message.getPayload().m_reference, m_sender, m_messageHandlerStore);

            m_dialogManager->setControlReceiver(receiver);

            break;
        }

        case models::dialog::DialogManagerFunctions::SET_LISTENING_HANDLER: {

            auto handler = std::make_shared<ListeningHandlerProxy>(
                message.getPayload().m_reference, m_sender, m_messageHandlerStore);

            m_dialogManager->setListeningHandler(handler);

            break;
        }

        case models::dialog::DialogManagerFunctions::SET_THINKING_HANDLER: {

            auto handler = std::make_shared<ThinkingHandlerProxy>(
                message.getPayload().m_reference, m_sender, m_messageHandlerStore);

            m_dialogManager->setThinkingHandler(handler);

            break;
        }

        case models::dialog::DialogManagerFunctions::SET_SPEAKING_HANDLER: {

            auto handler = std::make_shared<SpeakingHandlerProxy>(
                message.getPayload().m_reference, m_sender, m_messageHandlerStore);

            m_dialogManager->setSpeakingHandler(handler);

            break;
        }

        default:
            LX(ERROR, "Wrong function passed: " + ipc::utils::toString(message.getFunction()));
    }

}

/// For @c setAllHandlers method
void DialogManagerMessageHandler::handle(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogManagerFunctions,
    multiAgentExperience::ipc::messaging::ReferenceListPayload>& message) {
    LX(DEBUG0, ipc::utils::toString(message.getFunction()));

    switch (message.getFunction()) {
        case models::dialog::DialogManagerFunctions::SET_ALL_HANDLERS: {

            /// For each @c Reference in the payload, create its respective Proxy and invoke the
            /// @c DialogManagerInterface::setAllHandlers() method
            auto receiver = std::make_shared<ControlReceiverProxy>(
                    message.getPayload().m_references.at(0), m_sender, m_messageHandlerStore);

            auto listeningHandler = std::make_shared<ListeningHandlerProxy>(
                    message.getPayload().m_references.at(1), m_sender, m_messageHandlerStore);

            auto thinkingHandler = std::make_shared<ThinkingHandlerProxy>(
                    message.getPayload().m_references.at(2), m_sender, m_messageHandlerStore);

            auto speakingHandler = std::make_shared<SpeakingHandlerProxy>(
                    message.getPayload().m_references.at(3), m_sender, m_messageHandlerStore);

            m_dialogManager->setAllHandlers(receiver, listeningHandler, thinkingHandler, speakingHandler);

            break;
        }
        default:
            LX(ERROR, "Wrong function passed: " + ipc::utils::toString(message.getFunction()));
    }
}

/// For @c removeAllHandlers, @c removeControlReceiver, @c removeListeningHandler, @c removeThinkingHandler, @c removeSpeakingHandler
void DialogManagerMessageHandler::handle(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogManagerFunctions,
    multiAgentExperience::ipc::messaging::VoidPayload>& message) {
    LX(DEBUG0, ipc::utils::toString(message.getFunction()));

    switch (message.getFunction()) {
        case models::dialog::DialogManagerFunctions::REMOVE_ALL_HANDLERS:
            m_dialogManager->removeAllHandlers();
            break;
        case models::dialog::DialogManagerFunctions::REMOVE_CONTROL_RECEIVER:
            m_dialogManager->removeControlReceiver();
            break;
        case models::dialog::DialogManagerFunctions::REMOVE_LISTENING_HANDLER:
            m_dialogManager->removeListeningHandler();
            break;
        case models::dialog::DialogManagerFunctions::REMOVE_THINKING_HANDLER:
            m_dialogManager->removeThinkingHandler();
            break;
        case models::dialog::DialogManagerFunctions::REMOVE_SPEAKING_HANDLER:
            m_dialogManager->removeSpeakingHandler();
            break;
        default:
            /// For those cases (enum values) where we don't expect a @c VoidPayload to be passed, we report an error.
            LX(ERROR, "Wrong function passed: " + ipc::utils::toString(message.getFunction()));
    }
}

} // namespace dialog
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience
