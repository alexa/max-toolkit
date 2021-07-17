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

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_ACTIVITY_ACTIVITYHANDLERINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_ACTIVITY_ACTIVITYHANDLERINTERFACE_H_

#include <memory>

#include "MultiAgentExperience/Activity/ActivityFocus.h"
#include "MultiAgentExperience/Activity/ActivityControllerInterface.h"
#include "MultiAgentExperience/Control/ControlRegistryInterface.h"
#include "MultiAgentExperience/Experience/ExperienceControllerInterface.h"

namespace multiAgentExperience {
namespace activity {

/**
 * An ActivityHandlerInterface handles the lifecycle of an activity. It is requested in the ActivityManagerInterface
 * with an ActivityRequestInterface.
 *
 * The lifecycle of an activity is simple. Assuming it is granted onReady will be called to start the activity in the
 * given ActivityFocus type (If the request itself is not granted, then onDenied will be called). If in the FOREGROUND,
 * the activity is the primary experience for the user, and should be delivered normally. In the BACKGROUND, the
 * activity is not primary, and should attenuate its experience (e.g. pausing or lowering volume) of its experience
 * while another primary experience is active. An activity can change from FOREGROUND to BACKGROUND any number of times
 * while it is active and each transition must be handled.
 *
 * When completed onStop will be called. An activity is either completed when:
 * - The originating ActivityRequestInterface is used with ActivityManagerInterface#stop()
 * - The ActivityControllerInterface given in onReady is stopped.
 * - The ActivityManagerInterface determines it should stop the current activity. For example this can happen when
 *   another activity of the same ActivityType is granted.
 *
 * Once stopped an activity handler will receive no more lifecycle updates. Similarly a denied activity will also never
 * receive another lifecycle update. Any Controls or Experiences setup with APIs given in onReady will be automatically
 * cleaned up.
 */
class ActivityHandlerInterface {
public:
    /**
     * Destructor.
     */
    virtual ~ActivityHandlerInterface() = default;

    /**
     * Called if the associated request is denied. Once denied the activity will never receive another callback.
     */
    virtual void onDenied() = 0;

    /**
     * Called when the request is granted and the activity can start. The provided ActivityControllerInterface,
     * ControlRegistryInterface, and ExperienceControllerInterface are valid only until onStop is called. Once onStop is
     * called these interfaces will have no effect, and any registered Controls or started Experiences will be
     * automatically cleaned up.
     *
     * @param activityController - Used to control the activity's lifecycle.
     * @param focus - The current focus of the activity, must be used as if it were given in onFocusStateChange.
     * @param controlRegistry - Used to register controls which impact this activity.
     * @param experienceControl - Used to start experiences for this activity.
     */
    virtual void onReady(
        std::shared_ptr<ActivityControllerInterface> activityController,
        multiAgentExperience::activity::ActivityFocus focus,
        std::shared_ptr<control::ControlRegistryInterface> controlRegistry,
        std::shared_ptr<experience::ExperienceControllerInterface> experienceControl) = 0;

    /**
     * The focus changed to a new focus value.
     *
     * @param focus - The current focus of the activity.
     */
    virtual void onFocusStateChange(multiAgentExperience::activity::ActivityFocus focus) = 0;

    /**
     * The activity must stop immediately. Any registered Controls or started Experiences will be automatically cleaned
     * up.
     */
    virtual void onStop() = 0;
};

}  // namespace activity
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_ACTIVITY_ACTIVITYHANDLERINTERFACE_H_
