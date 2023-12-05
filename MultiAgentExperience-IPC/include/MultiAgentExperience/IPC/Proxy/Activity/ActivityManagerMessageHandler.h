/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_ACTIVITYMANAGERMESSAGEHANDLER_H
#define MULTIAGENTEXPERIENCE_IPC_ACTIVITYMANAGERMESSAGEHANDLER_H


#include <utility>
#include <memory>
#include <MultiAgentExperience/IPC/Messaging/Reference.h>
#include <MultiAgentExperience/IPC/Messaging/MessageUtils.h>
#include <MultiAgentExperience/IPC/Messaging/Message.h>
#include <MultiAgentExperience/Activity/ActivityManagerInterface.h>
#include <MultiAgentExperience/IPC/Messaging/ReferencePayload.h>
#include "MultiAgentExperience/IPC/Transport/MessageSender.h"
#include "MultiAgentExperience/IPC/Models/Activity/ActivityManagerModel.h"
#include "MultiAgentExperience/IPC/Transport/MessageHandler.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {

class MessageHandlerStore;

namespace activity {
class ActivityManagerMessageHandler : public multiAgentExperience::ipc::transport::MessageHandler {
public:
    explicit ActivityManagerMessageHandler(
            const multiAgentExperience::ipc::messaging::Reference& reference,
            std::shared_ptr<transport::MessageSender> sender,
            std::shared_ptr<proxy::MessageHandlerStore> messageHandlerStore,
            std::shared_ptr<::multiAgentExperience::activity::ActivityManagerInterface> activityManager);

    void handle(
            const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityManagerFunctions,
                    multiAgentExperience::ipc::messaging::ReferencePayload>& message);

private:
    std::shared_ptr<transport::MessageSender> m_sender;
    std::shared_ptr<proxy::MessageHandlerStore> m_messageHandlerStore;
    std::shared_ptr<multiAgentExperience::activity::ActivityManagerInterface> m_activityManager;
};

} // namespace activity
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_ACTIVITYMANAGERMESSAGEHANDLER_H
