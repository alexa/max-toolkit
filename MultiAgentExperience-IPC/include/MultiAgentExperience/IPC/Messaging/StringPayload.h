/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/


#ifndef CITADEL_IPC_MESSAGING_STRINGPAYLOAD_H
#define CITADEL_IPC_MESSAGING_STRINGPAYLOAD_H

#include <string>
#include <type_traits>
#include <utility>

#include "Payload.h"

namespace multiAgentExperience {
namespace ipc {
namespace messaging {

struct StringPayload: Payload {
  explicit StringPayload(std::string value) : m_value{std::move(value)} {
  }

  std::string m_value;
};

} // namespace messaging
} // namespace ipc
} // namespace multiAgentExperience


#endif //CITADEL_IPC_MESSAGING_STRINGPAYLOAD_H
