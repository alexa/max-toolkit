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

#include "Activity/ChannelToActivityObserver.h"

#include "Activity/ActivityID.h"
#include "Activity/ActivityLifecycle.h"
#include "Activity/CurrentActivities.h"
#include "Activity/CurrentActivityRequests.h"
#include "Control/ControlRegistryFactory.h"
#include "Utils/Logger/Logger.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

static const std::string MODULE_TAG("ChannelToActivityObserver");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

static ActivityID generateActivityID() {
    static ActivityID id = 1;
    return id++;
}

ChannelToActivityObserver::ChannelToActivityObserver(
    std::shared_ptr<CurrentActivityRequests> activeRequests,
    std::shared_ptr<CurrentActivities> currentActivities,
    const control::ControlPriority controlPriority,
    std::shared_ptr<control::ControlRegistryFactory> controlRegistryFactory,
    ActivityRequestID activityRequestId) :
        m_activeRequests{activeRequests},
        m_currentActivities{currentActivities},
        m_controlPriority{controlPriority},
        m_controlRegistryFactory{controlRegistryFactory},
        m_activityRequestID{activityRequestId},
        m_requestHandled{false} {
}

void ChannelToActivityObserver::onFocusChanged(FocusState newFocus, MixingBehavior behavior) {
    LX(DEBUG3, "");
    if (!m_requestHandled && (newFocus == FocusState::FOREGROUND || newFocus == FocusState::BACKGROUND)) {
        m_requestHandled = true;
        m_activity = m_activeRequests->grant(m_activityRequestID);

        if (!m_activity) {
            // If the activity does not exist immediately remove the request.
            cleanup();
        } else {
            auto activityId = generateActivityID();
            m_activity->markGranted(activityId);

            m_currentActivities->add(activityId, m_activity);
            auto registry = m_controlRegistryFactory->create(m_controlPriority);
            m_activity->makeControlRegistryAvailable(registry);
        }
    } else if (!m_requestHandled && (newFocus == FocusState::NONE)) {
        m_requestHandled = true;
        m_activeRequests->deny(m_activityRequestID);
    }

    if (m_activity) {
        if (newFocus == FocusState::FOREGROUND) {
            m_activity->enterForeground();
        } else if (newFocus == FocusState::BACKGROUND) {
            m_activity->enterBackground();
        } else if (newFocus == FocusState::NONE) {
            cleanup();
        }
    }
}

ChannelToActivityObserver::~ChannelToActivityObserver() {
    cleanup();
}

void ChannelToActivityObserver::cleanup() {
    if (m_activity) {
        m_activity->stop();
        m_activeRequests->remove(m_activityRequestID);
        m_currentActivities->remove(m_activity->getID());
        m_activity->cleanup();
    }
}

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience
