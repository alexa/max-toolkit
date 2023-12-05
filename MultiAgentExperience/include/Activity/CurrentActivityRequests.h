/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_CURRENTACTIVITYREQUESTS_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_CURRENTACTIVITYREQUESTS_H_

#include <memory>
#include <mutex>
#include <unordered_map>

#include "Activity.h"
#include "ActivityID.h"
#include "ActivityRequestID.h"
#include "ActivityLifecycle.h"
#include "ActivityRequestLifecycle.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

class CurrentActivityRequests {
public:
    virtual ~CurrentActivityRequests();

    virtual void add(std::shared_ptr<ActivityRequestLifecycle> activityRequest);

    virtual std::shared_ptr<ActivityLifecycle> grant(const ActivityRequestID activityRequestId);

    virtual bool wait(const ActivityRequestID activityRequestId);

    virtual void deny(const ActivityRequestID activityRequestId);

    virtual const ActivityID remove(const ActivityRequestID activityRequestId);

    virtual const ActivityID finish(const ActivityRequestID activityRequestId);

    virtual std::vector<ActivityRequestID> getActivityRequestIdsForActor(const actor::ActorId& actorId);

private:
    enum class RemovalReason { DENIED, REMOVED, ABANDONED };

    const ActivityID finish(const ActivityRequestID activityRequestId, const RemovalReason state);

    std::mutex m_activeRequestsMutex;
    std::unordered_map<ActivityRequestID, std::shared_ptr<ActivityRequestLifecycle>> m_activityRequests;
};

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_CURRENTACTIVITYREQUESTS_H_
