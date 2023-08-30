/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYLIFECYCLE_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYLIFECYCLE_H_

#include <atomic>
#include <memory>
#include <mutex>
#include <vector>
#include <tuple>

#include "Activity.h"
#include "ActivityID.h"
#include "Activity/FocusManager/MixingBehavior.h"
#include "Control/ControlRegistry.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

class ActivityLifecycle {
public:
    ActivityLifecycle(std::shared_ptr<Activity> activity, const ActivityType activityType);

    virtual ~ActivityLifecycle();

    void markGranted(const ActivityID id);

    void makeControlRegistryAvailable(std::shared_ptr<control::ControlRegistry> controlRegistry);

    void enterForeground();

    void enterBackground(MixingBehavior behavior);

    virtual void stop();

    virtual const ActivityID getID();

    void cleanup();

    virtual actor::ActorId getActorId() const;

    ActivityType getActivityType() const;

    virtual bool isInForeground();

private:
    enum class ActivityState { REQUESTED, WAITING, FOREGROUND, BACKGROUND, COMPLETED, CLEANED_UP };

    bool trySwitchStateToFrom(const ActivityState to, std::vector<ActivityState> from);
    bool trySwitchStateToUnlessInFrom(const ActivityState to, std::vector<ActivityState> from);
    bool isInOneOfStates(std::vector<ActivityState> states);

    std::mutex m_stateMutex;
    ActivityState m_state;
    std::shared_ptr<Activity> m_activity;
    const ActivityType m_activityType;
    std::shared_ptr<control::ControlRegistry> m_controlRegistry;
};

struct CompareActivityLifecyclesByPriorityAndActivityId {
    bool operator()(const std::weak_ptr<ActivityLifecycle>& lhs,
        const std::weak_ptr<ActivityLifecycle>& rhs) const {
        bool result = false;

        if(auto lhsPtr = lhs.lock()) {
            if (auto rhsPtr = rhs.lock()) {
                auto lhsActivityType = lhsPtr->getActivityType();
                auto lhsActivityId = lhsPtr->getID();
                auto rhsActivityType = rhsPtr->getActivityType();
                auto rhsActivityId = rhsPtr->getID();
                result = std::tie(lhsActivityType, rhsActivityId)
                       < std::tie(rhsActivityType, lhsActivityId);
            }
        }
        return result;
    }
};

using ActivityLifecyclesSortedByPriorityAndActivityId = std::set<std::weak_ptr<ActivityLifecycle>, CompareActivityLifecyclesByPriorityAndActivityId>;

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYLIFECYCLE_H_
