/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/IPC/Proxy/MessageHandlerStore.h"
#include "MultiAgentExperience/IPC/Proxy/Activity/ActivityRequestProxy.h"
#include "MultiAgentExperience/IPC/Proxy/Activity/ActivityManagerMessageHandler.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "MultiAgentExperience/IPC/Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace activity {

static const std::string MODULE_TAG("ActivityManagerMessageHandler");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ActivityManagerMessageHandler::ActivityManagerMessageHandler(
        const multiAgentExperience::ipc::messaging::Reference& reference,
        std::shared_ptr<transport::MessageSender> sender,
        std::shared_ptr<proxy::MessageHandlerStore> messageHandlerStore,
        std::shared_ptr<::multiAgentExperience::activity::ActivityManagerInterface> activityManager) :
        MessageHandler(reference),
        m_sender{std::move(sender)},
        m_messageHandlerStore{std::move(messageHandlerStore)},
        m_activityManager{std::move(activityManager)} {
}

void ActivityManagerMessageHandler::handle(
        const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityManagerFunctions,
                multiAgentExperience::ipc::messaging::ReferencePayload>& message) {

    LX(DEBUG0, ipc::utils::toString(message.getFunction()));

    auto request =
            std::make_shared<activity::ActivityRequestProxy>(
                    nullptr,
                    message.getPayload().m_reference,
                    m_sender,
                    m_messageHandlerStore);
    switch (message.getFunction()) {
        case models::activity::ActivityManagerFunctions::REQUEST:
            m_activityManager->request(request);
            break;
        case models::activity::ActivityManagerFunctions::STOP:
            m_activityManager->stop(request);
            break;
        default:
            LX(ERROR, "Wrong function passed: " + ipc::utils::toString(message.getFunction()));
    }
}

} // namespace activity
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience