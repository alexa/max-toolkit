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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_WAKEWORD_WAKEWORDENGINEFACTORY_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_WAKEWORD_WAKEWORDENGINEFACTORY_H_

#include <AVSCommon/AVS/AudioInputStream.h>

#include <MultiAgentExperience/Audio/AudioFormat.h>

#include "SampleApplication/AudioManager/Wakeword/WakewordEngine.h"
#include "SampleApplication/AudioManager/Wakeword/WakewordEnginesConfig.h"
#include "SampleApplication/AudioManager/Wakeword/WakewordMetadataCache.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace audioManager {
namespace wakeword {

namespace MAX = multiAgentExperience;

/**
 * This class defines the API which should be used to instantiate wakeword engines.
 */
class WakewordEngineFactory {
public:
    /**
     * Create a wakeword engine.
     *
     * @param audioFormat The audio format to be used.
     * @param config The config to be used.
     * @param crosswakeDetector The detector to prevent cross wakes.
     * @param wakewordObserver The MAX wakeword observer to be used.
     * @param metadataCache The metadata cache to be used when a wakeword is detected.
     * @param sharedDataStream The audio data stream to read from.
     * @return A wakeword engine if created successfully, otherwise nullptr.
     */
    static std::shared_ptr<WakewordEngine> createWakewordEngine(
        audio::AudioFormat audioFormat,
        const WakewordEnginesConfig::EngineConfig& config,
        std::shared_ptr<crosswake::SimpleCrosswakeDetector> crosswakeDetector,
        std::shared_ptr<MAX::application::WakeWordObserverInterface> wakewordObserver,
        std::shared_ptr<audioManager::wakeword::WakewordMetadataCache> metadataCache,
        std::shared_ptr<alexaClientSDK::avsCommon::avs::AudioInputStream> sharedDataStream);
};

}  // namespace wakeword
}  // namespace audioManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_WAKEWORD_WAKEWORDENGINEFACTORY_H_
