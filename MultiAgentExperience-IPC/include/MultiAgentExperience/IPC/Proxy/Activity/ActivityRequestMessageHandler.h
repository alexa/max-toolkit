/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_ACTIVITYREQUESTMESSAGEHANDLER_H
#define MULTIAGENTEXPERIENCE_IPC_ACTIVITYREQUESTMESSAGEHANDLER_H

#include <memory>
#include <utility>

#include "MultiAgentExperience/IPC/Models/Activity/ActivityRequestModel.h"
#include "MultiAgentExperience/IPC/Transport/MessageHandler.h"
#include "MultiAgentExperience/IPC/Transport/TransportResponder.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {

class MessageHandlerStore;

namespace activity {
class ActivityRequestMessageHandler : public transport::MessageHandler {
public:
    ActivityRequestMessageHandler(
            multiAgentExperience::ipc::messaging::Reference reference,
            std::shared_ptr<MessageHandlerStore> messageHandlerStore,
            std::shared_ptr<multiAgentExperience::activity::ActivityRequestInterface> request);

    void handle(
            const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestGetType, multiAgentExperience::ipc::messaging::VoidPayload>& message,
            const std::shared_ptr<transport::TransportResponder<
                    models::activity::ActivityRequestFunctionReturns,
                    multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::activity::ActivityType>>>
            &replyTo);

    void handle(
            const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestGetHandler, multiAgentExperience::ipc::messaging::VoidPayload>& message,
            const std::shared_ptr<transport::TransportResponder<
                    models::activity::ActivityRequestFunctionReturns,
                    multiAgentExperience::ipc::messaging::ReferencePayload>> &replyTo);

    void handle(
            const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestGetMixabilityType, multiAgentExperience::ipc::messaging::VoidPayload>& message,
            const std::shared_ptr<transport::TransportResponder<
                    models::activity::ActivityRequestFunctionReturns,
                    multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::activity::MixabilityType>>>
            &replyTo);

private:
    std::shared_ptr<MessageHandlerStore> m_messageHandlerStore;
    std::shared_ptr<multiAgentExperience::activity::ActivityRequestInterface> m_request;
};

} // namespace activity
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_ACTIVITYREQUESTMESSAGEHANDLER_H
