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

#include "Activity/ActivityRequestLifecycle.h"

#include "Activity/Activity.h"
#include "Activity/ActivityLifecycle.h"
#include "Activity/ActivityRequest.h"
#include "Utils/Logger/Logger.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

static const std::string MODULE_TAG("ActivityRequestLifecycle");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ActivityRequestLifecycle::ActivityRequestLifecycle(std::shared_ptr<ActivityRequest> activityRequest) :
        m_state(ActivityRequestState::REQUESTED),
        m_activityRequest(activityRequest) {
}

std::shared_ptr<ActivityLifecycle> ActivityRequestLifecycle::grant() {
    LX(DEBUG3, "");

    std::unique_lock<std::mutex> lock(m_stateMutex);
    if (m_state == ActivityRequestState::REQUESTED || m_state == ActivityRequestState::WAITING) {
        m_state = ActivityRequestState::GRANTED;
        lock.unlock();
        m_activityRequest->onGranted();
        return std::make_shared<ActivityLifecycle>(m_activityRequest->getActivity());
    }
    return nullptr;
}

void ActivityRequestLifecycle::deny() {
    LX(DEBUG3, "");

    std::unique_lock<std::mutex> lock(m_stateMutex);
    if (m_state == ActivityRequestState::REQUESTED || m_state == ActivityRequestState::WAITING) {
        m_state = ActivityRequestState::DENIED;
        lock.unlock();
        m_activityRequest->onDenied();
    }
}

void ActivityRequestLifecycle::remove() {
    LX(DEBUG3, "");

    std::unique_lock<std::mutex> lock(m_stateMutex);
    if (m_state != ActivityRequestState::COMPLETED && m_state != ActivityRequestState::DENIED) {
        m_state = ActivityRequestState::COMPLETED;
        lock.unlock();
        m_activityRequest->onRemoved();
    }
}

void ActivityRequestLifecycle::finish() {
    LX(DEBUG3, "");

    std::unique_lock<std::mutex> lock(m_stateMutex);
    if (m_state != ActivityRequestState::COMPLETED && m_state != ActivityRequestState::DENIED) {
        m_state = ActivityRequestState::COMPLETED;
        lock.unlock();
        m_activityRequest->onFinished();
    }
}

bool ActivityRequestLifecycle::enqueue() {
    LX(DEBUG3, "");

    std::unique_lock<std::mutex> lock(m_stateMutex);
    if (m_state == ActivityRequestState::REQUESTED) {
        if (m_activityRequest->isWillingToWait()) {
            m_state = ActivityRequestState::WAITING;
            lock.unlock();
            m_activityRequest->onWaiting();
            return true;
        } else {
            lock.unlock();
            deny();
        }
    }
    return false;
}

const ActivityRequestID ActivityRequestLifecycle::getID() {
    return m_activityRequest->getID();
}

const ActivityID ActivityRequestLifecycle::getActivityID() {
    return m_activityRequest->getActivity()->getID();
}

const ActivityType ActivityRequestLifecycle::getActivityType() {
    return m_activityRequest->getActivityType();
}

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience
