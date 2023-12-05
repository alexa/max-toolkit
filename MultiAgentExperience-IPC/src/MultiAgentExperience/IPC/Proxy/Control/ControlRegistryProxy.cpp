/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#include "MultiAgentExperience/IPC/Proxy/Control/ControlRegistryProxy.h"

#include <sstream>

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "MultiAgentExperience/IPC/Messaging/Control/ControlRegistryPayload.h"
#include "MultiAgentExperience/IPC/Models/Control/ControlModel.h"
#include "MultiAgentExperience/IPC/Proxy/MessageHandlerStore.h"
#include "MultiAgentExperience/IPC/Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace control {

static const std::string MODULE_TAG("ControlRegistryProxy");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ControlRegistryProxy::ControlRegistryProxy(
    multiAgentExperience::ipc::messaging::Reference reference,
    std::shared_ptr<transport::MessageSender> sender,
    std::shared_ptr<MessageHandlerStore> messageHandlerStore):
        MaxIpcComponentsBaseProxy(std::move(reference), transport::MaxApiType::CONTROL_REGISTRY, std::move(sender)),
        m_messageHandlerStore{std::move(messageHandlerStore)} {
}

void ControlRegistryProxy::update(std::set<std::shared_ptr<multiAgentExperience::control::Control>> controls) {
    std::stringstream ss;
    ss << "details:"
       << " controls=" << multiAgentExperience::ipc::utils::toString(controls);
    LX(DEBUG0, ss.str());

    std::list<std::tuple<
        multiAgentExperience::ipc::messaging::Reference,
        multiAgentExperience::control::ControlType>> referenceControlTypesList;
        for (auto control: controls) {
            auto controlWrapper = m_messageHandlerStore->createOrGet(control);
            auto referenceControlTypeTuple =
                std::make_tuple(controlWrapper->getReference(),
                                control->type);
            referenceControlTypesList.push_back(referenceControlTypeTuple);
        }
        auto controlRegistryPayload = multiAgentExperience::ipc::messaging::control::ControlRegistryPayload(referenceControlTypesList);

        auto message = multiAgentExperience::ipc::messaging::createMessage<models::control::ControlRegistryFunctions, multiAgentExperience::ipc::messaging::control::ControlRegistryPayload>(
            m_reference,
            models::control::ControlRegistryFunctions::UPDATE,
            controlRegistryPayload);

        m_sender->send(message);
}

} // namespace control
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience