/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/IPC/Proxy/Common/OnCompletionCallbackMessageHandler.h"

#include "MultiAgentExperience/IPC/Utils/ConversionUtils.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace common {

static const std::string MODULE_TAG("OnCompletionCallbackMessageHandler");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

OnCompletionCallbackMessageHandler::OnCompletionCallbackMessageHandler(
    const multiAgentExperience::ipc::messaging::Reference& reference,
    std::shared_ptr<::multiAgentExperience::common::OnCompletionCallbackInterface>
    onCompletionCallback) :
    multiAgentExperience::ipc::transport::MessageHandler(reference),
    m_onCompletionCallback{std::move(onCompletionCallback)} {

}

void OnCompletionCallbackMessageHandler::handle(const
multiAgentExperience::ipc::messaging::Message<models::common::OnCompletionCallbackFunctions,
multiAgentExperience::ipc::messaging::VoidPayload>& message) {
    LX(DEBUG0, ipc::utils::toString(message.getFunction()));

    if (models::common::OnCompletionCallbackFunctions::COMPLETED == message.getFunction()) {
        m_onCompletionCallback->completed();
    } else {
        LX(ERROR, "Wrong function passed: " + ipc::utils::toString(message.getFunction()));
    }
}

} // namespace common
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience