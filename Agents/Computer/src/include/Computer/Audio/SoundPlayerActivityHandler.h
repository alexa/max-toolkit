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

#ifndef MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_AUDIO_SOUNDPLAYERACTIVITYHANDLER_H_
#define MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_AUDIO_SOUNDPLAYERACTIVITYHANDLER_H_

#include <functional>
#include <memory>

#include <AVSCommon/Utils/MediaPlayer/MediaPlayerInterface.h>
#include <AVSCommon/Utils/MediaPlayer/MediaPlayerObserverInterface.h>

#include <MultiAgentExperience/Activity/ActivityHandlerInterface.h>
#include <MultiAgentExperience/Control/ControlRegistryInterface.h>
#include <MultiAgentExperience/Experience/ExperienceControllerInterface.h>

namespace multiAgentExperience {
namespace samples {
namespace agents {
namespace computer {
namespace audio {

/// shorthand namespace aliases.
namespace avssdkUtils = alexaClientSDK::avsCommon::utils;
namespace MAX = multiAgentExperience;

class SoundPlayerActivityHandler
        : public MAX::activity::ActivityHandlerInterface
        , public avssdkUtils::mediaPlayer::MediaPlayerObserverInterface
        , public std::enable_shared_from_this<SoundPlayerActivityHandler> {
public:
    SoundPlayerActivityHandler(
        std::shared_ptr<avssdkUtils::mediaPlayer::MediaPlayerInterface> mediaPlayer,
        std::shared_ptr<std::istream> audioStream);

    /// @name ActivityHandlerInterface method overrides.
    /// @{
    void onDenied() override;
    void onReady(
        std::shared_ptr<MAX::activity::ActivityControllerInterface> activityController,
        multiAgentExperience::activity::ActivityFocus focus,
        std::shared_ptr<MAX::control::ControlRegistryInterface> controlRegistry,
        std::shared_ptr<MAX::experience::ExperienceControllerInterface> experienceControl) override;
    void onFocusStateChange(MAX::activity::ActivityFocus focus) override;
    void onStop() override;
    /// @}

private:
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

    void stop(avssdkUtils::mediaPlayer::MediaPlayerObserverInterface::SourceId sourceId);

    std::function<void()> createStopTask();

    std::shared_ptr<avssdkUtils::mediaPlayer::MediaPlayerInterface> m_mediaPlayer;
    avssdkUtils::mediaPlayer::MediaPlayerObserverInterface::SourceId m_currentSourceId;
    bool m_isPlaying;
    std::shared_ptr<MAX::activity::ActivityControllerInterface> m_activityController;
    std::shared_ptr<MAX::control::ControlRegistryInterface> m_controlRegistry;
    std::shared_ptr<MAX::experience::ExperienceControllerInterface> m_experienceController;
};

}  // namespace audio
}  // namespace computer
}  // namespace agents
}  // namespace samples
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_AUDIO_SOUNDPLAYERACTIVITYHANDLER_H_
