/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#include "MultiAgentExperience/IPC/Proxy/Dialog/SpeakingHandlerProxy.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "MultiAgentExperience/IPC/Proxy/MessageHandlerStore.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace dialog {

static const std::string MODULE_TAG("SpeakingHandlerProxy");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

SpeakingHandlerProxy::SpeakingHandlerProxy(
    multiAgentExperience::ipc::messaging::Reference reference,
    std::shared_ptr<transport::MessageSender> sender,
    std::shared_ptr<MessageHandlerStore> messageHandlerStore) :
        MaxIpcComponentsBaseProxy(std::move(reference), transport::MaxApiType::SPEAKING_HANDLER, std::move(sender)),
        m_messageHandlerStore{std::move(messageHandlerStore)} {
}

void SpeakingHandlerProxy::onStartSpeaking(
    std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> controller,
    std::shared_ptr<multiAgentExperience::control::ControlRegistryInterface> controlRegistry) {
    LX(DEBUG0, "");

    m_messageHandlerStore->createOrGet(controller);

    auto packagedArguments = utils::PayloadPackager::packageReferenceListPayload(controller, controlRegistry);

    auto message = multiAgentExperience::ipc::messaging::createMessage<models::dialog::SpeakingHandlerFunctions, multiAgentExperience::ipc::messaging::ReferenceListPayload>(
        m_reference,
        models::dialog::SpeakingHandlerFunctions::ON_START_SPEAKING,
        packagedArguments);

    m_sender->send(message);
}

void SpeakingHandlerProxy::onStopSpeaking() {
    LX(DEBUG0, "");

    auto message = multiAgentExperience::ipc::messaging::createMessage(
        m_reference,
        models::dialog::SpeakingHandlerFunctions::ON_STOP_SPEAKING,
        multiAgentExperience::ipc::messaging::VoidPayload());

    m_sender->send(message);
}

} // namespace dialog
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience