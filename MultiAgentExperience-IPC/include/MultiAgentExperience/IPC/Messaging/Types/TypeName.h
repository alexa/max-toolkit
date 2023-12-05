/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/


#ifndef MULTIAGENTEXPERIENCE_IPC_MESSAGING_TYPENAME_H
#define MULTIAGENTEXPERIENCE_IPC_MESSAGING_TYPENAME_H

#include <string>


namespace multiAgentExperience {
namespace ipc {
namespace messaging {
namespace types {
/**
 * A TypeName holds the name and namespace of an instance of a type. An IPC call can then track the call to the instance
 * across the process boundary using the identifier, name and namespace.
 */
struct TypeName {
    std::string m_nspace;
    std::string m_name;
};
} // namespace types
} // namespace messaging
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_MESSAGING_TYPENAME_H
