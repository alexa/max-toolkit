/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_THINKINGHANDLERMESSAGEHANDLER_H
#define MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_THINKINGHANDLERMESSAGEHANDLER_H

#include <utility>

#include <MultiAgentExperience/IPC/Messaging/MessageUtils.h>
#include <MultiAgentExperience/Dialog/ThinkingHandlerInterface.h>

#include "MultiAgentExperience/IPC/Models/Dialog/ThinkingHandlerModel.h"
#include "MultiAgentExperience/IPC/Transport/MessageHandler.h"
#include "MultiAgentExperience/IPC/Transport/MessageSender.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace dialog {

class ThinkingHandlerMessageHandler : public transport::MessageHandler {

public:
    ThinkingHandlerMessageHandler(
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<transport::MessageSender> sender,
        std::shared_ptr<multiAgentExperience::dialog::ThinkingHandlerInterface> handler);

    /**
     * Responsible for handling the requests sent by the @c ThinkingHandlerProxy. Invokes the respective
     * @c ThinkingHandlerInterface::onStartThinking method.
     *
     * @param message The message sent by the proxy. This should contain a ReferencePayload.
     */
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::ThinkingHandlerFunctions,
        multiAgentExperience::ipc::messaging::ReferencePayload>& message);

    /**
     * Responsible for handling the requests sent by the @c ThinkingHandlerProxy. Invokes the respective
     * @c ThinkingHandlerInterface::onStopThinking method.
     *
     * @param message The message sent by the proxy. This should contain a VoidPayload.
     */
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::ThinkingHandlerFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message);
    /// @}

private:
    std::shared_ptr<transport::MessageSender> m_sender;
    std::shared_ptr<multiAgentExperience::dialog::ThinkingHandlerInterface> m_handler;
};

} // namespace dialog
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_THINKINGHANDLERMESSAGEHANDLER_H
