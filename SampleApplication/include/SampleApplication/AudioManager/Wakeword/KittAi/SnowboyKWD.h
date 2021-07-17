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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_WAKEWORD_KITTAI_SNOWBOYKWD_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_WAKEWORD_KITTAI_SNOWBOYKWD_H_

#include <atomic>
#include <thread>

#include <MultiAgentExperience/Audio/AudioReaderInterface.h>

#include "SampleApplication/AudioManager/Wakeword/KittAi/SnowboyWrapper.h"
#include "SampleApplication/AudioManager/Wakeword/WakewordEngine.h"
#include "SampleApplication/AudioManager/Wakeword/WakewordEnginesConfig.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace audioManager {
namespace wakeword {
namespace kittai {

namespace MAX = multiAgentExperience;

/**
 * A wakeword engine implementation based upon Kitt.ai's Snowboy.
 */
class SnowboyKWD : public WakewordEngine {
public:
    /**
     * Creates an engine.
     *
     * @param config The config to be used.
     * @param crosswakeDetector The detector to prevent cross wakes.
     * @param wakewordObserver The MAX wakeword observer to be used.
     * @param audioReader The audio reader to be used.
     * @return A Snowboy wakeword engine if successful, nullptr. otherwise.
     */
    static std::shared_ptr<SnowboyKWD> create(
        const WakewordEnginesConfig::EngineConfig& config,
        std::shared_ptr<audioManager::wakeword::crosswake::SimpleCrosswakeDetector> crosswakeDetector,
        std::shared_ptr<MAX::application::WakeWordObserverInterface> wakewordObserver,
        std::shared_ptr<MAX::audio::AudioReaderInterface> audioReader);

    /// @name WakewordEngineInterface methods.
    /// @{
    std::string getName() override;
    WakewordEngine::CreateMethod getCreateMethod() override;
    std::set<std::string> getWakewords() override;
    /// @}

    /// @name DataObserverInterface methods.
    /// @{
    std::pair<bool, std::size_t> onData(const void* buffer, std::size_t numWords) override;
    /// @}

    /**
     * Tests if the provided audio format is compatible with this engine.
     *
     * @param audioFormat The format to be considered.
     * @return Whether the format is compatible.
     */
    bool isCompatible(MAX::audio::AudioFormat audioFormat);

    /**
     * Start watching for keyword utterances.
     */
    void startWatching();

    /**
     * Stop watching for keyword utterances.
     */
    void stopWatching();

private:
    /**
     * Constructor.
     *
     * @param config The config to be used.
     * @param crosswakeDetector The detector to prevent cross wakes.
     * @param wakewordObserver The MAX wakeword observer to be used.
     * @param audioReader The audio reader to be used.
     * @param maxSamplesPerPush The maximum samples per push.
     * @param resources A resources path.
     * @param model The model to be used.
     * @param sensitivity The sensitivity to be used.
     * @param audioGain The audio gain to be used.
     * @param applyFrontEndProcessing Whether front-end processing should be applied.
     */
    SnowboyKWD(
        const WakewordEnginesConfig::EngineConfig& config,
        std::shared_ptr<audioManager::wakeword::crosswake::SimpleCrosswakeDetector> crosswakeDetector,
        std::shared_ptr<MAX::application::WakeWordObserverInterface> wakewordObserver,
        std::shared_ptr<MAX::audio::AudioReaderInterface> audioReader,
        const std::size_t maxSamplesPerPush,
        const char* resources,
        const char* model,
        const char* sensitivity,
        const float audioGain,
        const bool applyFrontEndProcessing);

    /**
     * Our main worker function.
     */
    void detectionLoop();

    /// Our config.
    WakewordEnginesConfig::EngineConfig m_config;
    /// Our MAX wakeword observer.
    std::shared_ptr<MAX::application::WakeWordObserverInterface> m_wakewordObserver;
    /// The audio reader from which audio data shall be read.
    std::shared_ptr<MAX::audio::AudioReaderInterface> m_audioReader;
    /// The maximum samples per push.
    std::size_t m_maxSamplesPerPush;
    /// Our worker thread.
    std::thread m_bgListener;
    /// Whether we are shutting down.
    std::atomic<bool> m_isShuttingDown;
    /// Our underlying snowboy wrapper.
    SnowboyWrapper m_detector;
};

}  // namespace kittai
}  // namespace wakeword
}  // namespace audioManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_WAKEWORD_KITTAI_SNOWBOYKWD_H_
