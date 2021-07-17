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

#include "SampleApplication/AudioManager/Microphone/PortAudioMicrophone.h"

#include <cstring>
#include <string>
#include <vector>

#include <rapidjson/document.h>

#include "SampleApplication/Utils/RadiantLogger.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace audioManager {
namespace microphone {

/// Metadata parameters that will be passed into our logging system.
static const std::string MODULE_TAG("PortAudioMicrophone");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, MODULE_TAG, __func__, message)

/**
 * Utility function to handle PortAudio callbacks.
 *
 * @param inputBuffer The input buffer to be used.
 * @param outputBuffer The output buffer to be used.
 * @param numSamples The number of samples provided.
 * @param timeInfo Timeinfo.
 * @param statusFlags Status flags.
 * @param userData Custom pointer to data.
 * @return @c paContinue if successful, other values otherwise.
 */
static int portAudioCallback(
    const void* inputBuffer,
    void* outputBuffer,
    unsigned long numSamples,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* userData) {
    PortAudioMicrophone* wrapper = static_cast<PortAudioMicrophone*>(userData);
    auto result = wrapper->write(inputBuffer, numSamples);
    if (!result.first) {
        LX(CRITICAL, "Failed to write portAudio data.");
        return paAbort;
    }

    return paContinue;
}

std::unique_ptr<PortAudioMicrophone> PortAudioMicrophone::create(
    const audio::AudioFormat& format,
    const MicrophoneConfig& config) {
    LX(DEBUG3, "");

    std::unique_ptr<PortAudioMicrophone> microphone(new PortAudioMicrophone());
    if (!microphone->initialize(format, config)) {
        LX(CRITICAL, "Failed to initialize PortAudioMicrophone");
        return nullptr;
    }
    return microphone;
}

PortAudioMicrophone::PortAudioMicrophone() : m_paStream{nullptr}, m_isMuted{false} {
    LX(DEBUG3, "");
}

PortAudioMicrophone::~PortAudioMicrophone() {
    LX(DEBUG3, "");

    Pa_StopStream(m_paStream);
    Pa_CloseStream(m_paStream);
    Pa_Terminate();
}

bool PortAudioMicrophone::initialize(const audio::AudioFormat& format, const MicrophoneConfig& config) {
    LX(DEBUG3, "");

    PaError err = paNoError;
    err = Pa_Initialize();
    if (err != paNoError) {
        LX(CRITICAL, std::string("Failed to initialize PortAudio. Error code:") + std::string("errorCode"));
        return false;
    }

    PaStreamParameters inputParameters;
    std::memset(&inputParameters, 0, sizeof(inputParameters));
    inputParameters.device = Pa_GetDefaultInputDevice();
    inputParameters.channelCount = format.numChannels;
    inputParameters.sampleFormat = paInt16;
    inputParameters.suggestedLatency = config.suggestedLatencySeconds;
    inputParameters.hostApiSpecificStreamInfo = nullptr;

    err = Pa_OpenStream(
        &m_paStream,
        &inputParameters,
        nullptr,
        format.sampleRateHz,
        paFramesPerBufferUnspecified,
        paNoFlag,
        portAudioCallback,
        this);

    if (err != paNoError) {
        LX(CRITICAL, std::string("Failed to open PortAudio default stream. Error code:") + std::string("errorCode"));
        return false;
    }

    return true;
}

bool PortAudioMicrophone::startStreamingData() {
    LX(DEBUG3, "");

    std::lock_guard<std::mutex> lock{m_mutex};
    PaError err = Pa_StartStream(m_paStream);
    if (err != paNoError) {
        LX(CRITICAL, "Failed to start PortAudio stream");
        return false;
    }

    return true;
}

bool PortAudioMicrophone::stopStreamingData() {
    LX(DEBUG3, "");

    std::lock_guard<std::mutex> lock{m_mutex};
    PaError err = Pa_StopStream(m_paStream);
    if (err != paNoError) {
        LX(CRITICAL, "Failed to stop PortAudio stream");
        return false;
    }

    return true;
}

std::pair<bool, size_t> PortAudioMicrophone::write(const void* buffer, size_t numWords) {
    // TODO VII-360: This may break if the PortAudio data format changes (the size of the words change from 16bit)
    static std::vector<unsigned short> s_zeroData;
    if (m_isMuted && s_zeroData.size() < numWords) {
        s_zeroData.assign(numWords, 0);
    }

    for (auto observer : m_observers) {
        std::pair<bool, std::size_t> result;
        if (m_isMuted) {
            result = observer->onData(s_zeroData.data(), numWords);
        } else {
            result = observer->onData(buffer, numWords);
        }
        if (!result.first) {
            return std::pair<bool, size_t>(false, 0);
        }
    }
    return std::pair<bool, size_t>(true, numWords);
}  // namespace microphone

void PortAudioMicrophone::addObserver(std::shared_ptr<MAX::utils::data::DataObserverInterface> observer) {
    LX(DEBUG3, "");
    if (m_observers.find(observer) != m_observers.end()) {
        LX(WARN, "Observer already present, so will not add.");
        return;
    }
    m_observers.insert(observer);
}

void PortAudioMicrophone::removeObserver(std::shared_ptr<MAX::utils::data::DataObserverInterface> observer) {
    LX(DEBUG3, "");
    if (m_observers.find(observer) == m_observers.end()) {
        LX(WARN, "Observer is not present, so cannot remove.");
        return;
    }
    m_observers.erase(observer);
}

void PortAudioMicrophone::mute(bool enabled) {
    LX(DEBUG3, "");
    m_isMuted = enabled;
}

bool PortAudioMicrophone::isMuted() {
    return m_isMuted;
}

}  // namespace microphone
}  // namespace audioManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
