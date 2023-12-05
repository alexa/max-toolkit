/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/IPC/Proxy/Control/ControlRegistryMessageHandler.h"

#include <sstream>

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "MultiAgentExperience/IPC/Proxy/MessageHandlerStore.h"
#include "MultiAgentExperience/IPC/Proxy/Control/ControlProxy.h"
#include "MultiAgentExperience/IPC/Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace control {

static const std::string MODULE_TAG("ControlRegistryMessageHandler");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ControlRegistryMessageHandler::ControlRegistryMessageHandler(
    const multiAgentExperience::ipc::messaging::Reference& reference,
    std::shared_ptr<transport::MessageSender> sender,
    std::shared_ptr<multiAgentExperience::control::ControlRegistryInterface> controlRegistry) :
    multiAgentExperience::ipc::transport::MessageHandler(reference),
    m_sender{sender},
    m_controlRegistry{std::move(controlRegistry)}{
}

void ControlRegistryMessageHandler::handle(
    const multiAgentExperience::ipc::messaging::Message<models::control::ControlRegistryFunctions,
    multiAgentExperience::ipc::messaging::control::ControlRegistryPayload>& message) {
    LX(DEBUG0, ipc::utils::toString(message.getFunction()));

    std::set<std::shared_ptr<multiAgentExperience::control::Control>> controls;
    switch (message.getFunction()) {
        case models::control::ControlRegistryFunctions::UPDATE:
            update(message.getPayload());
            break;
        default:
            LX(ERROR, "Wrong function passed: " + ipc::utils::toString(message.getFunction()));
    }
}

void ControlRegistryMessageHandler::update(
    const multiAgentExperience::ipc::messaging::control::ControlRegistryPayload& payload) {
    auto controls = getControlsFromReferences(payload.m_referenceControlTypesList);

    std::stringstream ss;
    ss << "Call to ControlRegistryInterface::update. details:"
       << " controls=" << multiAgentExperience::ipc::utils::toString(controls);
    LX(DEBUG0, ss.str());
    m_controlRegistry->update(controls);
}

std::set<std::shared_ptr<multiAgentExperience::control::Control>>
ControlRegistryMessageHandler::getControlsFromReferences(const std::list<std::tuple<
    multiAgentExperience::ipc::messaging::Reference,
    multiAgentExperience::control::ControlType>>& referenceControlTypesList) {
    LX(DEBUG3, "");

    std::set<std::shared_ptr<multiAgentExperience::control::Control>> controls;
    for(auto referenceControlTypeTuple : referenceControlTypesList) {
        auto control = std::make_shared<multiAgentExperience::ipc::proxy::control::ControlProxy>(
            std::get<0>(referenceControlTypeTuple),
            m_sender,
            std::get<1>(referenceControlTypeTuple));
        controls.insert(control);
    }
    return controls;
}

} // namespace control
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience