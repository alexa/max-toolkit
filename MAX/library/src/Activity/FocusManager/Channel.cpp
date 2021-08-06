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

#include "Activity/FocusManager/Channel.h"
#include "Utils/Logger/Logger.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

static const std::string MODULE_TAG("Channel");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

Channel::State::State(const std::string& name) :
        name{name},
        focusState{FocusState::NONE},
        timeAtIdle{std::chrono::steady_clock::now()} {
}

Channel::State::State() : focusState{FocusState::NONE}, timeAtIdle{std::chrono::steady_clock::now()} {
}

Channel::Channel(const std::string& name, const unsigned int priority, bool isVirtual) :
        m_priority{priority},
        m_isVirtual{isVirtual},
        m_state{name} {
}

const std::string& Channel::getName() const {
    return m_state.name;
}

unsigned int Channel::getPriority() const {
    return m_priority;
}

bool Channel::setFocus(FocusState focus, MixingBehavior behavior, bool forceUpdate) {
    LX(DEBUG3, "");

    std::unique_lock<std::mutex> lock(m_mutex);

    bool focusChanged = (m_state.focusState != focus);
    auto primaryActivity = getPrimaryActivityLocked();
    bool mixingBehaviorChanged = primaryActivity && (primaryActivity->getMixingBehavior() != behavior);

    if (!forceUpdate && !focusChanged && !mixingBehaviorChanged) {
        return false;
    }

    std::stringstream ss;
    ss << "name:" << m_state.name << ",newfocusState:" << focus << ",prevfocusState:" << m_state.focusState
       << ",newMixingBehavior:" << behavior << ",forceUpdate:" << forceUpdate;
    LX(DEBUG3, ss.str());

    m_state.focusState = focus;
    if (m_state.focusState == FocusState::NONE) {
        m_state.timeAtIdle = std::chrono::steady_clock::now();
    }

    // Update Channel State Updates
    addToChannelUpdatesLocked(m_state.interfaceName, m_state.focusState);
    lock.unlock();

    // Notify all activities of the new focus state for this channel
    notifyActivities(behavior, focus);

    return true;
}

void Channel::setPrimaryActivity(std::shared_ptr<FocusManagerInterface::Activity> activity) {
    LX(DEBUG3, "");

    std::unique_lock<std::mutex> lock(m_mutex);

    if (!activity) {
        LX(ERROR, "setPrimaryActivityFailed, Null Activity");
        return;
    }

    if (!m_activities.empty()) {
        processPolicyLocked(activity, m_activities.front());
    }

    // Establish the activity.
    m_activities.push_front(activity);
    updateChannelInterfaceLocked();
}

bool Channel::releaseActivity(std::shared_ptr<ChannelObserverInterface> observer) {
    LX(DEBUG3, "");

    if (observer == nullptr) {
        LX(ERROR, "releaseActivityFailed,reason:observer is null.");
        return false;
    }

    std::unique_lock<std::mutex> lock(m_mutex);
    for (auto it = m_activities.begin(); it != m_activities.end(); ++it) {
        if ((*it)->getChannelObserver() == observer) {
            bool success = removeActivityHelperLocked(it);
            if (success) {
                // No change in observer or activity if remove fails.
                addToChannelUpdatesLocked(m_state.interfaceName, m_state.focusState);
            }

            return success;
        }
    }

    LX(ERROR, "releaseActivityFailed, Observer not found");
    return false;
}

bool Channel::releaseActivity(const std::string& interfaceName) {
    LX(DEBUG3, "");

    std::unique_lock<std::mutex> lock(m_mutex);
    for (auto it = m_activities.begin(); it != m_activities.end(); ++it) {
        if ((*it)->getInterface() == interfaceName) {
            bool success = removeActivityHelperLocked(it);
            if (success) {
                // Update Channel State Updates.
                addToChannelUpdatesLocked(m_state.interfaceName, m_state.focusState);
            }

            return success;
        }
    }
    return false;
}

bool Channel::isActive() {
    std::unique_lock<std::mutex> lock(m_mutex);
    return !m_activities.empty();
}

bool Channel::operator>(const Channel& rhs) const {
    return m_priority < rhs.getPriority();
}

std::string Channel::getInterface() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_state.interfaceName;
}

Channel::State Channel::getState() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_state;
}

std::vector<Channel::State> Channel::getActivityUpdates() {
    std::unique_lock<std::mutex> lock(m_mutex);
    auto activityUpdatesRet = m_activityUpdates;
    m_activityUpdates.clear();
    return activityUpdatesRet;
}

std::shared_ptr<FocusManagerInterface::Activity> Channel::getPrimaryActivity() {
    std::unique_lock<std::mutex> lock(m_mutex);
    return getPrimaryActivityLocked();
}

std::shared_ptr<FocusManagerInterface::Activity> Channel::getPrimaryActivityLocked() const {
    if (m_activities.empty()) {
        return nullptr;
    }
    return *(m_activities.begin());
}

std::shared_ptr<FocusManagerInterface::Activity> Channel::getActivity(const std::string& interfaceName) {
    std::unique_lock<std::mutex> lock(m_mutex);
    for (const auto& it : m_activities) {
        if (it->getInterface() == interfaceName) return it;
    }

    return nullptr;
}

std::vector<std::string> Channel::getInterfaceList() const {
    std::vector<std::string> listOfInterface = {};
    for (const auto& activity : m_activities) {
        listOfInterface.push_back(activity->getInterface());
    }
    return listOfInterface;
}

void Channel::notifyActivities(MixingBehavior behavior, FocusState focusState) {
    LX(DEBUG3, "");

    std::unique_lock<std::mutex> lock(m_mutex);
    if (m_activities.empty()) {
        LX(WARN, "notifyActivitiesFailed, No Associated Activities Found");
        return;
    }
    auto activitiesCopy = m_activities;
    lock.unlock();

    auto activityIt = activitiesCopy.begin();
    // inform the primary activity with the MixingBehavior
    (*activityIt)->notifyObserver(focusState, behavior);
    activityIt++;

    // all other secondary activities must be PAUSED + BACKGROUND
    for (; activityIt != activitiesCopy.end(); activityIt++) {
        (*activityIt)->notifyObserver(FocusState::BACKGROUND, MixingBehavior::MUST_PAUSE);
    }
}

bool Channel::releaseActivityLocked(std::shared_ptr<FocusManagerInterface::Activity> activityToRelease) {
    LX(DEBUG3, "");

    if (!activityToRelease) {
        LX(ERROR, "releaseActivityLockedFailed, Null activityToRelease");
        return false;
    }

    auto priorActivityIt = std::find(m_activities.begin(), m_activities.end(), activityToRelease);
    if (priorActivityIt != m_activities.end()) {
        return removeActivityHelperLocked(priorActivityIt);
    }
    return false;
}

bool Channel::removeActivityHelperLocked(
    std::list<std::shared_ptr<FocusManagerInterface::Activity>>::iterator activityToRemoveIt) {
    LX(DEBUG3, "interface:" + (*activityToRemoveIt)->getInterface());

    auto isRemovingPatienceReceiver = false;
    if (m_patienceReceiver == *activityToRemoveIt) {
        isRemovingPatienceReceiver = true;
    }

    // Timer is active AND the job being removed is one of the patience Activities.
    if (m_patienceTimer.isActive() &&
        (m_patienceInitiator == *activityToRemoveIt || m_patienceReceiver == *activityToRemoveIt)) {
        m_patienceTimer.stop();
        LX(DEBUG3, "status: Patience Timer Stopped.");
        m_patienceInitiator = nullptr;
        m_patienceReceiver = nullptr;
    }

    // If the activity to remove is the last activity, then update the time at idle for this channel
    if (m_activities.size() == 1) {
        m_state.timeAtIdle = std::chrono::steady_clock::now();
    }

    // No need to update Channel updates for removing patience receiver.
    if (!isRemovingPatienceReceiver) {
        // Add the current State and override the FocusState with NONE.
        addToChannelUpdatesLocked((*activityToRemoveIt)->getInterface(), FocusState::NONE);
    }

    // Report NONE only to the single Activity that is removed
    (*activityToRemoveIt)->notifyObserver(FocusState::NONE, MixingBehavior::MUST_STOP);
    m_activities.erase(activityToRemoveIt);
    updateChannelInterfaceLocked();

    return true;
}

void Channel::addToChannelUpdatesLocked(const std::string& interfaceName, FocusState focusState) {
    LX(DEBUG3, "");

    if (m_state.interfaceName.empty()) {
        return;
    }
    // Only add to Channel updates if channel is not virtual.
    if (!m_isVirtual) {
        auto state = m_state;
        state.focusState = focusState;
        state.interfaceName = interfaceName;
        m_activityUpdates.push_back(state);
        LX(DEBUG0, "interface:" + state.interfaceName + ", focusState:" + focusStateToString(state.focusState));
    }
}

void Channel::processPolicyLocked(
    std::shared_ptr<FocusManagerInterface::Activity> incomingActivity,
    std::shared_ptr<FocusManagerInterface::Activity> currentActivity) {
    LX(DEBUG3, "");

    if (!incomingActivity || !currentActivity) {
        LX(ERROR, "processPolicyLockedFailed, Null Activities");
        return;
    }

    if (incomingActivity->getInterface() == currentActivity->getInterface()) {
        // Both incoming and current activity has identical interface. Remove the current activity regardless of policy.
        releaseActivityLocked(currentActivity);
        return;
    }

    if (m_patienceTimer.isActive()) {
        // A new Activity is incoming. If there is an ongoing patience release, remove the receiver immediately.
        // Any persistent initiator or receiver will not be removed.
        m_patienceTimer.stop();
        LX(DEBUG3, "status: Patience Release Timer Stopped");
        releaseActivityLocked(m_patienceReceiver);
        m_patienceReceiver = nullptr;
    }

    if (incomingActivity->getPatienceDuration().count() > 0) {
        // Incoming valid patience Activity
        LX(DEBUG3, "status: Patience Release Timer Started");
        addToChannelUpdatesLocked(currentActivity->getInterface(), FocusState::NONE);
        auto patienceDuration = incomingActivity->getPatienceDuration();
        m_patienceTimer.start(patienceDuration, std::bind(&Channel::patienceTimerCallback, this, currentActivity));
        m_patienceInitiator = incomingActivity;
        m_patienceReceiver = currentActivity;
    } else {
        if (m_patienceInitiator != nullptr) {
            // No valid patience duration, release the initiator.
            releaseActivityLocked(m_patienceInitiator);
            m_patienceInitiator = nullptr;
        }
        releaseActivityLocked(currentActivity);
    }
}

void Channel::patienceTimerCallback(std::shared_ptr<FocusManagerInterface::Activity> activity) {
    LX(DEBUG3, "");

    std::unique_lock<std::mutex> lock(m_mutex);
    LX(DEBUG3, "status: Patience Release Timer Triggered");
    releaseActivityLocked(std::move(activity));
    // No need to modify channel updates since it was Already reported
    // when patienceInitiator came into focus.
}

void Channel::updateChannelInterfaceLocked() {
    LX(DEBUG3, "");

    if (!m_activities.empty()) {
        m_state.interfaceName = m_activities.front()->getInterface();
    } else {
        m_state.interfaceName = "";
    }
}

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience
