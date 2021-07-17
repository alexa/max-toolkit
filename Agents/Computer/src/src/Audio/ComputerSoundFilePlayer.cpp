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

#include "Computer/Audio/ComputerSoundFilePlayer.h"

#include <MultiAgentExperience/Activity/ActivityRequestInterface.h>
#include <MultiAgentExperience/Activity/ActivityManagerInterface.h>

#include <AVSCommon/Utils/MediaPlayer/MediaPlayerInterface.h>

#include "Computer/Audio/AudioFileName.h"
#include "Computer/Audio/AudioFileNameParsingUtil.h"
#include "Computer/Audio/AudioStore.h"
#include "Computer/Audio/SoundPlayerActivityHandler.h"

namespace multiAgentExperience {
namespace samples {
namespace agents {
namespace computer {
namespace audio {

ComputerSoundFilePlayer::ComputerSoundFilePlayer(
    std::shared_ptr<alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerInterface> mediaPlayer,
    std::shared_ptr<multiAgentExperience::activity::ActivityManagerInterface> activityManager) :
        m_activityManager{activityManager},
        m_mediaPlayer{mediaPlayer} {
}

void ComputerSoundFilePlayer::play(const std::string& audioFileKey) {
    stop();

    AudioFileName audioFile = computer::audio::getAudioFileForString(audioFileKey);

    auto activityHandler =
        std::make_shared<SoundPlayerActivityHandler>(m_mediaPlayer, AudioStore::getStreamForLocalAudioFile(audioFile));

    auto activityRequest = std::make_shared<multiAgentExperience::activity::ActivityRequestInterface>(
        multiAgentExperience::activity::ActivityType::CONTENT, activityHandler);
    m_currentActivityRequest = activityRequest;
    m_activityManager->request(activityRequest);
}

void ComputerSoundFilePlayer::stop() {
    if (auto activityRequest = m_currentActivityRequest.lock()) {
        m_activityManager->stop(activityRequest);
    }
}

}  // namespace audio
}  // namespace computer
}  // namespace agents
}  // namespace samples
}  // namespace multiAgentExperience
