/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYREQUESTLIFECYCLE_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYREQUESTLIFECYCLE_H_

#include <memory>
#include <mutex>

#include "Activity.h"
#include "ActivityID.h"
#include "ActivityLifecycle.h"
#include "ActivityRequest.h"
#include "ActivityRequestID.h"
#include "ActivityType.h"
#include "Activity/FocusManager/MixabilityType.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

class ActivityRequestLifecycle {
public:
    ActivityRequestLifecycle(std::shared_ptr<ActivityRequest> activityRequest);

    std::shared_ptr<ActivityLifecycle> grant();

    void deny();

    void remove();

    void finish();

    bool enqueue();

    const ActivityRequestID getID();

    const ActivityID getActivityID();

    const ActivityType getActivityType();

    const MixabilityType getMixabilityType();

    const actor::ActorId getActorId();

private:
    enum class ActivityRequestState { REQUESTED, WAITING, GRANTED, DENIED, COMPLETED };

    std::mutex m_stateMutex;
    ActivityRequestState m_state;
    std::shared_ptr<ActivityRequest> m_activityRequest;
};

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYREQUESTLIFECYCLE_H_
