/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/IPC/Proxy/Activity/ActivityManagerProxy.h"
#include "MultiAgentExperience/IPC/Proxy/Agent/AgentRegistrationMessageHandler.h"
#include "MultiAgentExperience/IPC/Proxy/Dialog/DialogManagerProxy.h"
#include "MultiAgentExperience/IPC/Proxy/Common/OnCompletionCallbackProxy.h"
#include "MultiAgentExperience/IPC/Proxy/Experience/StaticExperienceManagerProxy.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "MultiAgentExperience/IPC/Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace agent {

static const std::string MODULE_TAG("AgentRegistrationMessageHandler");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

AgentRegistrationMessageHandler::AgentRegistrationMessageHandler(
    const multiAgentExperience::ipc::messaging::Reference& reference,
    std::shared_ptr<transport::MessageSender> sender,
    std::shared_ptr<proxy::MessageHandlerStore> messageHandlerStore,
    std::shared_ptr<::multiAgentExperience::agent::AgentRegistrationInterface> agentRegistration):
        multiAgentExperience::ipc::transport::MessageHandler(reference),
        m_sender{std::move(sender)},
        m_messageHandlerStore{std::move(messageHandlerStore)},
        m_agentRegistration{std::move(agentRegistration)} {}

void AgentRegistrationMessageHandler::handle(
    const multiAgentExperience::ipc::messaging::Message<models::agent::AgentRegistrationFunctions,
    multiAgentExperience::ipc::messaging::ReferenceListPayload>& message) {
    LX(DEBUG0, ipc::utils::toString(message.getFunction()));

    if (models::agent::AgentRegistrationFunctions::ON_READY == message.getFunction()) {

        auto references = message.getPayload().m_references;

        auto onCompletionCallback = std::make_shared<common::OnCompletionCallbackProxy>(
            message.getPayload().m_references.at(0), m_sender);

        auto activityManager = std::make_shared<activity::ActivityManagerProxy>(
            message.getPayload().m_references.at(1), m_sender, m_messageHandlerStore);

        auto dialogManager = std::make_shared<dialog::DialogManagerProxy>(
            message.getPayload().m_references.at(2), m_sender, m_messageHandlerStore);

        auto staticExperienceManager = std::make_shared<experience::StaticExperienceManagerProxy>(
            message.getPayload().m_references.at(3), m_sender);

        m_agentRegistration->onReady(onCompletionCallback, activityManager, dialogManager,
                                     staticExperienceManager);

    } else {
        LX(ERROR, "Wrong function passed: " + ipc::utils::toString(message.getFunction()));
    }
}

void AgentRegistrationMessageHandler::handle(
    const multiAgentExperience::ipc::messaging::Message<models::agent::AgentRegistrationFunctionGetId,
    multiAgentExperience::ipc::messaging::VoidPayload>& message,
    std::shared_ptr<transport::TransportResponder<models::agent
    ::AgentRegistrationFunctionReturns, multiAgentExperience::ipc::messaging::StringPayload>> replyTo) {
    LX(DEBUG0, "AgentRegistrationFunctionGetId::FUNCTION");
    if (models::agent::AgentRegistrationFunctionGetId::FUNCTION == message.getFunction()) {
        /// Retrieve the ActorId from the @c AgentRegistrationInterface object stored in this handler
        /// object
        auto actorId = m_agentRegistration->getId();

        /// Create a payload and send the ActorId value using the replyTo object
        auto payload = multiAgentExperience::ipc::messaging::StringPayload(actorId.get());

        replyTo->reply(payload);
    } else {
        LX(ERROR, "Wrong function passed");
    }
}

void AgentRegistrationMessageHandler::handle(
    const multiAgentExperience::ipc::messaging::Message<models::agent::AgentRegistrationFunctionGetName,
    multiAgentExperience::ipc::messaging::VoidPayload>& message,
    std::shared_ptr<transport::TransportResponder<models::agent::AgentRegistrationFunctionReturns,
    multiAgentExperience::ipc::messaging::StringPayload>> replyTo) {
    LX(DEBUG0, "AgentRegistrationFunctionGetName::FUNCTION");
    if (models::agent::AgentRegistrationFunctionGetName::FUNCTION == message.getFunction()) {
        /// Retrieve the Actor name from the @c AgentRegistrationInterface object stored in this
        /// handler object
        auto actorName = m_agentRegistration->getName();

        /// Create a payload and send the Actor name value using the replyTo object
        auto payload = multiAgentExperience::ipc::messaging::StringPayload(actorName);

        replyTo->reply(payload);
    } else {
        LX(ERROR, "Wrong function passed");
    }
}

} // namespace agent
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience