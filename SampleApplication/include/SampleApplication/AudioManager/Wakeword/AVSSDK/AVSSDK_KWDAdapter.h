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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_WAKEWORD_AVSSDK_KWDADAPTER_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_WAKEWORD_AVSSDK_KWDADAPTER_H_

#include "SampleApplication/AudioManager/Wakeword/WakewordEngine.h"

#include <KWD/AbstractKeywordDetector.h>
#include <AVSCommon/SDKInterfaces/KeyWordObserverInterface.h>

#include <MultiAgentExperience/Audio/AudioFormat.h>

#include "SampleApplication/AudioManager/Wakeword/WakewordEnginesConfig.h"
#include "SampleApplication/AudioManager/Wakeword/WakewordMetadataCache.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace audioManager {
namespace wakeword {
namespace avssdk {

namespace MAX = multiAgentExperience;

/**
 *
 */
class AVSSDK_KWDAdapter : public WakewordEngine {
public:
    static std::unique_ptr<AVSSDK_KWDAdapter> create(
        const WakewordEnginesConfig::EngineConfig& config,
        const audio::AudioFormat& format,
        std::shared_ptr<audioManager::wakeword::crosswake::SimpleCrosswakeDetector> crosswakeDetector,
        std::shared_ptr<MAX::application::WakeWordObserverInterface> wakewordObserver,
        std::shared_ptr<audioManager::wakeword::WakewordMetadataCache> metadataCache,
        std::shared_ptr<alexaClientSDK::avsCommon::avs::AudioInputStream> sharedDataStream);

    /// @name WakewordEngineInterface methods.
    /// @{
    std::string getName() override;
    WakewordEngine::CreateMethod getCreateMethod() override;
    std::set<std::string> getWakewords() override;
    void setGestureHandler(std::shared_ptr<agentManager::GestureHandlerInterface> gestureHandler) override;
    /// @}

    /// @name DataObserverInterface methods.
    /// @{
    std::pair<bool, std::size_t> onData(const void* buffer, std::size_t numWords) override;
    /// @}

private:
    AVSSDK_KWDAdapter(
        std::unique_ptr<alexaClientSDK::kwd::AbstractKeywordDetector> detector,
        std::shared_ptr<audioManager::wakeword::crosswake::SimpleCrosswakeDetector> crosswakeDetector,
        std::shared_ptr<MAX::application::WakeWordObserverInterface> wakewordObserver,
        std::shared_ptr<audioManager::wakeword::WakewordMetadataCache> metadataCache);

    WakewordEnginesConfig::EngineConfig m_config;

    std::shared_ptr<audioManager::wakeword::WakewordMetadataCache> m_metadataCache;

    std::unique_ptr<alexaClientSDK::kwd::AbstractKeywordDetector> m_detector;
};

}  // namespace avssdk
}  // namespace wakeword
}  // namespace audioManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_WAKEWORD_AVSSDK_KWDADAPTER_H_
