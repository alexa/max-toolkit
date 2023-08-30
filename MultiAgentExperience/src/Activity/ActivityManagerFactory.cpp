/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Activity/ActivityManagerFactory.h"

#include "Activity/ActivityManager.h"
#include "Activity/CurrentActivities.h"
#include "Activity/CurrentActivityRequests.h"
#include "Activity/FocusManagerActivityChannels.h"
#include "Activity/FocusManager/FocusManager.h"
#include "Activity/LoggingActivityTracker.h"
#include "Control/Control.h"
#include "Control/ControlRegistryFactory.h"
#include "Control/ControlStore.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

std::shared_ptr<ActivityManager> ActivityManagerFactory::create(
    std::shared_ptr<control::ControlRegistryFactory> controlRegistryFactory,
    const std::map<
        multiAgentExperience::activity::ActivityType,
        multiAgentExperience::application::ActivitySchedulingPolicy>& activitySchedulingPolicyMap,
    std::shared_ptr<device::DeviceRestrictRequestsHelper> deviceRestrictRequestsHelper,
    std::shared_ptr<application::MAXLifecycle> maxLifecycle,
    const bool async) {
    auto executor = std::make_shared<multiAgentExperience::library::utils::threading::Executor>(async);
    auto loggingActivityTracker = std::make_shared<LoggingActivityTracker>();
    auto focusManager = std::make_shared<FocusManager>(
        FocusManagerActivityChannels::getChannelConfigurations(activitySchedulingPolicyMap), executor, loggingActivityTracker);
    auto currentActivityRequests = std::make_shared<CurrentActivityRequests>();
    auto currentActivities = std::make_shared<CurrentActivities>();
    auto activityChannels = std::make_shared<FocusManagerActivityChannels>(
        focusManager, currentActivityRequests, currentActivities, controlRegistryFactory);

    auto activityManager = std::make_shared<ActivityManager>(
        activityChannels,
        currentActivityRequests,
        deviceRestrictRequestsHelper,
        maxLifecycle);

    /// Register the activityManager (which implements the @c MAXLifecycleObserverInterface) with MAXLifecycle
    maxLifecycle->addObserver(activityManager);

    return activityManager;
}

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience
