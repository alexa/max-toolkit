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

#include "Computer/Audio/SoundPlayerActivityHandler.h"

#include <AVSCommon/Utils/MediaType.h>
#include <AVSCommon/Utils/MediaPlayer/SourceConfig.h>

#include <MultiAgentExperience/Control/Control.h>

#include "Utils/Logger.h"

namespace multiAgentExperience {
namespace samples {
namespace agents {
namespace computer {
namespace audio {

static const std::string MODULE_TAG("SoundPlayerActivityHandler");
#define LX(logCommand, message) COMPUTER_AGENT_LOG_##logCommand("", MODULE_TAG, __func__, message)

using namespace multiAgentExperience::activity;

static const experience::ExperienceId PLAYING_COMPUTER_SOUNDS_EXPERIENCE{"playing_computer_sounds"};

static std::set<std::shared_ptr<multiAgentExperience::control::Control>> createStopControl(
    std::function<void()> stopControlCallback) {
    std::set<std::shared_ptr<multiAgentExperience::control::Control>> controls;
    auto stop = std::make_shared<multiAgentExperience::control::Control>(
        multiAgentExperience::control::ControlType::STOP, stopControlCallback);
    controls.insert(stop);
    return controls;
}

SoundPlayerActivityHandler::SoundPlayerActivityHandler(
    std::shared_ptr<alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerInterface> mediaPlayer,
    std::shared_ptr<std::istream> audioStream) :
        m_mediaPlayer{mediaPlayer},
        m_currentSourceId{0},
        m_isPlaying{false} {
    m_currentSourceId = m_mediaPlayer->setSource(
        audioStream,
        false,
        alexaClientSDK::avsCommon::utils::mediaPlayer::emptySourceConfig(),
        alexaClientSDK::avsCommon::utils::MediaType::MPEG);
}

void SoundPlayerActivityHandler::onDenied() {
    m_mediaPlayer.reset();
}

void SoundPlayerActivityHandler::onReady(
    std::shared_ptr<multiAgentExperience::activity::ActivityControllerInterface> activityController,
    ActivityFocus focus,
    std::shared_ptr<multiAgentExperience::control::ControlRegistryInterface> controlRegistry,
    std::shared_ptr<multiAgentExperience::experience::ExperienceControllerInterface> experienceControl) {
    m_activityController = activityController;
    m_controlRegistry = controlRegistry;
    m_experienceController = experienceControl;
    onFocusStateChange(focus);
}

void SoundPlayerActivityHandler::onFocusStateChange(ActivityFocus focus) {
    LX(DEBUG3, "");

    switch (focus) {
        case ActivityFocus::FOREGROUND: {
            m_mediaPlayer->addObserver(shared_from_this());
            if (!m_isPlaying) {
                m_mediaPlayer->play(m_currentSourceId);
            } else {
                m_mediaPlayer->resume(m_currentSourceId);
            }

            auto controls = createStopControl(createStopTask());
            m_controlRegistry->update(controls);
            m_experienceController->startExperience(PLAYING_COMPUTER_SOUNDS_EXPERIENCE);
            m_isPlaying = true;
            break;
        }
        case ActivityFocus::BACKGROUND: {
            m_mediaPlayer->pause(m_currentSourceId);
            m_experienceController->endExperience();
            break;
        }
        default: {
            onStop();
            break;
        }
    }
}

void SoundPlayerActivityHandler::onStop() {
    LX(DEBUG3, "");
    stop(m_currentSourceId);
}

void SoundPlayerActivityHandler::onFirstByteRead(
    alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerObserverInterface::SourceId id,
    const alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerState& state) {
    LX(DEBUG3, "");
}

void SoundPlayerActivityHandler::onPlaybackStarted(
    alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerObserverInterface::SourceId id,
    const alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerState& state) {
    LX(DEBUG3, "");
}

void SoundPlayerActivityHandler::onPlaybackFinished(
    alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerObserverInterface::SourceId id,
    const alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerState& state) {
    LX(DEBUG3, "");

    if (m_activityController) {
        m_activityController->stop();
    }
}

void SoundPlayerActivityHandler::onPlaybackError(
    alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerObserverInterface::SourceId id,
    const alexaClientSDK::avsCommon::utils::mediaPlayer::ErrorType& type,
    std::string error,
    const alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerState& state) {
    LX(DEBUG3, "");

    if (m_activityController) {
        m_activityController->stop();
    }
}

void SoundPlayerActivityHandler::stop(
    alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerObserverInterface::SourceId sourceId) {
    LX(DEBUG3, "");

    m_isPlaying = false;
    m_mediaPlayer->stop(sourceId);
    m_mediaPlayer->removeObserver(shared_from_this());
}

std::function<void()> SoundPlayerActivityHandler::createStopTask() {
    std::weak_ptr<ActivityControllerInterface> weakController = m_activityController;
    return [weakController]() {
        if (auto controller = weakController.lock()) {
            controller->stop();
        }
    };
}

}  // namespace audio
}  // namespace computer
}  // namespace agents
}  // namespace samples
}  // namespace multiAgentExperience
