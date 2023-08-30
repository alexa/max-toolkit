/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Activity/ActivityRequestBuffer.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

ActivityRequestBuffer::ActivityRequestBuffer():
    m_wasBufferCleared{false} {
}

bool ActivityRequestBuffer::insert(std::shared_ptr<ActivityRequest> activityRequest) {
    std::unique_lock<std::mutex> lock(m_mutex);

    /// If the buffer was cleared explicitly via @c clear, then it implies that the buffer should not be used anymore.
    /// Hence, we should not insert any activity requests. We should convey that the @c insert was unsuccessful
    if (m_wasBufferCleared) {
        return false;
    }

    m_activityRequestsBuffer.insert(activityRequest);
    return true;
}

ActivityRequestBuffer::OrderedActivityRequestBuffer ActivityRequestBuffer::retrieveAndClearBuffer() {
    std::unique_lock<std::mutex> lock(m_mutex);

    // Store a copy to return.
    ActivityRequestBuffer::OrderedActivityRequestBuffer activityRequestsBufferCopy(std::move(m_activityRequestsBuffer));

    /// Clear contents and set the @c m_wasBufferCleared state
    m_activityRequestsBuffer.clear();
    m_wasBufferCleared = true;

    return activityRequestsBufferCopy;
}

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience