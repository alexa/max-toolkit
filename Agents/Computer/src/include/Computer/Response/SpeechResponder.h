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

#ifndef MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_RESPONSE_SPEECHRESPONDER_H_
#define MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_RESPONSE_SPEECHRESPONDER_H_

#include <istream>
#include <memory>

#include <AVSCommon/Utils/MediaPlayer/MediaPlayerObserverInterface.h>
#include <AVSCommon/Utils/Threading/Executor.h>

#include <MultiAgentExperience/Agent/AgentTransferManagerInterface.h>
#include <MultiAgentExperience/Dialog/SpeakingHandlerInterface.h>

#include "MultiAgentExperience/Samples/Agents/Computer/ActiveAgentSpeechStore/ActiveAgentSpeechStoreInterface.h"

namespace multiAgentExperience {
namespace samples {
namespace agents {
namespace computer {
namespace response {

namespace avssdkUtils = alexaClientSDK::avsCommon::utils;
namespace MAX = multiAgentExperience;

class SpeechResponder
        : public MAX::dialog::SpeakingHandlerInterface
        , public avssdkUtils::mediaPlayer::MediaPlayerObserverInterface
        , public std::enable_shared_from_this<SpeechResponder> {
public:
    SpeechResponder(
        std::shared_ptr<speechStore::ActiveAgentSpeechStoreInterface> activeSpeechStore,
        std::shared_ptr<MAX::agent::AgentTransferManagerInterface> agentTransferManager,
        std::shared_ptr<avssdkUtils::mediaPlayer::MediaPlayerInterface> mediaPlayer);

    void speak(
        std::shared_ptr<MAX::dialog::DialogControllerInterface> controller,
        const std::string& responseCaption,
        std::shared_ptr<std::istream> speechAudioInputStream);

    void speakAndTransfer(
        std::shared_ptr<MAX::dialog::DialogControllerInterface> controller,
        const std::string& responseCaption,
        std::shared_ptr<std::istream> speechAudioInputStream,
        const MAX::actor::ActorId& agentToTransferTo);

    /// @name SpeakingHandlerInterface method overrides.
    /// @{
    void onStartSpeaking(
        std::shared_ptr<MAX::dialog::DialogControllerInterface> controller,
        std::shared_ptr<MAX::experience::ExperienceControllerInterface> experienceController,
        std::shared_ptr<MAX::control::ControlRegistryInterface> controlRegistry) override;
    void onStopSpeaking() override;
    /// @}

    /// @name MediaPlayerObserverInterface method overrides.
    /// @{
    void onFirstByteRead(SourceId id, const avssdkUtils::mediaPlayer::MediaPlayerState& state) override;
    void onPlaybackStarted(SourceId id, const avssdkUtils::mediaPlayer::MediaPlayerState& state) override;
    void onPlaybackFinished(SourceId id, const avssdkUtils::mediaPlayer::MediaPlayerState& state) override;
    void onPlaybackError(
        SourceId id,
        const avssdkUtils::mediaPlayer::ErrorType& type,
        std::string error,
        const avssdkUtils::mediaPlayer::MediaPlayerState& state) override;
    /// @}

private:
    bool m_isPlaying;
    SourceId m_currentSourceID;
    bool m_shouldTransfer;
    MAX::actor::ActorId m_agentToTransferTo;
    std::shared_ptr<speechStore::ActiveAgentSpeechStoreInterface> m_activeSpeechStore;
    std::shared_ptr<MAX::agent::AgentTransferManagerInterface> m_agentTransferManager;
    std::shared_ptr<MAX::dialog::DialogControllerInterface> m_respondingController;

    std::shared_ptr<avssdkUtils::mediaPlayer::MediaPlayerInterface> m_mediaPlayer;
    avssdkUtils::threading::Executor m_executor;
};

}  // namespace response
}  // namespace computer
}  // namespace agents
}  // namespace samples
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_RESPONSE_SPEECHRESPONDER_H_
