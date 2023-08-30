/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Activity/ActivitySnapshot.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

ActivitySnapshot::ActivitySnapshot(const ActivityID& activityId, const actor::ActorId& actorId) :
m_activityId{activityId},
m_actorId{actorId} {}

ActivityID ActivitySnapshot::getActivityId() const {
    return m_activityId;
}

actor::ActorId ActivitySnapshot::getActorId() const {
    return m_actorId;
}

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience
