/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_DIALOGCONTROLLERPROXY_H
#define MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_DIALOGCONTROLLERPROXY_H

#include <utility>

#include <MultiAgentExperience/IPC/Messaging/MessageUtils.h>
#include <MultiAgentExperience/Dialog/DialogControllerInterface.h>

#include "MultiAgentExperience/IPC/Models/Dialog/DialogControllerModel.h"
#include "MultiAgentExperience/IPC/Transport/MaxIpcComponentsBaseProxy.h"
#include "MultiAgentExperience/IPC/Transport/MessageSender.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace dialog {

class DialogControllerProxy : public multiAgentExperience::dialog::DialogControllerInterface,
                              public multiAgentExperience::ipc::transport::MaxIpcComponentsBaseProxy {

public:
  explicit DialogControllerProxy(
      multiAgentExperience::ipc::messaging::Reference reference,
      std::shared_ptr<transport::MessageSender> sender);

  /// @name DialogControllerInterface method overrides.
  /// @{
  void startListening() override;
  void startThinking() override;
  void startSpeaking() override;
  void invokeControlAndStartSpeaking(const multiAgentExperience::control::ControlType&
  controlType) override;
  void stop() override;
  void stopAndInvokeControl(const multiAgentExperience::control::ControlType& controlType) override;
  /// @}
};

} // namespace dialog
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_DIALOGCONTROLLERPROXY_H
