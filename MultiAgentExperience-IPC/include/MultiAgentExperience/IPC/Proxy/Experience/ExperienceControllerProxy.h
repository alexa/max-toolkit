/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_EXPERIENCECONTROLLERPROXY_H
#define MULTIAGENTEXPERIENCE_IPC_EXPERIENCECONTROLLERPROXY_H

#include <MultiAgentExperience/IPC/Messaging/Reference.h>
#include <MultiAgentExperience/Experience/ExperienceControllerInterface.h>

#include "MultiAgentExperience/IPC/Transport/MaxIpcComponentsBaseProxy.h"
#include "MultiAgentExperience/IPC/Transport/MessageSender.h"
#include "MultiAgentExperience/IPC/Proxy/MessageHandlerStore.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace experience {
class ExperienceControllerProxy : public multiAgentExperience::experience::ExperienceControllerInterface,
                                  public multiAgentExperience::ipc::transport::MaxIpcComponentsBaseProxy {
public:
    ExperienceControllerProxy(
            multiAgentExperience::ipc::messaging::Reference reference,
            std::shared_ptr<transport::MessageSender> sender);

    /// ExperienceControllerInterface Overrides
    /// @{
    void startExperience(const multiAgentExperience::experience::ExperienceId& experience) override;
    void endExperience() override;
    void invalidate() override;
    /// @}

};

} // namespace experience
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_EXPERIENCECONTROLLERPROXY_H
