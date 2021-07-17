/*
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include "MultiAgentExperience/Agent/Agent.h"

namespace multiAgentExperience {
namespace agent {

Agent::Agent(const actor::ActorId& id, const std::string& wakeword) : m_id{id}, m_wakeword{wakeword} {
}

void Agent::initializeCoreInterfaces(
    std::shared_ptr<multiAgentExperience::activity::ActivityManagerInterface> activityManager,
    std::shared_ptr<dialog::DialogManagerInterface> dialogManager,
    std::shared_ptr<AgentTransferManagerInterface> agentTransferManager) {
    m_activityManager = activityManager;
    m_dialogManager = dialogManager;
    m_agentTransferManager = agentTransferManager;
    onInitialized();
}

actor::ActorId Agent::getId() {
    return m_id;
}

std::string Agent::getWakeword() {
    return m_wakeword;
}

void Agent::onWakeWordDetected() {
    handleOnWakeWordDetected();
}

void Agent::onTapDetected() {
    handleOnTapDetected();
}

void Agent::onAgentTransfer() {
    handleOnAgentTransfer();
}

}  // namespace agent
}  // namespace multiAgentExperience
