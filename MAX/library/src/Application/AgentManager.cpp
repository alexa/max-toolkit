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

#include "Application/AgentManager.h"

#include "Core/Transformer/ActivityManagerTransformerFactory.h"
#include "Core/Transformer/AgentStore.h"
#include "Core/Transformer/DialogManagerTransformerFactory.h"
#include "MultiAgentExperience/Agent/Agent.h"
#include "Utils/Logger/Logger.h"

namespace multiAgentExperience {
namespace library {
namespace application {

static const std::string MODULE_TAG("AgentManager");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

using namespace multiAgentExperience::agent;
using namespace multiAgentExperience::activity;
using namespace multiAgentExperience::library::core;

std::shared_ptr<AgentManager> AgentManager::create(
    std::shared_ptr<transformer::AgentTransferManagerTransformerFactory> agentTransferManagerTransformerFactory,
    std::shared_ptr<transformer::ActivityManagerTransformerFactory> activityManagerTransformerFactory,
    std::shared_ptr<transformer::DialogManagerTransformerFactory> dialogManagerTransformerFactory) {
    LX(DEBUG3, "");

    auto manager = std::shared_ptr<AgentManager>(new AgentManager(
        agentTransferManagerTransformerFactory, activityManagerTransformerFactory, dialogManagerTransformerFactory));
    return manager;
}

AgentManager::AgentManager(
    std::shared_ptr<transformer::AgentTransferManagerTransformerFactory> agentTransferManagerTransformerFactory,
    std::shared_ptr<transformer::ActivityManagerTransformerFactory> activityManagerTransformerFactory,
    std::shared_ptr<transformer::DialogManagerTransformerFactory> dialogManagerTransformerFactory) :
        m_agentTransferManagerTransformerFactory{agentTransferManagerTransformerFactory},
        m_activityManagerTransformerFactory{activityManagerTransformerFactory},
        m_dialogManagerTransformerFactory{dialogManagerTransformerFactory} {
}

bool AgentManager::registerAgent(std::shared_ptr<Agent> agent) {
    LX(DEBUG3, "");

    if (!agent) {
        LX(ERROR, "registerAgentFailed: agent was nullptr");
        return false;
    }

    if (m_agents.find(agent) != m_agents.end()) {
        LX(ERROR, "registerAgentFailed: agent already registered");
        return false;
    }

    if (wakewordExists(agent->getWakeword())) {
        LX(ERROR, "registerAgentFailed: wakeword already exists for other agent:" + agent->getWakeword());
        return false;
    }

    m_agents.insert(agent);

    auto activityManagerTransformer = m_activityManagerTransformerFactory->create(agent->getId());

    auto dialogManagerTransformer = m_dialogManagerTransformerFactory->create(agent->getId());

    auto agentStore = std::make_shared<core::transformer::AgentStore>(shared_from_this());
    auto agentTransferManagerTransformer = m_agentTransferManagerTransformerFactory->create(agent->getId(), agentStore);

    agent->initializeCoreInterfaces(
        activityManagerTransformer, dialogManagerTransformer, agentTransferManagerTransformer);

    LX(DEBUG3, "registerAgent succeeded.");

    return true;
}

std::shared_ptr<Agent> AgentManager::getAgentById(const multiAgentExperience::actor::ActorId& agentId) {
    LX(DEBUG3, "");

    for (auto agent : m_agents) {
        if (agent->getId() == agentId) {
            return agent;
        }
    }
    return nullptr;
}

void AgentManager::deregisterAgent(std::shared_ptr<Agent> agent) {
    LX(DEBUG3, "");

    if (!agent) {
        LX(ERROR, "deregisterAgentFailed: agent was nullptr");
        return;
    }

    if (m_agents.find(agent) == m_agents.end()) {
        LX(ERROR, "deregisterAgentFailed: agent not registered");
        return;
    }

    m_agents.erase(agent);

    LX(DEBUG3, "deregisterAgent succeeded.");
}

void AgentManager::onWakeWordDetected(const std::string& wakeWord) {
    LX(DEBUG3, "wakeword detected:" + wakeWord);
    for (auto agent : m_agents) {
        LX(DEBUG3, "testing for agent:" + agent->getId().get() + " with WW:" + agent->getWakeword());
        if (agent->getWakeword() == wakeWord) {
            LX(DEBUG3, "notifying agent:" + agent->getId().get());
            agent->onWakeWordDetected();
            break;
        }
    }
}

bool AgentManager::wakewordExists(const std::string& wakeword) {
    if (wakeword.empty()) {
        LX(DEBUG3, "Ignoring wakeword check as no wakeword is supported.");
        return false;
    }

    for (auto agent : m_agents) {
        if (agent->getWakeword() == wakeword) {
            return true;
        }
    }

    return false;
}

}  // namespace application
}  // namespace library
}  // namespace multiAgentExperience
