/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_ACTIVITYCONTROLLERMESSAGEHANDLER_H
#define MULTIAGENTEXPERIENCE_IPC_ACTIVITYCONTROLLERMESSAGEHANDLER_H

#include <memory>
#include <MultiAgentExperience/IPC/Messaging/VoidMessageTypes.h>
#include <MultiAgentExperience/Activity/ActivityControllerInterface.h>

#include "MultiAgentExperience/IPC/Transport/MessageHandler.h"
#include "MultiAgentExperience/IPC/Models/Activity/ActivityControllerModel.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace activity {
class ActivityControllerMessageHandler : public transport::MessageHandler {
public:
    explicit ActivityControllerMessageHandler(
            const multiAgentExperience::ipc::messaging::Reference& reference,
            std::shared_ptr<multiAgentExperience::activity::ActivityControllerInterface> controller);

    void handle(
            const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityControllerFunctions,
                    multiAgentExperience::ipc::messaging::VoidPayload>& message);

private:
    std::shared_ptr<multiAgentExperience::activity::ActivityControllerInterface> m_controller;

};

} // namespace activity
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_ACTIVITYCONTROLLERMESSAGEHANDLER_H
