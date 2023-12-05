/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/IPC/Proxy/Activity/ActivityControllerProxy.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace activity {

static const std::string MODULE_TAG("ActivityControllerProxy");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ActivityControllerProxy::ActivityControllerProxy(multiAgentExperience::ipc::messaging::Reference reference,
                                                 std::shared_ptr<transport::MessageSender> sender) :
        MaxIpcComponentsBaseProxy(std::move(reference), transport::MaxApiType::ACTIVITY_CONTROLLER, std::move(sender)) {}

void ActivityControllerProxy:: stop() {
    LX(DEBUG0, "");
    auto message = createMessage(
            m_reference,
            models::activity::ActivityControllerFunctions::STOP,
            multiAgentExperience::ipc::messaging::VoidPayload());
    m_sender->send(message);
}

} // namespace activity
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience