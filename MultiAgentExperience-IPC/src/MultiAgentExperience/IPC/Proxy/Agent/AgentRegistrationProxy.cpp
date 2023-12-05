/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "MultiAgentExperience/IPC/Models/Agent/AgentRegistrationModel.h"
#include "MultiAgentExperience/IPC/Proxy/Agent/AgentRegistrationProxy.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace agent {

static const std::string MODULE_TAG("AgentRegistrationProxy");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

AgentRegistrationProxy::AgentRegistrationProxy(
    multiAgentExperience::ipc::messaging::Reference reference,
    std::shared_ptr<transport::MessageSender> sender,
    std::shared_ptr<MessageHandlerStore> messageHandlerStore) :
        m_sender{std::move(sender)},
        m_reference{std::move(reference)},
        m_messageHandlerStore{std::move(messageHandlerStore)} {}

void AgentRegistrationProxy::onReady(
    std::shared_ptr<multiAgentExperience::common::OnCompletionCallbackInterface>onCompletionCallback,
    std::shared_ptr<multiAgentExperience::activity::ActivityManagerInterface> activityManager,
    std::shared_ptr<multiAgentExperience::dialog::DialogManagerInterface> dialogManager,
    std::shared_ptr<multiAgentExperience::experience::StaticExperienceManagerInterface> staticExperienceManager) {

    /// Create MessageHandlers for the respective parameters passed
    m_messageHandlerStore->createOrGet(onCompletionCallback);
    m_messageHandlerStore->createOrGet(activityManager);
    m_messageHandlerStore->createOrGet(dialogManager);
    m_messageHandlerStore->createOrGet(staticExperienceManager);

    auto packagedArguments = utils::PayloadPackager::packageReferenceListPayload
        (onCompletionCallback, activityManager, dialogManager, staticExperienceManager);

    auto message = multiAgentExperience::ipc::messaging::createMessage<models::agent::AgentRegistrationFunctions,
        multiAgentExperience::ipc::messaging::ReferenceListPayload>(
        m_reference,
        models::agent::AgentRegistrationFunctions::ON_READY,
        packagedArguments);

    m_sender->send(message);
}

actor::ActorId AgentRegistrationProxy::getId() {
    LX(DEBUG0, "");

    /// This is the request message that may be used by MAX library to retrieve the @c ActorId from
    /// the @c AgentRegistrationInterface object that it receives.
    auto message = multiAgentExperience::ipc::messaging::createMessage(
        m_reference,
        models::agent::AgentRegistrationFunctionGetId::FUNCTION,
        multiAgentExperience::ipc::messaging::VoidPayload());

    /// MAX library expects a response (the @c ActorId), hence the type
    /// @c AgentRegistrationFunctionGetIdReturns is mentioned as the ReturnPayload for the send method.
    auto response = m_sender->send<models::agent::AgentRegistrationFunctionReturns,
        multiAgentExperience::ipc::messaging::StringPayload>(message);

    /// Since this API is a synchronous API, we should wait until we get an acknowledgment from the
    /// other side (The Agent)
    auto status = response.wait_for(config::SYNCHRONOUS_REQUEST_TIMEOUT);
    if (std::future_status::ready == status) {
        auto payload = response.get().getPayload();

        LX(DEBUG3, "Received ActorId : " + payload.m_value);

        return actor::ActorId(payload.m_value);
    } else {
        /// ToDo : we need to check if this could be a valid return value or not
        LX(DEBUG0, "Error while waiting for the sync API, returning default empty ActorId.");

        return actor::ActorId("");
    }
}

std::string AgentRegistrationProxy::getName() {
    LX(DEBUG0, "");

    /// This is the request message that may be used by MAX library to retrieve the @c ActorName
    /// from the @c AgentRegistrationInterface object that it receives.
    auto message = multiAgentExperience::ipc::messaging::createMessage(
        m_reference,
        models::agent::AgentRegistrationFunctionGetName::FUNCTION,
        multiAgentExperience::ipc::messaging::VoidPayload());

    /// MAX library expects a response (the @c std::string), hence the type
    /// @c AgentRegistrationFunctionReturns is mentioned as the ReturnPayload for the
    /// send method.
    auto response = m_sender->send<models::agent::AgentRegistrationFunctionReturns,
        multiAgentExperience::ipc::messaging::StringPayload>(message);

    /// Since this API is a synchronous API, we should wait until we get an acknowledgment
    /// from the other side (The Agent)
    auto status = response.wait_for(config::SYNCHRONOUS_REQUEST_TIMEOUT);
    if (std::future_status::ready == status) {
        auto payload = response.get().getPayload();

        LX(DEBUG3, "Received Agent Name : " + payload.m_value);

        return payload.m_value;
    } else {
        /// ToDo : we need to check if this could be a valid return value or not
        LX(DEBUG0, "Error while waiting for the sync API, returning default empty Actor name.");

        return std::string("");
    }
}

} // namespace agent
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience