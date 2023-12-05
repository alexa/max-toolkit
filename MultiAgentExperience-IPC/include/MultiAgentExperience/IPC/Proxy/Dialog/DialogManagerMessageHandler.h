/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_DIALOGMANAGERMESSAGEHANDLER_H
#define MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_DIALOGMANAGERMESSAGEHANDLER_H

#include <utility>
#include <memory>

#include <MultiAgentExperience/IPC/Messaging/Reference.h>
#include <MultiAgentExperience/IPC/Messaging/MessageUtils.h>
#include <MultiAgentExperience/IPC/Messaging/Message.h>
#include <MultiAgentExperience/Dialog/DialogManagerInterface.h>
#include <MultiAgentExperience/IPC/Messaging/ReferencePayload.h>

#include "MultiAgentExperience/IPC/Models/Dialog/DialogManagerModel.h"
#include "MultiAgentExperience/IPC/Proxy/Dialog/DialogRequestProxy.h"
#include "MultiAgentExperience/IPC/Proxy/Dialog/ListeningHandlerProxy.h"
#include "MultiAgentExperience/IPC/Proxy/Dialog/ThinkingHandlerProxy.h"
#include "MultiAgentExperience/IPC/Proxy/Dialog/SpeakingHandlerProxy.h"
#include "MultiAgentExperience/IPC/Transport/MessageHandler.h"
#include "MultiAgentExperience/IPC/Transport/MessageSender.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {

class MessageHandlerStore;

namespace dialog {

/**
 * Responsible for handling requests for APIs in @c DialogManagerInterface. Each method handles a request, extracts the payload
 * and translates it into a DialogManagerInterface API call. Proxy objects are used for non-primitive message types.
 */
class DialogManagerMessageHandler : public multiAgentExperience::ipc::transport::MessageHandler {

public:
    DialogManagerMessageHandler(
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<transport::MessageSender> sender,
        std::shared_ptr<proxy::MessageHandlerStore> messageHandlerStore,
        std::shared_ptr<::multiAgentExperience::dialog::DialogManagerInterface> dialogManager);

    /// For @c request, @c stop, @c setControlReceiver, @c setListeningHandler, @c setThinkingHandler, @c setSpeakingHandler
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogManagerFunctions,
        multiAgentExperience::ipc::messaging::ReferencePayload>& message);

    /// For @c setAllHandlers method
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogManagerFunctions,
        multiAgentExperience::ipc::messaging::ReferenceListPayload>& message);

    /// For @c removeAllHandlers, @c removeControlReceiver, @c removeListeningHandler, @c removeThinkingHandler, @c removeSpeakingHandler
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogManagerFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message);

private:
    std::shared_ptr<transport::MessageSender> m_sender;
    std::shared_ptr<proxy::MessageHandlerStore> m_messageHandlerStore;
    std::shared_ptr<multiAgentExperience::dialog::DialogManagerInterface> m_dialogManager;
};
} // namespace dialog
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_DIALOGMANAGERMESSAGEHANDLER_H
