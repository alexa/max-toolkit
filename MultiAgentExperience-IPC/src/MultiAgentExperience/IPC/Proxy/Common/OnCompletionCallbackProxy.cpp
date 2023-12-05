/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/IPC/Proxy/Common/OnCompletionCallbackProxy.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "MultiAgentExperience/IPC/Models/Common/OnCompletionCallbackModel.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace common {

static const std::string MODULE_TAG("OnCompletionCallbackProxy");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

OnCompletionCallbackProxy::OnCompletionCallbackProxy(
    multiAgentExperience::ipc::messaging::Reference reference,
    std::shared_ptr<transport::MessageSender> sender):
        MaxIpcComponentsBaseProxy(std::move(reference), transport::MaxApiType::ON_COMPLETION_CALLBACK, std::move(sender)) {}

void OnCompletionCallbackProxy::completed()  {
    LX(DEBUG0, "");
    auto message = multiAgentExperience::ipc::messaging::createMessage(
        m_reference,
        models::common::OnCompletionCallbackFunctions::COMPLETED,
        multiAgentExperience::ipc::messaging::VoidPayload());

    m_sender->send(message);
}

} // namespace common
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience