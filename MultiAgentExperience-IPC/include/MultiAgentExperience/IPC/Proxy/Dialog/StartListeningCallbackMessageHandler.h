/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_STARTLISTENINGCALLBACKMESSAGEHANDLER_H
#define MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_STARTLISTENINGCALLBACKMESSAGEHANDLER_H

#include <utility>

#include <MultiAgentExperience/IPC/Messaging/MessageUtils.h>
#include <MultiAgentExperience/Dialog/SpeakingHandlerInterface.h>

#include "MultiAgentExperience/IPC/Models/Dialog/SpeakingHandlerModel.h"
#include "MultiAgentExperience/IPC/Proxy/Utils/PayloadPackager.h"
#include "MultiAgentExperience/IPC/Transport/MessageHandler.h"
#include "MultiAgentExperience/IPC/Transport/MessageSender.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace dialog {

class StartListeningCallbackMessageHandler : public transport::MessageHandler {

public:
    StartListeningCallbackMessageHandler(
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<transport::MessageSender> sender,
        std::shared_ptr<multiAgentExperience::dialog::StartListeningCallback> startListeningCallback);

    /**
     * Responsible for handling the requests sent by the @c StartListeningCallbackProxy. Invokes the respective
     * @c StartListeningCallback::onStartListening method.
     *
     * @param message The message sent by the proxy. This should contain a VoidPayload.
     */
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::StartListeningCallbackFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message);
    /// @}

private:
    std::shared_ptr<transport::MessageSender> m_sender;
    std::shared_ptr<multiAgentExperience::dialog::StartListeningCallback> m_startListeningCallback;
};

} // namespace dialog
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_STARTLISTENINGCALLBACKMESSAGEHANDLER_H
