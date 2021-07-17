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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_ACTIVITYTRANSFORMER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_ACTIVITYTRANSFORMER_H_

#include <memory>

#include <MultiAgentExperience/Activity/ActivityFocus.h>
#include <MultiAgentExperience/Activity/ActivityHandlerInterface.h>
#include <MultiAgentExperience/Control/ControlRegistryInterface.h>
#include <MultiAgentExperience/Experience/ExperienceControllerInterface.h>

#include "Activity/ActivityManager.h"
#include "Control/ControlRegistry.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

class ActivityTransformer : public multiAgentExperience::library::activity::Activity {
public:
    ActivityTransformer(
        std::shared_ptr<multiAgentExperience::library::activity::ActivityManager> activityManager,
        std::shared_ptr<multiAgentExperience::activity::ActivityHandlerInterface> activityHandlerInterface,
        std::shared_ptr<multiAgentExperience::experience::ExperienceControllerInterface> experienceControl);

    /// @name Activity method overrides.
    /// @{
    void onControlRegistryAvailable(std::shared_ptr<library::control::ControlRegistry> controlRegistry) override;
    void onForeground() override;
    void onBackground() override;
    void onStop() override;
    /// @}

private:
    void updateFocus(multiAgentExperience::activity::ActivityFocus focus);

    bool m_wasGranted;
    std::weak_ptr<multiAgentExperience::library::activity::ActivityManager> m_activityManager;
    std::shared_ptr<multiAgentExperience::control::ControlRegistryInterface> m_controlRegistryInterface;
    std::shared_ptr<multiAgentExperience::activity::ActivityHandlerInterface> m_activityHandlerInterface;
    std::shared_ptr<multiAgentExperience::experience::ExperienceControllerInterface> m_experienceControlInterface;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_ACTIVITYTRANSFORMER_H_
