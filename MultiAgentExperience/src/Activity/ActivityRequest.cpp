/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Activity/ActivityRequest.h"
#include "Activity/ActivityType.h"
#include "Activity/FocusManager/MixabilityType.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

static ActivityRequestID generateID() {
    static ActivityRequestID id = 1;
    return id++;
}

ActivityRequest::ActivityRequest(
    ActivityType activityType,
    std::shared_ptr<Activity> activity,
    MixabilityType mixabilityType,
    bool willingToWait) :
        m_id(generateID()),
        m_activityType(activityType),
        m_activity(activity),
        m_willingToWait(willingToWait),
        m_mixabilityType(mixabilityType) {
}

const ActivityType ActivityRequest::getActivityType() const {
    return m_activityType;
}

const std::shared_ptr<Activity> ActivityRequest::getActivity() const {
    return m_activity;
}

bool ActivityRequest::isWillingToWait() const {
    return m_willingToWait;
}

const ActivityRequestID ActivityRequest::getID() const {
    return m_id;
}

const MixabilityType ActivityRequest::getMixabilityType() const {
    return m_mixabilityType;
}

const actor::ActorId ActivityRequest::getActorId() const {
    return m_activity->getActorId();
}

ActivityRequest::~ActivityRequest() {
}

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience
