/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_STARTLISTENINGCALLBACKPROXY_H
#define MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_STARTLISTENINGCALLBACKPROXY_H

#include <utility>

#include <MultiAgentExperience/IPC/Messaging/MessageUtils.h>
#include <MultiAgentExperience/Dialog/StartListeningCallback.h>

#include "MultiAgentExperience/IPC/Models/Dialog/StartListeningCallbackModel.h"
#include "MultiAgentExperience/IPC/Transport/MessageSender.h"
#include "MultiAgentExperience/IPC/Transport/MaxIpcComponentsBaseProxy.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace dialog {

class StartListeningCallbackProxy : public multiAgentExperience::dialog::StartListeningCallback,
                                    public multiAgentExperience::ipc::transport::MaxIpcComponentsBaseProxy {

public:
    StartListeningCallbackProxy(
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<transport::MessageSender> sender);

    /// @name StartListeningCallback method overrides.
    /// @{
    void startListening() override;
    /// @}

};

} // namespace dialog
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_STARTLISTENINGCALLBACKPROXY_H
