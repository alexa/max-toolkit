/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_PROXY_CONTROL_CONTROLREGISTRYPROXY_H
#define MULTIAGENTEXPERIENCE_IPC_PROXY_CONTROL_CONTROLREGISTRYPROXY_H

#include <MultiAgentExperience/Control/ControlRegistryInterface.h>

#include <MultiAgentExperience/IPC/Messaging/ListPayload.h>
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

class ControlRegistryProxy : public multiAgentExperience::control::ControlRegistryInterface,
                             public multiAgentExperience::ipc::transport::MaxIpcComponentsBaseProxy {
public:
    explicit ControlRegistryProxy(
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<transport::MessageSender> sender,
        std::shared_ptr<MessageHandlerStore> messageHandlerStore);

    void update(std::set<std::shared_ptr<multiAgentExperience::control::Control>> controls) override;

private:
    std::shared_ptr<MessageHandlerStore> m_messageHandlerStore;
};

} // namespace control
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_PROXY_CONTROL_CONTROLREGISTRYPROXY_H
