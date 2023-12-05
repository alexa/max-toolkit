/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#include "MultiAgentExperience/AlexaAdapter/Agent/AlexaAgentRegistration.h"
#include "MultiAgentExperience/AlexaAdapter/Dialog/AlexaControlReceiver.h"
#include "MultiAgentExperience/AlexaAdapter/UniversalDeviceController/UniversalDeviceCommandsProvider.h"

#include "AVSCommon/Utils/Logger/Logger.h"
#include "MultiAgentExperience/AlexaAdapter/Alexa/AlexaAgentNames.h"
#include "MultiAgentExperience/AlexaAdapter/Experience/AlexaNotificationsObserver.h"

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace agent {

static const std::string TAG("AlexaAgentRegistration");
#define LX(event) alexaClientSDK::avsCommon::utils::logger::LogEntry(TAG, event)

void AlexaAgentRegistration::onReady(
        std::shared_ptr<::multiAgentExperience::common::OnCompletionCallbackInterface> onCompletionCallback,
        std::shared_ptr<::multiAgentExperience::activity::ActivityManagerInterface> activityManager,
        std::shared_ptr<::multiAgentExperience::dialog::DialogManagerInterface> dialogManager,
        std::shared_ptr<::multiAgentExperience::experience::StaticExperienceManagerInterface> staticExperienceManager) {

    ACSDK_DEBUG5(LX(__func__));

    if (m_doNotDisturbSettingObserver) {
        m_doNotDisturbSettingObserver->onReady(staticExperienceManager);
    } else {
        ACSDK_INFO(LX(__func__).m("doNotDisturbSettingObserver is null"));
    }

    if (m_notificationsObserver) {
        m_notificationsObserver->onReady(staticExperienceManager);
    } else {
        ACSDK_INFO(LX(__func__).m("notificationsObserver is null"));
    }

    auto activityRequester = std::make_shared<mediator::MAXActivityFocusRequester>(activityManager);

    // TODO: inject an AlexaControlsReceiver in the future
    auto alexaControlReceiver = std::make_shared<dialog::AlexaControlReceiver>(m_universalDeviceCommandsProvider);
    auto dialogRequester = std::make_shared<mediator::MAXDialogFocusRequester>(dialogManager, alexaControlReceiver);
    m_mediator->onReady(activityRequester, dialogRequester, onCompletionCallback);

    m_universalDeviceCommandsInvoker->onReady(dialogRequester);
}

::multiAgentExperience::actor::ActorId AlexaAgentRegistration::getId() {
    //TODO: finalize alexa actor id with partner
    return ::multiAgentExperience::actor::ActorId(m_agentName);
}

std::string AlexaAgentRegistration::getName() {
    return m_agentName;
}

} // namespace agent
} // namespace multiAgentExperience
} // namespace alexaClientSDK
