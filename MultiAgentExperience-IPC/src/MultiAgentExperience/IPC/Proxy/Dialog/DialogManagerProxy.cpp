/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#include "MultiAgentExperience/IPC/Proxy/Dialog/DialogManagerProxy.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace dialog {

static const std::string MODULE_TAG("DialogManagerProxy");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

DialogManagerProxy::DialogManagerProxy(
    multiAgentExperience::ipc::messaging::Reference reference,
    std::shared_ptr<transport::MessageSender> sender,
    std::shared_ptr<MessageHandlerStore> messageHandlerStore) :
        MaxIpcComponentsBaseProxy(std::move(reference), transport::MaxApiType::DIALOG_MANAGER, std::move(sender)),
        m_messageHandlerStore{messageHandlerStore} {
}

void DialogManagerProxy::request
    (std::shared_ptr<multiAgentExperience::dialog::DialogRequestInterface> request) {

    LX(DEBUG0, "");

    m_messageHandlerStore->createOrGet(request);

    auto packagedArguments = utils::PayloadPackager::packageReferencePayload(request);

    auto message = multiAgentExperience::ipc::messaging::createMessage<models::dialog::DialogManagerFunctions, multiAgentExperience::ipc::messaging::ReferencePayload>(
        m_reference,
        models::dialog::DialogManagerFunctions::REQUEST,
        packagedArguments);

    m_sender->send(message);
}

void DialogManagerProxy::stop(std::shared_ptr<multiAgentExperience::dialog::DialogRequestInterface> request) {

    LX(DEBUG0, "");

    auto packagedArguments = utils::PayloadPackager::packageReferencePayload(request);

    auto message = multiAgentExperience::ipc::messaging::createMessage<models::dialog::DialogManagerFunctions, multiAgentExperience::ipc::messaging::ReferencePayload>(
        m_reference,
        models::dialog::DialogManagerFunctions::STOP,
        packagedArguments);

    m_sender->send(message);
}

void DialogManagerProxy::setAllHandlers(
    std::shared_ptr<multiAgentExperience::dialog::ControlReceiverInterface> controlReceiver,
    std::shared_ptr<multiAgentExperience::dialog::ListeningHandlerInterface> listeningHandler,
    std::shared_ptr<multiAgentExperience::dialog::ThinkingHandlerInterface> thinkingHandler,
    std::shared_ptr<multiAgentExperience::dialog::SpeakingHandlerInterface> speakingHandler) {
    LX(DEBUG0, "");

    m_messageHandlerStore->createOrGet(controlReceiver);
    m_messageHandlerStore->createOrGet(listeningHandler);
    m_messageHandlerStore->createOrGet(thinkingHandler);
    m_messageHandlerStore->createOrGet(speakingHandler);

    auto packagedArguments = utils::PayloadPackager::packageReferenceListPayload(
        controlReceiver, listeningHandler, thinkingHandler, speakingHandler);

    auto message = multiAgentExperience::ipc::messaging::createMessage<models::dialog::DialogManagerFunctions, multiAgentExperience::ipc::messaging::ReferenceListPayload>(
        m_reference,
        models::dialog::DialogManagerFunctions::SET_ALL_HANDLERS,
        packagedArguments);

    m_sender->send(message);
}

void DialogManagerProxy::removeAllHandlers() {
    LX(DEBUG0, "");

    auto message = multiAgentExperience::ipc::messaging::createMessage(
        m_reference,
        models::dialog::DialogManagerFunctions::REMOVE_ALL_HANDLERS,
        multiAgentExperience::ipc::messaging::VoidPayload());

    m_sender->send(message);
}

