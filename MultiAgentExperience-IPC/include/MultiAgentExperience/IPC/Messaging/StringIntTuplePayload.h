/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_TUPLEPAYLOAD_H
#define MULTIAGENTEXPERIENCE_IPC_TUPLEPAYLOAD_H

#include <vector>
#include <string>

#include "Payload.h"

namespace multiAgentExperience {
namespace ipc {
namespace messaging {

struct StringIntTuplePayload: Payload {
  explicit StringIntTuplePayload(std::string value1, int value2):
  m_value1{value1}, m_value2{value2} {}

  std::string m_value1;
  int m_value2;
};

} // namespace messaging
} // namespace ipc
} // namespace multiAgentExperience

#endif // MULTIAGENTEXPERIENCE_IPC_TUPLEPAYLOAD_H