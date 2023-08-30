/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Activity/ActivityRequestLifecycle.h"

#include "Activity/Activity.h"
#include "Activity/ActivityLifecycle.h"
#include "Activity/ActivityRequest.h"

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
        return std::make_shared<ActivityLifecycle>(m_activityRequest->getActivity(), m_activityRequest->getActivityType());
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

const MixabilityType ActivityRequestLifecycle::getMixabilityType() {
    return m_activityRequest->getMixabilityType();
}

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience
