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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYREQUESTLIFECYCLE_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYREQUESTLIFECYCLE_H_

#include <memory>
#include <mutex>

#include "Activity.h"
#include "ActivityID.h"
#include "ActivityLifecycle.h"
#include "ActivityRequest.h"
#include "ActivityRequestID.h"
#include "ActivityType.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

class ActivityRequestLifecycle {
public:
    ActivityRequestLifecycle(std::shared_ptr<ActivityRequest> activityRequest);

    std::shared_ptr<ActivityLifecycle> grant();

    void deny();

    void remove();

    void finish();

    bool enqueue();

    const ActivityRequestID getID();

    const ActivityID getActivityID();

    const ActivityType getActivityType();

private:
    enum class ActivityRequestState { REQUESTED, WAITING, GRANTED, DENIED, COMPLETED };

    std::mutex m_stateMutex;
    ActivityRequestState m_state;
    std::shared_ptr<ActivityRequest> m_activityRequest;
};

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYREQUESTLIFECYCLE_H_
