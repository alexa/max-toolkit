/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_CONTROLRECEIVERMESSAGEHANDLER_H
#define MULTIAGENTEXPERIENCE_IPC_CONTROLRECEIVERMESSAGEHANDLER_H

#include <MultiAgentExperience/Dialog/ControlReceiverInterface.h>
#include <MultiAgentExperience/IPC/Messaging/Message.h>
#include "MultiAgentExperience/IPC/Messaging/Dialog/ControlReceiverPayload.h"
#include "MultiAgentExperience/IPC/Models/Dialog/ControlReceiverModel.h"
#include "MultiAgentExperience/IPC/Transport/MessageHandler.h"
#include "MultiAgentExperience/IPC/Transport/MessageSender.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace dialog {

class ControlReceiverMessageHandler : public transport::MessageHandler {
public:
    explicit ControlReceiverMessageHandler(
        const multiAgentExperience::ipc::messaging::Reference& reference,
        std::shared_ptr<transport::MessageSender> sender,
        std::shared_ptr<multiAgentExperience::dialog::ControlReceiverInterface> controlReceiver);

    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::ControlReceiverFunctions,
        messaging::dialog::ControlReceiverPayload>& message);

private:
    void onControlsReceived(const messaging::dialog::ControlReceiverPayload& payload);

    std::shared_ptr<transport::MessageSender> m_sender;
    std::shared_ptr<multiAgentExperience::dialog::ControlReceiverInterface> m_controlReceiver;
};

} // namespace dialog
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience


#endif //MULTIAGENTEXPERIENCE_IPC_CONTROLRECEIVERMESSAGEHANDLER_H
