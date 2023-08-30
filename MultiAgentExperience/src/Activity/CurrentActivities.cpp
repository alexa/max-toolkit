/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <unordered_set>
#include "Activity/CurrentActivities.h"

#include "Activity/ActivityLifecycle.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

void CurrentActivities::add(const ActivityID activityId, std::shared_ptr<ActivityLifecycle> activity) {
    std::unique_lock<std::mutex> lock(m_activitiesMutex);
    m_activities[activityId] = activity;
}

bool CurrentActivities::isCurrent(const ActivityID activityId) {
    std::unique_lock<std::mutex> lock(m_activitiesMutex);
    return m_activities.find(activityId) != m_activities.end();
}

void CurrentActivities::remove(const ActivityID activityId) {
    std::shared_ptr<ActivityLifecycle> activity;
    {
        std::unique_lock<std::mutex> lock(m_activitiesMutex);
        auto activityEntry = m_activities.find(activityId);
        if (activityEntry != m_activities.end()) {
            activity = activityEntry->second;
            m_activities.erase(activityId);
        }
    }

    if (activity) {
        activity->stop();
    }
}

ActivityLifecyclesSortedByPriorityAndActivityId CurrentActivities::getAllActivitiesSortedByPriority() {
    ActivityLifecyclesSortedByPriorityAndActivityId activityLifecycles;

    {
        std::unique_lock<std::mutex> lock(m_activitiesMutex);
        for (auto& activity : m_activities) {
            activityLifecycles.insert(activity.second);
        }
    }

    return activityLifecycles;
}

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience
