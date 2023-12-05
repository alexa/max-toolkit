/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_LISTPAYLOAD_H
#define MULTIAGENTEXPERIENCE_IPC_LISTPAYLOAD_H

#include <set>
#include <vector>
#include "Payload.h"

namespace multiAgentExperience {
namespace ipc {
namespace messaging {
/**
 * ListPayload can be used to package a parameter of type list in a function for IPC
 * @tparam ListType - Any list type
 */
template<typename ListType>
struct ListPayload: Payload {
    ListPayload(std::vector<ListType> values): m_value{values} {
    }

    ListPayload(std::set<ListType> values) {
        std::copy(values.begin(), values.end(), std::back_inserter(m_value));
    }

    std::vector<ListType> m_value;
};
} // namespace messaging
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_LISTPAYLOAD_H
