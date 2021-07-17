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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UIMANAGER_UIMANAGER_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UIMANAGER_UIMANAGER_H_

#include <memory>

#include "SampleApplication/AgentManager/AgentManager.h"
#include "SampleApplication/UIManager/InputHandler.h"
#include "SampleApplication/UIManager/InteractionHandler.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace uiManager {

/**
 * This class handles all UI concerns for the Sample Application. This consists of console input, output, and
 * supporting the potential menu systems of the various components such as agents and wakeword engines.
 */
class UIManager {
public:
    /**
     * Creates a UIManager instance.
     *
     * @param agentManager An initialized agentManager.
     * @param udcManager A Universal Device Command Manager to use.
     * @return A UIManager if successful, otherwise nullptr.
     */
    static std::unique_ptr<UIManager> create(
        std::shared_ptr<agentManager::AgentManager> agentManager,
        std::shared_ptr<universalDeviceCommandManager::UniversalDeviceCommandManager> udcManager,
        std::weak_ptr<audioManager::AudioManager> audioManager);

    /**
     * Acquire our consolePrinter.
     * @return the consolePrinter.
     */
    std::shared_ptr<uiManager::ConsolePrinter> getConsolePrinter();

    /**
     * Starts the UI components for use.
     */
    void start();

private:
    /**
     * Constructor.
     *
     * @param interactionHandler Our interactionHandler.
     * @param inputHandler Our inputHandler.
     * @param consolePrinter our consolePrinter.
     */
    UIManager(
        std::shared_ptr<InteractionHandler> interactionHandler,
        std::shared_ptr<InputHandler> inputHandler,
        std::shared_ptr<uiManager::ConsolePrinter> consolePrinter);

    /// our interactionHandler.
    std::shared_ptr<InteractionHandler> m_InteractionHandler;
    /// our inputHandler.
    std::shared_ptr<InputHandler> m_InputHandler;
    /// our consolePrinter.
    std::shared_ptr<ConsolePrinter> m_consolePrinter;
};

}  // namespace uiManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UIMANAGER_UIMANAGER_H_
