/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_DIALOGREQUESTPROXY_H
#define MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_DIALOGREQUESTPROXY_H

#include <utility>

#include <MultiAgentExperience/IPC/Messaging/MessageUtils.h>
#include <MultiAgentExperience/Dialog/DialogRequestInterface.h>

#include "MultiAgentExperience/IPC/Config/Config.h"
#include "MultiAgentExperience/IPC/Models/Dialog/DialogRequestModel.h"
#include "MultiAgentExperience/IPC/Proxy/Utils/PayloadPackager.h"
#include "MultiAgentExperience/IPC/Transport/MaxIpcComponentsBaseProxy.h"
#include "MultiAgentExperience/IPC/Transport/MessageSender.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {

class MessageHandlerStore;

namespace dialog {

class DialogRequestProxy : public multiAgentExperience::dialog::DialogRequestInterface,
                           public multiAgentExperience::ipc::transport::MaxIpcComponentsBaseProxy {

public:
  explicit DialogRequestProxy(
          multiAgentExperience::ipc::messaging::Reference reference,
      std::shared_ptr<transport::MessageSender> sender,
      std::shared_ptr<MessageHandlerStore> messageHandlerStore);

  /// @name DialogRequestInterface method overrides.
  /// @{
  void onDenied(const std::string& denialMessage) override;
  void onDialogStarted(std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface>
      controller) override;
  void onError(const std::string& errorMessage) override;
  void onDialogStopped() override;
  multiAgentExperience::dialog::DialogBargeInPriority getDialogBargeInPriority() const override;
  std::size_t getHash() const override;
  /// @}

private:
    std::shared_ptr<MessageHandlerStore> m_messageHandlerStore;

};

} // namespace dialog
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_DIALOGREQUESTPROXY_H
