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

#include "SampleApplication/UIManager/InputHandler.h"

#include "SampleApplication/UIManager/ConsoleInputs.h"

#include <iostream>

#include "SampleApplication/Utils/RadiantLogger.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace uiManager {

/// Metadata parameters that will be passed into our logging system.
static const std::string MODULE_TAG("InputHandler");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, MODULE_TAG, __func__, message)

/// Time to wait for console input to be read.
static const auto READ_CONSOLE_TIMEOUT = std::chrono::milliseconds(100);

std::unique_ptr<InputHandler> InputHandler::create(
    std::shared_ptr<agentManager::AgentManager> agentManager,
    std::shared_ptr<InteractionHandler> interactionHandler,
    std::shared_ptr<universalDeviceCommandManager::UniversalDeviceCommandManager> udcManager,
    std::weak_ptr<audioManager::AudioManager> audioManager) {
    LX(DEBUG3, "");

    if (!agentManager) {
        LX(ERROR, "agentManager is nullptr.");
        return nullptr;
    }

    if (!interactionHandler) {
        LX(ERROR, "interactionHandler is nullptr.");
        return nullptr;
    }

    if (!audioManager.lock()) {
        LX(ERROR, "audioManager is nullptr.");
        return nullptr;
    }

    std::unique_ptr<InputHandler> handler =
        std::unique_ptr<InputHandler>(new InputHandler(agentManager, interactionHandler, udcManager, audioManager));

    return handler;
}

InputHandler::InputHandler(
    std::shared_ptr<agentManager::AgentManager> agentManager,
    std::shared_ptr<InteractionHandler> interactionHandler,
    std::shared_ptr<universalDeviceCommandManager::UniversalDeviceCommandManager> udcManager,
    std::weak_ptr<audioManager::AudioManager> audioManager) :
        m_agentManager{agentManager},
        m_interactionHandler{interactionHandler},
        m_udcManager{udcManager},
        m_audioManager{audioManager} {
}

void InputHandler::run() {
    LX(DEBUG3, "");

    while (true) {
        char inputChar;
        readConsoleInput(&inputChar);

        inputChar = ::tolower(inputChar);
        if (inputChar >= consoleInputs::TAP_STARTING_CHAR && inputChar <= consoleInputs::TAP_ENDING_CHAR) {
            bool allowTap = false;
            if (auto audioManager = m_audioManager.lock()) {
                allowTap = !audioManager->isMicrophoneMuted();
            } else {
                LX(ERROR, "audioManager is nullptr! Unable to check microphone status");
            }

            if (allowTap) {
                // TODO VII-255: Decouple this from AgentManager
                // TODO VII-361: Replace agentIndex with ActorId usage.
                int agentIndex = inputChar - consoleInputs::TAP_STARTING_CHAR;
                m_agentManager->invokeTapToTalk(agentIndex);

            } else {
                m_interactionHandler->printMicrophoneStatus(true);
            }
        } else if (consoleInputs::HELP == inputChar) {
            m_interactionHandler->printHelpMessage();
        } else if (consoleInputs::MIC_TOGGLE == inputChar) {
            if (auto audioManager = m_audioManager.lock()) {
                bool microphoneIsMuted = audioManager->isMicrophoneMuted();
                audioManager->muteMicrophone(!microphoneIsMuted);
                m_interactionHandler->printMicrophoneStatus(!microphoneIsMuted);
            } else {
                LX(ERROR, "audioManager is nullptr! Unable to toggle microphone mute");
            }
        } else if (consoleInputs::UDC_STOP == inputChar) {
            m_interactionHandler->printInvokingStop();
            m_udcManager->invokeStop();
        } else if (consoleInputs::QUIT == inputChar) {
            break;
        }
    }
}

void InputHandler::readConsoleInput(char* input) {
    while (true) {
        if (m_consoleReader.read(READ_CONSOLE_TIMEOUT, input)) {
            return;
        }
    }
}

}  // namespace uiManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
