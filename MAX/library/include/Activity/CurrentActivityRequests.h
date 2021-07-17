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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_CURRENTACTIVITYREQUESTS_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_CURRENTACTIVITYREQUESTS_H_

#include <memory>
#include <mutex>
#include <unordered_map>

#include "Activity.h"
#include "ActivityID.h"
#include "ActivityRequestID.h"
#include "ActivityLifecycle.h"
#include "ActivityRequestLifecycle.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

class CurrentActivityRequests {
public:
    virtual ~CurrentActivityRequests();

    virtual void add(std::shared_ptr<ActivityRequestLifecycle> activityRequest);

    virtual std::shared_ptr<ActivityLifecycle> grant(const ActivityRequestID activityRequestId);

    virtual bool wait(const ActivityRequestID activityRequestId);

    virtual void deny(const ActivityRequestID activityRequestId);

    virtual const ActivityID remove(const ActivityRequestID activityRequestId);

    virtual const ActivityID finish(const ActivityRequestID activityRequestId);

private:
    enum class RemovalReason { DENIED, REMOVED, ABANDONED };

    const ActivityID finish(const ActivityRequestID activityRequestId, const RemovalReason state);

    std::mutex m_activeRequestsMutex;
    std::unordered_map<ActivityRequestID, std::shared_ptr<ActivityRequestLifecycle>> m_activityRequests;
};

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_CURRENTACTIVITYREQUESTS_H_
