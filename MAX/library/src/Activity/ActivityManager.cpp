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

#include "Activity/ActivityManager.h"

#include "Activity/ActivityChannels.h"
#include "Activity/ActivityRequest.h"
#include "Activity/ActivityRequestLifecycle.h"
#include "Activity/CurrentActivityRequests.h"
#include "Utils/Logger/Logger.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

static const std::string MODULE_TAG("ActivityManager");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ActivityManager::ActivityManager(
    std::shared_ptr<ActivityChannels> activityChannels,
    std::shared_ptr<CurrentActivityRequests> activityRequests) :
        m_activityChannels(activityChannels),
        m_currentActivityRequests(activityRequests) {
}

void ActivityManager::request(std::shared_ptr<ActivityRequest> activityRequest) {
    LX(DEBUG3, "");

    auto requestLifecycle = std::make_shared<ActivityRequestLifecycle>(activityRequest);
    m_currentActivityRequests->add(requestLifecycle);
    if (!m_activityChannels->add(requestLifecycle)) {
        auto id = activityRequest->getID();
        m_currentActivityRequests->remove(id);
    }
}

void ActivityManager::finish(const ActivityRequestID activityRequestId) {
    LX(DEBUG3, "");

    m_activityChannels->remove(activityRequestId);
}

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience
