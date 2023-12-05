/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_CONTROLPROXY_H
#define MULTIAGENTEXPERIENCE_IPC_CONTROLPROXY_H

#include <MultiAgentExperience/Control/Control.h>

#include <MultiAgentExperience/IPC/Messaging/Payload.h>
#include <MultiAgentExperience/IPC/Messaging/Reference.h>

#include "MultiAgentExperience/IPC/Transport/MaxIpcComponentsBaseProxy.h"
#include "MultiAgentExperience/IPC/Transport/MessageSender.h"
#include "MultiAgentExperience/IPC/Proxy/MessageHandlerStore.h"
#include "MultiAgentExperience/IPC/Proxy/Utils/PayloadPackager.h"
#include "MultiAgentExperience/IPC/Models/Control/ControlRegistryModel.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {

class MessageHandlerStore;

namespace control {

/// ControlProxy is implemented from a struct.
/// This is different from other Proxy classes that are implemented from an abstract class.
/// The members of struct, specifically Control::task, is accessed directly from the passed object.
/// Its of type std::function. Hence, IPC message needs to be sent when this member is accessed,
/// as opposed to overloading a function from base abstract class.
/// To achieve this, we have a private function ControlProxy::invokeControlTask, which will be assigned
/// to Control::task. This private function will be responsible for sending message across, when
/// Control::task is accessed.
class ControlProxy : public multiAgentExperience::control::Control,
                     public multiAgentExperience::ipc::transport::MaxIpcComponentsBaseProxy {
public:
    explicit ControlProxy(
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<transport::MessageSender> sender,
        const multiAgentExperience::control::ControlType& controlType);

private:
    void invokeControlTask();
};

} // namespace control
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_CONTROLPROXY_H
