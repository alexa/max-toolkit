/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_LISTENINGHANDLERPROXY_H
#define MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_LISTENINGHANDLERPROXY_H

#include <utility>

#include <MultiAgentExperience/IPC/Messaging/MessageUtils.h>
#include <MultiAgentExperience/Dialog/ListeningHandlerInterface.h>

#include "MultiAgentExperience/IPC/Models/Dialog/ListeningHandlerModel.h"
#include "MultiAgentExperience/IPC/Proxy/Utils/PayloadPackager.h"
#include "MultiAgentExperience/IPC/Transport/MaxIpcComponentsBaseProxy.h"
#include "MultiAgentExperience/IPC/Transport/MessageSender.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {

class MessageHandlerStore;

namespace dialog {

class ListeningHandlerProxy : public multiAgentExperience::dialog::ListeningHandlerInterface,
                              public multiAgentExperience::ipc::transport::MaxIpcComponentsBaseProxy {

 public:
  explicit ListeningHandlerProxy(
      multiAgentExperience::ipc::messaging::Reference reference,
      std::shared_ptr<transport::MessageSender> sender,
      std::shared_ptr<MessageHandlerStore> messageHandlerStore);

  /// @name ListeningHandlerInterface method overrides.
  /// @{
  void onStartListening(std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface>
                        controller) override;
  void onStopListening() override;
  /// @}

 private:
  std::shared_ptr<MessageHandlerStore> m_messageHandlerStore;
};

} // namespace dialog
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_LISTENINGHANDLERPROXY_H
