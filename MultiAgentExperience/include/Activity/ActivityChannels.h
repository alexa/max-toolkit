/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYCHANNELS_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYCHANNELS_H_

#include <memory>

#include "ActivityRequestID.h"
#include "ActivityRequestLifecycle.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

class ActivityChannels {
public:
    virtual ~ActivityChannels() = default;

    virtual bool add(std::shared_ptr<ActivityRequestLifecycle> activityRequest) = 0;

    virtual void remove(const ActivityRequestID activityRequestId) = 0;

    virtual ActivityLifecyclesSortedByPriorityAndActivityId getAllActivitiesSortedByPriority() = 0;
};

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYCHANNELS_H_
