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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AGENTMANAGER_ALEXA_DEFAULTCLIENTFACTORY_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AGENTMANAGER_ALEXA_DEFAULTCLIENTFACTORY_H_

#include <memory>
#include <string>
#include <unordered_map>

#include <acsdkExternalMediaPlayer/ExternalMediaPlayer.h>
#include <AVSCommon/SDKInterfaces/ChannelVolumeInterface.h>
#include <AVSCommon/SDKInterfaces/ActiveAgentSpeechStoreInterface.h>
#include <DefaultClient/DefaultClient.h>

#ifdef GSTREAMER_MEDIA_PLAYER
#include <MediaPlayer/MediaPlayer.h>
#endif

#include "SampleApplication/AgentManager/AgentsConfig.h"
#include "SampleApplication/AudioManager/Wakeword/WakewordMetadataCache.h"
#include "SampleApplication/Utils/AudioDataDirectAccessInterface.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace agentManager {
namespace alexa {

/**
 * This class encapsulates the AVS SDK DefaultClient. This is the key component which defines the Alexa client. This
 * class decouples the Alexa client from microphone and wakeword concerns, requiring only handles to the underlying
 * SDS from which audio data may be read.
 */
class DefaultClientFactory {
public:
    /**
     * Creates an instance of the AVS SDK DefaultClient.
     *
     * @param configFilePath Path to the config file to use for the AVS SDK.
     * @param audioDataAccessProvider he provider of the underlying audio data buffers.
     * @param metadataCache kwd metadata cache that shall be used upon wakeword detection.
     * @return An instance of the AVS SDK DefaultClient if successful, otherwise nullptr.
     */
    static std::shared_ptr<alexaClientSDK::defaultClient::DefaultClient> create(
        const AgentsConfig::AgentConfig& config,
        std::shared_ptr<utils::AudioDataDirectAccessInterface> audioDataAccessProvider,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ActiveAgentSpeechStoreInterface> agentSpeechStore,
        std::shared_ptr<audioManager::wakeword::WakewordMetadataCache> metadataCache);

private:
    /**
     * Helper method which performs actual instantiation.
     *
     * @param configFilePath Path to the config file to use for the AVS SDK.
     * @param audioDataAccessProvider he provider of the underlying audio data buffers.
     * @param metadataCache kwd metadata cache that shall be used upon wakeword detection.
     * @return An instance of the AVS SDK DefaultClient if successful, otherwise nullptr.
     */
    std::shared_ptr<alexaClientSDK::defaultClient::DefaultClient> instantiateDefaultClient(
        const AgentsConfig::AgentConfig& config,
        std::shared_ptr<utils::AudioDataDirectAccessInterface> audioDataAccessProvider,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ActiveAgentSpeechStoreInterface> agentSpeechStore,
        std::shared_ptr<audioManager::wakeword::WakewordMetadataCache> metadataCache);

    /**
     * Create an application media player.
     *
     * @param contentFetcherFactory Used to create objects that can fetch remote HTTP content.
     * @param enableEqualizer Flag indicating if equalizer should be enabled for this media player.
     * @param name The media player instance name used for logging purpose.
     * @param enableLiveMode Flag, indicating if the player is in live mode.
     * @return Application Media interface if it succeeds; otherwise, return @c nullptr.
     */
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ApplicationMediaInterfaces> createApplicationMediaPlayer(
        std::shared_ptr<alexaClientSDK::avsCommon::utils::libcurlUtils::HTTPContentFetcherFactory>
            httpContentFetcherFactory,
        bool enableEqualizer,
        const std::string& name,
        bool enableLiveMode = false);

    /**
     * Method to create mediaPlayers for the optional music provider adapters plugged into the SDK.
     *
     * @param httpContentFetcherFactory The HTTPContentFetcherFactory to be used while creating the mediaPlayers.
     * @param equalizerRuntimeSetup Equalizer runtime setup to register equalizers
     * @return @c true if the mediaPlayer of all the registered adapters could be created @c false otherwise.
     */
    bool createMediaPlayersForAdapters(
        std::shared_ptr<alexaClientSDK::avsCommon::utils::libcurlUtils::HTTPContentFetcherFactory>
            httpContentFetcherFactory,
        std::shared_ptr<alexaClientSDK::defaultClient::EqualizerRuntimeSetup> equalizerRuntimeSetup);

    /**
     * Instances of this class register ExternalMediaAdapters. Each adapter registers itself by instantiating
     * a static instance of the below class supplying their business name and creator method.
     */
    class AdapterRegistration {
    public:
        /**
         * Constructor.
         *
         * @param playerId The player id.
         * @param createFunction The create function.
         */
        AdapterRegistration(
            const std::string& playerId,
            alexaClientSDK::acsdkExternalMediaPlayer::ExternalMediaPlayer::AdapterCreateFunction createFunction);
    };

    /**
     * Instances of this class register MediaPlayers to be created. Each third-party adapter registers a mediaPlayer
     * for itself by instantiating a static instance of the below class supplying their business name, speaker interface
     * type and creator method.
     */
    class MediaPlayerRegistration {
    public:
        /**
         * Constructor.
         *
         * @param playerId The player id.
         * @param speakerType The speaker type.
         */
        MediaPlayerRegistration(
            const std::string& playerId,
            alexaClientSDK::avsCommon::sdkInterfaces::ChannelVolumeInterface::Type speakerType);
    };

    /// The map of the adapters and their mediaPlayers.
    std::
        unordered_map<std::string, std::shared_ptr<alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerInterface>>
            m_externalMusicProviderMediaPlayersMap;

    /// The map of the adapters and their mediaPlayers.
    std::unordered_map<std::string, std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerInterface>>
        m_externalMusicProviderSpeakersMap;

    /// The Pool of @c MediaPlayers used by @c AudioPlayer (via @c PooledMediaPlayerFactory)
    std::vector<std::shared_ptr<alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerInterface>>
        m_audioMediaPlayerPool;

    /// The singleton map from @c playerId to @c ChannelVolumeInterface::Type.
    static std::unordered_map<std::string, alexaClientSDK::avsCommon::sdkInterfaces::ChannelVolumeInterface::Type>
        m_playerToSpeakerTypeMap;

    /// The singleton map from @c playerId to @c ExternalMediaAdapter creation functions.
    static alexaClientSDK::acsdkExternalMediaPlayer::ExternalMediaPlayer::AdapterCreationMap m_adapterToCreateFuncMap;

    /// The vector of components requiring shutdown
    std::vector<std::shared_ptr<alexaClientSDK::avsCommon::utils::RequiresShutdown>> m_shutdownRequiredList;
};

}  // namespace alexa
}  // namespace agentManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AGENTMANAGER_ALEXA_DEFAULTCLIENTFACTORY_H_
