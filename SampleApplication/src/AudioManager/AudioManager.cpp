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

#include "SampleApplication/AudioManager/AudioManager.h"

#include "SampleApplication/AudioManager/AudioConfig.h"
#include "SampleApplication/AudioManager/Microphone/PortAudioMicrophone.h"
#include "SampleApplication/AudioManager/Wakeword/WakewordEngineFactory.h"
#include "SampleApplication/Utils/RadiantLogger.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace audioManager {

/// Metadata parameters that will be passed into our logging system.
static const std::string MODULE_TAG("AudioManager");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, MODULE_TAG, __func__, message)

using namespace rapidjson;
using namespace alexaClientSDK;

/// How many words (ie. bytes) are in an SDS sample.
static const int AUDIO_WORDS_PER_SAMPLE = 2;
/// Our SDS instance.
static std::shared_ptr<avsCommon::avs::AudioInputStream> g_sharedDataStream;
/// Our SDS writer.
static std::shared_ptr<avsCommon::avs::AudioInputStream::Writer> g_SDSWriter;

/**
 * Utility function to initalize our AVS SDK SDS and the SDS writer.
 *
 * @param audioFormat The audio format to be used for the SDS.
 * @return If initialization was successful.
 */
static bool initializeSDS(const audio::AudioFormat& audioFormat) {
    if (g_sharedDataStream) {
        return true;
    }

    // TODO : VII-252 : Update this code to use our m_audioFormat, as aligned with the config.
    unsigned int SAMPLE_RATE_HZ = 16000;
    size_t WORD_SIZE = 2;
    size_t MAX_READERS = 10;
    std::chrono::seconds AMOUNT_OF_AUDIO_DATA_IN_BUFFER = std::chrono::seconds(15);
    size_t BUFFER_SIZE_IN_SAMPLES = (SAMPLE_RATE_HZ)*AMOUNT_OF_AUDIO_DATA_IN_BUFFER.count();

    size_t sdsBufferSize =
        avsCommon::avs::AudioInputStream::calculateBufferSize(BUFFER_SIZE_IN_SAMPLES, WORD_SIZE, MAX_READERS);

    if (0 == sdsBufferSize) {
        LX(ERROR, "Unable to calculate SDS buffer size.");
        return false;
    }

    auto sdsBuffer = std::make_shared<alexaClientSDK::avsCommon::avs::AudioInputStream::Buffer>(sdsBufferSize);
    g_sharedDataStream = alexaClientSDK::avsCommon::avs::AudioInputStream::create(sdsBuffer, WORD_SIZE, MAX_READERS);

    g_SDSWriter = g_sharedDataStream->createWriter(
        alexaClientSDK::avsCommon::avs::AudioInputStream::Writer::Policy::NONBLOCKABLE);
    if (!g_SDSWriter) {
        LX(ERROR, "Failed to create SDS writer.");
        return false;
    }

    return true;
}

std::shared_ptr<AudioManager> AudioManager::create(
    std::shared_ptr<audioManager::wakeword::crosswake::SimpleCrosswakeDetector> crosswakeDetector,
    std::shared_ptr<MAX::application::WakeWordObserverInterface> wakewordObserver,
    const rapidjson::Document& parsedJsonDocumentRoot) {
    LX(DEBUG3, "");

    audio::AudioFormat audioFormat;
    if (!parseJSONConfig(parsedJsonDocumentRoot, &audioFormat)) {
        LX(ERROR, "Unable to parse audio format from config.");
        return nullptr;
    }

    audioFormat.wordsPerSample = AUDIO_WORDS_PER_SAMPLE;

    microphone::MicrophoneConfig microphoneConfig;
    if (!audioManager::microphone::parseJSONConfig(parsedJsonDocumentRoot, &microphoneConfig)) {
        LX(ERROR, "Unable to parse microphone config.");
        return nullptr;
    }

    audioManager::wakeword::WakewordEnginesConfig wwConfig;
    if (!audioManager::wakeword::parseJSONConfig(parsedJsonDocumentRoot, &wwConfig)) {
        LX(ERROR, "Unable to parse wakeword engines config.");
        return nullptr;
    }

    auto audioManager =
        std::shared_ptr<AudioManager>(new AudioManager(audioFormat, crosswakeDetector, wakewordObserver));
    if (!audioManager->initialize(microphoneConfig, wwConfig)) {
        LX(ERROR, "Unable to initialize audioManager.");
        return nullptr;
    }

    return audioManager;
}

