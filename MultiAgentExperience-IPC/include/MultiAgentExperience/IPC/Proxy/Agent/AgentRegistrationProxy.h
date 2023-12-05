/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_AGENTREGISTRATIONPROXY_H
#define MULTIAGENTEXPERIENCE_IPC_AGENTREGISTRATIONPROXY_H

#include <MultiAgentExperience/Agent/AgentRegistrationInterface.h>

#include "MultiAgentExperience/IPC/Transport/MaxIpcComponentsBaseProxy.h"
#include "MultiAgentExperience/IPC/Transport/MessageSender.h"
#include "MultiAgentExperience/IPC/Proxy/MessageHandlerStore.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace agent {

class AgentRegistrationProxy : public multiAgentExperience::agent::AgentRegistrationInterface {
 public:
  explicit AgentRegistrationProxy(multiAgentExperience::ipc::messaging::Reference reference,
                                  std::shared_ptr<transport::MessageSender> sender,
                                  std::shared_ptr<MessageHandlerStore> messageHandlerStore);

  void onReady(
      std::shared_ptr<multiAgentExperience::common::OnCompletionCallbackInterface>onCompletionCallback,
      std::shared_ptr<multiAgentExperience::activity::ActivityManagerInterface> activityManager,
      std::shared_ptr<multiAgentExperience::dialog::DialogManagerInterface> dialogManager,
      std::shared_ptr<multiAgentExperience::experience::StaticExperienceManagerInterface>
      staticExperienceManager) override;

  actor::ActorId getId() override;

  std::string getName() override;

 private:
  /// AgentRegistrationProxy requires a MessageHandlerStore as its responsible for creating
  /// message handlers for different objects such as OnCompletionCallback, ActivityManager,
  /// DialogManager and StaticExperienceManager
    std::shared_ptr<MessageHandlerStore> m_messageHandlerStore;
    const multiAgentExperience::ipc::messaging::Reference m_reference;
    std::shared_ptr<transport::MessageSender> m_sender;
};

} // namespace agent
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif // MULTIAGENTEXPERIENCE_IPC_AGENTREGISTRATIONPROXY_H