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

#include "SampleApplication/AgentManager/Computer/ComputerAgentFactory.h"

#include <string>

#include <AVSCommon/Utils/LibcurlUtils/HTTPContentFetcherFactory.h>
#include <MediaPlayer/MediaPlayer.h>

#include <MultiAgentExperience/Samples/Agents/Computer/Computer.h>

#include "SampleApplication/AgentManager/Computer/ComputerAudioReader.h"
#include "SampleApplication/AgentManager/Computer/ComputerActiveAgentSpeechStore.h"
#include "SampleApplication/Utils/RadiantLogger.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace agentManager {
namespace computer {

/// Metadata parameters that will be passed into our logging system.
static const std::string MODULE_TAG("ComputerAgentFactory");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, MODULE_TAG, __func__, message)

/**
 * Utility function to create an AVS SDK media player for the Computer Agent.
 *
 * @return A media player if successful, otherwise nullptr.
 */
static std::shared_ptr<alexaClientSDK::mediaPlayer::MediaPlayer> createComputerMediaPlayer() {
    auto httpContentFetcherFactory =
        std::make_shared<alexaClientSDK::avsCommon::utils::libcurlUtils::HTTPContentFetcherFactory>();
    if (!httpContentFetcherFactory) {
        LX(ERROR, "Could not create httpContentFetcherFactory.");
        return nullptr;
    }

    std::string mediaPlayerName = "ComputerAgentSpeakPlayer";
    bool enableEqualizer = false;
    bool enableLiveMode = false;

    auto mediaPlayer = alexaClientSDK::mediaPlayer::MediaPlayer::create(
        httpContentFetcherFactory, enableEqualizer, mediaPlayerName, enableLiveMode);
    if (!mediaPlayer) {
        LX(ERROR, "Could not create MediaPlayer.");
        return nullptr;
    }

    return mediaPlayer;
}

std::shared_ptr<MAX::agent::Agent> ComputerAgentFactory::create(
    const AgentsConfig::AgentConfig& config,
    const audio::AudioFormat& audioFormat,
    std::shared_ptr<utils::AudioDataDirectAccessInterface> audioDataAccessProvider,
    std::shared_ptr<audioManager::wakeword::crosswake::SimpleCrosswakeDetector> crosswakeDetector) {
    LX(DEBUG3, "");

    static std::shared_ptr<MAX::agent::Agent> agent;

    if (!agent) {
        LX(DEBUG3, "creating.");
        auto mediaPlayer = createComputerMediaPlayer();
        std::shared_ptr<MAX::audio::AudioReaderInterface> audioReader =
            ComputerAudioReader::create(audioFormat, audioDataAccessProvider->createSDSReader());

        std::string wakeword;
        if (!config.wakewords.empty()) {
            wakeword = config.wakewords.front();
        }

        auto agentSpeechStore = std::make_shared<ComputerActiveAgentSpeechStore>();
        crosswakeDetector->addAgentSpeechStore(agentSpeechStore);

        agent = MAX::samples::agents::computer::Computer::create(
            config.name,
            wakeword,
            audioReader,
            mediaPlayer,
            agentSpeechStore,
            utils::RadiantLogger::instance(),
            utils::RadiantLogger::COMPUTER_AGENT_COMPONENT_NAME);
    }

    return agent;
}
}  // namespace computer
}  // namespace agentManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
