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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYLIFECYCLE_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYLIFECYCLE_H_

#include <atomic>
#include <memory>
#include <mutex>
#include <vector>

#include "Activity.h"
#include "ActivityID.h"
#include "Control/ControlRegistry.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

class ActivityLifecycle {
public:
    ActivityLifecycle(std::shared_ptr<Activity> activity);

    ~ActivityLifecycle();

    void markGranted(const ActivityID id);

    void makeControlRegistryAvailable(std::shared_ptr<control::ControlRegistry> controlRegistry);

    void enterForeground();

    void enterBackground();

    void stop();

    const ActivityID getID();

    void cleanup();

private:
    enum class ActivityState { REQUESTED, WAITING, FOREGROUND, BACKGROUND, COMPLETED, CLEANED_UP };

    bool trySwitchStateToFrom(const ActivityState to, std::vector<ActivityState> from);
    bool trySwitchStateToUnlessInFrom(const ActivityState to, std::vector<ActivityState> from);
    bool isInOneOfStates(std::vector<ActivityState> states);

    std::mutex m_stateMutex;
    ActivityState m_state;
    std::shared_ptr<Activity> m_activity;
    std::shared_ptr<control::ControlRegistry> m_controlRegistry;
};

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYLIFECYCLE_H_
