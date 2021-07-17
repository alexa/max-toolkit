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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_CHANNELTOACTIVITYOBSERVER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_CHANNELTOACTIVITYOBSERVER_H_

#include <memory>
#include <mutex>

#include "ActivityRequestID.h"
#include "FocusManager/ChannelObserverInterface.h"
#include "Control/ControlPriority.h"
#include "Control/ControlRegistryFactory.h"
#include "ActivityLifecycle.h"
#include "CurrentActivityRequests.h"
#include "CurrentActivities.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

class ChannelToActivityObserver : public ChannelObserverInterface {
public:
    ChannelToActivityObserver(
        std::shared_ptr<CurrentActivityRequests> activeRequests,
        std::shared_ptr<CurrentActivities> currentActivities,
        const control::ControlPriority controlPriority,
        std::shared_ptr<control::ControlRegistryFactory> controlRegistryFactory,
        ActivityRequestID activityRequestId);

    ~ChannelToActivityObserver();

    /// @name ChannelObserverInterface method overrides.
    /// @{
    void onFocusChanged(FocusState newFocus, MixingBehavior behavior) override;
    /// @}

private:
    void cleanup();

    std::shared_ptr<CurrentActivityRequests> m_activeRequests;
    std::shared_ptr<CurrentActivities> m_currentActivities;
    const control::ControlPriority m_controlPriority;
    std::shared_ptr<control::ControlRegistryFactory> m_controlRegistryFactory;
    const ActivityRequestID m_activityRequestID;
    bool m_requestHandled;
    std::shared_ptr<ActivityLifecycle> m_activity;
};

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_CHANNELTOACTIVITYOBSERVER_H_
