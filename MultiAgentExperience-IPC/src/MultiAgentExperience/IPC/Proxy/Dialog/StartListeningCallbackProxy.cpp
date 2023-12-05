/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#include "MultiAgentExperience/IPC/Proxy/Dialog/StartListeningCallbackProxy.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace dialog {

static const std::string MODULE_TAG("StartListeningCallbackProxy");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

StartListeningCallbackProxy::StartListeningCallbackProxy(
    multiAgentExperience::ipc::messaging::Reference reference,
    std::shared_ptr<transport::MessageSender> sender):
        /// The proxy class does not make use of the promise. Since the @c StartListeningCallback constructor
        /// requires a promise, we pass a dummy object here.
        multiAgentExperience::dialog::StartListeningCallback(std::promise<void>()),
        MaxIpcComponentsBaseProxy(std::move(reference), transport::MaxApiType::START_LISTENING_CALLBACK, std::move(sender)) {
}

void StartListeningCallbackProxy::startListening() {
    LX(DEBUG0, "");

    auto message = multiAgentExperience::ipc::messaging::createMessage(
        m_reference,
        models::dialog::StartListeningCallbackFunctions::START_LISTENING,
        multiAgentExperience::ipc::messaging::VoidPayload());

    m_sender->send(message);
}

} // namespace dialog
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience