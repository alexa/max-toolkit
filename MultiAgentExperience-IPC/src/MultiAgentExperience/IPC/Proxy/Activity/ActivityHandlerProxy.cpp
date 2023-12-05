/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/IPC/Proxy/MessageHandlerStore.h"
#include "MultiAgentExperience/IPC/Proxy/Activity/ActivityHandlerProxy.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace activity {

static const std::string MODULE_TAG("ActivityHandlerProxy");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ActivityHandlerProxy::ActivityHandlerProxy(
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<transport::MessageSender> sender,
        std::shared_ptr<MessageHandlerStore> messageHandlerStore) :
        MaxIpcComponentsBaseProxy(std::move(reference), transport::MaxApiType::ACTIVITY_HANDLER, std::move(sender)),
        m_messageHandlerStore{std::move(messageHandlerStore)} {
}

void ActivityHandlerProxy::onDenied() {
    LX(DEBUG0, "");
    auto message = multiAgentExperience::ipc::messaging::createMessage(
            m_reference,
            models::activity::ActivityHandlerFunctions::ON_DENIED,
            multiAgentExperience::ipc::messaging::VoidPayload());
    m_sender->send(message);
}

void ActivityHandlerProxy::onGranted(
        std::shared_ptr<multiAgentExperience::activity::ActivityControllerInterface> activityController,
        std::shared_ptr<multiAgentExperience::control::ControlRegistryInterface> controlRegistry,
        std::shared_ptr<multiAgentExperience::experience::ExperienceControllerInterface>
        experienceControl) {
    LX(DEBUG0, "");
    auto activityControllerMessageHandler = m_messageHandlerStore->createOrGet(activityController);
    auto controlRegistryMessageHandler = m_messageHandlerStore->createOrGet(controlRegistry);
    auto experienceControlMessageHandler= m_messageHandlerStore->createOrGet(experienceControl);

    auto packagedArguments = utils::PayloadPackager::packageReferenceListPayload(
            activityController,controlRegistry, experienceControl);
    auto message = multiAgentExperience::ipc::messaging::createMessage(
            m_reference, models::activity::ActivityHandlerFunctions::ON_GRANTED, packagedArguments);

    m_sender->send(message);
}

void ActivityHandlerProxy::onFocusStateChange(
        multiAgentExperience::activity::ActivityFocus focus,
        multiAgentExperience::activity::MixingBehavior behavior) {
    LX(DEBUG0, "");
    auto message = multiAgentExperience::ipc::messaging::createMessage(
            m_reference,
            models::activity::ActivityHandlerFunctions::ON_FOCUS_CHANGED,
            multiAgentExperience::ipc::messaging::EnumTuplePayload<multiAgentExperience::activity::ActivityFocus,
                    multiAgentExperience::activity::MixingBehavior>(focus, behavior));
    m_sender->send(message);
}

void ActivityHandlerProxy::onStop() {
    LX(DEBUG0, "");
    auto message = multiAgentExperience::ipc::messaging::createMessage(
            m_reference,
            models::activity::ActivityHandlerFunctions::ON_STOP,
            multiAgentExperience::ipc::messaging::VoidPayload());

    m_sender->send(message);
}

} // namespace activity
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience