/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <vector>

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Activity/ActivityLifecycle.h"

#include "Activity/Activity.h"
#include "Control/ControlRegistry.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

static const std::string MODULE_TAG("ActivityLifecycle");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ActivityLifecycle::ActivityLifecycle(std::shared_ptr<Activity> activity, ActivityType activityType) :
        m_state(ActivityState::REQUESTED),
        m_activity(activity),
        m_activityType(activityType) {
}

void ActivityLifecycle::markGranted(const ActivityID id) {
    LX(DEBUG3, "");

    if (trySwitchStateToFrom(ActivityState::WAITING, {ActivityState::REQUESTED})) {
        m_activity->onRequestGranted(id);
    }
}

void ActivityLifecycle::makeControlRegistryAvailable(std::shared_ptr<control::ControlRegistry> controlRegistry) {
    LX(DEBUG3, "");
    if (isInOneOfStates({ActivityState::FOREGROUND, ActivityState::BACKGROUND, ActivityState::WAITING})) {
        m_controlRegistry = controlRegistry;
        m_activity->onControlRegistryAvailable(controlRegistry);
    }
}

void ActivityLifecycle::enterForeground() {
    LX(DEBUG3, "");
    if (trySwitchStateToFrom(ActivityState::FOREGROUND, {ActivityState::BACKGROUND, ActivityState::WAITING})) {
        m_activity->onForeground();
    }
}

void ActivityLifecycle::enterBackground(MixingBehavior behavior) {
    LX(DEBUG3, "");

    /**
     * An activity in the foreground/waiting states may enter background.
     * An activity that is already in the background state is only allowed to enter background, if its MixingBehavior
     * needs to be updated. We don't expect enterBackground to be invoked if there is no change in the activity's MixingBehavior.
     */
    if (trySwitchStateToFrom(ActivityState::BACKGROUND,
        {ActivityState::FOREGROUND, ActivityState::WAITING, ActivityState::BACKGROUND})) {
        m_activity->onBackground(behavior);
    }
}

void ActivityLifecycle::stop() {
    LX(DEBUG3, "");
    if (trySwitchStateToUnlessInFrom(ActivityState::COMPLETED, {ActivityState::COMPLETED, ActivityState::CLEANED_UP})) {
        m_activity->onStop();
    }
}

void ActivityLifecycle::cleanup() {
    LX(DEBUG3, "");
    if (trySwitchStateToUnlessInFrom(ActivityState::CLEANED_UP, {ActivityState::CLEANED_UP})) {
        if (m_controlRegistry) {
            m_controlRegistry->cleanup();
        }
    }
}

const ActivityID ActivityLifecycle::getID() {
    LX(DEBUG3, "");
    return m_activity->getID();
}

bool ActivityLifecycle::trySwitchStateToFrom(const ActivityState to, std::vector<ActivityState> from) {
    LX(DEBUG3, "");
    std::unique_lock<std::mutex> lock(m_stateMutex);
    for (auto option : from) {
        if (m_state == option) {
            m_state = to;
            return true;
        }
    }
    return false;
}

bool ActivityLifecycle::trySwitchStateToUnlessInFrom(const ActivityState to, std::vector<ActivityState> from) {
    LX(DEBUG3, "");
    std::unique_lock<std::mutex> lock(m_stateMutex);
    bool shouldSwitch = true;
    for (auto option : from) {
        if (m_state == option) {
            shouldSwitch = false;
            break;
        }
    }
    if (shouldSwitch) {
        m_state = to;
    }

    return shouldSwitch;
}

bool ActivityLifecycle::isInOneOfStates(std::vector<ActivityState> states) {
    LX(DEBUG3, "");
    std::unique_lock<std::mutex> lock(m_stateMutex);
    for (auto option : states) {
        if (m_state == option) {
            return true;
        }
    }
    return false;
}

actor::ActorId ActivityLifecycle::getActorId() const {
    return m_activity->getActorId();
}

ActivityType ActivityLifecycle::getActivityType() const {
    return m_activityType;
}

bool ActivityLifecycle::isInForeground() {
    LX(DEBUG3, "");
    std::unique_lock<std::mutex> lock(m_stateMutex);
    return ActivityState::FOREGROUND == m_state;
}

ActivityLifecycle::~ActivityLifecycle() {
    if (m_controlRegistry) {
        m_controlRegistry->cleanup();
    }
}

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience
