/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#include "MultiAgentExperience/IPC/Proxy/Dialog/DialogRequestMessageHandler.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "MultiAgentExperience/IPC/Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace dialog {

static const std::string MODULE_TAG("DialogRequestMessageHandler");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

DialogRequestMessageHandler::DialogRequestMessageHandler(
    multiAgentExperience::ipc::messaging::Reference reference,
    std::shared_ptr<transport::MessageSender> sender,
    std::shared_ptr<proxy::MessageHandlerStore> messageHandlerStore,
    std::shared_ptr<::multiAgentExperience::dialog::DialogRequestInterface> dialogRequest) :
        multiAgentExperience::ipc::transport::MessageHandler(std::move(reference)),
        m_sender{std::move(sender)},
        m_messageHandlerStore{std::move(messageHandlerStore)},
        m_dialogRequest{std::move(dialogRequest)} {
}

void DialogRequestMessageHandler::handle(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctions,
    multiAgentExperience::ipc::messaging::StringPayload>& message) {
    LX(DEBUG0, ipc::utils::toString(message.getFunction()));

    switch (message.getFunction()) {
        case models::dialog::DialogRequestFunctions::ON_DENIED:
            m_dialogRequest->onDenied(message.getPayload().m_value);
            break;
        case models::dialog::DialogRequestFunctions::ON_ERROR:
            m_dialogRequest->onError(message.getPayload().m_value);
            break;
        default:
            LX(ERROR, "Wrong function passed: " + ipc::utils::toString(message.getFunction()));
    }

}

void DialogRequestMessageHandler::handle(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctions,
    multiAgentExperience::ipc::messaging::ReferencePayload>& message) {
    LX(DEBUG0, ipc::utils::toString(message.getFunction()));

    switch (message.getFunction()) {
        case models::dialog::DialogRequestFunctions::ON_DIALOG_STARTED: {

            auto controller = std::make_shared<DialogControllerProxy>(message.getPayload().m_reference, m_sender);

            m_dialogRequest->onDialogStarted(controller);

            break;
        }
        default:
            LX(ERROR, "Wrong function passed: " + ipc::utils::toString(message.getFunction()));
    }

}

void DialogRequestMessageHandler::handle(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctions,
    multiAgentExperience::ipc::messaging::VoidPayload>& message) {
    LX(DEBUG0, ipc::utils::toString(message.getFunction()));

    switch (message.getFunction()) {
        case models::dialog::DialogRequestFunctions::ON_DIALOG_STOPPED:
            m_dialogRequest->onDialogStopped();
            break;
        default:
            LX(ERROR, "Wrong function passed: " + ipc::utils::toString(message.getFunction()));
    }
}

void DialogRequestMessageHandler::handle(
    const multiAgentExperience::ipc::messaging::Message<
        models::dialog::DialogRequestFunctionGetDialogBargeInPriority, multiAgentExperience::ipc::messaging::VoidPayload>& message,
    std::shared_ptr<transport::TransportResponder<
        models::dialog::DialogRequestFunctionReturns, multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::dialog::DialogBargeInPriority>>> replyTo) {

    LX(DEBUG0, "DialogRequestFunctionGetDialogBargeInPriority::FUNCTION");

    // We don't have to use a switch case here, since DialogRequestFunctionGetDialogBargeInPriority only has one enum value.

    /// Retrieve the DialogBargeInPriority from the @c DialogRequestInterface object stored in this handler object
    auto dialogBargeInPriority = m_dialogRequest->getDialogBargeInPriority();

    // Create a payload and send the DialogBargeInPriority value using the replyTo object
    auto payload = multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::dialog::DialogBargeInPriority>(dialogBargeInPriority);
    replyTo->reply(payload);
}

} // namespace dialog
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

