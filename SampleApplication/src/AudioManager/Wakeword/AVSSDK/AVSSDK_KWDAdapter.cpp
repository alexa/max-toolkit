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

#include "SampleApplication/AudioManager/Wakeword/AVSSDK/AVSSDK_KWDAdapter.h"

#include <sstream>

#ifdef LINK_AGAINST_AVS_SDK_KWDPROVIDER
#include <KWDProvider/KeywordDetectorProvider.h>
#endif

#include "SampleApplication/Utils/RadiantLogger.h"
#include "SampleApplication/Utils/StringUtils.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace audioManager {
namespace wakeword {
namespace avssdk {

using namespace alexaClientSDK;

/// Metadata parameters that will be passed into our logging system.
static const std::string MODULE_TAG("AVSSDK_KWDAdapter");
#define LX(logCommand, message)                                               \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::AVS_SDK_COMPONENT_NAME, \
                                MODULE_TAG, __func__, message)

/**
 * Static method to determine if AVS SDK kwd metadata indicates tap to talk.
 * @param metadata The metadata to inspect.
 * @return Whether the metadata indicates tap to talk.
 */
static bool indicatesTapToTalk(
    avsCommon::sdkInterfaces::KeyWordMetadataAccessorInterface::Metadata
        metadata) {
    return (metadata.endIndex !=
            avsCommon::sdkInterfaces::KeyWordObserverInterface::
                UNSPECIFIED_INDEX) &&
           (metadata.beginIndex ==
            avsCommon::sdkInterfaces::KeyWordObserverInterface::
                UNSPECIFIED_INDEX);
}

/**
 * Static method to determine if AVS SDK kwd metadata indicates wakeword.
 * @param metadata The metadata to inspect.
 * @return Whether the metadata indicates wakeword.
 */
static bool indicatesWakeword(
    avsCommon::sdkInterfaces::KeyWordMetadataAccessorInterface::Metadata
        metadata) {
    return (metadata.endIndex !=
            avsCommon::sdkInterfaces::KeyWordObserverInterface::
                UNSPECIFIED_INDEX) &&
           (metadata.beginIndex !=
            avsCommon::sdkInterfaces::KeyWordObserverInterface::
                UNSPECIFIED_INDEX);
}

/**
 * Utility class to capture wakeword detections from an AVS SDK wakeword engine.
 */
class AVSSDK_KWDAdapterKeywordObserver
    : public avsCommon::sdkInterfaces::KeyWordObserverInterface {
   public:
    /**
     * Constructor.
     *
     * @param metadataCache The metadata cache to be used upon wakeword
     * detection.
     * @param wakewordObserver The observer to notify once wakeword has been
     * detected.
     */
    AVSSDK_KWDAdapterKeywordObserver(
        std::shared_ptr<audioManager::wakeword::WakewordMetadataCache>
            metadataCache,
        std::shared_ptr<
            audioManager::wakeword::crosswake::SimpleCrosswakeDetector>
            crosswakeDetector,
        std::shared_ptr<MAX::application::WakeWordObserverInterface>
            wakewordObserver);

    /// @name KeyWordObserverInterface Functions
    /// @{
    void onKeyWordDetected(
        std::shared_ptr<avsCommon::avs::AudioInputStream> stream,
        std::string keyword,
        avsCommon::avs::AudioInputStream::Index beginIndex = UNSPECIFIED_INDEX,
        avsCommon::avs::AudioInputStream::Index endIndex = UNSPECIFIED_INDEX,
        std::shared_ptr<const std::vector<char>> KWDMetadata =
            nullptr) override;
    /// @}

    /**
     * Sets the gesture handler to be used.
     * @param gestureHandler The gesture handler to be used.
     */
    void setGestureHandler(
        std::shared_ptr<agentManager::GestureHandlerInterface> gestureHandler);

   private:
    /// Our metadata cache.
    std::shared_ptr<audioManager::wakeword::WakewordMetadataCache>
        m_metadataCache;
    /// Our gesture handler.
    std::shared_ptr<agentManager::GestureHandlerInterface> m_gestureHandler;
    /// Our crosswake detector.
    std::shared_ptr<audioManager::wakeword::crosswake::SimpleCrosswakeDetector>
        m_crosswakeDetector;
    /// Our wakeword observer.
    std::shared_ptr<MAX::application::WakeWordObserverInterface>
        m_wakewordObserver;
};

AVSSDK_KWDAdapterKeywordObserver::AVSSDK_KWDAdapterKeywordObserver(
    std::shared_ptr<audioManager::wakeword::WakewordMetadataCache>
        metadataCache,
    std::shared_ptr<audioManager::wakeword::crosswake::SimpleCrosswakeDetector>
        crosswakeDetector,
    std::shared_ptr<MAX::application::WakeWordObserverInterface>
        wakewordObserver)
    : m_metadataCache{metadataCache},
      m_crosswakeDetector{crosswakeDetector},
      m_wakewordObserver{wakewordObserver} {}

void AVSSDK_KWDAdapterKeywordObserver::onKeyWordDetected(
    std::shared_ptr<avsCommon::avs::AudioInputStream> stream,
    std::string keyword, avsCommon::avs::AudioInputStream::Index beginIndex,
    avsCommon::avs::AudioInputStream::Index endIndex,
    std::shared_ptr<const std::vector<char>> KWDMetadata) {
    keyword = utils::stringToLowerCase(keyword);

    std::stringstream ss;
    ss << "AVSSDK_KWDAdapterKeywordObserver received KWD metadata:"
       << "keyword:" << keyword << ", beginIndex:" << beginIndex
       << ", endIndex:" << endIndex;
    if (KWDMetadata) {
        ss << ", KWDMetadata size:" << KWDMetadata->size();
    }

    LX(DEBUG3, "KEYWORD DETECTED:" + keyword + ", \n" + ss.str());

    if (!m_crosswakeDetector->canWake(keyword)) {
        LX(DEBUG3,
           "Keyword: " + keyword + " would cause a cross wake, ignoring.");
        return;
    }

    avsCommon::sdkInterfaces::KeyWordMetadataAccessorInterface::Metadata
        metadata;
    metadata.keyword = keyword;
    metadata.beginIndex = beginIndex;
    metadata.endIndex = endIndex;
    metadata.additionalFields = KWDMetadata;

    if (indicatesWakeword(metadata)) {
        m_metadataCache->setMetadata(metadata);
        m_wakewordObserver->onWakeWordDetected(keyword);
    } else if (indicatesTapToTalk(metadata)) {
        if (m_gestureHandler) {
            m_gestureHandler->invokeGesture(
                agentManager::GestureHandlerInterface::GestureType::TAP,
                keyword);
        }
    }
}

void AVSSDK_KWDAdapterKeywordObserver::setGestureHandler(
    std::shared_ptr<agentManager::GestureHandlerInterface> gestureHandler) {
    LX(DEBUG3, "");
    m_gestureHandler = gestureHandler;
}

// Our keyword observer.
// TODO: refactor this into a more intuitively managed object under VII-355.
static std::shared_ptr<AVSSDK_KWDAdapterKeywordObserver> g_kwdObserver;

std::unique_ptr<AVSSDK_KWDAdapter> AVSSDK_KWDAdapter::create(
    const WakewordEnginesConfig::EngineConfig& config,
    const audio::AudioFormat& format,
    std::shared_ptr<audioManager::wakeword::crosswake::SimpleCrosswakeDetector>
        crosswakeDetector,
    std::shared_ptr<MAX::application::WakeWordObserverInterface>
        wakewordObserver,
    std::shared_ptr<audioManager::wakeword::WakewordMetadataCache>
        metadataCache,
    std::shared_ptr<avsCommon::avs::AudioInputStream> sharedDataStream) {
#ifdef LINK_AGAINST_AVS_SDK_KWDPROVIDER
    avsCommon::utils::AudioFormat compatibleAudioFormat;
    compatibleAudioFormat.sampleRateHz = format.sampleRateHz;
    compatibleAudioFormat.sampleSizeInBits =
        format.wordsPerSample * format.wordSizeBits;
    compatibleAudioFormat.numChannels = format.numChannels;

    compatibleAudioFormat.endianness =
        (audio::AudioFormat::Endianness::LITTLE == format.endianness)
            ? avsCommon::utils::AudioFormat::Endianness::LITTLE
            : avsCommon::utils::AudioFormat::Endianness::BIG;

    compatibleAudioFormat.encoding =
        (audio::AudioFormat::Encoding::LPCM == format.encoding)
            ? avsCommon::utils::AudioFormat::Encoding::LPCM
            : avsCommon::utils::AudioFormat::Encoding::OPUS;

    g_kwdObserver = std::make_shared<AVSSDK_KWDAdapterKeywordObserver>(
        metadataCache, crosswakeDetector, wakewordObserver);

    auto detector = kwd::KeywordDetectorProvider::create(
        sharedDataStream, compatibleAudioFormat, {g_kwdObserver},
        std::unordered_set<std::shared_ptr<
            avsCommon::sdkInterfaces::KeyWordDetectorStateObserverInterface>>(),
        config.resourceFolder);
#else
    std::unique_ptr<kwd::AbstractKeywordDetector> detector = nullptr;
#endif

    if (!detector) {
        LX(ERROR, "createFailed : unable to create AVS SDK keyword detector.");
        return nullptr;
    }

    bool kwdTypeCorrect = true;
    auto detectorType = detector->getType();
    if (kwd::AbstractKeywordDetector::Type::KITT_AI == detectorType) {
        if ("kitt.ai" != config.name) {
            kwdTypeCorrect = false;
        }
    } else if (kwd::AbstractKeywordDetector::Type::SENSORY == detectorType) {
        if ("sensory" != config.name) {
            kwdTypeCorrect = false;
        }
    } else if (kwd::AbstractKeywordDetector::Type::AMAZONLITE == detectorType) {
        if ("amazonlite" != config.name) {
            kwdTypeCorrect = false;
        }
    }

    if (!kwdTypeCorrect) {
        std::stringstream ss;
        ss << "createFailed : AVS SDK KWD is not the type required. Requested:"
           << config.name << ", created:" << detectorType;
        LX(ERROR, ss.str());
        return nullptr;
    }

    auto kwdAdapter = std::unique_ptr<AVSSDK_KWDAdapter>(new AVSSDK_KWDAdapter(
        std::move(detector), crosswakeDetector, wakewordObserver,
        metadataCache /*, gestureHandler*/));

    return kwdAdapter;
}

AVSSDK_KWDAdapter::AVSSDK_KWDAdapter(
    std::unique_ptr<kwd::AbstractKeywordDetector> detector,
    std::shared_ptr<audioManager::wakeword::crosswake::SimpleCrosswakeDetector>
        crosswakeDetector,
    std::shared_ptr<MAX::application::WakeWordObserverInterface>
        wakewordObserver,
    std::shared_ptr<audioManager::wakeword::WakewordMetadataCache>
        metadataCache)
    : WakewordEngine{crosswakeDetector, wakewordObserver},
      m_metadataCache{metadataCache},
      m_detector{std::move(detector)} {}

std::pair<bool, size_t> AVSSDK_KWDAdapter::onData(const void* buffer,
                                                  size_t numWords) {
    return std::pair<bool, size_t>(true, numWords);
}

std::string AVSSDK_KWDAdapter::getName() { return m_config.name; }

WakewordEngine::CreateMethod AVSSDK_KWDAdapter::getCreateMethod() {
    return WakewordEngine::CreateMethod::AVS_SDK;
}

std::set<std::string> AVSSDK_KWDAdapter::getWakewords() {
    return std::set<std::string>(m_config.wakewords.begin(),
                                 m_config.wakewords.end());
}

void AVSSDK_KWDAdapter::setGestureHandler(
    std::shared_ptr<agentManager::GestureHandlerInterface> gestureHandler) {
    LX(DEBUG3, "");
    if (g_kwdObserver) {
        g_kwdObserver->setGestureHandler(gestureHandler);
    }
}

}  // namespace avssdk
}  // namespace wakeword
}  // namespace audioManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
