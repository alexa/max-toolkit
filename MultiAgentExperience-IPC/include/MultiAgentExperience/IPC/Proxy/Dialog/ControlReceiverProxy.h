/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_CONTROLRECEIVERPROXY_H
#define MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_CONTROLRECEIVERPROXY_H

#include <MultiAgentExperience/IPC/Messaging/ListPayload.h>
#include <MultiAgentExperience/IPC/Messaging/Reference.h>
#include <MultiAgentExperience/Dialog/ControlReceiverInterface.h>

#include "MultiAgentExperience/IPC/Models/Control/ControlRegistryModel.h"
#include "MultiAgentExperience/IPC/Proxy/MessageHandlerStore.h"
#include "MultiAgentExperience/IPC/Proxy/Utils/PayloadPackager.h"
#include "MultiAgentExperience/IPC/Transport/MaxIpcComponentsBaseProxy.h"
#include "MultiAgentExperience/IPC/Transport/MessageSender.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace dialog {

class ControlReceiverProxy : public multiAgentExperience::dialog::ControlReceiverInterface,
                             public multiAgentExperience::ipc::transport::MaxIpcComponentsBaseProxy {
public:
    ControlReceiverProxy(
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<transport::MessageSender> sender,
        std::shared_ptr<MessageHandlerStore> messageHandlerStore);

    void onControlsReceived(
        std::shared_ptr<multiAgentExperience::dialog::StartListeningCallback> startListeningCallback,
        std::set<multiAgentExperience::control::ControlType> controls) override;

private:
    std::shared_ptr<MessageHandlerStore> m_messageHandlerStore;
};

} // namespace dialog
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_PROXY_DIALOG_CONTROLRECEIVERPROXY_H
