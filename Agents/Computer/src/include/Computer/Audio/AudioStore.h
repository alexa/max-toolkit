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

#ifndef MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_AUDIO_AUDIOSTORE_H_
#define MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_AUDIO_AUDIOSTORE_H_

#include <iostream>
#include <memory>

#include <AVSCommon/Utils/Stream/StreamFunctions.h>

#include "AudioFileName.h"
#include "default_error_message.mp3.h"
#include "computer_sounds_response.mp3.h"

namespace multiAgentExperience {
namespace samples {
namespace agents {
namespace computer {
namespace audio {

class AudioStore {
public:
    static std::unique_ptr<std::istream> getStreamForLocalAudioFile(AudioFileName audioFile) {
        if (AudioFileName::COMPUTER_SOUNDS == audioFile) {
            return alexaClientSDK::avsCommon::utils::stream::streamFromData(
                computer_sounds_response_mp3, sizeof(computer_sounds_response_mp3));
        } else if (audioFile == AudioFileName::DEFAULT_ERROR_MESSAGE) {
            return alexaClientSDK::avsCommon::utils::stream::streamFromData(
                default_error_message_mp3, sizeof(default_error_message_mp3));
        } else {
            return nullptr;
        }
    }
};

}  // namespace audio
}  // namespace computer
}  // namespace agents
}  // namespace samples
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_AUDIO_AUDIOSTORE_H_
