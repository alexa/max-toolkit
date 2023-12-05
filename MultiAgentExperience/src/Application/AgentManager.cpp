/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#include "Application/AgentManager.h"

#include <functional>

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Core/Transformer/ActivityManagerTransformerFactory.h"
#include "Core/Transformer/DialogManagerTransformerFactory.h"
#include "MultiAgentExperience/Agent/AgentRegistrationInterface.h"
#include "Utils/Threading/Executor.h"

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
    std::shared_ptr<MAXLifecycle> maxLifecycle,
    std::shared_ptr<multiAgentExperience::library::utils::threading::Executor> executor) :
        m_activityManagerTransformerFactory{std::move(activityManagerTransformerFactory)},
        m_dialogManagerTransformerFactory{std::move(dialogManagerTransformerFactory)},
        m_staticExperienceManagerTransformerFactory{std::move(staticExperienceManagerTransformerFactory)},
        m_maxLifecycle{std::move(maxLifecycle)},
        m_executor{std::move(executor)} {
}

bool AgentManager::registerAgents(std::set<std::shared_ptr<AgentRegistrationInterface>> agentRegistrations) {
    LX(DEBUG3, "");

    std::unique_lock<std::mutex> lock(m_mutex);

    if (agentRegistrations.empty()) {
        LX(ERROR, "registerAgentFailed: set of agent registrations is empty");
        return false;
    }

    m_agentRegistrations = agentRegistrations;

    // The list of OnCompletion callbacks that MAX waits on
    std::vector<std::shared_ptr<common::OnCompletionCallback>> onReadyCompletionCallbacks;

    // Invoke AgentRegistrationInterface::onReady() for each agent and store the CallbackDispatcher
    for (const auto& agentRegistration: m_agentRegistrations) {
        auto onReadyCompletionCallback = executeOnReady(agentRegistration);
        onReadyCompletionCallbacks.push_back(onReadyCompletionCallback);
    }

    /**
     * Wait for each callback to be executed by the agent. This allows all agents to re-request any activities/dialogs
     * after MAX recovers from a process crash. Once the agents have completed all requests, MAX can order the requests
     * based on their priorities. This ensures that the state of activities/dialogs is the same as before the crash.
     */
    for (const auto& onReadyCompletionCallback : onReadyCompletionCallbacks) {
        onReadyCompletionCallback->wait();
    }

    // Transition to ready when all OnCompletionCallbacks (for AgentRegistrationInterface::onReady) are received.
    m_maxLifecycle->transitionToReady();

    LX(DEBUG3, "registerAgents succeeded for all agents.");

    return true;
}

bool AgentManager::registerAgent(
    std::shared_ptr<multiAgentExperience::agent::AgentRegistrationInterface> agentRegistration) {
    LX(DEBUG3, "");

    std::unique_lock<std::mutex> lock(m_mutex);

    if (m_agentRegistrations.find(agentRegistration) != m_agentRegistrations.end()) {
        LX(ERROR, "registerAgentFailed: agent already registered. Agent should be deregistered before registering.");
        return false;
    }

    m_agentRegistrations.insert(agentRegistration);

    // Store the CallbackDispatcher for the agent registration
    auto onReadyCompletionCallback = executeOnReady(agentRegistration);

    onReadyCompletionCallback->wait();

    // Transition to ready when the OnCompletionCallback (for AgentRegistrationInterface::onReady) is received.
    m_maxLifecycle->transitionToReady();

    LX(DEBUG3, "registerAgent succeeded for the agent " + agentRegistration->getId().get());
    return true;
}

void AgentManager::deregisterAgent(std::shared_ptr<AgentRegistrationInterface> agentRegistration) {
    LX(DEBUG3, "");

    std::unique_lock<std::mutex> lock(m_mutex);

    if (m_agentRegistrations.find(agentRegistration) == m_agentRegistrations.end()) {
        LX(ERROR, "deregisterAgentFailed: agent not registered");
        return;
    }

    m_agentRegistrations.erase(agentRegistration);

    LX(DEBUG3, "deregisterAgent succeeded.");
}

std::shared_ptr<common::OnCompletionCallback> AgentManager::executeOnReady(
    std::shared_ptr<multiAgentExperience::agent::AgentRegistrationInterface> agentRegistration) {
    LX(DEBUG3, "");

    auto onReadyCompletionCallback = std::make_shared<common::OnCompletionCallback>();

    m_executor->submit([this, onReadyCompletionCallback, agentRegistration]() {
        auto activityManagerTransformer = m_activityManagerTransformerFactory->create(agentRegistration->getId());
        auto dialogManagerTransformer = m_dialogManagerTransformerFactory->create(agentRegistration->getId());
        auto staticExperienceManagerTransformer =
            m_staticExperienceManagerTransformerFactory->create(agentRegistration->getId());

        agentRegistration->onReady(
            onReadyCompletionCallback,
            activityManagerTransformer,
            dialogManagerTransformer,
            staticExperienceManagerTransformer);
    });

    return onReadyCompletionCallback;
}

}  // namespace application
}  // namespace library
}  // namespace multiAgentExperience
