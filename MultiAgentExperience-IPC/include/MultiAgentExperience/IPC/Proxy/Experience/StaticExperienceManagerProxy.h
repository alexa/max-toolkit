/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_STATICEXPERIENCEMANAGERPROXY_H
#define MULTIAGENTEXPERIENCE_IPC_STATICEXPERIENCEMANAGERPROXY_H

#include <MultiAgentExperience/IPC/Messaging/Reference.h>
#include <MultiAgentExperience/IPC/Messaging/StringIntTuplePayload.h>
#include <MultiAgentExperience/Experience/ExperienceId.h>
#include <MultiAgentExperience/Experience/StaticExperienceManagerInterface.h>

#include "MultiAgentExperience/IPC/Transport/MaxIpcComponentsBaseProxy.h"
#include "MultiAgentExperience/IPC/Transport/MessageSender.h"
#include "MultiAgentExperience/IPC/Proxy/MessageHandlerStore.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace experience {

class StaticExperienceManagerProxy : public multiAgentExperience::experience::StaticExperienceManagerInterface,
                                     public multiAgentExperience::ipc::transport::MaxIpcComponentsBaseProxy {
public:
    StaticExperienceManagerProxy(
    multiAgentExperience::ipc::messaging::Reference reference,
    std::shared_ptr<transport::MessageSender> sender);

    void addStaticExperience(
        const ::multiAgentExperience::experience::ExperienceId& experienceId,
        const unsigned int priority) override;
    void removeStaticExperience(const ::multiAgentExperience::experience::ExperienceId& experienceId) override;
    void removeAllStaticExperiences() override;
};

} // namespace experience
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif // MULTIAGENTEXPERIENCE_IPC_STATICEXPERIENCEMANAGERPROXY_H