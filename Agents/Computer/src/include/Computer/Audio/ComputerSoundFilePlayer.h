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

#ifndef MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_AUDIO_COMPUTERSOUNDFILEPLAYER_H_
#define MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_AUDIO_COMPUTERSOUNDFILEPLAYER_H_

#include <istream>
#include <memory>
#include <mutex>

#include <AVSCommon/Utils/MediaPlayer/MediaPlayerInterface.h>

#include <MultiAgentExperience/Activity/ActivityRequestInterface.h>
#include <MultiAgentExperience/Activity/ActivityManagerInterface.h>

namespace multiAgentExperience {
namespace samples {
namespace agents {
namespace computer {
namespace audio {

class ComputerSoundFilePlayer {
public:
    ComputerSoundFilePlayer(
        std::shared_ptr<alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerInterface> mediaPlayer,
        std::shared_ptr<multiAgentExperience::activity::ActivityManagerInterface> activityManager);

    void play(const std::string& audioFileKey);

    void stop();

private:
    std::shared_ptr<multiAgentExperience::activity::ActivityManagerInterface> m_activityManager;
    std::weak_ptr<multiAgentExperience::activity::ActivityRequestInterface> m_currentActivityRequest;
    std::shared_ptr<alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerInterface> m_mediaPlayer;
};

}  // namespace audio
}  // namespace computer
}  // namespace agents
}  // namespace samples
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_AUDIO_COMPUTERSOUNDFILEPLAYER_H_
