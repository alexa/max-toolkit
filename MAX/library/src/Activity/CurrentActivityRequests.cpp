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

#include "Activity/CurrentActivityRequests.h"

#include "Activity/Activity.h"
#include "Activity/ActivityLifecycle.h"
#include "Activity/ActivityRequestLifecycle.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

void CurrentActivityRequests::add(std::shared_ptr<ActivityRequestLifecycle> activityRequest) {
    if (activityRequest) {
        std::unique_lock<std::mutex> lock(m_activeRequestsMutex);
        m_activityRequests[activityRequest->getID()] = activityRequest;
    }
}

std::shared_ptr<ActivityLifecycle> CurrentActivityRequests::grant(const ActivityRequestID activityRequestId) {
    std::shared_ptr<ActivityRequestLifecycle> request;
    {
        std::unique_lock<std::mutex> lock(m_activeRequestsMutex);
        auto requestEntry = m_activityRequests.find(activityRequestId);
        if (requestEntry != m_activityRequests.end()) {
            request = requestEntry->second;
        }
    }

    if (request) {
        return request->grant();
    } else {
        return nullptr;
    }
}

bool CurrentActivityRequests::wait(ActivityRequestID activityRequestId) {
    std::shared_ptr<ActivityRequestLifecycle> request;
    {
        std::unique_lock<std::mutex> lock(m_activeRequestsMutex);
        auto requestEntry = m_activityRequests.find(activityRequestId);
        if (requestEntry != m_activityRequests.end()) {
            request = requestEntry->second;
        }
    }
    if (request) {
        return request->enqueue();
    }
    return false;
}

void CurrentActivityRequests::deny(const ActivityRequestID activityRequestId) {
    finish(activityRequestId, RemovalReason::DENIED);
}

const ActivityID CurrentActivityRequests::remove(const ActivityRequestID activityRequestId) {
    return finish(activityRequestId, RemovalReason::REMOVED);
}

const ActivityID CurrentActivityRequests::finish(const ActivityRequestID activityRequestId) {
    return finish(activityRequestId, RemovalReason::ABANDONED);
}

const ActivityID CurrentActivityRequests::finish(
    const ActivityRequestID activityRequestId,
    const CurrentActivityRequests::RemovalReason state) {
    std::shared_ptr<ActivityRequestLifecycle> request;
    {
        std::unique_lock<std::mutex> lock(m_activeRequestsMutex);
        auto requestEntry = m_activityRequests.find(activityRequestId);
        if (requestEntry != m_activityRequests.end()) {
            request = requestEntry->second;
        }
    }

    if (request) {
        switch (state) {
            case RemovalReason::DENIED:
                request->deny();
                break;
            case RemovalReason::ABANDONED:
                request->finish();
                break;
            default:
                request->remove();
                break;
        }
        m_activityRequests.erase(activityRequestId);

        return request->getActivityID();
    } else {
        return -1;
    }
}

CurrentActivityRequests::~CurrentActivityRequests() {
}

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience
