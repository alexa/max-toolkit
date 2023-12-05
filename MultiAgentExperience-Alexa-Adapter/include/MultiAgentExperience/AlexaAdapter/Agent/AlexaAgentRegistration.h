/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_AGENT_ALEXAAGENTREGISTRATION_H
#define MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_AGENT_ALEXAAGENTREGISTRATION_H

#include <MultiAgentExperience/Agent/AgentRegistrationInterface.h>

#include <utility>

#include "MultiAgentExperience/AlexaAdapter/Alexa/AlexaAgentNames.h"
#include "MultiAgentExperience/AlexaAdapter/Experience/AlexaNotificationsObserver.h"
#include "MultiAgentExperience/AlexaAdapter/Experience/DoNotDisturbSettingObserver.h"
#include "MultiAgentExperience/AlexaAdapter/Mediator/MAXFocusMediator.h"
#include "MultiAgentExperience/AlexaAdapter/UniversalDeviceController/UniversalDeviceCommandsInvoker.h"
#include "MultiAgentExperience/AlexaAdapter/UniversalDeviceController/UniversalDeviceCommandsProvider.h"

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace agent {

class AlexaAgentRegistration : public ::multiAgentExperience::agent::AgentRegistrationInterface {

public:
    explicit AlexaAgentRegistration(
        std::shared_ptr<mediator::MAXFocusMediator> mediator,
        std::shared_ptr<multiAssistant::universalDeviceController::UniversalDeviceCommandsInvoker> universalDeviceCommandsInvoker,
        std::shared_ptr<multiAssistant::universalDeviceController::UniversalDeviceCommandsProvider> universalDeviceCommandsProvider,
        std::shared_ptr<experience::DoNotDisturbSettingObserver> doNotDisturbSettingObserver = nullptr,
        std::shared_ptr<experience::AlexaNotificationsObserver> notificationsObserver = nullptr,
        const std::string& agentName = alexaClientSDK::multiAgentExperience::alexa::ALEXA_AGENT_NAME) :
            m_mediator{std::move(mediator)},
            m_universalDeviceCommandsInvoker{std::move(universalDeviceCommandsInvoker)},
            m_universalDeviceCommandsProvider{std::move(universalDeviceCommandsProvider)},
            m_doNotDisturbSettingObserver{doNotDisturbSettingObserver},
            m_notificationsObserver{notificationsObserver},
            m_agentName{agentName} {
    }

    void onReady(
        std::shared_ptr<::multiAgentExperience::common::OnCompletionCallbackInterface> onCompletionCallback,
        std::shared_ptr<::multiAgentExperience::activity::ActivityManagerInterface> activityManager,
        std::shared_ptr<::multiAgentExperience::dialog::DialogManagerInterface> dialogManager,
        std::shared_ptr<::multiAgentExperience::experience::StaticExperienceManagerInterface> staticExperienceManager) final;

    ::multiAgentExperience::actor::ActorId getId() final;

    std::string getName() final;

private:
    std::shared_ptr<mediator::MAXFocusMediator> m_mediator;
    std::shared_ptr<multiAssistant::universalDeviceController::UniversalDeviceCommandsInvoker> m_universalDeviceCommandsInvoker;
    std::shared_ptr<multiAssistant::universalDeviceController::UniversalDeviceCommandsProvider> m_universalDeviceCommandsProvider;
    std::shared_ptr<experience::DoNotDisturbSettingObserver> m_doNotDisturbSettingObserver;
    std::shared_ptr<experience::AlexaNotificationsObserver> m_notificationsObserver;
    std::string m_agentName;
};

} // namespace agent
} // namespace multiAgentExperience
} // namespace alexaClientSDK

#endif //MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_AGENT_ALEXAAGENTREGISTRATION_H
