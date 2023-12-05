/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_TRANSPORT_BASEPROXY_H
#define MULTIAGENTEXPERIENCE_IPC_TRANSPORT_BASEPROXY_H

#include <MultiAgentExperience/IPC/Messaging/Reference.h>
#include <MultiAgentExperience/Thread/Executor/Threading/Executor.h>

#include "MultiAgentExperience/IPC/Transport/MaxApiTypes.h"
#include "MultiAgentExperience/IPC/Transport/MessageSender.h"

namespace multiAgentExperience {
namespace ipc {
namespace transport {

class MaxIpcComponentsBaseProxy {
public:
    MaxIpcComponentsBaseProxy(
            multiAgentExperience::ipc::messaging::Reference reference,
            transport::MaxApiType maxApiType,
            std::shared_ptr<transport::MessageSender> sender);
    virtual ~MaxIpcComponentsBaseProxy();
private:
    transport::MaxApiType m_maxApiType;
protected:
    const multiAgentExperience::ipc::messaging::Reference m_reference;
    std::shared_ptr<transport::MessageSender> m_sender;
};

} // namespace transport
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_TRANSPORT_BASEPROXY_H
