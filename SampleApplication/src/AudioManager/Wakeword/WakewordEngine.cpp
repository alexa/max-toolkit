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

#include "SampleApplication/AudioManager/Wakeword/WakewordEngine.h"
#include "SampleApplication/Utils/RadiantLogger.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace audioManager {
namespace wakeword {

/// Metadata parameters that will be passed into our logging system.
static const std::string MODULE_TAG("WakewordEngine");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, MODULE_TAG, __func__, message)

WakewordEngine::WakewordEngine(
    std::shared_ptr<crosswake::SimpleCrosswakeDetector> crosswakeDetector,
    std::shared_ptr<MAX::application::WakeWordObserverInterface> observer) :
        m_crosswakeDetector{crosswakeDetector},
        m_observer{observer} {
    LX(ERROR, "createdww with " + std::to_string(crosswakeDetector == nullptr));
}

void WakewordEngine::setGestureHandler(std::shared_ptr<agentManager::GestureHandlerInterface> gestureHandler) {
    LX(DEBUG3, "");
    // no-op for base class
}

}  // namespace wakeword
}  // namespace audioManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
