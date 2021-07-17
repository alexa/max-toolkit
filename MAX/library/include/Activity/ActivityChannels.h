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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYCHANNELS_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYCHANNELS_H_

#include <memory>

#include "ActivityRequestID.h"
#include "ActivityRequestLifecycle.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

class ActivityChannels {
public:
    virtual ~ActivityChannels() = default;

    virtual bool add(std::shared_ptr<ActivityRequestLifecycle> activityRequest) = 0;

    virtual void remove(const ActivityRequestID activityRequestId) = 0;
};

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYCHANNELS_H_
