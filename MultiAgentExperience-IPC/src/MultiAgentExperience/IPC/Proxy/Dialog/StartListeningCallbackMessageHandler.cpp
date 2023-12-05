/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#include "MultiAgentExperience/IPC/Proxy/Dialog/StartListeningCallbackMessageHandler.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "MultiAgentExperience/IPC/Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace dialog {

static const std::string MODULE_TAG("StartListeningCallbackMessageHandler");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

StartListeningCallbackMessageHandler::StartListeningCallbackMessageHandler(
    multiAgentExperience::ipc::messaging::Reference reference,
    std::shared_ptr<transport::MessageSender> sender,
    std::shared_ptr<multiAgentExperience::dialog::StartListeningCallback> startListeningCallback):
        multiAgentExperience::ipc::transport::MessageHandler(std::move(reference)),
        m_sender{std::move(sender)},
        m_startListeningCallback{std::move(startListeningCallback)} {
}

void StartListeningCallbackMessageHandler::handle(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::StartListeningCallbackFunctions,
    multiAgentExperience::ipc::messaging::VoidPayload>& message) {
    LX(DEBUG0, ipc::utils::toString(message.getFunction()));

    switch (message.getFunction()) {
        case models::dialog::StartListeningCallbackFunctions::START_LISTENING:
            m_startListeningCallback->startListening();
            break;
        default:
            LX(ERROR, "Wrong function passed: " + ipc::utils::toString(message.getFunction()));
    }
}

} // namespace dialog
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience