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


#include "SampleApplication/UniversalDeviceCommandManager/UniversalDeviceCommandManager.h"
#include "SampleApplication/Utils/RadiantLogger.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace universalDeviceCommandManager {

/// Metadata parameters that will be passed into our logging system.
static const std::string MODULE_TAG("ExperienceManager");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, MODULE_TAG, __func__, message)

std::unique_ptr<UniversalDeviceCommandManager> UniversalDeviceCommandManager::create(
    std::shared_ptr<MAX::control::ControlManagerInterface> maxControlManager,
    std::shared_ptr<MAX::control::ControlInvokerInterface> maxControlInvoker) {
    LX(DEBUG3, "");

    if (!maxControlManager) {
        LX(ERROR, "maxControlManager is nullptr.");
        return nullptr;
    }

    return std::unique_ptr<UniversalDeviceCommandManager>(
        new UniversalDeviceCommandManager(maxControlManager, maxControlInvoker));
}

UniversalDeviceCommandManager::UniversalDeviceCommandManager(
    std::shared_ptr<MAX::control::ControlManagerInterface> maxControlManager,
    std::shared_ptr<MAX::control::ControlInvokerInterface> maxControlInvoker) :
        m_maxControlManager{maxControlManager},
        m_maxControlInvoker{maxControlInvoker} {
}

void UniversalDeviceCommandManager::addRenderer(std::weak_ptr<UniversalDeviceCommandRendererInterface> renderer) {
    m_maxControlManager->addObserver(renderer);
}

void UniversalDeviceCommandManager::clearRenderers() {
    m_maxControlManager->clearObservers();
}

void UniversalDeviceCommandManager::invokeStop() {
    m_maxControlInvoker->invokeControl(multiAgentExperience::control::ControlType::STOP);
}

}  // namespace universalDeviceCommandManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience