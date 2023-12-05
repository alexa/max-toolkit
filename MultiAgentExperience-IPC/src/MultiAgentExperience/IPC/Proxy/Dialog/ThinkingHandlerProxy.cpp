/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#include "MultiAgentExperience/IPC/Proxy/Dialog/ThinkingHandlerProxy.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "MultiAgentExperience/IPC/Proxy/MessageHandlerStore.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace dialog {

static const std::string MODULE_TAG("ThinkingHandlerProxy");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ThinkingHandlerProxy::ThinkingHandlerProxy(
    multiAgentExperience::ipc::messaging::Reference reference,
    std::shared_ptr<transport::MessageSender> sender,
    std::shared_ptr<MessageHandlerStore> messageHandlerStore) :
        MaxIpcComponentsBaseProxy(std::move(reference), transport::MaxApiType::THINKING_HANDLER, std::move(sender)),
        m_messageHandlerStore{std::move(messageHandlerStore)} {
}

void ThinkingHandlerProxy::onStartThinking(std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> controller) {
    LX(DEBUG0, "");

    m_messageHandlerStore->createOrGet(controller);

    auto packagedArguments = utils::PayloadPackager::packageReferencePayload(controller);

    auto message = multiAgentExperience::ipc::messaging::createMessage<models::dialog::ThinkingHandlerFunctions, multiAgentExperience::ipc::messaging::ReferencePayload>(
        m_reference,
        models::dialog::ThinkingHandlerFunctions::ON_START_THINKING,
        packagedArguments);

    m_sender->send(message);
}

void ThinkingHandlerProxy::onStopThinking() {
    LX(DEBUG0, "");

    auto message = multiAgentExperience::ipc::messaging::createMessage(
        m_reference,
        models::dialog::ThinkingHandlerFunctions::ON_STOP_THINKING,
        multiAgentExperience::ipc::messaging::VoidPayload());

    m_sender->send(message);
}

} // namespace dialog
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience