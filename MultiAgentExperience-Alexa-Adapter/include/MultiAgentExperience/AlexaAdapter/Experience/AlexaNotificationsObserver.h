/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_ACTIVITY_ALEXANOTIFICATIONSOBSERVER_H
#define MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_ACTIVITY_ALEXANOTIFICATIONSOBSERVER_H

#include <acsdkNotificationsInterfaces/NotificationsObserverInterface.h>

#include <memory>
#include <mutex>

#include <AVSCommon/AVS/IndicatorState.h>
#include <MultiAgentExperience/AlexaAdapter/Alexa/AlexaExperiencePriorities.h>
#include <MultiAgentExperience/Experience/ExperienceId.h>
#include <MultiAgentExperience/Experience/StaticExperienceManagerInterface.h>

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace experience {

class AlexaNotificationsObserver : public acsdkNotificationsInterfaces::NotificationsObserverInterface {
public:

    AlexaNotificationsObserver();

    /// @name NotificationsObserverInterface Functions
    /// @{
    void onSetIndicator(avsCommon::avs::IndicatorState state) override;
    void onNotificationReceived() override;
    /// @}

    /// Stores the static experience manager object and takes some initialization action
    void onReady(
        std::shared_ptr<::multiAgentExperience::experience::StaticExperienceManagerInterface> staticExperienceManager);

private:
    /// Updates the static experience for pending notifications using the state stored in @c m_latestIndicatorState
    void updateStaticExperience();

    /// The @c StaticExperienceManager object which is expected to be given in @c onReady.
    std::shared_ptr<::multiAgentExperience::experience::StaticExperienceManagerInterface> m_staticExperienceManager;

    /// The latest IndicatorState received by the observer. This also helps us keep track of
    /// any updates that occur before the @c StaticExperienceManager object is provided to us.
    avsCommon::avs::IndicatorState m_latestIndicatorState;

    /// Mutex to synchronize access to shared members in the @c onSetIndicator() and @c updateStaticExperience() methods
    std::mutex m_mutex;
};

} // namespace experience
} // namespace multiAgentExperience
} // namespace alexaClientSDK

#endif //MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_ACTIVITY_ALEXANOTIFICATIONSOBSERVER_H