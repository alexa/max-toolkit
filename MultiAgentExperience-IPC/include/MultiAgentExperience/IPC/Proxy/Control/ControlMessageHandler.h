/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_CONTROLMESSAGEHANDLER_H
#define MULTIAGENTEXPERIENCE_IPC_CONTROLMESSAGEHANDLER_H

#include <MultiAgentExperience/Control/Control.h>
#include <MultiAgentExperience/IPC/Messaging/Message.h>
#include <MultiAgentExperience/IPC/Messaging/VoidMessageTypes.h>
#include "MultiAgentExperience/IPC/Models/Control/ControlModel.h"
#include "MultiAgentExperience/IPC/Transport/MessageHandler.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace control {

class ControlMessageHandler : public transport::MessageHandler {
public:
    explicit ControlMessageHandler(
        const multiAgentExperience::ipc::messaging::Reference& reference,
        std::shared_ptr<multiAgentExperience::control::Control> control);

    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::control::ControlFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message);

private:
    void invokeTask();

    std::shared_ptr<multiAgentExperience::control::Control> m_control;
};

} // namespace control
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_CONTROLMESSAGEHANDLER_H
