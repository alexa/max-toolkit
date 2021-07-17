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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYMANAGER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYMANAGER_H_

#include <memory>
#include <unordered_map>

#include "ActivityRequestID.h"
#include "ActivityType.h"
#include "ActivityChannels.h"
#include "ActivityRequest.h"
#include "CurrentActivityRequests.h"
#include "CurrentActivities.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

class ActivityManager {
public:
    ActivityManager(
        std::shared_ptr<ActivityChannels> activeChannels,
        std::shared_ptr<CurrentActivityRequests> activityRequests);

    void request(std::shared_ptr<ActivityRequest> activityRequest);

    void finish(const ActivityRequestID activityRequestId);

private:
    std::shared_ptr<ActivityChannels> m_activityChannels;
    std::shared_ptr<CurrentActivityRequests> m_currentActivityRequests;
};

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYMANAGER_H_
