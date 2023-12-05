/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_MESSAGING_ENUMPAYLOAD_H
#define MULTIAGENTEXPERIENCE_IPC_MESSAGING_ENUMPAYLOAD_H

#include <type_traits>
#include "Payload.h"

namespace multiAgentExperience {
namespace ipc {
namespace messaging {
template<typename EnumType>
struct EnumPayload: Payload {
    static_assert(std::is_enum<EnumType>::value, "EnumType must be an enum");
    EnumPayload(EnumType value): m_value{value} {
    }

    EnumType m_value;
};
} // namespace messaging
} // namespace ipc
} // namespace multiAgentExperience


#endif //MULTIAGENTEXPERIENCE_IPC_MESSAGING_ENUMPAYLOAD_H
