/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYREQUEST_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYREQUEST_H_

#include <memory>

#include "Activity.h"
#include "ActivityRequestID.h"
#include "ActivityType.h"
#include "Activity/FocusManager/MixabilityType.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

class ActivityRequest {
public:
    ActivityRequest(
        const ActivityType activityType,
        std::shared_ptr<Activity> activity,
        const MixabilityType mixabilityType = MixabilityType::MIXABLE_RESTRICTED,
        const bool willingToWait = false);

    virtual ~ActivityRequest();

    const ActivityType getActivityType() const;

    const std::shared_ptr<Activity> getActivity() const;

    bool isWillingToWait() const;

    const ActivityRequestID getID() const;

    const MixabilityType getMixabilityType() const;

    virtual const actor::ActorId getActorId() const;

    virtual void onGranted() = 0;

    virtual void onDenied() = 0;

    virtual void onRemoved() = 0;

    virtual void onFinished() = 0;

    virtual void onWaiting() = 0;

private:
    const ActivityRequestID m_id;
    const ActivityType m_activityType;
    std::shared_ptr<Activity> m_activity;
    const bool m_willingToWait;
    const MixabilityType m_mixabilityType;
};

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

template <>
struct std::hash<multiAgentExperience::library::activity::ActivityRequest> {
    std::size_t operator()(multiAgentExperience::library::activity::ActivityRequest const& request) const noexcept {
        return request.getID();
    }
};

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYREQUEST_H_
