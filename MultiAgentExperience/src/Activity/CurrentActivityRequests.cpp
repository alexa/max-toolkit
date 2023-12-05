/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Activity/CurrentActivityRequests.h"

#include "Activity/Activity.h"
#include "Activity/ActivityLifecycle.h"
#include "Activity/ActivityRequestLifecycle.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

void CurrentActivityRequests::add(std::shared_ptr<ActivityRequestLifecycle> activityRequest) {
    if (activityRequest) {
        std::unique_lock<std::mutex> lock(m_activeRequestsMutex);
        m_activityRequests[activityRequest->getID()] = activityRequest;
    }
}

std::shared_ptr<ActivityLifecycle> CurrentActivityRequests::grant(const ActivityRequestID activityRequestId) {
    std::shared_ptr<ActivityRequestLifecycle> request;
    {
        std::unique_lock<std::mutex> lock(m_activeRequestsMutex);
        auto requestEntry = m_activityRequests.find(activityRequestId);
        if (requestEntry != m_activityRequests.end()) {
            request = requestEntry->second;
        }
    }

    if (request) {
        return request->grant();
    } else {
        return nullptr;
    }
}

bool CurrentActivityRequests::wait(ActivityRequestID activityRequestId) {
    std::shared_ptr<ActivityRequestLifecycle> request;
    {
        std::unique_lock<std::mutex> lock(m_activeRequestsMutex);
        auto requestEntry = m_activityRequests.find(activityRequestId);
        if (requestEntry != m_activityRequests.end()) {
            request = requestEntry->second;
        }
    }
    if (request) {
        return request->enqueue();
    }
    return false;
}

void CurrentActivityRequests::deny(const ActivityRequestID activityRequestId) {
    finish(activityRequestId, RemovalReason::DENIED);
}

const ActivityID CurrentActivityRequests::remove(const ActivityRequestID activityRequestId) {
    return finish(activityRequestId, RemovalReason::REMOVED);
}

const ActivityID CurrentActivityRequests::finish(const ActivityRequestID activityRequestId) {
    return finish(activityRequestId, RemovalReason::ABANDONED);
}

const ActivityID CurrentActivityRequests::finish(
    const ActivityRequestID activityRequestId,
    const CurrentActivityRequests::RemovalReason state) {
    std::shared_ptr<ActivityRequestLifecycle> request;
    {
        std::unique_lock<std::mutex> lock(m_activeRequestsMutex);
        auto requestEntry = m_activityRequests.find(activityRequestId);
        if (requestEntry != m_activityRequests.end()) {
            request = requestEntry->second;
        }
    }

    if (request) {
        switch (state) {
            case RemovalReason::DENIED:
                request->deny();
                break;
            case RemovalReason::ABANDONED:
                request->finish();
                break;
            default:
                request->remove();
                break;
        }
        m_activityRequests.erase(activityRequestId);

        return request->getActivityID();
    } else {
        return -1;
    }
}

std::vector<ActivityRequestID> CurrentActivityRequests::getActivityRequestIdsForActor(const actor::ActorId &actorId) {

    std::unique_lock<std::mutex> lock(m_activeRequestsMutex);

    std::vector<ActivityRequestID> activityRequestIds;
    for (const auto& entry: m_activityRequests) {
        auto activityRequest = entry.second;

        // MAX internally represents dialogs as activities too. We don't want to return the ActivityRequestID for the dialog activity here
        if (actorId == activityRequest->getActorId() && activityRequest->getActivityType() != ActivityType::DIALOG) {
            activityRequestIds.push_back(activityRequest->getID());
        }
    }

    return activityRequestIds;
}

CurrentActivityRequests::~CurrentActivityRequests() {
}

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience
