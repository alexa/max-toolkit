/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/IPC/Proxy/Activity/ActivityControllerMessageHandler.h"

#include "MultiAgentExperience/IPC/Utils/ConversionUtils.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace activity {

static const std::string MODULE_TAG("ActivityControllerMessageHandler");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ActivityControllerMessageHandler::ActivityControllerMessageHandler(
        const multiAgentExperience::ipc::messaging::Reference& reference,
        std::shared_ptr<multiAgentExperience::activity::ActivityControllerInterface> controller):
        multiAgentExperience::ipc::transport::MessageHandler(reference),
        m_controller{std::move(controller)} {}

void ActivityControllerMessageHandler::handle(
        const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityControllerFunctions,
                multiAgentExperience::ipc::messaging::VoidPayload>& message)  {
    LX(DEBUG0, ipc::utils::toString(message.getFunction()));
    if (models::activity::ActivityControllerFunctions::STOP == message.getFunction()) {
        m_controller->stop();
    } else {
        LX(ERROR, "Wrong function passed: " + ipc::utils::toString(message.getFunction()));
    }
}

} // namespace activity
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience