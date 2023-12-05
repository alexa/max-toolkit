/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/IPC/Proxy/Control/ControlProxy.h"

#include <MultiAgentExperience/IPC/Messaging/VoidMessageTypes.h>

#include "MultiAgentExperience/IPC/Models/Control/ControlModel.h"
#include "MultiAgentExperience/IPC/Proxy/MessageHandlerStore.h"
#include <MultiAgentExperience/Utils/Logger/Logger.h>

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace control {

static const std::string MODULE_TAG("ControlProxy");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ControlProxy::ControlProxy(
    multiAgentExperience::ipc::messaging::Reference reference,
    std::shared_ptr<transport::MessageSender> sender,
    const multiAgentExperience::control::ControlType& controlType):
    MaxIpcComponentsBaseProxy(std::move(reference), transport::MaxApiType::CONTROL, std::move(sender)),
    multiAgentExperience::control::Control(
        controlType,
        std::bind(&ControlProxy::invokeControlTask, this)) {
}

void ControlProxy::invokeControlTask() {
    LX(DEBUG0, "");

    auto payload = multiAgentExperience::ipc::messaging::VoidPayload();

    auto message = multiAgentExperience::ipc::messaging::createMessage<models::control::ControlFunctions, multiAgentExperience::ipc::messaging::VoidPayload>(
        m_reference,
        models::control::ControlFunctions::CONTROL_TASK,
        payload);

    m_sender->send(message);
}

} // namespace control
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience
