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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_AUDIOMANAGER_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_AUDIOMANAGER_H_

#include <set>
#include <memory>

#include <AVSCommon/AVS/AudioInputStream.h>
#include <AVSCommon/Utils/Threading/Executor.h>

#include <MultiAgentExperience/Audio/AudioFormat.h>

#include <rapidjson/document.h>

#include "SampleApplication/AgentManager/GestureHandlerInterface.h"
#include "SampleApplication/AudioManager/Microphone/MicrophoneConfig.h"
#include "SampleApplication/AudioManager/Microphone/MicrophoneInterface.h"
#include "SampleApplication/AudioManager/Wakeword/WakewordEnginesConfig.h"
#include "SampleApplication/AudioManager/Wakeword/WakewordEngine.h"
#include "SampleApplication/AudioManager/Wakeword/WakewordMetadataCache.h"
#include "SampleApplication/AudioManager/Wakeword/CrosswakeDetector/SimpleCrosswakeDetector.h"
#include "SampleApplication/Utils/AudioDataDirectAccessInterface.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace audioManager {

namespace MAX = multiAgentExperience;

/**
 * This class manages all components which pertain to audio in an Multi-Agent application. In particular:
 *
 *  * microphone(s)
 *  * wakeword engines
 *  * audio data buffer(s)
 *
 * Furthermore, this class ensures that formats between each such managed components align.
 */
class AudioManager
        : public MAX::utils::data::DataObserverInterface
        , public utils::AudioDataDirectAccessInterface
        , public std::enable_shared_from_this<AudioManager> {
public:
    /**
     * Method to create an instance of the @c AudioManager.
     *
     * @param crosswakeDetector The detector to prevent cross wakes.
     * @param wakewordObserver A wakeword observer as provided by the MAX Library.
     * @param parsedJsonDocumentRoot The parsed JSON document from which we shall extract configuration.
     * @return A handle to an @c AudioManager if successful, otherwise nullptr.
     */
    static std::shared_ptr<AudioManager> create(
        std::shared_ptr<audioManager::wakeword::crosswake::SimpleCrosswakeDetector> crosswakeDetector,
        std::shared_ptr<MAX::application::WakeWordObserverInterface> wakewordObserver,
        const rapidjson::Document& parsedJsonDocumentRoot);

    /// @name DataObserverInterface methods.
    /// @{
    std::pair<bool, std::size_t> onData(const void* buffer, std::size_t numWords) override;
    /// @}

    /// @name AudioDataDirectAccessInterface methods.
    /// @{
    std::shared_ptr<alexaClientSDK::avsCommon::avs::AudioInputStream> getSDSHandle() override;

    std::shared_ptr<alexaClientSDK::avsCommon::avs::AudioInputStream::Reader> createSDSReader() override;
    /// @}

    /**
     * Acquire the audio format used by all audio components.
     * @return The audio format.
     */
    audio::AudioFormat getAudioFormat();

    /**
     * Sets the gesture handler which shall be used.
     * @param gestureHandler The gesture handler to be used.
     */
    void setGestureHandler(std::shared_ptr<agentManager::GestureHandlerInterface> gestureHandler);

    /**
     * Acquires the keyword metadata cache.
     * @return The metadata cache.
     */
    std::shared_ptr<audioManager::wakeword::WakewordMetadataCache> getMetadataCache();

    /**
     * Control whether or not the microphone is muted
     *
     * @param isMuted true to mute the microphone, false to unmute
     */
    void muteMicrophone(bool isMuted);

    /**
     * Is the microphone muted?
     * @return true if the microphone is muted
     */
    bool isMicrophoneMuted();

private:
    /**
     * Constructor.
     *
     * @param audioFormat The audio format to be used.
     * @param crosswakeDetector The detector to prevent cross wakes.
     * @param wakewordObserver The MAX wakeword observer to be used.
     */
    AudioManager(
        const audio::AudioFormat& audioFormat,
        std::shared_ptr<audioManager::wakeword::crosswake::SimpleCrosswakeDetector> crosswakeDetector,
        std::shared_ptr<MAX::application::WakeWordObserverInterface> wakewordObserver);

    /**
     * Method to initialize an instance of this class.
     *
     * @param microphoneConfig The microphone configuration.
     * @param wwConfig The wakeword engine configuration.
     * @return Whether initialization was successful.
     */
    bool initialize(
        const microphone::MicrophoneConfig& microphoneConfig,
        const wakeword::WakewordEnginesConfig& wwConfig);

    /**
     * A helper function to process data provided.
     *
     * @param buffer The data provided.
     * @param numWords The number of words of data.
     */
    void executeOnData(const void* buffer, std::size_t numWords);

    /// Our audio format.
    audio::AudioFormat m_audioFormat;
    /// Our microphone handle.
    std::shared_ptr<microphone::MicrophoneInterface> m_microphone;
    /// Our wakeword engines.
    std::set<std::shared_ptr<wakeword::WakewordEngine>> m_wakewordEngines;
    /// Our MAX crosswakeDetector.
    std::shared_ptr<audioManager::wakeword::crosswake::SimpleCrosswakeDetector> m_crosswakeDetector;
    /// Our MAX wakeword observer.
    std::shared_ptr<MAX::application::WakeWordObserverInterface> m_wakewordObserver;
    /// Our kwd metadata cache.
    std::shared_ptr<wakeword::WakewordMetadataCache> m_metadataCache;
    /// Our executor to perform asynchronous operations.
    alexaClientSDK::avsCommon::utils::threading::Executor m_executor;
};

}  // namespace audioManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_AUDIOMANAGER_H_
