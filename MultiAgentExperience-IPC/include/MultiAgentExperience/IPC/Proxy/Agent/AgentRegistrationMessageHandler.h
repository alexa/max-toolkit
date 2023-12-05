/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_AGENTREGISTRATIONMESSAGEHANDLER_H
#define MULTIAGENTEXPERIENCE_IPC_AGENTREGISTRATIONMESSAGEHANDLER_H

#include <MultiAgentExperience/IPC/Messaging/Message.h>
#include <MultiAgentExperience/IPC/Messaging/ReferenceListPayload.h>
#include <MultiAgentExperience/IPC/Messaging/VoidMessageTypes.h>

#include <MultiAgentExperience/Agent/AgentRegistrationInterface.h>

#include "MultiAgentExperience/IPC/Models/Agent/AgentRegistrationModel.h"
#include "MultiAgentExperience/IPC/Transport/MessageHandler.h"
#include "MultiAgentExperience/IPC/Transport/MessageSender.h"
#include "MultiAgentExperience/IPC/Transport/TransportResponder.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {

class MessageHandlerStore;

namespace agent {
class AgentRegistrationMessageHandler : public transport::MessageHandler {
 public:
    explicit AgentRegistrationMessageHandler(
        const multiAgentExperience::ipc::messaging::Reference& reference,
        std::shared_ptr<multiAgentExperience::ipc::transport::MessageSender> sender,
        std::shared_ptr<multiAgentExperience::ipc::proxy::MessageHandlerStore> messageHandlerStore,
        std::shared_ptr<::multiAgentExperience::agent::AgentRegistrationInterface>
        agentRegistration);

    /// method for @c onReady
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::agent::AgentRegistrationFunctions,
                                                     multiAgentExperience::ipc::messaging::ReferenceListPayload>& message);

    /**
     * Used by Agent to handle a MAX request (for @c getId)
     *
     * @param message The message object sent by MAX in the request.
     * @param replyTo The transport responder object. We use this object to send back the
     * response (actor::ActorId which is sent as std::string in StringPayload value)
     * since we are handling a synchronous request.
     */
    void handle(
        const multiAgentExperience::ipc::messaging::Message<
            models::agent::AgentRegistrationFunctionGetId, multiAgentExperience::ipc::messaging::VoidPayload>&
            message, std::shared_ptr<transport::TransportResponder<
            models::agent::AgentRegistrationFunctionReturns,
            multiAgentExperience::ipc::messaging::StringPayload>> replyTo);

    /**
     * Used by Agent to handle a MAX request (for @c getName)
     *
     * @param message The message object sent by MAX in the request.
     * @param replyTo The transport responder object. We use this object to send back the
     * response (actor::ActorId which is sent as std::string in StringPayload value)
     * since we are handling a synchronous request.
     */
    void handle(
        const multiAgentExperience::ipc::messaging::Message<
        models::agent::AgentRegistrationFunctionGetName, multiAgentExperience::ipc::messaging::VoidPayload>&
        message, std::shared_ptr<transport::TransportResponder<models::agent::AgentRegistrationFunctionReturns,
        multiAgentExperience::ipc::messaging::StringPayload>> replyTo);

    /// The handle method for AgentRegistrationFunctionReturns is implemented in MessageRouter.

 private:
    std::shared_ptr<transport::MessageSender> m_sender;
    std::shared_ptr<proxy::MessageHandlerStore> m_messageHandlerStore;
    std::shared_ptr<::multiAgentExperience::agent::AgentRegistrationInterface> m_agentRegistration;
};

} // namespace agent
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif // MULTIAGENTEXPERIENCE_IPC_AGENTREGISTRATIONMESSAGEHANDLER_H