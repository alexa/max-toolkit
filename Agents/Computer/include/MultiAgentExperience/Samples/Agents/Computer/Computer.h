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

#ifndef MULTI_AGENT_EXPERIENCE_SAMPLES_AGENTS_COMPUTER_COMPUTER_H_
#define MULTI_AGENT_EXPERIENCE_SAMPLES_AGENTS_COMPUTER_COMPUTER_H_

#include <memory>
#include <set>

#include <AVSCommon/Utils/MediaPlayer/MediaPlayerObserverInterface.h>

#include <MultiAgentExperience/Agent/Agent.h>
#include <MultiAgentExperience/Audio/AudioReaderInterface.h>
#include <MultiAgentExperience/Utils/Log.h>

#include "ActiveAgentSpeechStore/ActiveAgentSpeechStoreInterface.h"

namespace multiAgentExperience {
namespace samples {
namespace agents {
namespace computer {

// shorthand namespace aliases.
namespace avssdkUtils = alexaClientSDK::avsCommon::utils;
namespace MAX = multiAgentExperience;

/**
 * This class represents an example of a MAX-conformant @c Agent. It implements an AWS Lex client to parse and respond
 * to simple user requests. It is expected that this @c Agent will be integrated with an Alexa client via the MAX
 * Library, as some responses from this @c Agent may refer to Alexa. This class is provided for demonstration purposes
 * only, and is not supported for commercial use.
 */
class Computer : public MAX::agent::Agent {
public:
    /**
     * Handles the conditional creation of @c Computer objects. Should any parameter be invalid then this function
     * shall return nullptr.
     *
     * @param name The name which should be used for logging and display of this @c Agent.
     * @param wakeword The wakeword which this @c Agent should respond to.
     * @param audioReader A reader which this @c Agent may use to read audio data containing user speech from.
     * @param mediaPlayer A mediaplayer which this @c Agent may use to render responses.
     * @param logger The logger to be used to output messages ranging from DEBUG3 to ERROR.
     * @param logComponentName The component name which shall be passed to the logger as metadata.
     * @return A new @c Computer object if the parameters are valid, otherwise nullptr.
     */
    static std::unique_ptr<Computer> create(
        const std::string& name,
        const std::string& wakeword,
        std::shared_ptr<MAX::audio::AudioReaderInterface> audioReader,
        std::shared_ptr<avssdkUtils::mediaPlayer::MediaPlayerInterface> mediaPlayer,
        std::shared_ptr<speechStore::ActiveAgentSpeechStoreInterface> activeSpeechStore,
        std::shared_ptr<MAX::utils::Log> logger,
        const std::string& logComponentName);

    /// @name Agent method overrides.
    /// @{
    void handleOnWakeWordDetected() override;
    void handleOnTapDetected() override;
    void handleOnAgentTransfer() override;
    void onInitialized() override;
    /// @}

private:
    /**
     * Constructor.
     *
     * @param name The name which should be used for logging and display of this @c Agent.
     * @param wakeword The wakeword which this @c Agent should respond to.
     * @param audioReader A reader which this @c Agent may use to read audio data containing user speech from.
     * @param mediaPlayer A mediaplayer which this @c Agent may use to render responses.
     */
    Computer(
        const std::string& name,
        const std::string& wakeword,
        std::shared_ptr<MAX::audio::AudioReaderInterface> audioReader,
        std::shared_ptr<avssdkUtils::mediaPlayer::MediaPlayerInterface> mediaPlayer,
        std::shared_ptr<speechStore::ActiveAgentSpeechStoreInterface> activeSpeechStore);

    /// The audio reader which will contain user speech data.
    std::shared_ptr<MAX::audio::AudioReaderInterface> m_audioReader;
    /// The media player to be used to render responses.
    std::shared_ptr<avssdkUtils::mediaPlayer::MediaPlayerInterface> m_mediaPlayer;
    /// The utterance store to use when computer is speaking.
    std::shared_ptr<speechStore::ActiveAgentSpeechStoreInterface> m_activeSpeechStore;
};

}  // namespace computer
}  // namespace agents
}  // namespace samples
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_SAMPLES_AGENTS_COMPUTER_COMPUTER_H_
