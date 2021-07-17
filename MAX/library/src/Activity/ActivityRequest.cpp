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

#include "Activity/ActivityRequest.h"

#include "Activity/ActivityType.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

static ActivityRequestID generateID() {
    static ActivityRequestID id = 1;
    return id++;
}

ActivityRequest::ActivityRequest(ActivityType activityType, std::shared_ptr<Activity> activity, bool willingToWait) :
        m_id(generateID()),
        m_activityType(activityType),
        m_activity(activity),
        m_willingToWait(willingToWait) {
}

const ActivityType ActivityRequest::getActivityType() const {
    return m_activityType;
}

const std::shared_ptr<Activity> ActivityRequest::getActivity() const {
    return m_activity;
}

bool ActivityRequest::isWillingToWait() const {
    return m_willingToWait;
}

const ActivityRequestID ActivityRequest::getID() const {
    return m_id;
}

ActivityRequest::~ActivityRequest() {
}

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience
