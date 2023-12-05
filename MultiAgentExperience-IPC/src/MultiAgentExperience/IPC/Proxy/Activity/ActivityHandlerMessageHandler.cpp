/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/IPC/Proxy/Activity/ActivityControllerProxy.h"
#include "MultiAgentExperience/IPC/Proxy/Activity/ActivityHandlerMessageHandler.h"
#include "MultiAgentExperience/IPC/Proxy/Control/ControlRegistryProxy.h"
#include "MultiAgentExperience/IPC/Proxy/Experience/ExperienceControllerProxy.h"
#include "MultiAgentExperience/IPC/Proxy/MessageHandlerStore.h"
#include "MultiAgentExperience/IPC/Utils/ConversionUtils.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace activity {

static const std::string MODULE_TAG("ActivityHandlerMessageHandler");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ActivityHandlerMessageHandler::ActivityHandlerMessageHandler(
        const multiAgentExperience::ipc::messaging::Reference& reference,
        std::shared_ptr<transport::MessageSender> sender,
        std::shared_ptr<proxy::MessageHandlerStore> messageHandlerStore,
        std::shared_ptr<multiAgentExperience::activity::ActivityHandlerInterface> handler):
        multiAgentExperience::ipc::transport::MessageHandler(reference),
        m_sender{std::move(sender)},
        m_messageHandlerStore{std::move(messageHandlerStore)},
        m_handler{std::move(handler)} {
}

void ActivityHandlerMessageHandler::handle(
        const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityHandlerFunctions,
                multiAgentExperience::ipc::messaging::VoidPayload>& message) {
    LX(DEBUG0, ipc::utils::toString(message.getFunction()));

    if (models::activity::ActivityHandlerFunctions::ON_DENIED == message.getFunction()) {
        m_handler->onDenied();
    } else if (models::activity::ActivityHandlerFunctions::ON_STOP == message.getFunction()) {
        m_handler->onStop();
    } else {
        LX(ERROR, "Wrong function passed: " + ipc::utils::toString(message.getFunction()));
    }
}

void ActivityHandlerMessageHandler::handle(
        const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityHandlerFunctions,
                multiAgentExperience::ipc::messaging::ReferenceListPayload>& message) {
    LX(DEBUG0, ipc::utils::toString(message.getFunction()));

    if (models::activity::ActivityHandlerFunctions::ON_GRANTED == message.getFunction()) {
        auto activityControllerReference = message.getPayload().m_references.at(ACTIVITY_CONTROLLER);
        auto controlRegistryReference = message.getPayload().m_references.at(CONTROL_REGISTRY);
        auto experienceControlReference = message.getPayload().m_references.at(EXPERIENCE_CONTROL);

        auto activityControllerProxy = std::make_shared<ActivityControllerProxy>(
                activityControllerReference, m_sender);
        auto controlRegistryProxy = std::make_shared<control::ControlRegistryProxy>(
                controlRegistryReference, m_sender, m_messageHandlerStore);
        auto experienceControlProxy = std::make_shared<experience::ExperienceControllerProxy>(
                experienceControlReference, m_sender);

        m_handler->onGranted(
                activityControllerProxy,
                controlRegistryProxy,
                experienceControlProxy);
    } else {
        LX(ERROR, "Wrong function passed: " + ipc::utils::toString(message.getFunction()));
    }
}

void ActivityHandlerMessageHandler::handle(
        const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityHandlerFunctions,
                multiAgentExperience::ipc::messaging::EnumTuplePayload<multiAgentExperience::activity::ActivityFocus,
                        multiAgentExperience::activity::MixingBehavior>>& message) {
    LX(DEBUG0, ipc::utils::toString(message.getFunction()));

    if (models::activity::ActivityHandlerFunctions::ON_FOCUS_CHANGED == message.getFunction()) {
        auto activityFocus = message.getPayload().m_value1;
        auto mixabilityBehavior = message.getPayload().m_value2;
        m_handler->onFocusStateChange(activityFocus, mixabilityBehavior);
    } else {
        LX(ERROR, "Wrong function passed: " + ipc::utils::toString(message.getFunction()));
    }
}

} // namespace activity
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience