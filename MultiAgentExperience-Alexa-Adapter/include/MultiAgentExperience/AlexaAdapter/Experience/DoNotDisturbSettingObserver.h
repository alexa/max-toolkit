/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_DONOTDISTURBSETTINGOBSERVER_H
#define MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_DONOTDISTURBSETTINGOBSERVER_H

#include <MultiAgentExperience/Experience/StaticExperienceManagerInterface.h>

#include <memory>
#include <mutex>

#include <AVSCommon/SDKInterfaces/DoNotDisturbSettingObserverInterface.h>

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace experience {

class DoNotDisturbSettingObserver
    : public alexaClientSDK::avsCommon::sdkInterfaces::DoNotDisturbSettingObserverInterface {
public:

    DoNotDisturbSettingObserver();

    void onDoNotDisturbSettingChanged(const bool& value) override;

    void onReady(
        std::shared_ptr<::multiAgentExperience::experience::StaticExperienceManagerInterface> staticExperienceManager);

private:
    /// Updates the static experience for pending notifications using the state stored in @c m_latestIndicatorState
    void updateStaticExperience();

    /// The @c StaticExperienceManager object which is expected to be given in @c onReady.
    std::shared_ptr<::multiAgentExperience::experience::StaticExperienceManagerInterface> m_staticExperienceManager;

    /// The latest boolean value for DoNotDisturbSetting received by the observer. This also helps
    /// us keep track of any updates that occur before the @c StaticExperienceManager object is provided to us.
    bool m_latestState;

    /// Mutex to synchronize access to shared members in the @c onDoNotDisturbSettingChanged() and @c updateStaticExperience() methods
    std::mutex m_mutex;
};

} // namespace experience
} // namespace multiAgentExperience
} // namespace alexaClientSDK


#endif //MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_DONOTDISTURBSETTINGOBSERVER_H
