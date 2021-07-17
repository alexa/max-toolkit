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

#include <SampleApplication/AudioManager/SDS/SDSReader.h>
#include "SampleApplication/AudioManager/Wakeword/WakewordEngineFactory.h"
#include "SampleApplication/AudioManager/Wakeword/AVSSDK/AVSSDK_KWDAdapter.h"
#include "SampleApplication/Utils/RadiantLogger.h"

#ifdef BUILD_WITH_SNOWBOY
#include "SampleApplication/AudioManager/Wakeword/KittAi/SnowboyKWD.h"
#endif

namespace multiAgentExperience {
namespace sampleApplication {
namespace audioManager {
namespace wakeword {

/// Metadata parameters that will be passed into our logging system.
static const std::string MODULE_TAG("WakewordEnginesFactory");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, MODULE_TAG, __func__, message)

/**
 * Utility function to create a wakeword engine directly. Currently only supports Kitt.ai SNOWBOY.
 *
 * @param audioFormat The audio format to use.
 * @param config The config to use.
 * @param wakewordObserver The MAX wakeword observer to use.
 * @param sharedDataStream The audio data stream to be read from.
 * @return A handle to a wakeword engine if successful, nullptr otherwise.
 */
static std::shared_ptr<WakewordEngine> createCustomWakewordEngine(
    audio::AudioFormat audioFormat,
    const WakewordEnginesConfig::EngineConfig& config,
    std::shared_ptr<crosswake::SimpleCrosswakeDetector> crosswakeDetector,
    std::shared_ptr<MAX::application::WakeWordObserverInterface> wakewordObserver,
    std::shared_ptr<alexaClientSDK::avsCommon::avs::AudioInputStream> sharedDataStream) {
    LX(DEBUG3, "");

    if ("kitt.ai" == config.name) {
#ifdef BUILD_WITH_SNOWBOY
        std::shared_ptr<alexaClientSDK::avsCommon::avs::AudioInputStream::Reader> wrappedReader =
            sharedDataStream->createReader(alexaClientSDK::avsCommon::avs::AudioInputStream::Reader::Policy::BLOCKING);
        auto sdsReader = std::make_shared<sds::SDSReader>(config.name, audioFormat, wrappedReader, true);
        auto kwd = kittai::SnowboyKWD::create(config, crosswakeDetector, wakewordObserver, sdsReader);
        // TODO: The wake word lifecycle needs extension: VII-250.
        kwd->startWatching();
        return kwd;
#else
        LX(ERROR, "build not configured to allow KittAI use.");
#endif
    }

    LX(ERROR, "invalid wakewordEngine name : " + config.name);

    return nullptr;
}

/**
 * Utility function to create a wakeword engine via the AVS SDK.
 *
 * @param audioFormat The audio format to use.
 * @param config The config to use.
 * @param wakewordObserver The MAX wakeword observer to use.
 * @param metadataCache The kwd metadata cache that should be used.
 * @param sharedDataStream The audio data stream to be read from.
 * @return A handle to a wakeword engine if successful, nullptr otherwise.
 */
static std::shared_ptr<WakewordEngine> createAVSSDKWakewordEngine(
    audio::AudioFormat audioFormat,
    const WakewordEnginesConfig::EngineConfig& config,
    std::shared_ptr<crosswake::SimpleCrosswakeDetector> crosswakeDetector,
    std::shared_ptr<MAX::application::WakeWordObserverInterface> wakewordObserver,
    std::shared_ptr<WakewordMetadataCache> metadataCache,
    std::shared_ptr<alexaClientSDK::avsCommon::avs::AudioInputStream> sharedDataStream) {
    LX(DEBUG3, "");

    return avssdk::AVSSDK_KWDAdapter::create(
        config, audioFormat, crosswakeDetector, wakewordObserver, metadataCache, sharedDataStream);
}

std::shared_ptr<WakewordEngine> WakewordEngineFactory::createWakewordEngine(
    audio::AudioFormat audioFormat,
    const WakewordEnginesConfig::EngineConfig& config,
    std::shared_ptr<crosswake::SimpleCrosswakeDetector> crosswakeDetector,
    std::shared_ptr<MAX::application::WakeWordObserverInterface> wakewordObserver,
    std::shared_ptr<audioManager::wakeword::WakewordMetadataCache> metadataCache,
    std::shared_ptr<alexaClientSDK::avsCommon::avs::AudioInputStream> sharedDataStream) {
    LX(DEBUG3, "Creating engine with name:" + config.name);

    if (WakewordEngine::CreateMethod::CUSTOM == config.createMethod) {
        return createCustomWakewordEngine(audioFormat, config, crosswakeDetector, wakewordObserver, sharedDataStream);
    } else {
        return createAVSSDKWakewordEngine(
            audioFormat, config, crosswakeDetector, wakewordObserver, metadataCache, sharedDataStream);
    }
}
}  // namespace wakeword
}  // namespace audioManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
