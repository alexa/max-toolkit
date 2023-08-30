/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Activity/ActivityManager.h"

#include <sstream>

#include "Activity/ActivityChannels.h"
#include "Activity/ActivityRequest.h"
#include "Activity/ActivityRequestLifecycle.h"
#include "Activity/CurrentActivityRequests.h"
#include "Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

static const std::string MODULE_TAG("ActivityManager");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ActivityManager::ActivityManager(
    std::shared_ptr<ActivityChannels> activityChannels,
    std::shared_ptr<CurrentActivityRequests> activityRequests,
    std::shared_ptr<device::DeviceRestrictRequestsHelper> deviceRestrictRequestsHelper,
    std::shared_ptr<application::MAXLifecycle> maxLifecycle) :
        m_activityChannels{activityChannels},
        m_currentActivityRequests{activityRequests},
        m_deviceRestrictRequestsHelper{deviceRestrictRequestsHelper},
        m_maxLifecycle{maxLifecycle} {
}

void ActivityManager::request(std::shared_ptr<ActivityRequest> activityRequest) {
    std::stringstream ss;
    ss << "ActivityRequest details:"
       << "activityRequestID=" << std::to_string(activityRequest->getID())
       << ",activityType=" << utils::toString(activityRequest->getActivityType())
       << ",mixabilityType=" << utils::toString(activityRequest->getMixabilityType());
    LX(DEBUG3, ss.str());

    if (!m_deviceRestrictRequestsHelper->canRequestBeGrantedForActor(activityRequest->getActorId())) {
        activityRequest->onDenied();
        return;
    }

    /**
     * Buffer any activity requests until MAX is in READY state.
     *
     * Before MAX transitions to a READY state, agents are allowed to re-request any activities that were previously
     * active. MAX stores these activity requests in a buffer in priority ordering. This is to ensure that the correct
     * state is restored after a MAX process crash. Once all requests are placed, the stored activity requests will be
     * processed with the help of @c MAXLifecycleToActivityObserver.
     *
     * If the MAXLifecycle was not ready, and the insert was unsuccessful, we go ahead and place the activity request.
     */
    if (!m_maxLifecycle->isReady() && m_activityRequestBuffer.insert(activityRequest)) {
        return;
    }

    auto requestLifecycle = std::make_shared<ActivityRequestLifecycle>(activityRequest);
    m_currentActivityRequests->add(requestLifecycle);

    if (!m_activityChannels->add(requestLifecycle)) {
        auto id = activityRequest->getID();
        m_currentActivityRequests->remove(id);
    }
}

void ActivityManager::finish(const ActivityRequestID activityRequestId) {
    LX(DEBUG3, "");

    m_activityChannels->remove(activityRequestId);
}

std::shared_ptr<ActivitySnapshot> ActivityManager::getForegroundActivitySnapshotFromOtherActor(const actor::ActorId& actorId) {
    LX(DEBUG3, "");

    std::shared_ptr<ActivitySnapshot> activitySnapshot = nullptr;

    auto activities =  m_activityChannels->getAllActivitiesSortedByPriority();
    if(0 < activities.size()) {
        auto foregroundActivity = activities.cbegin();
        if(auto foregroundActivityPtr = foregroundActivity->lock()) {
            if(foregroundActivityPtr->isInForeground() && actorId != foregroundActivityPtr->getActorId()) {
                activitySnapshot = std::make_shared<ActivitySnapshot>(
                    foregroundActivityPtr->getID(),
                    foregroundActivityPtr->getActorId());
                LX(DEBUG3, "Foreground activity present and taking a snapshot!");
            }
        }
        else {
            LX(DEBUG3, "No foreground activity present!");
        }
    }

    return activitySnapshot;
}

void ActivityManager::stopAllAlerts() {
    LX(DEBUG3, "");
    auto currentActivities = m_activityChannels->getAllActivitiesSortedByPriority();

    for(auto curActivity : currentActivities) {
        if(auto curActivityPtr = curActivity.lock()) {
            if(ActivityType::ALERTS == curActivityPtr->getActivityType()) {
                curActivityPtr->stop();
            }
        }
    }
}

ActivityLifecyclesSortedByPriorityAndActivityId ActivityManager::getAllActivitiesSortedByPriorityAndActivityId() {
    LX(DEBUG3, "");
    return m_activityChannels->getAllActivitiesSortedByPriority();
}

void ActivityManager::stopAllActivities() {
    LX(DEBUG3, "");
    auto currentActivities = m_activityChannels->getAllActivitiesSortedByPriority();

    for(auto curActivity : currentActivities) {
        if(auto curActivityPtr = curActivity.lock()) {
            curActivityPtr->stop();
        }
    }
}

void ActivityManager::onTransitionToReady() {
    LX(DEBUG3, "");
    // Retrieve all activity requests
    auto activityRequests = m_activityRequestBuffer.retrieveAndClearBuffer();

    // Execute all the activity requests stored in the buffer
    for (const auto& activityRequest: activityRequests) {
        this->request(activityRequest);
    }
}

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience
