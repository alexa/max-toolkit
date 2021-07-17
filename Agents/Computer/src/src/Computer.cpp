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

#include <MultiAgentExperience/Samples/Agents/Computer/Computer.h>
#include <MultiAgentExperience/Actor/ActorId.h>

#include <iostream>
#include <memory>

#include "Computer/Dialog/UserDialogRequest.h"
#include "Computer/Lex/LexClient.h"
#include "Computer/Response/ResponseHandler.h"
#include "Computer/Response/SpeechResponder.h"
#include "Utils/Logger.h"

using namespace alexaClientSDK::avsCommon::utils::mediaPlayer;
using namespace multiAgentExperience::agent;
using namespace multiAgentExperience::dialog;
using namespace multiAgentExperience::samples::agents::computer::response;

namespace maxaudio = multiAgentExperience::audio;

namespace multiAgentExperience {
namespace samples {
namespace agents {
namespace computer {

static const std::string MODULE_TAG("Computer");
#define LX(logCommand, message) COMPUTER_AGENT_LOG_##logCommand("", MODULE_TAG, __func__, message)

static std::shared_ptr<lex::LexClient> getLexClientInstance(
    std::shared_ptr<ResponseHandler> responseHandler,
    std::shared_ptr<maxaudio::AudioReaderInterface> audioReader) {
    LX(DEBUG3, "");
    static std::shared_ptr<lex::LexClient> lexClient;
    if (!lexClient) {
        LX(DEBUG3, "creating.");
        lexClient = std::make_shared<lex::LexClient>(responseHandler, audioReader);
    }

    LX(DEBUG3, "created.");
    return lexClient;
}

std::unique_ptr<Computer> Computer::create(
    const std::string& name,
    const std::string& wakeword,
    std::shared_ptr<multiAgentExperience::audio::AudioReaderInterface> audioReader,
    std::shared_ptr<alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerInterface> mediaPlayer,
    std::shared_ptr<speechStore::ActiveAgentSpeechStoreInterface> activeSpeechStore,
    std::shared_ptr<multiAgentExperience::utils::Log> logger,
    const std::string& logComponentName) {
    if (name.empty()) {
        LX(ERROR, "name not provided.");
        return nullptr;
    }
    if (!audioReader) {
        LX(ERROR, "audioReader is nullptr.");
        return nullptr;
    }
    if (!mediaPlayer) {
        LX(ERROR, "mediaPlayer is nullptr.");
        return nullptr;
    }
    if (!logger) {
        LX(ERROR, "logger is nullptr.");
        return nullptr;
    }
    if (logComponentName.empty()) {
        LX(ERROR, "logComponentName not provided.");
        return nullptr;
    }

    utils::setLoggerInstance(logger);
    utils::setLoggerComponentName(logComponentName);

    auto agent = std::unique_ptr<Computer>(new Computer(name, wakeword, audioReader, mediaPlayer, activeSpeechStore));
    return agent;
}

Computer::Computer(
    const std::string& name,
    const std::string& wakeword,
    std::shared_ptr<maxaudio::AudioReaderInterface> audioReader,
    std::shared_ptr<MediaPlayerInterface> mediaPlayer,
    std::shared_ptr<speechStore::ActiveAgentSpeechStoreInterface> activeSpeechStore) :
        Agent{multiAgentExperience::actor::ActorId(name), wakeword},
        m_audioReader{audioReader},
        m_mediaPlayer{mediaPlayer},
        m_activeSpeechStore{activeSpeechStore} {
}

void Computer::onInitialized() {
    LX(DEBUG3, "");
    auto speechResponder =
        std::make_shared<SpeechResponder>(m_activeSpeechStore, m_agentTransferManager, m_mediaPlayer);
    auto soundPlayer = std::make_shared<audio::ComputerSoundFilePlayer>(m_mediaPlayer, m_activityManager);
    auto responseHandler = std::make_shared<ResponseHandler>(speechResponder, soundPlayer);
    auto lexCient = getLexClientInstance(responseHandler, m_audioReader);
    m_dialogManager->setListeningHandler(lexCient);
    m_dialogManager->setThinkingHandler(lexCient);
    m_dialogManager->setSpeakingHandler(speechResponder);
}

void Computer::handleOnWakeWordDetected() {
    LX(DEBUG3, "");
    auto userDialogRequest = std::make_shared<computer::dialog::UserDialogRequest>();
    m_dialogManager->request(userDialogRequest);
}

void Computer::handleOnTapDetected() {
    LX(DEBUG3, "");
    auto userDialogRequest = std::make_shared<computer::dialog::UserDialogRequest>();
    m_dialogManager->request(userDialogRequest);
}

void Computer::handleOnAgentTransfer() {
    LX(WARN, "AgentTransfer detected but Computer does not yet implement transfer!");
}

}  // namespace computer
}  // namespace agents
}  // namespace samples
}  // namespace multiAgentExperience
