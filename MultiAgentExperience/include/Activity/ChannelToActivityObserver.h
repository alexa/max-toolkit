/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_CHANNELTOACTIVITYOBSERVER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_CHANNELTOACTIVITYOBSERVER_H_

#include <memory>
#include <mutex>

#include "ActivityRequestID.h"
#include "FocusManager/ChannelObserverInterface.h"
#include "Control/ControlPriority.h"
#include "Control/ControlRegistryFactory.h"
#include "ActivityLifecycle.h"
#include "CurrentActivityRequests.h"
#include "CurrentActivities.h"
#include "FocusManagerActivityChannels.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

class ChannelToActivityObserver : public ChannelObserverInterface {
public:
    ChannelToActivityObserver(
        std::shared_ptr<CurrentActivityRequests> activeRequests,
        std::shared_ptr<CurrentActivities> currentActivities,
        const control::ControlPriority controlPriority,
        std::shared_ptr<control::ControlRegistryFactory> controlRegistryFactory,
        ActivityRequestID activityRequestId,
        std::shared_ptr<FocusManagerActivityChannels::CleanupCallback> cleanupCallback);

    ~ChannelToActivityObserver();

    /// @name ChannelObserverInterface method overrides.
    /// @{
    void onFocusChanged(FocusState newFocus, MixingBehavior behavior) override;
    /// @}

private:
    void cleanup();

    std::shared_ptr<CurrentActivityRequests> m_activeRequests;
    std::shared_ptr<CurrentActivities> m_currentActivities;
    const control::ControlPriority m_controlPriority;
    std::shared_ptr<control::ControlRegistryFactory> m_controlRegistryFactory;
    const ActivityRequestID m_activityRequestID;
    bool m_requestHandled;
    std::shared_ptr<ActivityLifecycle> m_activity;
    std::shared_ptr<FocusManagerActivityChannels::CleanupCallback> m_cleanupCallback;
};

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_CHANNELTOACTIVITYOBSERVER_H_
