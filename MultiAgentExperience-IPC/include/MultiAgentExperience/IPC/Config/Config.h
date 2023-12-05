/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_IPC_CONFIG_CONFIG_H
#define MULTIAGENTEXPERIENCE_IPC_CONFIG_CONFIG_H

#include <chrono>

namespace multiAgentExperience {
namespace ipc {
namespace config {

/// The timeout value for any synchronous request that is made by the a proxy. This value can be configured using @c MAXBuilder
static std::chrono::milliseconds SYNCHRONOUS_REQUEST_TIMEOUT = std::chrono::milliseconds(1000);

} // namespace config
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_CONFIG_CONFIG_H
