/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/IPC/Proxy/Dialog/ControlReceiverMessageHandler.h"

#include <sstream>

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "MultiAgentExperience/IPC/Proxy/Dialog/StartListeningCallbackProxy.h"
#include "MultiAgentExperience/IPC/Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace dialog {

static const std::string MODULE_TAG("ControlReceiverMessageHandler");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ControlReceiverMessageHandler::ControlReceiverMessageHandler(
    const multiAgentExperience::ipc::messaging::Reference& reference,
    std::shared_ptr<transport::MessageSender> sender,
    std::shared_ptr<multiAgentExperience::dialog::ControlReceiverInterface> controlReceiver) :
    multiAgentExperience::ipc::transport::MessageHandler(reference),
    m_sender{sender},
    m_controlReceiver{std::move(controlReceiver)}{
}

void ControlReceiverMessageHandler::handle(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::ControlReceiverFunctions,
    messaging::dialog::ControlReceiverPayload>& message) {
    LX(DEBUG0, ipc::utils::toString(message.getFunction()));

    switch (message.getFunction()) {
        case models::dialog::ControlReceiverFunctions::ON_CONTROLS_RECEIVED:
            onControlsReceived(message.getPayload());
            break;
        default:
            LX(ERROR, "Wrong function passed: " + ipc::utils::toString(message.getFunction()));
    }
}

void ControlReceiverMessageHandler::onControlsReceived(const messaging::dialog::ControlReceiverPayload& payload) {
    std::shared_ptr<multiAgentExperience::dialog::StartListeningCallback> startListeningCallbackProxy =
        std::make_shared<multiAgentExperience::ipc::proxy::dialog::StartListeningCallbackProxy>(
            payload.m_reference,
            m_sender);
    std::set<multiAgentExperience::control::ControlType> controls;
    for(auto control : payload.m_controlTypes) {
        controls.insert(control);
    }

    std::stringstream ss;
    ss << "Call to ControlReceiverInterface::onControlsReceived. details:"
       << " controls=" << multiAgentExperience::ipc::utils::toString(controls);
    LX(DEBUG0, ss.str());
    m_controlReceiver->onControlsReceived(
        startListeningCallbackProxy,
        controls);
}

} // namespace dialog
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience
