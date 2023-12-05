/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_MESSAGING_TYPEUTILS_H
#define MULTIAGENTEXPERIENCE_IPC_MESSAGING_TYPEUTILS_H

#include <memory>
#include <string>
#include "MultiAgentExperience/IPC/Messaging/Model.h"

namespace multiAgentExperience {
namespace ipc {
namespace messaging {
namespace types {
template<typename T>
std::string getNamespace(std::shared_ptr<T> const& t);

template<typename T>
std::string getName(std::shared_ptr<T> const& t);

template<typename T>
std::size_t getIdentifier(std::shared_ptr<T> const& t) {
    return std::hash<std::shared_ptr<T> >()(t);
}
} // namespace types
} // namespace messaging
} // namespace ipc
} // namespace multiAgentExperience


#endif //MULTIAGENTEXPERIENCE_IPC_MESSAGING_TYPEUTILS_H
