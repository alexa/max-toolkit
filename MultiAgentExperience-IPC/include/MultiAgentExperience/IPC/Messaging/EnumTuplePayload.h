/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_ENUMLISTPAYLOAD_H
#define MULTIAGENTEXPERIENCE_IPC_ENUMLISTPAYLOAD_H

#include <vector>
#include "Payload.h"

namespace multiAgentExperience {
namespace ipc {
namespace messaging {
/**
 * Some of the API functions in MAX takes 2 Enum parameters. Ex: ActivityHandlerInterface::onFocusStateChanged
 * This will require a the enums to be part of the payloads. This Payload is created to hold parameters which will
 * take 2 enum types.
 * @tparam EnumType1 - Any enum type
 * @tparam EnumType2 - Any enum type
 */
template<typename EnumType1, typename EnumType2>
struct EnumTuplePayload: Payload {
    static_assert(std::is_enum<EnumType1>::value, "EnumType1 must be an enum");
    static_assert(std::is_enum<EnumType2>::value, "EnumType2 must be an enum");
    EnumTuplePayload(EnumType1 value1, EnumType2 value2):
    m_value1{value1},
    m_value2{value2} {
    }

    EnumType1 m_value1;
    EnumType2 m_value2;
};
} // namespace messaging
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_ENUMLISTPAYLOAD_H
