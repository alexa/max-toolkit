/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_MESSAGING_INTPAYLOAD_H
#define MULTIAGENTEXPERIENCE_IPC_MESSAGING_INTPAYLOAD_H

#include <utility>

#include "Payload.h"


namespace multiAgentExperience {
namespace ipc {
namespace messaging {
struct IntPayload: Payload {
  explicit IntPayload(int value) : m_value{value} {}

  int m_value;
};
} // namespace messaging
} // namespace ipc
} // namespace multiAgentExperience


#endif // MULTIAGENTEXPERIENCE_IPC_MESSAGING_INTPAYLOAD_H