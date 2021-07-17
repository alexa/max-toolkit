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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYREQUEST_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYREQUEST_H_

#include <memory>

#include "Activity.h"
#include "ActivityRequestID.h"
#include "ActivityType.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

class ActivityRequest {
public:
    ActivityRequest(
        const ActivityType activityType,
        std::shared_ptr<Activity> activity,
        const bool willingToWait = false);

    virtual ~ActivityRequest();

    const ActivityType getActivityType() const;

    const std::shared_ptr<Activity> getActivity() const;

    bool isWillingToWait() const;

    const ActivityRequestID getID() const;

    virtual void onGranted() = 0;

    virtual void onDenied() = 0;

    virtual void onRemoved() = 0;

    virtual void onFinished() = 0;

    virtual void onWaiting() = 0;

private:
    const ActivityRequestID m_id;
    const ActivityType m_activityType;
    std::shared_ptr<Activity> m_activity;
    const bool m_willingToWait;
};

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

template <>
struct std::hash<multiAgentExperience::library::activity::ActivityRequest> {
    std::size_t operator()(multiAgentExperience::library::activity::ActivityRequest const& request) const noexcept {
        return request.getID();
    }
};

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYREQUEST_H_
