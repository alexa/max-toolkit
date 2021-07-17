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

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_ACTIVITY_ACTIVITYREQUESTINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_ACTIVITY_ACTIVITYREQUESTINTERFACE_H_

#include "MultiAgentExperience/Activity/ActivityType.h"
#include "MultiAgentExperience/Activity/ActivityHandlerInterface.h"

namespace multiAgentExperience {
namespace activity {

/**
 * An ActivityRequestInterface is used to request activities from the ActivityManagerInterface. It gathers all state
 * the manager will need to determine if the request is grantable. A new ActivityRequestInterface is expected to be
 * used for each request.
 */
class ActivityRequestInterface {
public:
    /**
     * Creates an activity request of the given ActivityType and handled by the given ActivityHandlerInterface.
     *
     * @param activityType - The type of the activity.
     * @param handler - The handler for the activity if the request is granted.
     */
    ActivityRequestInterface(ActivityType activityType, std::shared_ptr<ActivityHandlerInterface> handler) :
            m_activityType{activityType},
            m_handler{handler} {
    }

    /**
     * Destructor.
     */
    virtual ~ActivityRequestInterface() = default;

    /**
     * @return The type of the requested activity.
     */
    ActivityType getType() const {
        return m_activityType;
    }

    /**
     * @return The handler for the requested activity.
     */
    std::shared_ptr<ActivityHandlerInterface> getHandler() const {
        return m_handler;
    }

private:
    ActivityType m_activityType;
    std::shared_ptr<ActivityHandlerInterface> m_handler;
};

}  // namespace activity
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_ACTIVITY_ACTIVITYREQUESTINTERFACE_H_
