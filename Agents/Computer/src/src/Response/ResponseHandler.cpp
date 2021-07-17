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

#include "Computer/Response/ResponseHandler.h"

#include <MultiAgentExperience/Activity/ActivityManagerInterface.h>
#include <MultiAgentExperience/Dialog/DialogControllerInterface.h>
#include <MultiAgentExperience/Control/Control.h>

#include "Computer/Audio/AudioStore.h"
#include "Utils/ControlTypeUtils.h"
#include "Utils/Logger.h"

using namespace multiAgentExperience::control;
using namespace multiAgentExperience::dialog;
using namespace multiAgentExperience::experience;
using namespace multiAgentExperience::samples::agents::computer::utils;
using namespace multiAgentExperience::samples::agents::computer::audio;
using namespace multiAgentExperience::actor;

using namespace alexaClientSDK;
using namespace alexaClientSDK::avsCommon::utils;

namespace multiAgentExperience {
namespace samples {
namespace agents {
namespace computer {
namespace response {

static const std::string MODULE_TAG("ResponseHandler");
#define LX(logCommand, message) COMPUTER_AGENT_LOG_##logCommand("", MODULE_TAG, __func__, message)

ResponseHandler::ResponseHandler(
    std::shared_ptr<SpeechResponder> speechResponder,
    std::shared_ptr<audio::ComputerSoundFilePlayer> soundPlayer) :
        m_speechResponder{speechResponder},
        m_soundPlayer{soundPlayer} {
}

void ResponseHandler::handleResponse(
    std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> dialogController,
    std::shared_ptr<Response> response) {
    LX(DEBUG3, "");

    switch (response->getResponseType()) {
        case ResponseType::SPEAK: {
            m_speechResponder->speak(dialogController, response->getResponseText(), response->getAudioStream());
            break;
        }
        case ResponseType::PLAY_LOCAL_AUDIO: {
            std::string audioFileKey = response->getResponsePayload();
            dialogController->stop();
            m_soundPlayer->play(audioFileKey);
            break;
        }
        case ResponseType::INVOKE_ACTIVITY_CONTROL: {
            std::string controlTypeString = response->getResponsePayload();
            ControlType controlType = ControlTypeUtils::getControlTypeForName(controlTypeString);
            dialogController->stopAndInvokeControl(controlType);
            break;
        }
        case ResponseType::INVOKE_AGENT_TRANSFER: {
            m_speechResponder->speakAndTransfer(
                dialogController, response->getResponseText(), response->getAudioStream(), ActorId("alexa"));
            break;
        }
        case ResponseType::ERROR: {
            m_speechResponder->speak(
                dialogController,
                response->getResponseText(),
                AudioStore::getStreamForLocalAudioFile(AudioFileName::DEFAULT_ERROR_MESSAGE));
            break;
        }
    }
}

}  // namespace response
}  // namespace computer
}  // namespace agents
}  // namespace samples
}  // namespace multiAgentExperience
