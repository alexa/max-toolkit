/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYMANAGER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYMANAGER_H_

#include <memory>
#include <unordered_map>

#include "ActivityRequestID.h"
#include "ActivityType.h"
#include "ActivityChannels.h"
#include "ActivityRequest.h"
#include "ActivitySnapshot.h"
#include "Application/MAXLifecycle.h"
#include "CurrentActivityRequests.h"
#include "CurrentActivities.h"
#include "Device/DeviceRestrictRequestsHelper.h"
#include "ActivityRequestBuffer.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

class ActivityManager : public multiAgentExperience::library::application::MAXLifecycleObserverInterface {
public:
    ActivityManager(
        std::shared_ptr<ActivityChannels> activeChannels,
        std::shared_ptr<CurrentActivityRequests> activityRequests,
        std::shared_ptr<device::DeviceRestrictRequestsHelper> deviceRestrictRequestsHelper,
        std::shared_ptr<application::MAXLifecycle> maxLifecycle);

    void request(std::shared_ptr<ActivityRequest> activityRequest);

    void finish(const ActivityRequestID activityRequestId);

    virtual ActivityLifecyclesSortedByPriorityAndActivityId getAllActivitiesSortedByPriorityAndActivityId();

    std::shared_ptr<ActivitySnapshot> getForegroundActivitySnapshotFromOtherActor(const actor::ActorId& actorId);

    virtual void stopAllAlerts();

    virtual void stopAllActivities();

private:

    /// @name MAXLifecycleObserverInterface method overrides.
    /// @{
    /// This method is private, so that it is only accessible by @c MAXLifecycleObserverInterface
    void onTransitionToReady() override;
    /// @}

    std::shared_ptr<ActivityChannels> m_activityChannels;
    std::shared_ptr<CurrentActivityRequests> m_currentActivityRequests;
    std::shared_ptr<device::DeviceRestrictRequestsHelper> m_deviceRestrictRequestsHelper;
    std::shared_ptr<application::MAXLifecycle> m_maxLifecycle;
    ActivityRequestBuffer m_activityRequestBuffer;
};

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYMANAGER_H_
