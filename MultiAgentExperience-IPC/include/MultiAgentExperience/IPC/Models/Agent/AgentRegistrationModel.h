/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_AGENTREGISTRATIONMODEL_H
#define MULTIAGENTEXPERIENCE_IPC_AGENTREGISTRATIONMODEL_H

#include <memory>

#include <MultiAgentExperience/IPC/Messaging/Types/TypeUtils.h>
#include <MultiAgentExperience/Agent/AgentRegistrationInterface.h>

namespace multiAgentExperience {
namespace ipc {
namespace models {
namespace agent {

enum class AgentRegistrationFunctions {
    ON_READY
};

enum class AgentRegistrationFunctionGetId {
    FUNCTION
};

enum class AgentRegistrationFunctionGetName {
    FUNCTION
};

enum class AgentRegistrationFunctionReturns {
    GET_ID,
    GET_NAME
};

} // namespace agent
} // namespace models
} // namespace ipc
} // namespace multiAgentExperience

template<>
inline std::string multiAgentExperience::ipc::messaging::types::getNamespace(const
                                                                std::shared_ptr<::multiAgentExperience::agent::AgentRegistrationInterface> &t) {
  return "multiAgentExperience::agent";
}

template<>
inline std::string multiAgentExperience::ipc::messaging::types::getName(const
                                                           std::shared_ptr<::multiAgentExperience::agent::AgentRegistrationInterface> &t) {
  return "AgentRegistration";
}

/// We need a hardcoded reference for AgentRegistration identifier because this same hardcoded
/// reference will be use by the Agent Shim while adding an AgentRegistrationMessageHandler in
/// their corresponding MessageHandlerStore using messageHandlerStore->createOrGet(). This hardcoded
/// reference is required for handling the special case of AgentRegistration when MAX submits a call
/// to a method like onReady(), getId() or getName() for the agent registration to happen
/// successfully. AgentRegistration is a special case because such messages are exchanged only once
/// that is at the time of registration and the agent side should already have the message handler
/// created in order to handle such kind of messages from MAX
template<>
inline std::size_t multiAgentExperience::ipc::messaging::types::getIdentifier(const
std::shared_ptr<::multiAgentExperience::agent::AgentRegistrationInterface> &t) {
    return 123456789;
}

#endif // MULTIAGENTEXPERIENCE_IPC_AGENTREGISTRATIONMODEL_H