/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_DIALOGCONTROLLERMESSAGEHANDLER_H
#define MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_DIALOGCONTROLLERMESSAGEHANDLER_H

#include <utility>

#include <MultiAgentExperience/IPC/Messaging/MessageUtils.h>
#include <MultiAgentExperience/IPC/Messaging/EnumPayload.h>
#include <MultiAgentExperience/IPC/Messaging/VoidMessageTypes.h>
#include <MultiAgentExperience/Dialog/DialogControllerInterface.h>

#include "MultiAgentExperience/IPC/Models/Dialog/DialogControllerModel.h"
#include "MultiAgentExperience/IPC/Transport/MessageHandler.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace dialog {

class DialogControllerMessageHandler : public transport::MessageHandler {

public:
    DialogControllerMessageHandler(
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> controller);

    /**
     * Responsible for handling the requests sent by the @c DialogControllerProxy. Invokes the respective
     * @c DialogControllerInterface methods.
     *
     * @param message The message sent by the proxy. This should contain a VoidPayload.
     */
    void handle(
        const multiAgentExperience::ipc::messaging::Message<
            models::dialog::DialogControllerFunctions,
            multiAgentExperience::ipc::messaging::VoidPayload>& message);

    /**
     * Responsible for handling the requests sent by the @c DialogControllerProxy. Invokes the respective
     * @c DialogControllerInterface methods - @c invokeControlAndStartSpeaking and @c stopAndInvokeControl.
     *
     * @param message The message sent by the proxy. This should contain a EnumPayload (of @c ControlType).
     */
    void handle(
        const multiAgentExperience::ipc::messaging::Message<
            models::dialog::DialogControllerFunctions,
            multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::control::ControlType>>& message);

private:
    std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> m_controller;
};

} // namespace dialog
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_DIALOGCONTROLLERMESSAGEHANDLER_H
