/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_ONCOMPLETIONCALLBACKMODEL_H
#define MULTIAGENTEXPERIENCE_IPC_ONCOMPLETIONCALLBACKMODEL_H

#include <memory>

#include <MultiAgentExperience/IPC/Messaging/Types/TypeUtils.h>
#include <MultiAgentExperience/Common/OnCompletionCallbackInterface.h>

namespace multiAgentExperience {
namespace ipc {
namespace models {
namespace common {

enum class OnCompletionCallbackFunctions {
  COMPLETED
};

} // namespace common
} // namespace models
} // namespace ipc
} // namespace multiAgentExperience

template<>
inline std::string multiAgentExperience::ipc::messaging::types::getNamespace(const
                                                                std::shared_ptr<::multiAgentExperience::common::OnCompletionCallbackInterface> &t) {
  return "multiAgentExperience::common";
}

template<>
inline std::string multiAgentExperience::ipc::messaging::types::getName(const
                                                           std::shared_ptr<::multiAgentExperience::common::OnCompletionCallbackInterface> &t) {
  return "OnCompletionCallback";
}

#endif // MULTIAGENTEXPERIENCE_IPC_ONCOMPLETIONCALLBACKMODEL_H