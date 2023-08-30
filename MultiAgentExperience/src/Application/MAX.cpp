/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include <utility>
#include "Application/MAX.h"

#include "Activity/ActivityManagerFactory.h"
#include "Application/AgentManager.h"
#include "Application/MAXLifecycle.h"
#include "Control/ControlStore.h"
#include "Control/ControlInvokerFactory.h"
#include "Control/ControlRegistryFactory.h"
#include "Control/CurrentControls.h"
#include "Dialog/DialogManagerFactory.h"
#include "Experience/ExperienceManager.h"

#include "Core/Transformer/ActivityRequestTransformerFactory.h"
#include "Core/Transformer/ControlInvokerTransformer.h"
#include "Core/Transformer/ControlManagerTransformer.h"
#include "Core/Transformer/SetupManagerTransformer.h"
#include "Core/Transformer/StaticExperienceManagerTransformerFactory.h"

namespace multiAgentExperience {
namespace library {
namespace application {

static const std::string MODULE_TAG("MAX");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

using namespace multiAgentExperience::agent;

std::shared_ptr<MAX> MAX::create(
    const actor::ActorId& integratorActorId,
    multiAgentExperience::application::HighPriorityCrossAgentBargeInPolicy highPriorityCrossAgentBargeInPolicy,
    multiAgentExperience::application::NormalPriorityCrossAgentBargeInPolicy normalPriorityCrossAgentBargeInPolicy,
    const std::map<
        multiAgentExperience::activity::ActivityType,
        multiAgentExperience::application::ActivitySchedulingPolicy>& activitySchedulingPolicyMap) {
    LX(DEBUG3, "");

    auto controlAccessKeys = std::make_shared<library::control::ControlAccessKeys>();
    auto controlStore = std::make_shared<library::control::ControlStore>(controlAccessKeys);
    auto controlRegistryFactory =
        std::make_shared<library::control::ControlRegistryFactory>(controlAccessKeys, controlStore);
    auto controlInvokerFactory =
        std::make_shared<library::control::ControlInvokerFactory>(controlAccessKeys, controlStore);
    auto currentControls =
        std::make_shared<library::control::CurrentControls>(controlAccessKeys->requestAccessKey(), controlStore);

    auto deviceRestrictRequestsHelper = std::make_shared<device::DeviceRestrictRequestsHelper>();

    auto maxLifecycle = std::make_shared<MAXLifecycle>();

    auto activityManager = library::activity::ActivityManagerFactory::create(
        controlRegistryFactory,
        activitySchedulingPolicyMap,
        deviceRestrictRequestsHelper,
        maxLifecycle);

    /// experience manager now requires activity manager as input during its construction as there
    /// is a requirement to sort experiences in the priority order of their ActivityId's
    auto experienceManager = std::make_shared<library::experience::ExperienceManager>(activityManager);

    auto dialogManager = library::dialog::DialogManagerFactory::create(
        activityManager,
        currentControls,
        controlInvokerFactory,
        controlRegistryFactory,
        deviceRestrictRequestsHelper,
        highPriorityCrossAgentBargeInPolicy,
        normalPriorityCrossAgentBargeInPolicy);

    auto activityRequestTransformerFactory =
        std::make_shared<core::transformer::ActivityRequestTransformerFactory>(activityManager, experienceManager);
    auto activityManagerTransformerFactory = std::make_shared<core::transformer::ActivityManagerTransformerFactory>(
        activityManager, activityRequestTransformerFactory);

    auto dialogControllerTransformerFactory =
        std::make_shared<core::transformer::DialogControllerTransformerFactory>(controlInvokerFactory);
    auto dialogManagerTransformerFactory = std::make_shared<core::transformer::DialogManagerTransformerFactory>(
        dialogManager, experienceManager, dialogControllerTransformerFactory);

    /// factory instance that will be used by MAX agent manager to provide static experience
    /// manager instances to MAX conformant agents
    auto staticExperienceManagerTransformerFactory =
        std::make_shared<library::core::transformer ::StaticExperienceManagerTransformerFactory>(experienceManager);

    auto agentManager = library::application::AgentManager::create(
        activityManagerTransformerFactory,
        dialogManagerTransformerFactory,
        staticExperienceManagerTransformerFactory,
        maxLifecycle);

    auto integratorActivityManager = activityManagerTransformerFactory->create(integratorActorId);

    auto integratorControlManager =
        std::make_shared<core::transformer::ControlManagerTransformer>(integratorActorId, controlStore, activityManager);

    auto controlInvoker = controlInvokerFactory->create();
    auto integratorControlInvoker =
        std::make_shared<core::transformer::ControlInvokerTransformer>(integratorActorId, controlInvoker);

    auto setupManager = std::make_shared<core::transformer::SetupManagerTransformer>(deviceRestrictRequestsHelper, activityManager);

    return std::shared_ptr<MAX>(new MAX(
        integratorActorId,
        agentManager,
        experienceManager,
        integratorActivityManager,
        integratorControlManager,
        integratorControlInvoker,
        setupManager));
}

MAX::MAX(
    actor::ActorId integratorActorId,
    std::shared_ptr<multiAgentExperience::agent::AgentManagerInterface> agentManager,
    std::shared_ptr<multiAgentExperience::experience::ExperienceManagerInterface> experienceManager,
    std::shared_ptr<multiAgentExperience::activity::ActivityManagerInterface> activityManager,
    std::shared_ptr<multiAgentExperience::control::ControlManagerInterface> controlManager,
    std::shared_ptr<multiAgentExperience::control::ControlInvokerInterface> controlInvoker,
    std::shared_ptr<multiAgentExperience::device::SetupManagerInterface> setupManager) :
        m_integratorActorId{std::move(integratorActorId)},
        m_agentManager{std::move(agentManager)},
        m_experienceManager{std::move(experienceManager)},
        m_activityManager{std::move(activityManager)},
        m_controlManager{std::move(controlManager)},
        m_controlInvoker{std::move(controlInvoker)},
        m_setupManager{std::move(setupManager)} {
}

std::shared_ptr<multiAgentExperience::experience::ExperienceManagerInterface> MAX::getExperienceManager() {
    return m_experienceManager;
}

std::shared_ptr<multiAgentExperience::agent::AgentManagerInterface> MAX::getAgentManager() {
    return m_agentManager;
}

std::shared_ptr<multiAgentExperience::control::ControlManagerInterface> MAX::getControlManager() {
    return m_controlManager;
}

std::shared_ptr<multiAgentExperience::control::ControlInvokerInterface> MAX::getControlInvoker() {
    return m_controlInvoker;
}

std::shared_ptr<multiAgentExperience::activity::ActivityManagerInterface> MAX::getActivityManager() {
    return m_activityManager;
}

std::shared_ptr<multiAgentExperience::device::SetupManagerInterface> MAX::getSetupManager() {
    return m_setupManager;
}

void MAX::setLogLevel(multiAgentExperience::utils::Log::Level level) {
    multiAgentExperience::logger::getLoggerInstance()->setLogLevel(level);
}

}  // namespace application
}  // namespace library
}  // namespace multiAgentExperience
