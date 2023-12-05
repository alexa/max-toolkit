/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_ACTIVITYHANDLERPROXY_H
#define MULTIAGENTEXPERIENCE_IPC_ACTIVITYHANDLERPROXY_H

#include <MultiAgentExperience/IPC/Messaging/MessageUtils.h>
#include <MultiAgentExperience/IPC/Messaging/StringPayload.h>
#include <MultiAgentExperience/IPC/Messaging/Reference.h>
#include <MultiAgentExperience/IPC/Messaging/VoidMessageTypes.h>
#include <MultiAgentExperience/IPC/Messaging/ReferencePayload.h>
#include <MultiAgentExperience/IPC/Messaging/EnumPayload.h>
#include <MultiAgentExperience/IPC/Messaging/ReferenceListPayload.h>

#include <MultiAgentExperience/Activity/ActivityHandlerInterface.h>
#include <MultiAgentExperience/Activity/ActivityControllerInterface.h>

#include "MultiAgentExperience/IPC/Models/Activity/ActivityHandlerModel.h"
#include "MultiAgentExperience/IPC/Transport/MaxIpcComponentsBaseProxy.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {

class MessageHandlerStore;

namespace activity {
class ActivityHandlerProxy : public multiAgentExperience::activity::ActivityHandlerInterface,
                             public multiAgentExperience::ipc::transport::MaxIpcComponentsBaseProxy {
public:
    ActivityHandlerProxy(
            multiAgentExperience::ipc::messaging::Reference reference,
            std::shared_ptr<transport::MessageSender> sender,
            std::shared_ptr<MessageHandlerStore> messageHandlerStore);

    void onDenied() override;

    void onGranted(
            std::shared_ptr<multiAgentExperience::activity::ActivityControllerInterface> activityController,
            std::shared_ptr<multiAgentExperience::control::ControlRegistryInterface> controlRegistry,
            std::shared_ptr<multiAgentExperience::experience::ExperienceControllerInterface>
            experienceControl) override;

    void onFocusStateChange(
            multiAgentExperience::activity::ActivityFocus focus,
            multiAgentExperience::activity::MixingBehavior behavior) override;

    void onStop() override;

private:
    std::shared_ptr<MessageHandlerStore> m_messageHandlerStore;

};

} // namespace activity
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_ACTIVITYHANDLERPROXY_H
