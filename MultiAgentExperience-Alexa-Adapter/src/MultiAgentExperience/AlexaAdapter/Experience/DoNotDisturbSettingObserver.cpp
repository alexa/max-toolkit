/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#include "MultiAgentExperience/AlexaAdapter/Experience/DoNotDisturbSettingObserver.h"

#include "AVSCommon/Utils/Logger/Logger.h"
#include "MultiAgentExperience/AlexaAdapter/Alexa/AlexaExperienceIds.h"
#include "MultiAgentExperience/AlexaAdapter/Alexa/AlexaExperiencePriorities.h"

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace experience {

static const std::string TAG("DoNotDisturbSettingObserver");
#define LX(event) alexaClientSDK::avsCommon::utils::logger::LogEntry(TAG, event)

DoNotDisturbSettingObserver::DoNotDisturbSettingObserver() :
        m_staticExperienceManager{},
        m_latestState{false},
        m_mutex{} {
}

void DoNotDisturbSettingObserver::onDoNotDisturbSettingChanged(const bool& value) {
    ACSDK_DEBUG3(LX(__func__).d("DND Setting value", value));
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        // Store the latest DoNotDisturbSetting state
        m_latestState = value;
    }

    updateStaticExperience();
}

void DoNotDisturbSettingObserver::updateStaticExperience() {

    if (m_staticExperienceManager) {
        std::lock_guard<std::mutex> lock(m_mutex);

        /// If the DND mode is turned on by AVS SDK then we use the static experience manager to
        /// communicate the relevant DND experience to MAX
        if (m_latestState) {
            ACSDK_DEBUG3(LX(__func__).m("Adding static experience for DND."));
            m_staticExperienceManager->addStaticExperience(
                    alexa::AlexaExperienceIds::DND, alexa::AlexaExperiencePriorities::DND);
        } else {
            ACSDK_DEBUG3(LX(__func__).m("Removing static experience for DND."));
            m_staticExperienceManager->removeStaticExperience(alexa::AlexaExperienceIds::DND);
        }
    }
}

void DoNotDisturbSettingObserver::onReady(
    std::shared_ptr<::multiAgentExperience::experience::StaticExperienceManagerInterface> staticExperienceManager) {
    ACSDK_DEBUG5(LX(__func__));

    m_staticExperienceManager = staticExperienceManager;

    /// If any static experience update was received before the StaticExperienceManager was set, that update was stored
    /// in @c m_latestState. Now, we forward that information and update the static experience.
    updateStaticExperience();
}

} // namespace experience
} // namespace multiAgentExperience
} // namespace alexaClientSDK
