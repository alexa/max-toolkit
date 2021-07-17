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

#ifndef MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_LEX_LEXCLIENT_H_
#define MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_LEX_LEXCLIENT_H_

#include <aws/core/Aws.h>
#include <aws/identity-management/auth/CognitoCachingCredentialsProvider.h>
#include <aws/lex/LexRuntimeServiceClient.h>

#include <AVSCommon/Utils/Threading/Executor.h>

#include <MultiAgentExperience/Audio/AudioReaderInterface.h>
#include <MultiAgentExperience/Control/Control.h>
#include <MultiAgentExperience/Dialog/DialogControllerInterface.h>
#include <MultiAgentExperience/Dialog/ListeningHandlerInterface.h>
#include <MultiAgentExperience/Dialog/ThinkingHandlerInterface.h>

#include "Computer/Response/Response.h"
#include "Computer/Response/ResponseHandler.h"
#include "Computer/VoiceActivityDetection/VoiceActivityDetection.h"

namespace multiAgentExperience {
namespace samples {
namespace agents {
namespace computer {
namespace lex {

/// shorthand namespace aliases.
namespace avssdkUtils = alexaClientSDK::avsCommon::utils;
namespace MAX = multiAgentExperience;

/**
 * A client that can record audio and make requests to the Computer Agent AWS Lex Bot.
 */
class LexClient
        : public MAX::dialog::ListeningHandlerInterface
        , public MAX::dialog::ThinkingHandlerInterface {
public:
    /**
     * Constructor.
     * @param responseHandler
     * @param audioReader
     */
    LexClient(
        std::shared_ptr<response::ResponseHandler> responseHandler,
        std::shared_ptr<MAX::audio::AudioReaderInterface> audioReader);

    /**
     * Destructor.
     */
    ~LexClient();

    /// @name ListeningHandlerInterface method overrides.
    /// @{
    void onStartListening(
        std::shared_ptr<MAX::dialog::DialogControllerInterface> controller,
        std::set<MAX::control::ControlType> controls) override;
    void onStopListening() override;
    /// @}

    /// @name ThinkingHandlerInterface method overrides.
    /// @{
    void onStartThinking(std::shared_ptr<MAX::dialog::DialogControllerInterface> controller) override;
    void onStopThinking() override;
    /// @}

private:
    Aws::Client::ClientConfiguration getAwsClientConfiguration();

    std::shared_ptr<Aws::Auth::CognitoCachingAnonymousCredentialsProvider> getCognitoCredentialsProvider();

    /**
     * Record audio for a Computer Agent utterance
     * @param audioProvider Audio Provider
     * @param activityControls Set of available activity controls
     * @param autoStopRecording Boolean indicating if the recording should be
     * automatically stopped after silence/timeout
     * @return a boolean indicating if the audio recording was successful
     */
    bool recordAudio(
        std::set<MAX::control::ControlType> activityControls = std::set<multiAgentExperience::control::ControlType>(),
        bool autoStopRecording = true);

    /**
     * Stop recording audio.
     */
    void stopRecording();

    /**
     * Process the recorded audio utterance
     * @return Response object
     */
    std::shared_ptr<computer::response::Response> processRequest();

    std::shared_ptr<Aws::LexRuntimeService::LexRuntimeServiceClient> m_lexClient;
    std::shared_ptr<Aws::Client::ClientConfiguration> m_awsClientConfiguration;
    std::shared_ptr<computer::response::ResponseHandler> m_responseHandler;
    Aws::SDKOptions m_awsSdkOptions;
    std::shared_ptr<MAX::audio::AudioReaderInterface> m_audioReader;
    computer::VoiceActivityDetector m_voiceActivityDetector;
    std::set<MAX::control::ControlType> m_activeActivityControls;
    avssdkUtils::threading::Executor m_executor;
};

}  // namespace lex
}  // namespace computer
}  // namespace agents
}  // namespace samples
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_LEX_LEXCLIENT_H_
