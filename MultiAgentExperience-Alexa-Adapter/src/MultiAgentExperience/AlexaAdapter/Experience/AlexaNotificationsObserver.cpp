/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/AlexaAdapter/Experience/AlexaNotificationsObserver.h"

#include "AVSCommon/Utils/Logger/Logger.h"
#include "MultiAgentExperience/AlexaAdapter/Alexa/AlexaAgentNames.h"
#include "MultiAgentExperience/AlexaAdapter/Alexa/AlexaExperienceIds.h"

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace experience {

static const std::string TAG("AlexaNotificationsObserver");
#define LX(event) alexaClientSDK::avsCommon::utils::logger::LogEntry(TAG, event)

AlexaNotificationsObserver::AlexaNotificationsObserver() :
        m_staticExperienceManager{},
        m_latestIndicatorState{avsCommon::avs::IndicatorState::OFF},
        m_mutex{} {
}

void AlexaNotificationsObserver::onSetIndicator(avsCommon::avs::IndicatorState state) {
    ACSDK_DEBUG3(LX(__func__).d("indicatorState", state));
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        // Store the latest indicator state
        m_latestIndicatorState = state;
    }

    updateStaticExperience();
}

void AlexaNotificationsObserver::updateStaticExperience() {
    if (m_staticExperienceManager) {
        std::lock_guard<std::mutex> lock(m_mutex);

        /// If the Notifications indicator state is turned on/off by AVS SDK then we use the static experience manager to
        /// communicate the relevant experience to MAX
        if (m_latestIndicatorState == avsCommon::avs::IndicatorState::ON) {
            ACSDK_DEBUG3(LX(__func__).m("Adding a static experience for pending notifications."));
            m_staticExperienceManager->addStaticExperience(
                    alexa::AlexaExperienceIds::PENDING_NOTIFICATION, alexa::AlexaExperiencePriorities::PENDING_NOTIFICATION);

        } else if (m_latestIndicatorState == avsCommon::avs::IndicatorState::OFF) {
            ACSDK_DEBUG3(LX(__func__).m("Removing the static experience for pending notifications."));
            m_staticExperienceManager->removeStaticExperience(alexa::AlexaExperienceIds::PENDING_NOTIFICATION);

        } else {
            ACSDK_ERROR(LX(__func__)
                .m("Unable to update static experience for pending notifications")
                .d("reason", "received unknown IndicatorState"));
        }
    }
}

void AlexaNotificationsObserver::onNotificationReceived() {}

void AlexaNotificationsObserver::onReady(
    std::shared_ptr<::multiAgentExperience::experience::StaticExperienceManagerInterface> staticExperienceManager) {
    ACSDK_DEBUG5(LX(__func__));

    m_staticExperienceManager = staticExperienceManager;

    /// If any static experience update was received before the StaticExperienceManager was set, that update was stored
    /// in @c m_latestIndicatorState. Now, we forward that information and update the static experience.
    updateStaticExperience();
}

} // namespace experience
} // namespace multiAgentExperience
} // namespace alexaClientSDK