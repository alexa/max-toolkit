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

#include "SampleApplication/AudioManager/Wakeword/KittAi/SnowboyKWD.h"

#include <AIP/AudioProvider.h>

#include "SampleApplication/Utils/RadiantLogger.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace audioManager {
namespace wakeword {
namespace kittai {

namespace avs = alexaClientSDK::avsCommon::avs;

/// The resource path that should be used.
constexpr const char* RESOURCE_PATH = "/common.res";

// TODO: Instead of hard coding to computer, use what is set in MAXConfig.json if available. VII-251
constexpr const char* MODEL_PATH = "/models/computer.umdl";

/// Our sensitivity value.
constexpr const char* SENSITIVITY = "0.4";

/// Our audio gain value.
constexpr float AUDIO_GAIN = 2.0;

/// Whether audio front end processing should be applied.
constexpr bool APPLY_FRONT_END_PROCESSING = true;

/// How long to wait to push data.
constexpr std::chrono::milliseconds TIME_PER_PUSH = std::chrono::milliseconds(20);

/// One kilohertz.
const size_t HERTZ_PER_KILOHERTZ = 1000;

/// The timeout to use for read calls to the SharedDataStream.
const std::chrono::milliseconds TIMEOUT_FOR_READ_CALLS = std::chrono::milliseconds(1000);

/// Kitt.ai returns -2 if silence is detected.
static const int KITT_AI_SILENCE_DETECTION_RESULT = -2;

/// Kitt.ai returns -1 if an error occurred.
static const int KITT_AI_ERROR_DETECTION_RESULT = -1;

/// Kitt.ai returns 0 if no keyword was detected but audio has been heard.
static const int KITT_AI_NO_DETECTION_RESULT = 0;

/// Metadata parameters that will be passed into our logging system.
static const std::string MODULE_TAG("SnowboyKWD");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, MODULE_TAG, __func__, message)

/**
 * Utility function to cast an int to a size_t.
 * @param value The value to cast.
 * @return The casted value.
 */
static std::size_t asSizeT(const int value) {
    return static_cast<size_t>(value);
}

/**
 * A utility function to read data into a buffer.
 *
 * @param reader The reader which will provide audio data.
 * @param buf The buffer into which we shall copy the data.
 * @param nWords The number of words to read.
 * @param timeout The timeout we are willing to wait to read the data.
 * @param errorOccurred [out] Whether an error as occurred.
 * @return The number of words read.
 */
static ssize_t readFromStream(
    std::shared_ptr<MAX::audio::AudioReaderInterface> reader,
    void* buf,
    size_t nWords,
    std::chrono::milliseconds timeout,
    bool* errorOccurred) {
    if (errorOccurred) {
        *errorOccurred = false;
    }
    ssize_t bytesRead = reader->read(buf, nWords * sizeof(int16_t));
    // Stream has been closed
    if (bytesRead == 0) {
        if (errorOccurred) {
            *errorOccurred = true;
        }
        // This represents some sort of error with the read() call
    } else if (bytesRead < 0) {
        switch (bytesRead) {
            case avs::AudioInputStream::Reader::Error::OVERRUN:
                break;
            case avs::AudioInputStream::Reader::Error::TIMEDOUT:
                break;
            default:
                if (errorOccurred) {
                    *errorOccurred = true;
                }
                break;
        }
    }
    ssize_t wordsRead = bytesRead / sizeof(int16_t);
    return wordsRead;
}

std::shared_ptr<SnowboyKWD> SnowboyKWD::create(
    const WakewordEnginesConfig::EngineConfig& config,
    std::shared_ptr<audioManager::wakeword::crosswake::SimpleCrosswakeDetector> crosswakeDetector,
    std::shared_ptr<MAX::application::WakeWordObserverInterface> wakewordObserver,
    std::shared_ptr<MAX::audio::AudioReaderInterface> audioReader) {
    auto format = audioReader->getAudioFormat();
    auto maxSamplesPerPush = format.sampleRateHz / HERTZ_PER_KILOHERTZ * TIME_PER_PUSH.count();
    auto resources = config.resourceFolder + RESOURCE_PATH;
    auto model = config.resourceFolder + MODEL_PATH;

    std::shared_ptr<SnowboyKWD> kwd(new SnowboyKWD(
        config,
        crosswakeDetector,
        wakewordObserver,
        audioReader,
        maxSamplesPerPush,
        resources.c_str(),
        model.c_str(),
        SENSITIVITY,
        AUDIO_GAIN,
        APPLY_FRONT_END_PROCESSING));

    if (!kwd->isCompatible(format)) {
        LX(ERROR, "Incompatible format, cannot create engine.");
        return nullptr;
    }

    return kwd;
}

SnowboyKWD::SnowboyKWD(
    const WakewordEnginesConfig::EngineConfig& config,
    std::shared_ptr<audioManager::wakeword::crosswake::SimpleCrosswakeDetector> crosswakeDetector,
    std::shared_ptr<MAX::application::WakeWordObserverInterface> wakewordObserver,
    std::shared_ptr<MAX::audio::AudioReaderInterface> audioReader,
    const std::size_t maxSamplesPerPush,
    const char* resources,
    const char* model,
    const char* sensitivity,
    const float audioGain,
    const bool applyFrontEndProcessing) :
        WakewordEngine(crosswakeDetector, wakewordObserver),
        m_config{config},
        m_wakewordObserver{wakewordObserver},
        m_audioReader{audioReader},
        m_maxSamplesPerPush{maxSamplesPerPush},
        m_detector{resources, model} {
    m_detector.SetSensitivity(sensitivity);
    m_detector.SetAudioGain(audioGain);
    m_detector.ApplyFrontend(applyFrontEndProcessing);
}

void SnowboyKWD::detectionLoop() {
    int16_t audioDataToPush[m_maxSamplesPerPush];
    ssize_t wordsRead = 0;
    LX(DEBUG3, "detection loop starting");

    while (!m_isShuttingDown) {
        bool didErrorOccur = false;
        wordsRead =
            readFromStream(m_audioReader, audioDataToPush, m_maxSamplesPerPush, TIMEOUT_FOR_READ_CALLS, &didErrorOccur);
        if (didErrorOccur) {
            break;
        } else if (wordsRead > 0) {
            // Words were successfully read.
            int detectionResult = m_detector.RunDetection(audioDataToPush, wordsRead);
            if (detectionResult > 0) {
                // We just got our wakeword.
                LX(DEBUG3, "detection!");
                auto wakeword = m_config.wakewords.front();
                if (m_crosswakeDetector->canWake(wakeword)) {
                    m_wakewordObserver->onWakeWordDetected(wakeword);
                } else {
                    LX(DEBUG3, "Keyword: " + wakeword + " would have caused a crosswake, ignoring.");
                }
            } else {
                switch (detectionResult) {
                    case KITT_AI_ERROR_DETECTION_RESULT:
                        didErrorOccur = true;
                        break;
                    case KITT_AI_SILENCE_DETECTION_RESULT:
                        break;
                    case KITT_AI_NO_DETECTION_RESULT:
                        break;
                    default:
                        didErrorOccur = true;
                        break;
                }
                if (didErrorOccur) {
                    break;
                }
            }
        }
    }

    LX(DEBUG3, "detection loop finishing");
    m_audioReader->close();
}

void SnowboyKWD::startWatching() {
    LX(DEBUG3, "");
    stopWatching();
    m_isShuttingDown = false;
    m_bgListener = std::thread(&SnowboyKWD::detectionLoop, this);
}

void SnowboyKWD::stopWatching() {
    LX(DEBUG3, "");
    m_isShuttingDown = true;
    if (m_bgListener.joinable()) {
        m_bgListener.join();
    }
}

bool SnowboyKWD::isCompatible(MAX::audio::AudioFormat audioFormat) {
    return !(
        asSizeT(m_detector.SampleRate()) != audioFormat.sampleRateHz ||
        asSizeT(m_detector.NumChannels()) != audioFormat.numChannels ||
        asSizeT(m_detector.BitsPerSample()) != audioFormat.wordsPerSample * audioFormat.wordSizeBits);
}

std::string SnowboyKWD::getName() {
    return m_config.name;
}

WakewordEngine::CreateMethod SnowboyKWD::getCreateMethod() {
    return WakewordEngine::CreateMethod::CUSTOM;
}

std::set<std::string> SnowboyKWD::getWakewords() {
    return std::set<std::string>(m_config.wakewords.begin(), m_config.wakewords.end());
}

std::pair<bool, std::size_t> SnowboyKWD::onData(const void* buffer, std::size_t numWords) {
    return std::pair<bool, std::size_t>();
}

}  // namespace kittai
}  // namespace wakeword
}  // namespace audioManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
