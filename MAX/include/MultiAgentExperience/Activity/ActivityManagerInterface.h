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

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_ACTIVITY_ACTIVITYMANAGERINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_ACTIVITY_ACTIVITYMANAGERINTERFACE_H_

#include <memory>

#include "MultiAgentExperience/Activity/ActivityRequestInterface.h"

namespace multiAgentExperience {
namespace activity {

/**
 * The ActivityManagerInterface is used to request and stop activities.
 */
class ActivityManagerInterface {
public:
    /**
     * Destructor.
     */
    virtual ~ActivityManagerInterface() = default;

    /**
     * Requests an activity to be started.
     * @param request
     */
    virtual void request(std::shared_ptr<multiAgentExperience::activity::ActivityRequestInterface> request) = 0;

    /**
     * Immediately stops an activity which was started for the given request. If the activity is not active for this
     * request it has no effect.
     *
     * @param request - The originating request of the activity which be stopped.
     */
    virtual void stop(std::shared_ptr<multiAgentExperience::activity::ActivityRequestInterface> request) = 0;
};

}  // namespace activity
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_ACTIVITY_ACTIVITYMANAGERINTERFACE_H_
