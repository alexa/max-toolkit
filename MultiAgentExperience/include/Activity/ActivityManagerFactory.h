/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYMANAGERFACTORY_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYMANAGERFACTORY_H_

#include <map>
#include <memory>

#include <MultiAgentExperience/Activity/ActivityType.h>
#include <MultiAgentExperience/Application/MAXPolicies.h>

#include "ActivityManager.h"
#include "Application/MAXLifecycle.h"
#include "Control/ControlRegistryFactory.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

struct ActivityManagerFactory {
    static std::shared_ptr<ActivityManager> create(
        std::shared_ptr<control::ControlRegistryFactory> controlRegistryFactory,
        const std::map<
            multiAgentExperience::activity::ActivityType,
            multiAgentExperience::application::ActivitySchedulingPolicy>& activitySchedulingPolicyMap,
        std::shared_ptr<device::DeviceRestrictRequestsHelper> deviceRestrictRequestsHelper,
        std::shared_ptr<application::MAXLifecycle> maxLifecycle,
        const bool async = true);
};

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYMANAGERFACTORY_H_
