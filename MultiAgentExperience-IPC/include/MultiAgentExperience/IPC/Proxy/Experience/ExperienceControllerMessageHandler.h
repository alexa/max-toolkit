/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_EXPERIENCECONTROLLERMESSAGEHANDLER_H
#define MULTIAGENTEXPERIENCE_IPC_EXPERIENCECONTROLLERMESSAGEHANDLER_H

#include <MultiAgentExperience/IPC/Messaging/Message.h>
#include <MultiAgentExperience/IPC/Messaging/StringPayload.h>
#include <MultiAgentExperience/IPC/Messaging/VoidMessageTypes.h>

#include <MultiAgentExperience/Experience/ExperienceControllerInterface.h>

#include "MultiAgentExperience/IPC/Models/Experience/ExperienceControllerModel.h"
#include "MultiAgentExperience/IPC/Transport/MessageHandler.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace experience {
class ExperienceControllerMessageHandler : public transport::MessageHandler {
public:
    explicit ExperienceControllerMessageHandler(
            const multiAgentExperience::ipc::messaging::Reference& reference,
            std::shared_ptr<::multiAgentExperience::experience::ExperienceControllerInterface>
                experienceController);

    /// method for @c startExperience()
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::experience::ExperienceControllerFunctions,
        multiAgentExperience::ipc::messaging::StringPayload>& message);

    /// method for @c endExperience() & invalidate()
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::experience::ExperienceControllerFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message);

private:
    std::shared_ptr<::multiAgentExperience::experience::ExperienceControllerInterface> m_experienceController;
};

} // namespace experience
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_EXPERIENCECONTROLLERMESSAGEHANDLER_H
