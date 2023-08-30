/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITY_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITY_H_

#include <memory>

#include <MultiAgentExperience/Actor/ActorId.h>

#include "ActivityID.h"
#include "ActivityType.h"
#include "Activity/FocusManager/MixingBehavior.h"
#include "Control/ControlRegistry.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

class Activity {
public:
    Activity();

    virtual ~Activity() = default;

    void onRequestGranted(const ActivityID id);

    virtual void onControlRegistryAvailable(std::shared_ptr<control::ControlRegistry> controlRegistry);

    virtual void onForeground() = 0;

    virtual void onBackground(MixingBehavior behavior) = 0;

    virtual void onStop() = 0;

    const ActivityID getID();

    virtual actor::ActorId getActorId() const = 0;

private:
    ActivityID m_id;
};

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITY_H_
