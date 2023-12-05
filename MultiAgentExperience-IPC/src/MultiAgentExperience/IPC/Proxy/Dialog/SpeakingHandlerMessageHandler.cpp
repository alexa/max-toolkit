/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#include "MultiAgentExperience/IPC/Proxy/Dialog/SpeakingHandlerMessageHandler.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "MultiAgentExperience/IPC/Proxy/Dialog/DialogControllerProxy.h"
#include "MultiAgentExperience/IPC/Proxy/Control/ControlRegistryProxy.h"
#include "MultiAgentExperience/IPC/Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace dialog {

static const std::string MODULE_TAG("SpeakingHandlerMessageHandler");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

SpeakingHandlerMessageHandler::SpeakingHandlerMessageHandler(
    multiAgentExperience::ipc::messaging::Reference reference,
    std::shared_ptr<transport::MessageSender> sender,
    std::shared_ptr<proxy::MessageHandlerStore> messageHandlerStore,
    std::shared_ptr<multiAgentExperience::dialog::SpeakingHandlerInterface> handler):
        multiAgentExperience::ipc::transport::MessageHandler(std::move(reference)),
        m_sender{std::move(sender)},
        m_messageHandlerStore{std::move(messageHandlerStore)},
        m_handler{std::move(handler)} {
}

void SpeakingHandlerMessageHandler::handle(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::SpeakingHandlerFunctions,
    multiAgentExperience::ipc::messaging::ReferenceListPayload>& message) {
    LX(DEBUG0, ipc::utils::toString(message.getFunction()));

    switch (message.getFunction()) {
        case models::dialog::SpeakingHandlerFunctions::ON_START_SPEAKING: {

            /**
             * An agent expects @c DialogControllerInterface and @c ControlRegistryInterface objects to be received
             * in @c SpeakingHandlerInterface::onStartSpeaking.
             *
             * In the IPC scenario, the handler receives a Reference for the controller/registry, from the MAX library.
             * Hence, we extract the References from the list and create the corresponding proxy objects. The agent can
             * then use these proxies to invoke any methods on @c DialogControllerInterface and @c ControlRegistryInterface.
             */
            auto controller = std::make_shared<DialogControllerProxy>(message.getPayload().m_references.at(0), m_sender);

            auto controlRegistry = std::make_shared<control::ControlRegistryProxy>(
                message.getPayload().m_references.at(1), m_sender, m_messageHandlerStore);

            /// Pass the proxy object to the agent
            m_handler->onStartSpeaking(controller, controlRegistry);

            break;
        }
        default:
            LX(ERROR, "Wrong function passed: " + ipc::utils::toString(message.getFunction()));
    }
}

void SpeakingHandlerMessageHandler::handle(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::SpeakingHandlerFunctions,
    multiAgentExperience::ipc::messaging::VoidPayload>& message) {
    LX(DEBUG0, ipc::utils::toString(message.getFunction()));

    switch (message.getFunction()) {
        case models::dialog::SpeakingHandlerFunctions::ON_STOP_SPEAKING:
            m_handler->onStopSpeaking();
            break;
        default:
            LX(ERROR, "Wrong function passed: " + ipc::utils::toString(message.getFunction()));
    }
}


} // namespace dialog
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

