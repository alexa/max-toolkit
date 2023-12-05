/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/


#ifndef MULTIAGENTEXPERIENCE_IPC_MESSAGING_TYPEINSTANCE_H
#define MULTIAGENTEXPERIENCE_IPC_MESSAGING_TYPEINSTANCE_H

#include <utility>

namespace multiAgentExperience {
namespace ipc {
namespace messaging {
namespace types {
/**
 * A TypeInstance holds the identifier of an instance of a type. An IPC call can then track the call to the instance
 * across the process boundary.
 */
struct TypeInstance {
    std::size_t m_identifier;
};
} // namespace types
} // namespace messaging
} // namespace ipc
} // namespace multiAgentExperience


#endif //MULTIAGENTEXPERIENCE_IPC_MESSAGING_TYPEINSTANCE_H
