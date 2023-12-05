/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_DIALOGREQUESTMESSAGEHANDLER_H
#define MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_DIALOGREQUESTMESSAGEHANDLER_H

#include <memory>
#include <utility>

#include <MultiAgentExperience/IPC/Messaging/Reference.h>
#include <MultiAgentExperience/IPC/Messaging/MessageUtils.h>
#include <MultiAgentExperience/IPC/Messaging/Message.h>
#include <MultiAgentExperience/Dialog/DialogRequestInterface.h>
#include <MultiAgentExperience/IPC/Messaging/ReferencePayload.h>

#include "MultiAgentExperience/IPC/Models/Dialog/DialogRequestModel.h"
#include "MultiAgentExperience/IPC/Proxy/Dialog/DialogControllerProxy.h"
#include "MultiAgentExperience/IPC/Transport/MessageHandler.h"
#include "MultiAgentExperience/IPC/Transport/MessageSender.h"
#include "MultiAgentExperience/IPC/Transport/TransportResponder.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {

class MessageHandlerStore;

namespace dialog {

/**
 * Responsible for handling requests for APIs in @c DialogRequestInterface. Each method handles a request, extracts the payload
 * and translates it into a DialogRequestInterface API call. Proxy objects are used for non-primitive message types.
 */
class DialogRequestMessageHandler : public multiAgentExperience::ipc::transport::MessageHandler {

public:
    DialogRequestMessageHandler(
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<transport::MessageSender> sender,
        std::shared_ptr<proxy::MessageHandlerStore> messageHandlerStore,
        std::shared_ptr<::multiAgentExperience::dialog::DialogRequestInterface> dialogRequest);

    /// For @c onDenied, @c onError
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctions,
        multiAgentExperience::ipc::messaging::StringPayload>& message);

    /// For @c onDialogStarted method
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctions,
        multiAgentExperience::ipc::messaging::ReferencePayload>& message);

    /// For @c onDialogStopped
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message);

    /**
     * Used by MAX library to handle an agent request (for @c getDialogBargeInPriority)
     *
     * @param message The message object sent by the agent in the request.
     * @param replyTo The transport responder object. We use this object to send back the response (DialogBargeInPriority enum value)
     * since we are handling a synchronous request.
     */
    void handle(
        const multiAgentExperience::ipc::messaging::Message<
            models::dialog::DialogRequestFunctionGetDialogBargeInPriority, multiAgentExperience::ipc::messaging::VoidPayload>& message,
        std::shared_ptr<transport::TransportResponder<
            models::dialog::DialogRequestFunctionReturns, multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::dialog::DialogBargeInPriority>>> replyTo);

    /// THe handle method for DialogRequestFunctionReturns is implemented in MessageRouter.

private:
    std::shared_ptr<transport::MessageSender> m_sender;
    std::shared_ptr<proxy::MessageHandlerStore> m_messageHandlerStore;
    std::shared_ptr<multiAgentExperience::dialog::DialogRequestInterface> m_dialogRequest;
};

} // namespace dialog
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_DIALOGREQUESTMESSAGEHANDLER_H
