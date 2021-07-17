/*
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

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

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience
