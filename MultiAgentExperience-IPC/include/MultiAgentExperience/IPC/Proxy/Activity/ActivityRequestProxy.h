/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_ACTIVITYREQUESTPROXY_H
#define MULTIAGENTEXPERIENCE_IPC_ACTIVITYREQUESTPROXY_H

#include <utility>
#include <MultiAgentExperience/IPC/Messaging/MessageUtils.h>
#include <MultiAgentExperience/IPC/Messaging/Message.h>
#include <MultiAgentExperience/Activity/ActivityType.h>
#include <MultiAgentExperience/IPC/Messaging/VoidMessageTypes.h>
#include <MultiAgentExperience/IPC/Messaging/EnumPayload.h>
#include <MultiAgentExperience/IPC/Messaging/ReferencePayload.h>
#include "MultiAgentExperience/IPC/Models/Activity/ActivityRequestModel.h"
#include "MultiAgentExperience/IPC/Proxy/Activity/ActivityHandlerProxy.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {

class MessageHandlerStore;

namespace activity {
class ActivityRequestProxy : public multiAgentExperience::activity::ActivityRequestInterface,
                             public multiAgentExperience::ipc::transport::MaxIpcComponentsBaseProxy {
public:
    ActivityRequestProxy(
            std::shared_ptr<::multiAgentExperience::activity::ActivityHandlerInterface> handler,
            multiAgentExperience::ipc::messaging::Reference reference,
            std::shared_ptr<transport::MessageSender> sender,
            std::shared_ptr<MessageHandlerStore> messageHandlerStore);

    /// ToDo: These functions must override functions in @c ActivityRequestInterface.
    /// Also functions in @c must be made virtual.
    multiAgentExperience::activity::ActivityType getType () const override;

    std::shared_ptr<multiAgentExperience::activity::ActivityHandlerInterface> getHandler() const override ;

    multiAgentExperience::activity::MixabilityType getMixabilityType() const override;

    std::size_t getHash() const override;

private:
    std::shared_ptr<MessageHandlerStore> m_messageHandlerStore;
    std::shared_ptr<ActivityHandlerProxy> createOrGet(const multiAgentExperience::ipc::messaging::Reference& reference) const;
    mutable std::map<multiAgentExperience::ipc::messaging::Reference, std::weak_ptr<ActivityHandlerProxy>> m_activityHandlerProxies;
};

} // namespace activity
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_ACTIVITYREQUESTPROXY_H
