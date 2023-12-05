/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_STATICEXPERIENCEMANAGERMESSAGEHANDLER_H
#define MULTIAGENTEXPERIENCE_IPC_STATICEXPERIENCEMANAGERMESSAGEHANDLER_H

#include <MultiAgentExperience/IPC/Messaging/Message.h>
#include <MultiAgentExperience/IPC/Messaging/StringPayload.h>
#include <MultiAgentExperience/IPC/Messaging/StringIntTuplePayload.h>
#include <MultiAgentExperience/IPC/Messaging/VoidMessageTypes.h>

#include <MultiAgentExperience/Experience/StaticExperienceManagerInterface.h>

#include "MultiAgentExperience/IPC/Models/Experience/StaticExperienceManagerModel.h"
#include "MultiAgentExperience/IPC/Transport/MessageHandler.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace experience {
class StaticExperienceManagerMessageHandler : public transport::MessageHandler {
 public:
    explicit StaticExperienceManagerMessageHandler(
        const multiAgentExperience::ipc::messaging::Reference& reference,
        std::shared_ptr<::multiAgentExperience::experience::StaticExperienceManagerInterface>
        staticExperienceManager);

    /// method for @c addStaticExperience
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::experience::StaticExperienceManagerFunctions,
        multiAgentExperience::ipc::messaging::StringIntTuplePayload>& message);

    /// method for @c removeStaticExperience
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::experience::StaticExperienceManagerFunctions,
        multiAgentExperience::ipc::messaging::StringPayload>& message);

    /// method for @c removeAllStaticExperiences
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::experience::StaticExperienceManagerFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message);

 private:
    std::shared_ptr<::multiAgentExperience::experience::StaticExperienceManagerInterface>
    m_staticExperienceManager;
};

} // namespace experience
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif // MULTIAGENTEXPERIENCE_IPC_STATICEXPERIENCEMANAGERMESSAGEHANDLER_H