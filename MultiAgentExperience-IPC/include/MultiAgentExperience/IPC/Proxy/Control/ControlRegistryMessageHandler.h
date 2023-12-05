/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_CONTROLREGISTRYMESSAGEHANDLER_H
#define MULTIAGENTEXPERIENCE_IPC_CONTROLREGISTRYMESSAGEHANDLER_H

#include <MultiAgentExperience/Control/ControlRegistryInterface.h>
#include <MultiAgentExperience/IPC/Messaging/Message.h>
#include "MultiAgentExperience/IPC/Messaging/Control/ControlRegistryPayload.h"
#include "MultiAgentExperience/IPC/Models/Control/ControlRegistryModel.h"
#include "MultiAgentExperience/IPC/Transport/MessageHandler.h"
#include "MultiAgentExperience/IPC/Transport/MessageSender.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
    class MessageHandlerStore;
namespace control {
class ControlRegistryMessageHandler : public transport::MessageHandler {
public:
  explicit ControlRegistryMessageHandler(
      const multiAgentExperience::ipc::messaging::Reference& reference,
      std::shared_ptr<transport::MessageSender> sender,
      std::shared_ptr<multiAgentExperience::control::ControlRegistryInterface> controlRegistry);

  void handle(
      const multiAgentExperience::ipc::messaging::Message<models::control::ControlRegistryFunctions,
            multiAgentExperience::ipc::messaging::control::ControlRegistryPayload>& message);

private:
    void update(const multiAgentExperience::ipc::messaging::control::ControlRegistryPayload& payload);

    std::set<std::shared_ptr<multiAgentExperience::control::Control>> getControlsFromReferences(
        const std::list<std::tuple<
            multiAgentExperience::ipc::messaging::Reference,
            multiAgentExperience::control::ControlType>>& referenceControlTypesList);

    std::shared_ptr<transport::MessageSender> m_sender;
    std::shared_ptr<multiAgentExperience::control::ControlRegistryInterface> m_controlRegistry;

};

} // namespace control
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_CONTROLREGISTRYMESSAGEHANDLER_H
