/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_STRINGLISTPAYLOAD_H
#define MULTIAGENTEXPERIENCE_IPC_STRINGLISTPAYLOAD_H

#include <vector>

#include "Payload.h"
#include "Reference.h"


namespace multiAgentExperience {
namespace ipc {
namespace messaging {

struct StringListPayload: Payload {
  explicit StringListPayload(std::vector<std::string> values): m_values{std::move(values)} {
  }

  std::vector<std::string> m_values;
};

} // namespace messaging
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_STRINGLISTPAYLOAD_H
