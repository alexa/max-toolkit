/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#include "Application/AgentManager.h"

#include <functional>

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Common/CallbackDispatcher.h"
#include "Common/OnCompletionCallback.h"
#include "Core/Transformer/ActivityManagerTransformerFactory.h"
#include "Core/Transformer/AgentStore.h"
#include "Core/Transformer/DialogManagerTransformerFactory.h"
#include "MultiAgentExperience/Agent/AgentRegistrationInterface.h"

namespace multiAgentExperience {
namespace library {
namespace application {

static const std::string MODULE_TAG("AgentManager");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

using namespace multiAgentExperience::agent;
using namespace multiAgentExperience::activity;
using namespace multiAgentExperience::library::core;

std::shared_ptr<AgentManager> AgentManager::create(
    std::shared_ptr<transformer::ActivityManagerTransformerFactory> activityManagerTransformerFactory,
    std::shared_ptr<transformer::DialogManagerTransformerFactory> dialogManagerTransformerFactory,
    std::shared_ptr<transformer::StaticExperienceManagerTransformerFactory> staticExperienceManagerTransformerFactory,
    std::shared_ptr<MAXLifecycle> maxLifecycle) {
    LX(DEBUG3, "");

    auto manager = std::shared_ptr<AgentManager>(new AgentManager(
        activityManagerTransformerFactory,
        dialogManagerTransformerFactory,
        staticExperienceManagerTransformerFactory,
        maxLifecycle));
    return manager;
}

AgentManager::AgentManager(
    std::shared_ptr<transformer::ActivityManagerTransformerFactory> activityManagerTransformerFactory,
    std::shared_ptr<transformer::DialogManagerTransformerFactory> dialogManagerTransformerFactory,
    std::shared_ptr<transformer::StaticExperienceManagerTransformerFactory> staticExperienceManagerTransformerFactory,
    std::shared_ptr<MAXLifecycle> maxLifecycle) :
        m_activityManagerTransformerFactory{activityManagerTransformerFactory},
        m_dialogManagerTransformerFactory{dialogManagerTransformerFactory},
        m_staticExperienceManagerTransformerFactory{staticExperienceManagerTransformerFactory},
        m_maxLifecycle{maxLifecycle} {
}

bool AgentManager::registerAgents(std::set<std::shared_ptr<AgentRegistrationInterface>> agentRegistrations) {
    LX(DEBUG3, "");

    if (agentRegistrations.empty()) {
        LX(ERROR, "registerAgentFailed: set of agent registrations is empty");
        return false;
    }

    m_agentRegistrations = agentRegistrations;

    // The list of OnCompletion callbacks that MAX waits on
    std::vector<std::shared_ptr<common::CallbackDispatcher<common::OnCompletionCallback>>> onReadyDispatchers;

    for (auto agentRegistration : m_agentRegistrations) {
        auto activityManagerTransformer = m_activityManagerTransformerFactory->create(agentRegistration->getId());

        auto dialogManagerTransformer = m_dialogManagerTransformerFactory->create(agentRegistration->getId());

        auto agentStore = std::make_shared<core::transformer::AgentStore>(shared_from_this());
        auto staticExperienceManagerTransformer =
            m_staticExperienceManagerTransformerFactory->create(agentRegistration->getId());

        auto onReadyDispatcher = std::make_shared<common::CallbackDispatcher<common::OnCompletionCallback>>();
        (*onReadyDispatcher)(
            agentRegistration,
            &AgentRegistrationInterface::onReady,
            activityManagerTransformer,
            dialogManagerTransformer,
            staticExperienceManagerTransformer);
        onReadyDispatchers.push_back(onReadyDispatcher);
    }

    // Iterate through the list and conditionally wait for each callback to be executed by the agent
    for (auto& onReadyDispatcher : onReadyDispatchers) {
        onReadyDispatcher->waitForCallback();
    }

    // Transition to ready when all @c OnCompletionCallbacks (for @c AgentRegistrationInterface::onReady) are received.
    m_maxLifecycle->transitionToReady();

    LX(DEBUG3, "registerAgent succeeded for all agents.");

    return true;
}

std::shared_ptr<AgentRegistrationInterface> AgentManager::getAgentById(
    const multiAgentExperience::actor::ActorId& agentId) {
    LX(DEBUG3, "");

    for (auto agentRegistration : m_agentRegistrations) {
        if (agentRegistration->getId() == agentId) {
            return agentRegistration;
        }
    }
    return nullptr;
}

void AgentManager::deregisterAgent(std::shared_ptr<AgentRegistrationInterface> agentRegistration) {
    LX(DEBUG3, "");

    if (!agentRegistration) {
        LX(ERROR, "deregisterAgentFailed: agent was nullptr");
        return;
    }

    if (m_agentRegistrations.find(agentRegistration) == m_agentRegistrations.end()) {
        LX(ERROR, "deregisterAgentFailed: agent not registered");
        return;
    }

    m_agentRegistrations.erase(agentRegistration);

    LX(DEBUG3, "deregisterAgent succeeded.");
}
}  // namespace application
}  // namespace library
}  // namespace multiAgentExperience
