/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_ACTIVITYHANDLERMESSAGEHANDLER_H
#define MULTIAGENTEXPERIENCE_IPC_ACTIVITYHANDLERMESSAGEHANDLER_H


#include <utility>
#include <memory>

#include <MultiAgentExperience/IPC/Messaging/ReferencePayload.h>
#include <MultiAgentExperience/IPC/Messaging/StringPayload.h>
#include <MultiAgentExperience/IPC/Messaging/MessageUtils.h>
#include <MultiAgentExperience/IPC/Messaging/Message.h>
#include <MultiAgentExperience/Activity/ActivityFocus.h>
#include <MultiAgentExperience/Activity/ActivityHandlerInterface.h>

#include "MultiAgentExperience/IPC/Models/Activity/ActivityHandlerModel.h"
#include "MultiAgentExperience/IPC/Transport/MessageSender.h"
#include "MultiAgentExperience/IPC/Transport/MessageHandler.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {

class MessageHandlerStore;

namespace activity {
class ActivityHandlerMessageHandler : public transport::MessageHandler {
public:
    explicit ActivityHandlerMessageHandler(
            const multiAgentExperience::ipc::messaging::Reference& reference,
            std::shared_ptr<transport::MessageSender> sender,
            std::shared_ptr<proxy::MessageHandlerStore> messageHandlerStore,
            std::shared_ptr<multiAgentExperience::activity::ActivityHandlerInterface> handler);

    void handle(
            const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityHandlerFunctions,
                    multiAgentExperience::ipc::messaging::VoidPayload>& message
    );

    void handle(
            const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityHandlerFunctions,
                    multiAgentExperience::ipc::messaging::ReferenceListPayload>& message
    );

    void handle(
            const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityHandlerFunctions,
                    multiAgentExperience::ipc::messaging::EnumTuplePayload<multiAgentExperience::activity::ActivityFocus,
                            multiAgentExperience::activity::MixingBehavior>>& message);

private:
    std::shared_ptr<transport::MessageSender> m_sender;
    std::shared_ptr<proxy::MessageHandlerStore> m_messageHandlerStore;
    std::shared_ptr<multiAgentExperience::activity::ActivityHandlerInterface> m_handler;
    const unsigned int ACTIVITY_CONTROLLER = 0;
    const unsigned int CONTROL_REGISTRY = 1;
    const unsigned int EXPERIENCE_CONTROL = 2;
};

} // namespace activity
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_ACTIVITYHANDLERMESSAGEHANDLER_H
