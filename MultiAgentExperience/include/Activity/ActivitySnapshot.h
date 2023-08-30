/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_ACTIVITYSNAPSHOT_H
#define MULTIAGENTEXPERIENCE_ACTIVITYSNAPSHOT_H

#include "ActivityID.h"
#include "MultiAgentExperience/Actor/ActorId.h"

namespace multiAgentExperience {
namespace library {
namespace activity {


class ActivitySnapshot {
public:
    ActivitySnapshot(const ActivityID& activityId, const actor::ActorId& actorId);

    ActivityID getActivityId() const;

    actor::ActorId getActorId() const;
private:
    const ActivityID m_activityId;
    const actor::ActorId m_actorId;
};

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_ACTIVITYSNAPSHOT_H
