/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_PROXY_MAXAPITYPES_H
#define MULTIAGENTEXPERIENCE_IPC_PROXY_MAXAPITYPES_H

#include <memory>
#include <string>

#include <MultiAgentExperience/IPC/Messaging/Types/TypeUtils.h>
#include <MultiAgentExperience/Activity/ActivityControllerInterface.h>

namespace multiAgentExperience {
namespace ipc {
namespace transport {

enum class MaxApiType {
    // Activities
    ACTIVITY_CONTROLLER,
    ACTIVITY_HANDLER,
    ACTIVITY_MANAGER,
    ACTIVITY_REQUEST,

    // Agent
    AGENT_REGISTRATION,

    // Common
    ON_COMPLETION_CALLBACK,

    // Control
    CONTROL,
    CONTROL_REGISTRY,

    // Dialog
    CONTROL_RECEIVER,
    DIALOG_CONTROLLER,
    DIALOG_MANAGER,
    DIALOG_REQUEST,
    LISTENING_HANDLER,
    SPEAKING_HANDLER,
    START_LISTENING_CALLBACK,
    THINKING_HANDLER,

    // Experience
    EXPERIENCE_CONTROLLER,
    STATIC_EXPERIENCE_MANAGER
};

} // namespace transport
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_PROXY_MAXAPITYPES_H
