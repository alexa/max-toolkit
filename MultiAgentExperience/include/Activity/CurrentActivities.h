/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_CURRENTACTIVITIES_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_CURRENTACTIVITIES_H_

#include <memory>
#include <mutex>
#include <unordered_map>
#include <set>

#include "ActivityID.h"
#include "ActivityRequestID.h"
#include "ActivityLifecycle.h"
#include "ActivityType.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

class CurrentActivities {
public:
    void add(const ActivityID activityRequestId, std::shared_ptr<ActivityLifecycle> activity);

    bool isCurrent(const ActivityID activityId);

    void remove(const ActivityID activityId);

    ActivityLifecyclesSortedByPriorityAndActivityId getAllActivitiesSortedByPriority();

private:
    std::mutex m_activitiesMutex;
    std::unordered_map<ActivityID, std::shared_ptr<ActivityLifecycle>> m_activities;
};

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_CURRENTACTIVITIES_H_
