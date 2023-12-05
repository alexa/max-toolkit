/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_ACTIVITYCONTROLLERPROXY_H
#define MULTIAGENTEXPERIENCE_IPC_ACTIVITYCONTROLLERPROXY_H

#include <memory>

#include <MultiAgentExperience/IPC/Messaging/ReferencePayload.h>
#include <MultiAgentExperience/IPC/Messaging/VoidMessageTypes.h>

#include "MultiAgentExperience/IPC/Models/Activity/ActivityControllerModel.h"
#include "MultiAgentExperience/IPC/Transport/MaxIpcComponentsBaseProxy.h"
#include "MultiAgentExperience/IPC/Proxy/MessageHandlerStore.h"
#include "MultiAgentExperience/IPC/Transport/MessageSender.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {

class MessageHandlerStore;

namespace activity {
    class ActivityControllerProxy : public multiAgentExperience::activity::ActivityControllerInterface,
                                    public multiAgentExperience::ipc::transport::MaxIpcComponentsBaseProxy {
    public:
        ActivityControllerProxy(multiAgentExperience::ipc::messaging::Reference reference,
                                std::shared_ptr<transport::MessageSender> sender);

        void stop() override;

    private:
        std::shared_ptr<proxy::MessageHandlerStore> m_messageHandlerStore;
    };

} // namespace activity
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_ACTIVITYCONTROLLERPROXY_H
