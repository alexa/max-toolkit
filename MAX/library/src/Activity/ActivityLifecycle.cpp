/*
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include <vector>

#include "Activity/ActivityLifecycle.h"

#include "Activity/Activity.h"
#include "Control/ControlRegistry.h"
#include "Utils/Logger/Logger.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

static const std::string MODULE_TAG("ActivityLifecycle");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ActivityLifecycle::ActivityLifecycle(std::shared_ptr<Activity> activity) :
        m_state(ActivityState::REQUESTED),
        m_activity(activity) {
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

void ActivityLifecycle::enterBackground() {
    LX(DEBUG3, "");
    if (trySwitchStateToFrom(ActivityState::BACKGROUND, {ActivityState::FOREGROUND, ActivityState::WAITING})) {
        m_activity->onBackground();
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
ActivityLifecycle::~ActivityLifecycle() {
    if (m_controlRegistry) {
        m_controlRegistry->cleanup();
    }
}

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience
