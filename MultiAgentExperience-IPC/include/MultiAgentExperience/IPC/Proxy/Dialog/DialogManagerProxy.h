/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_DIALOGMANAGERPROXY_H
#define MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_DIALOGMANAGERPROXY_H

#include <utility>

#include <MultiAgentExperience/Dialog/DialogManagerInterface.h>

#include "MultiAgentExperience/IPC/Models/Dialog/DialogManagerModel.h"
#include "MultiAgentExperience/IPC/Proxy/MessageHandlerStore.h"
#include "MultiAgentExperience/IPC/Proxy/Utils/PayloadPackager.h"
#include "MultiAgentExperience/IPC/Transport/MessageSender.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace dialog {

class DialogManagerProxy : public multiAgentExperience::dialog::DialogManagerInterface,
                           public multiAgentExperience::ipc::transport::MaxIpcComponentsBaseProxy {
 public:
  explicit DialogManagerProxy(
      multiAgentExperience::ipc::messaging::Reference reference,
      std::shared_ptr<transport::MessageSender> sender,
      std::shared_ptr<MessageHandlerStore> messageHandlerStore);

  /// @name DialogManagerInterface method overrides.
  /// @{
  void request(std::shared_ptr<multiAgentExperience::dialog::DialogRequestInterface> request)
  override;
  void stop(std::shared_ptr<multiAgentExperience::dialog::DialogRequestInterface> request) override;
  void setAllHandlers(
      std::shared_ptr<multiAgentExperience::dialog::ControlReceiverInterface> controlReceiver,
      std::shared_ptr<multiAgentExperience::dialog::ListeningHandlerInterface> listeningHandler,
      std::shared_ptr<multiAgentExperience::dialog::ThinkingHandlerInterface> thinkingHandler,
      std::shared_ptr<multiAgentExperience::dialog::SpeakingHandlerInterface> speakingHandler)
      override;
  void removeAllHandlers() override;
  void setControlReceiver(std::shared_ptr<multiAgentExperience::dialog::ControlReceiverInterface>
      receiver) override;
  void removeControlReceiver() override;
  void setListeningHandler(std::shared_ptr<multiAgentExperience::dialog
  ::ListeningHandlerInterface> handler) override;
  void removeListeningHandler() override;
  void setThinkingHandler(std::shared_ptr<multiAgentExperience::dialog::ThinkingHandlerInterface>
      handler) override;
  void removeThinkingHandler() override;
  void setSpeakingHandler(std::shared_ptr<multiAgentExperience::dialog::SpeakingHandlerInterface>
      handler) override;
  void removeSpeakingHandler() override;
  /// @}

private:
    std::shared_ptr<MessageHandlerStore> m_messageHandlerStore;
};

} // namespace dialog
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_DIALOGMANAGERPROXY_H
