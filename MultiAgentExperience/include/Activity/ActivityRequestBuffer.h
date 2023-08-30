/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYREQUESTBUFFER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYREQUESTBUFFER_H_

#include <memory>

#include "ActivityRequest.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

/**
 * A temporary buffer used by @c ActivityManager, that stores all activity requests until the @c MAXLifecycle state
 * changes to READY. The activity requests are ordered by their @c ActivityType priority.
 */
class ActivityRequestBuffer {
public:

    ActivityRequestBuffer();

    /// Comparator for ActivityRequests which sorts based on ActivityType priority. If ActivityType priorities
    /// are equal, then the ActivityRequestIds are used for determining priority.
    struct CompareActivityRequestsByPriority {
        bool operator()(const std::shared_ptr<ActivityRequest>& lhs, const std::shared_ptr<ActivityRequest>& rhs) const {
            return lhs->getActivityType() == rhs->getActivityType()
                   ? lhs->getID() < rhs->getID()
                   : lhs->getActivityType() < rhs->getActivityType();
        }
    };

    using OrderedActivityRequestBuffer = std::multiset<std::shared_ptr<ActivityRequest>, CompareActivityRequestsByPriority>;

    /**
     * Stores the activity request in the buffer
     *
     * @param activityRequest The activity request to be stored
     * @return true if insert was successful. False, otherwise.
     */
    bool insert(std::shared_ptr<ActivityRequest> activityRequest);

    /**
     * Returns a copy of the buffer, and then clears its contents.
     */
    OrderedActivityRequestBuffer retrieveAndClearBuffer();

private:
    OrderedActivityRequestBuffer m_activityRequestsBuffer;

    /// A mutex to ensure that an ActivityRequest cannot be inserted into the buffer, when items in the buffer are being retrieved.
    std::mutex m_mutex;

    /// Boolean to track whether the buffer was cleared or not
    bool m_wasBufferCleared;
};

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYREQUESTBUFFER_H_

