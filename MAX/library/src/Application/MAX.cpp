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

#include <Core/Transformer/AgentTransferManagerTransformerFactory.h>
#include "Application/MAX.h"

#include "Application/AgentManager.h"
#include "Activity/ActivityManagerFactory.h"
#include "Agent/AgentTransferManager.h"
#include "Control/ControlStore.h"
#include "Control/ControlInvokerFactory.h"
#include "Control/ControlRegistryFactory.h"
#include "Control/CurrentControls.h"
#include "Dialog/DialogManagerFactory.h"
#include "Experience/ExperienceManager.h"
#include "Utils/Logger/Logger.h"

#include "Core/Transformer/ActivityRequestTransformerFactory.h"
#include "Core/Transformer/ControlInvokerTransformer.h"
#include "Core/Transformer/ControlManagerTransformer.h"

namespace multiAgentExperience {
namespace library {
namespace application {

static const std::string MODULE_TAG("MAX");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

using namespace multiAgentExperience::agent;

std::shared_ptr<MAX> MAX::create(const actor::ActorId integratorActorId) {
    LX(DEBUG3, "");

    static std::shared_ptr<MAX> manager;

    if (!manager) {
        auto controlAccessKeys = std::make_shared<library::control::ControlAccessKeys>();
        auto controlStore = std::make_shared<library::control::ControlStore>(controlAccessKeys);
        auto controlRegistryFactory =
            std::make_shared<library::control::ControlRegistryFactory>(controlAccessKeys, controlStore);
        auto controlInvokerFactory =
            std::make_shared<library::control::ControlInvokerFactory>(controlAccessKeys, controlStore);
        auto currentControls =
            std::make_shared<library::control::CurrentControls>(controlAccessKeys->requestAccessKey(), controlStore);

        auto experienceManager = std::make_shared<library::experience::ExperienceManager>();

        auto activityManager = library::activity::ActivityManagerFactory::create(controlRegistryFactory);

        auto dialogManager = library::dialog::DialogManagerFactory::create(
            activityManager, currentControls, controlInvokerFactory, controlRegistryFactory);

        auto activityRequestTransformerFactory =
            std::make_shared<core::transformer::ActivityRequestTransformerFactory>(activityManager, experienceManager);
        auto activityManagerTransformerFactory = std::make_shared<core::transformer::ActivityManagerTransformerFactory>(
            activityManager, activityRequestTransformerFactory);

        auto dialogControllerTransformerFactory =
            std::make_shared<core::transformer::DialogControllerTransformerFactory>(controlInvokerFactory);
        auto dialogManagerTransformerFactory = std::make_shared<core::transformer::DialogManagerTransformerFactory>(
            dialogManager, experienceManager, dialogControllerTransformerFactory);

        auto agentTransferManager = std::make_shared<agent::AgentTransferManager>();

        auto agentTransferManagerTransformerFactory =
            std::make_shared<library::core::transformer::AgentTransferManagerTransformerFactory>(agentTransferManager);

        auto agentManager = library::application::AgentManager::create(
            agentTransferManagerTransformerFactory, activityManagerTransformerFactory, dialogManagerTransformerFactory);

        auto integratorActivityManager = activityManagerTransformerFactory->create(integratorActorId);

        auto integratorControlManager =
            std::make_shared<core::transformer::ControlManagerTransformer>(integratorActorId, controlStore);

        auto controlInvoker = controlInvokerFactory->create();
        auto integratorControlInvoker =
            std::make_shared<core::transformer::ControlInvokerTransformer>(integratorActorId, controlInvoker);

        manager = std::shared_ptr<MAX>(new MAX(
            integratorActorId,
            agentManager,
            experienceManager,
            agentManager,
            integratorActivityManager,
            integratorControlManager,
            integratorControlInvoker));
    }

    return manager;
}

MAX::MAX(
    const actor::ActorId integratorActorId,
    std::shared_ptr<multiAgentExperience::agent::AgentManagerInterface> agentManager,
    std::shared_ptr<multiAgentExperience::experience::ExperienceManagerInterface> experienceManager,
    std::shared_ptr<multiAgentExperience::application::WakeWordObserverInterface> wakewordObserver,
    std::shared_ptr<multiAgentExperience::activity::ActivityManagerInterface> activityManager,
    std::shared_ptr<multiAgentExperience::control::ControlManagerInterface> controlManager,
    std::shared_ptr<multiAgentExperience::control::ControlInvokerInterface> controlInvoker) :
        m_integratorActorId{integratorActorId},
        m_agentManager{agentManager},
        m_experienceManager{experienceManager},
        m_wakewordObserver{wakewordObserver},
        m_activityManager{activityManager},
        m_controlManager{controlManager},
        m_controlInvoker{controlInvoker} {
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

std::shared_ptr<multiAgentExperience::application::WakeWordObserverInterface> MAX::getWakewordObserver() {
    return m_wakewordObserver;
}

std::shared_ptr<multiAgentExperience::activity::ActivityManagerInterface> MAX::getActivityManager() {
    return m_activityManager;
}

void MAX::setLogLevel(multiAgentExperience::utils::Log::Level level) {
    utils::logger::getLoggerInstance()->setLogLevel(level);
}

}  // namespace application
}  // namespace library
}  // namespace multiAgentExperience
