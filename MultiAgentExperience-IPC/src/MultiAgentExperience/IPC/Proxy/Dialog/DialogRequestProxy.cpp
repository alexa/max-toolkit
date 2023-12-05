/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#include "MultiAgentExperience/IPC/Proxy/Dialog/DialogRequestProxy.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "MultiAgentExperience/IPC/Proxy/MessageHandlerStore.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace dialog {

static const std::string MODULE_TAG("DialogRequestProxy");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

DialogRequestProxy::DialogRequestProxy(
    multiAgentExperience::ipc::messaging::Reference reference,
    std::shared_ptr<transport::MessageSender> sender,
    std::shared_ptr<MessageHandlerStore> messageHandlerStore):
        MaxIpcComponentsBaseProxy(std::move(reference), transport::MaxApiType::DIALOG_REQUEST, std::move(sender)),
        m_messageHandlerStore{std::move(messageHandlerStore)} {
}

void DialogRequestProxy::onDenied(const std::string& denialMessage) {
    LX(DEBUG0, "");

    auto message = multiAgentExperience::ipc::messaging::createMessage(
        m_reference,
        models::dialog::DialogRequestFunctions::ON_DENIED,
        multiAgentExperience::ipc::messaging::StringPayload(denialMessage));

    m_sender->send(message);
}

void DialogRequestProxy::onDialogStarted(std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> controller) {
    LX(DEBUG0, "");

    m_messageHandlerStore->createOrGet(controller);

    auto packagedArguments = utils::PayloadPackager::packageReferencePayload(controller);

    auto message = multiAgentExperience::ipc::messaging::createMessage<models::dialog::DialogRequestFunctions, multiAgentExperience::ipc::messaging::ReferencePayload>(
        m_reference,
        models::dialog::DialogRequestFunctions::ON_DIALOG_STARTED,
        packagedArguments);

    m_sender->send(message);
}

void DialogRequestProxy::onError(const std::string& errorMessage) {
    LX(DEBUG0, "");

    auto message = multiAgentExperience::ipc::messaging::createMessage(
        m_reference,
        models::dialog::DialogRequestFunctions::ON_ERROR,
        multiAgentExperience::ipc::messaging::StringPayload(errorMessage));

    m_sender->send(message);
}

void DialogRequestProxy::onDialogStopped() {
    LX(DEBUG0, "");

    auto message = multiAgentExperience::ipc::messaging::createMessage(
        m_reference,
        models::dialog::DialogRequestFunctions::ON_DIALOG_STOPPED,
        multiAgentExperience::ipc::messaging::VoidPayload());

    m_sender->send(message);
}

multiAgentExperience::dialog::DialogBargeInPriority DialogRequestProxy::getDialogBargeInPriority() const {
    LX(DEBUG0, "");

    /// This is the request message that may be used MAX library to retrieve the @c DialogBargeInPriority from the
    /// @c DialogRequestInterface object that it receives.
    auto message = multiAgentExperience::ipc::messaging::createMessage(
        m_reference,
        models::dialog::DialogRequestFunctionGetDialogBargeInPriority::FUNCTION,
        multiAgentExperience::ipc::messaging::VoidPayload());

    /// MAX library expects a response (the @c DialogBargeInPriority), hence the type
    /// @c DialogRequestFunctionReturns is mentioned as the ReturnPayload for the send method.
    auto response = m_sender->send<
        models::dialog::DialogRequestFunctionReturns,
        multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::dialog::DialogBargeInPriority>>(message);

    /// Since this API is a synchronous API, we should wait until we get an acknowledgment from the other side (MAX library)
    auto status = response.wait_for(config::SYNCHRONOUS_REQUEST_TIMEOUT);
    if (std::future_status::ready == status) {
        auto payload = response.get().getPayload();
        return payload.m_value;
    } else {
        // TODO: need to have this not be a default somehow. maybe: static_cast<DialogBargeInPriority>(-1)
        LX(ERROR, "Error while waiting for the sync API, returning default DialogBargeInPriority::NORMAL.");
        return multiAgentExperience::dialog::DialogBargeInPriority::NORMAL;
    }
}

std::size_t DialogRequestProxy::getHash() const {
    // We can directly return the Reference for the Proxy object, since it is unique
    return m_reference.getInstance().m_identifier;
}

} // namespace dialog
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience