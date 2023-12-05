/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_ONCOMPLETIONCALLBACKPROXY_H
#define MULTIAGENTEXPERIENCE_IPC_ONCOMPLETIONCALLBACKPROXY_H

#include <MultiAgentExperience/Common/OnCompletionCallbackInterface.h>

#include "MultiAgentExperience/IPC/Transport/MaxIpcComponentsBaseProxy.h"
#include "MultiAgentExperience/IPC/Transport/MessageSender.h"
#include "MultiAgentExperience/IPC/Proxy/MessageHandlerStore.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace common {

class OnCompletionCallbackProxy : public multiAgentExperience::common::OnCompletionCallbackInterface,
                                  public multiAgentExperience::ipc::transport::MaxIpcComponentsBaseProxy {
 public:
  explicit OnCompletionCallbackProxy(multiAgentExperience::ipc::messaging::Reference reference,
                            std::shared_ptr<transport::MessageSender> sender);

  void completed() override;
};

} // namespace common
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif // MULTIAGENTEXPERIENCE_IPC_ONCOMPLETIONCALLBACKPROXY_H