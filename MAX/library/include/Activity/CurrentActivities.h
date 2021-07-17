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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_CURRENTACTIVITIES_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_CURRENTACTIVITIES_H_

#include <memory>
#include <mutex>
#include <unordered_map>

#include "ActivityID.h"
#include "ActivityRequestID.h"
#include "ActivityLifecycle.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

class CurrentActivities {
public:
    void add(const ActivityID activityRequestId, std::shared_ptr<ActivityLifecycle> activity);

    bool isCurrent(const ActivityID activityId);

    void remove(const ActivityID activityId);

private:
    std::mutex m_activitiesMutex;
    std::unordered_map<ActivityID, std::shared_ptr<ActivityLifecycle>> m_activities;
};

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_CURRENTACTIVITIES_H_
