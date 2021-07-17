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

#include "Computer/Response/SpeechResponder.h"

#include <MultiAgentExperience/Dialog/DialogControllerInterface.h>
#include <MultiAgentExperience/Experience/ExperienceControllerInterface.h>

#include "Utils/Logger.h"

namespace multiAgentExperience {
namespace samples {
namespace agents {
namespace computer {
namespace response {

static const std::string MODULE_TAG("SpeechResponder");
#define LX(logCommand, message) COMPUTER_AGENT_LOG_##logCommand("", MODULE_TAG, __func__, message)

using namespace multiAgentExperience::control;
using namespace multiAgentExperience::dialog;
using namespace multiAgentExperience::experience;
using namespace multiAgentExperience::actor;
using namespace alexaClientSDK::avsCommon::utils::mediaPlayer;

SpeechResponder::SpeechResponder(
    std::shared_ptr<speechStore::ActiveAgentSpeechStoreInterface> activeSpeechStore,
    std::shared_ptr<multiAgentExperience::agent::AgentTransferManagerInterface> agentTransferManager,
    std::shared_ptr<MediaPlayerInterface> mediaPlayer) :
        m_activeSpeechStore{activeSpeechStore},
        m_agentTransferManager{agentTransferManager},
        m_mediaPlayer{mediaPlayer},
        m_isPlaying{false},
        m_currentSourceID{0},
        m_shouldTransfer{false} {
}

void SpeechResponder::speak(
    std::shared_ptr<DialogControllerInterface> controller,
    const std::string& responseCaption,
    std::shared_ptr<std::istream> speechAudioInputStream) {
    LX(DEBUG3, "");
    m_activeSpeechStore->setActiveSpeech(responseCaption);

    m_executor.submit([this, controller, responseCaption, speechAudioInputStream]() {
        m_mediaPlayer->addObserver(shared_from_this());
        m_currentSourceID = m_mediaPlayer->setSource(speechAudioInputStream);
        controller->startSpeaking();
    });
}

void SpeechResponder::speakAndTransfer(
    std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> controller,
    const std::string& responseCaption,
    std::shared_ptr<std::istream> speechAudioInputStream,
    const ActorId& agentToTransferTo) {
    LX(DEBUG3, "");

    m_activeSpeechStore->setActiveSpeech(responseCaption);
    m_executor.submit([this, controller, responseCaption, speechAudioInputStream, agentToTransferTo]() {
        m_mediaPlayer->addObserver(shared_from_this());
        m_currentSourceID = m_mediaPlayer->setSource(speechAudioInputStream);
        controller->startSpeaking();
        m_shouldTransfer = true;
        m_agentToTransferTo = agentToTransferTo;
    });
}

void SpeechResponder::onStartSpeaking(
    std::shared_ptr<DialogControllerInterface> controller,
    std::shared_ptr<ExperienceControllerInterface> experienceController,
    std::shared_ptr<ControlRegistryInterface> controlRegistry) {
    LX(DEBUG3, "");

    m_executor.submit([this, controller, experienceController]() {
        m_respondingController = controller;
        experienceController->startExperience(commonIds::SPEAKING);
        m_mediaPlayer->play(m_currentSourceID);
    });
}

void SpeechResponder::onStopSpeaking() {
    LX(DEBUG3, "");
    m_activeSpeechStore->clear();
    m_executor.submit([this]() {
        m_mediaPlayer->removeObserver(shared_from_this());
        if (m_isPlaying) {
            m_mediaPlayer->stop(m_currentSourceID);
            m_isPlaying = false;
        }
        m_currentSourceID = MediaPlayerInterface::ERROR;
        m_shouldTransfer = false;
    });
}

void SpeechResponder::onFirstByteRead(SourceId id, const MediaPlayerState& state) {
    LX(DEBUG3, "");
}
void SpeechResponder::onPlaybackStarted(SourceId id, const MediaPlayerState& state) {
    LX(DEBUG3, "");

    if (id == m_currentSourceID) {
        m_isPlaying = true;
    }
}
void SpeechResponder::onPlaybackFinished(SourceId id, const MediaPlayerState& state) {
    LX(DEBUG3, "");

    if (id == m_currentSourceID) {
        m_activeSpeechStore->clear();
        m_isPlaying = false;
        if (m_respondingController) {
            m_respondingController->stop();
            if (m_shouldTransfer) {
                m_agentTransferManager->invokeAgent(m_agentToTransferTo);
                m_shouldTransfer = false;
            }
        }
    }
}
void SpeechResponder::onPlaybackError(
    SourceId id,
    const ErrorType& type,
    std::string error,
    const MediaPlayerState& state) {
    LX(DEBUG3, "");

    if (id == m_currentSourceID) {
        m_activeSpeechStore->clear();
        m_isPlaying = false;
        if (m_respondingController) {
            m_respondingController->stop();
        }

        m_shouldTransfer = false;
    }
}

}  // namespace response
}  // namespace computer
}  // namespace agents
}  // namespace samples
}  // namespace multiAgentExperience
