/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_ONCOMPLETIONCALLBACKMESSAGEHANDLER_H
#define MULTIAGENTEXPERIENCE_IPC_ONCOMPLETIONCALLBACKMESSAGEHANDLER_H

#include <MultiAgentExperience/IPC/Messaging/VoidMessageTypes.h>

#include <MultiAgentExperience/Common/OnCompletionCallbackInterface.h>

#include "MultiAgentExperience/IPC/Models/Common/OnCompletionCallbackModel.h"
#include "MultiAgentExperience/IPC/Transport/MessageHandler.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace common {

class OnCompletionCallbackMessageHandler : public transport::MessageHandler {
 public:
    explicit OnCompletionCallbackMessageHandler(
        const multiAgentExperience::ipc::messaging::Reference& reference,
        std::shared_ptr<::multiAgentExperience::common::OnCompletionCallbackInterface>
        onCompletionCallback);

    /// method for @c completed()
    void handle(const multiAgentExperience::ipc::messaging::Message<models::common
    ::OnCompletionCallbackFunctions,
    multiAgentExperience::ipc::messaging::VoidPayload>& message);

 private:
    std::shared_ptr<::multiAgentExperience::common::OnCompletionCallbackInterface>
    m_onCompletionCallback;
};

} // namespace common
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif // MULTIAGENTEXPERIENCE_IPC_ONCOMPLETIONCALLBACKMESSAGEHANDLER_H