void DialogManagerProxy::setControlReceiver(std::shared_ptr<multiAgentExperience::dialog::ControlReceiverInterface> receiver) {
    LX(DEBUG0, "");

    m_messageHandlerStore->createOrGet(receiver);

    auto packagedArguments = utils::PayloadPackager::packageReferencePayload(receiver);

    auto message = multiAgentExperience::ipc::messaging::createMessage<models::dialog::DialogManagerFunctions, multiAgentExperience::ipc::messaging::ReferencePayload>(
        m_reference,
        models::dialog::DialogManagerFunctions::SET_CONTROL_RECEIVER,
        packagedArguments);

    m_sender->send(message);
}

void DialogManagerProxy::removeControlReceiver() {
    LX(DEBUG0, "");

    auto message = multiAgentExperience::ipc::messaging::createMessage(
        m_reference,
        models::dialog::DialogManagerFunctions::REMOVE_CONTROL_RECEIVER,
        multiAgentExperience::ipc::messaging::VoidPayload());

    m_sender->send(message);
}

void DialogManagerProxy::setListeningHandler(std::shared_ptr<multiAgentExperience::dialog::ListeningHandlerInterface> handler) {
    LX(DEBUG0, "");

    m_messageHandlerStore->createOrGet(handler);

    auto packagedArguments = utils::PayloadPackager::packageReferencePayload(handler);

    auto message = multiAgentExperience::ipc::messaging::createMessage<models::dialog::DialogManagerFunctions, multiAgentExperience::ipc::messaging::ReferencePayload>(
        m_reference,
        models::dialog::DialogManagerFunctions::SET_LISTENING_HANDLER,
        packagedArguments);

    m_sender->send(message);
}

void DialogManagerProxy::removeListeningHandler() {
    LX(DEBUG0, "");

    auto message = multiAgentExperience::ipc::messaging::createMessage(
        m_reference,
        models::dialog::DialogManagerFunctions::REMOVE_LISTENING_HANDLER,
        multiAgentExperience::ipc::messaging::VoidPayload());

    m_sender->send(message);
}

void DialogManagerProxy::setThinkingHandler(std::shared_ptr<multiAgentExperience::dialog::ThinkingHandlerInterface> handler) {
    LX(DEBUG0, "");

    m_messageHandlerStore->createOrGet(handler);

    auto packagedArguments = utils::PayloadPackager::packageReferencePayload(handler);

    auto message = multiAgentExperience::ipc::messaging::createMessage<models::dialog::DialogManagerFunctions, multiAgentExperience::ipc::messaging::ReferencePayload>(
        m_reference,
        models::dialog::DialogManagerFunctions::SET_THINKING_HANDLER,
        packagedArguments);

    m_sender->send(message);
}

void DialogManagerProxy::removeThinkingHandler() {
    LX(DEBUG0, "");

    auto message = multiAgentExperience::ipc::messaging::createMessage(
        m_reference,
        models::dialog::DialogManagerFunctions::REMOVE_THINKING_HANDLER,
        multiAgentExperience::ipc::messaging::VoidPayload());

    m_sender->send(message);
}

void DialogManagerProxy::setSpeakingHandler(std::shared_ptr<multiAgentExperience::dialog::SpeakingHandlerInterface> handler) {
    LX(DEBUG0, "");

    m_messageHandlerStore->createOrGet(handler);

    auto packagedArguments = utils::PayloadPackager::packageReferencePayload(handler);

    auto message = multiAgentExperience::ipc::messaging::createMessage<models::dialog::DialogManagerFunctions, multiAgentExperience::ipc::messaging::ReferencePayload>(
        m_reference,
        models::dialog::DialogManagerFunctions::SET_SPEAKING_HANDLER,
        packagedArguments);

    m_sender->send(message);
}

void DialogManagerProxy::removeSpeakingHandler() {
    LX(DEBUG0, "");

    auto message = multiAgentExperience::ipc::messaging::createMessage(
        m_reference,
        models::dialog::DialogManagerFunctions::REMOVE_SPEAKING_HANDLER,
        multiAgentExperience::ipc::messaging::VoidPayload());

    m_sender->send(message);
}

} // namespace dialog
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience