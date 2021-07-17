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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UIMANAGER_INPUTHANDLER_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UIMANAGER_INPUTHANDLER_H_

#include "SampleApplication/UIManager/InputHandler.h"
#include "SampleApplication/UIManager/InteractionHandler.h"
#include "SampleApplication/UIManager/ConsoleReader.h"
#include "SampleApplication/AgentManager/AgentManager.h"
#include "SampleApplication/AudioManager/AudioManager.h"
#include "SampleApplication/UniversalDeviceCommandManager/UniversalDeviceCommandManager.h"

#include <memory>

namespace multiAgentExperience {
namespace sampleApplication {
namespace uiManager {

/**
 * This class encapsulates logic for reading console input and routing to the appropriate UX command.
 */
class InputHandler {
public:
    /**
     * Creates an @c InputHandler.
     *
     * @param agentManager The agent manager to be used.
     * @param interactionHandler The interaction handler.
     * @param udcManager The Universal Device Command Manager to be used.
     * @param audioManager The Audio Manager to be used.
     * @return An @c InputHandler if successful, otherwise nullptr.
     */
    static std::unique_ptr<InputHandler> create(
        std::shared_ptr<agentManager::AgentManager> agentManager,
        std::shared_ptr<InteractionHandler> interactionHandler,
        std::shared_ptr<universalDeviceCommandManager::UniversalDeviceCommandManager> udcManager,
        std::weak_ptr<audioManager::AudioManager> audioManager);

    /**
     * Begin reading from console input.
     */
    void run();

private:
    /**
     * Constructor.
     *
     * @param agentManager The AgentManager we shall use.
     * @param interactionHandler The InteractionHandler.
     * @param udcManager The Universal Device Command Manager to be used.
     * @param audioManager The Audio Manager to be used.
     */
    InputHandler(
        std::shared_ptr<agentManager::AgentManager> agentManager,
        std::shared_ptr<InteractionHandler> interactionHandler,
        std::shared_ptr<universalDeviceCommandManager::UniversalDeviceCommandManager> udcManager,
        std::weak_ptr<audioManager::AudioManager> audioManager);

    /**
     * A blocking utility function to read a character from the console.
     * @param input [out] The character typed at the console.
     */
    void readConsoleInput(char* input);

    /// Our Agent Manager.
    std::shared_ptr<agentManager::AgentManager> m_agentManager;
    /// Our console reader.
    ConsoleReader m_consoleReader;
    /// Our Interaction Handler.
    std::shared_ptr<InteractionHandler> m_interactionHandler;
    /// Our UDC Manager.
    std::shared_ptr<universalDeviceCommandManager::UniversalDeviceCommandManager> m_udcManager;
    /// Our AudioManager
    std::weak_ptr<audioManager::AudioManager> m_audioManager;
};

}  // namespace uiManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UIMANAGER_INPUTHANDLER_H_
