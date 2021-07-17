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

#include "SampleApplication/UIManager/UIManager.h"

#include "SampleApplication/Utils/RadiantLogger.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace uiManager {

/// Metadata parameters that will be passed into our logging system.
static const std::string MODULE_TAG("UIManager");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, MODULE_TAG, __func__, message)

std::unique_ptr<UIManager> UIManager::create(
    std::shared_ptr<agentManager::AgentManager> agentManager,
    std::shared_ptr<universalDeviceCommandManager::UniversalDeviceCommandManager> udcManager,
    std::weak_ptr<audioManager::AudioManager> audioManager) {
    LX(DEBUG3, "");

    auto consolePrinter = std::make_shared<ConsolePrinter>();

    std::shared_ptr<InteractionHandler> interactionHandler = InteractionHandler::create(agentManager, consolePrinter);
    if (!interactionHandler) {
        LX(ERROR, "Unable to create interactionHandler.");
        return nullptr;
    }

    std::shared_ptr<InputHandler> inputHandler =
        InputHandler::create(agentManager, interactionHandler, udcManager, audioManager);
    if (!inputHandler) {
        LX(ERROR, "Unable to create inputHandler.");
        return nullptr;
    }

    std::unique_ptr<UIManager> uiManager =
        std::unique_ptr<UIManager>(new UIManager(interactionHandler, inputHandler, consolePrinter));

    return uiManager;
}

UIManager::UIManager(
    std::shared_ptr<InteractionHandler> interactionHandler,
    std::shared_ptr<InputHandler> inputHandler,
    std::shared_ptr<uiManager::ConsolePrinter> consolePrinter) :
        m_InteractionHandler(interactionHandler),
        m_InputHandler{inputHandler},
        m_consolePrinter{consolePrinter} {
}

std::shared_ptr<uiManager::ConsolePrinter> UIManager::getConsolePrinter() {
    return m_consolePrinter;
}

void UIManager::start() {
    LX(DEBUG3, "");

    m_InteractionHandler->begin();
    m_InputHandler->run();
}

}  // namespace uiManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