AudioManager::AudioManager(
    const audio::AudioFormat& audioFormat,
    std::shared_ptr<audioManager::wakeword::crosswake::SimpleCrosswakeDetector> crosswakeDetector,
    std::shared_ptr<MAX::application::WakeWordObserverInterface> wakewordObserver) :
        m_audioFormat{audioFormat},
        m_crosswakeDetector{crosswakeDetector},
        m_wakewordObserver{wakewordObserver} {
}

bool AudioManager::initialize(
    const microphone::MicrophoneConfig& microphoneConfig,
    const wakeword::WakewordEnginesConfig& wwConfig) {
    LX(DEBUG3, "");

    m_metadataCache = std::make_shared<wakeword::WakewordMetadataCache>();

    if (!initializeSDS(m_audioFormat)) {
        LX(ERROR, "initializeFailed : unable to initialize SDS.");
    }

    m_microphone = microphone::PortAudioMicrophone::create(m_audioFormat, microphoneConfig);
    m_microphone->addObserver(shared_from_this());
    m_microphone->startStreamingData();

    for (auto& config : wwConfig.engineConfigs) {
        auto wwEngine = wakeword::WakewordEngineFactory::createWakewordEngine(
            m_audioFormat, config, m_crosswakeDetector, m_wakewordObserver, m_metadataCache, g_sharedDataStream);
        if (wwEngine) {
            m_wakewordEngines.insert(wwEngine);
        } else {
            LX(ERROR, "created a null " + config.name);
        }
    }

    return true;
}

std::pair<bool, std::size_t> AudioManager::onData(const void* buffer, std::size_t numWords) {
    m_executor.submit([this, buffer, numWords]() { executeOnData(buffer, numWords); });

    return std::pair<bool, std::size_t>(true, numWords);
}

void AudioManager::executeOnData(const void* buffer, std::size_t numWords) {
    ssize_t returnCode = g_SDSWriter->write(buffer, numWords);
    if (returnCode <= 0) {
        LX(ERROR, "Failed to write to SDS stream. error code:" + std::to_string(returnCode));
    }
}

std::shared_ptr<avsCommon::avs::AudioInputStream> AudioManager::getSDSHandle() {
    return g_sharedDataStream;
}

std::shared_ptr<avsCommon::avs::AudioInputStream::Reader> AudioManager::createSDSReader() {
    LX(DEBUG3, "");

    auto reader = g_sharedDataStream->createReader(avsCommon::avs::AudioInputStream::Reader::Policy::BLOCKING);
    if (!reader) {
        LX(ERROR, "reader is nullptr.");
        return nullptr;
    }
    return reader;
}

audio::AudioFormat AudioManager::getAudioFormat() {
    return m_audioFormat;
}

std::shared_ptr<wakeword::WakewordMetadataCache> AudioManager::getMetadataCache() {
    return m_metadataCache;
}

void AudioManager::muteMicrophone(bool isMuted) {
    m_microphone->mute(isMuted);
}

bool AudioManager::isMicrophoneMuted() {
    return m_microphone->isMuted();
}

void AudioManager::setGestureHandler(std::shared_ptr<agentManager::GestureHandlerInterface> gestureHandler) {
    LX(DEBUG3, "");
    for (auto engine : m_wakewordEngines) {
        engine->setGestureHandler(gestureHandler);
    }
}

}  // namespace audioManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
