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

#include "Core/Transformer/ActivityTransformer.h"

#include "Activity/ActivityManager.h"
#include "Core/Transformer/ActivityControllerTransformer.h"
#include "Core/Transformer/ControlRegistryTransformer.h"
#include "MultiAgentExperience/Activity/ActivityHandlerInterface.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

ActivityTransformer::ActivityTransformer(
    std::shared_ptr<multiAgentExperience::library::activity::ActivityManager> activityManager,
    std::shared_ptr<multiAgentExperience::activity::ActivityHandlerInterface> activityHandlerInterface,
    std::shared_ptr<multiAgentExperience::experience::ExperienceControllerInterface> experienceControl) :
        m_wasGranted{false},
        m_activityManager{activityManager},
        m_controlRegistryInterface{nullptr},
        m_activityHandlerInterface{activityHandlerInterface},
        m_experienceControlInterface{experienceControl} {
}

void ActivityTransformer::onControlRegistryAvailable(
    std::shared_ptr<multiAgentExperience::library::control::ControlRegistry> controlRegistry) {
    // this is critical, without this value for the id, activities cannot be unscheduled.
    m_controlRegistryInterface = std::make_shared<ControlRegistryTransformer>(controlRegistry);
}

void ActivityTransformer::onForeground() {
    updateFocus(multiAgentExperience::activity::ActivityFocus::FOREGROUND);
}

void ActivityTransformer::onBackground() {
    updateFocus(multiAgentExperience::activity::ActivityFocus::BACKGROUND);
}

void ActivityTransformer::onStop() {
    m_experienceControlInterface->invalidate();
    if (m_wasGranted) {
        m_activityHandlerInterface->onStop();
    }
}

void ActivityTransformer::updateFocus(multiAgentExperience::activity::ActivityFocus focus) {
    if (!m_wasGranted) {
        m_wasGranted = true;
        auto id = getID();
        std::weak_ptr<multiAgentExperience::library::activity::ActivityManager> activityManagerWeak = m_activityManager;
        auto stopCallback = [activityManagerWeak, id]() {
            if (auto activityManager = activityManagerWeak.lock()) {
                activityManager->finish(id);
            }
        };
        auto activityController = std::make_shared<ActivityControllerTransformer>(stopCallback);

        m_activityHandlerInterface->onReady(
            activityController, focus, m_controlRegistryInterface, m_experienceControlInterface);
    }
    m_activityHandlerInterface->onFocusStateChange(focus);
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
