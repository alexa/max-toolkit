/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#include "MultiAgentExperience/IPC/Proxy/Dialog/ControlReceiverProxy.h"

#include <sstream>

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "MultiAgentExperience/IPC/Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace dialog {

static const std::string MODULE_TAG("ControlReceiverProxy");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ControlReceiverProxy::ControlReceiverProxy(
    multiAgentExperience::ipc::messaging::Reference reference,
    std::shared_ptr<transport::MessageSender> sender,
    std::shared_ptr<MessageHandlerStore> messageHandlerStore):
        MaxIpcComponentsBaseProxy(std::move(reference), transport::MaxApiType::CONTROL_RECEIVER, std::move(sender)),
        m_messageHandlerStore{std::move(messageHandlerStore)} {
}

void ControlReceiverProxy::onControlsReceived(
    std::shared_ptr<multiAgentExperience::dialog::StartListeningCallback> startListeningCallback,
    std::set<multiAgentExperience::control::ControlType> controls) {
    std::stringstream ss;
    ss << "details:"
       << " controls=" << multiAgentExperience::ipc::utils::toString(controls);
    LX(DEBUG0, ss.str());

     auto startListeningCallbackHandler = m_messageHandlerStore->createOrGet(startListeningCallback);
     auto controlsReceiverPayload = messaging::dialog::ControlReceiverPayload(
                                         startListeningCallbackHandler->getReference(),
                                         controls);

    auto message = multiAgentExperience::ipc::messaging::createMessage<models::dialog::ControlReceiverFunctions, messaging::dialog::ControlReceiverPayload>(
        m_reference,
        models::dialog::ControlReceiverFunctions::ON_CONTROLS_RECEIVED,
        controlsReceiverPayload);

    m_sender->send(message);
}

} // namespace dialog
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience
