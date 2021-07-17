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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_PORTAUDIOMICROPHONE_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_PORTAUDIOMICROPHONE_H_

#include <atomic>
#include <mutex>
#include <set>

#include <portaudio.h>

#include <MultiAgentExperience/Audio/AudioFormat.h>
#include <MultiAgentExperience/Utils/Data/DataObserverInterface.h>

#include "SampleApplication/AudioManager/Microphone/MicrophoneConfig.h"
#include "SampleApplication/AudioManager/Microphone/MicrophoneInterface.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace audioManager {
namespace microphone {

namespace MAX = multiAgentExperience;

/**
 * This acts as a wrapper around PortAudio, a cross-platform open-source audio I/O library.
 */
class PortAudioMicrophone : public MicrophoneInterface {
public:
    /**
     * Creates a @c PortAudioMicrophone.
     *
     * @param format The audio format to be used.
     * @param config The config to be used.
     * @return A unique_ptr to a @c PortAudioMicrophone if creation was successful and @c nullptr otherwise.
     */
    static std::unique_ptr<PortAudioMicrophone> create(
        const audio::AudioFormat& format,
        const MicrophoneConfig& config);

    /**
     * Destructor.
     */
    ~PortAudioMicrophone();

    /// @name MicrophoneInterface methods.
    /// @{
    bool startStreamingData() override;
    bool stopStreamingData() override;
    void mute(bool enabled) override;
    bool isMuted() override;
    /// @}

    /// @name DataWriterInterface methods.
    /// @{
    std::pair<bool, std::size_t> write(const void* buffer, std::size_t numWords) override;
    void addObserver(std::shared_ptr<MAX::utils::data::DataObserverInterface> observer) override;
    void removeObserver(std::shared_ptr<MAX::utils::data::DataObserverInterface> observer) override;
    /// @}

private:
    /**
     * Constructor.
     */
    PortAudioMicrophone();

    /**
     * Initialize this class.
     *
     * @param format The audio format to be used.
     * @param config The config to be used.
     * @return Whether initialization was successful.
     */
    bool initialize(const audio::AudioFormat& format, const MicrophoneConfig& config);

    /// The PortAudio stream.
    PaStream* m_paStream;
    /// A mutex to synchronize calls on public APIs.
    std::mutex m_mutex;
    /// Data observers.
    std::set<std::shared_ptr<MAX::utils::data::DataObserverInterface>> m_observers;

    std::atomic<bool> m_isMuted;
};

}  // namespace microphone
}  // namespace audioManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_PORTAUDIOMICROPHONE_H_
