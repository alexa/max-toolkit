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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UIMANAGER_INTERACTIONHANDLER_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UIMANAGER_INTERACTIONHANDLER_H_

#include <memory>
#include <vector>

#include "SampleApplication/AgentManager/AgentManager.h"
#include "SampleApplication/UIManager/ConsolePrinter.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace uiManager {

/**
 * This class manages rendering UI messages to the console to direct the user on current options.
 */
class InteractionHandler {
public:
    /**
     * Creates an @c InteractionHandler object.
     *
     * @param agentManager The Agent Manager we will use.
     * @param consolePrinter The console printer.
     * @return A @c InteractionHandler if successful, otherwise nullptr.
     */
    static std::unique_ptr<InteractionHandler> create(
        std::shared_ptr<agentManager::AgentManager> agentManager,
        std::shared_ptr<uiManager::ConsolePrinter> consolePrinter);

    /**
     * Begins UI rendering.
     */
    void begin();

    /**
     * Prints our welcome message to the user.
     */
    void printWelcomeScreen();

    /**
     * Prints a help message to the user.
     */
    void printHelpMessage();

    /**
     * Prints a message describing microphone enabled/disabled state.
     */
    void printMicrophoneStatus(bool isMuted);

    /**
     * Prints a message to message the stop UDC was invoked.
     */
    void printInvokingStop();

private:
    /**
     * Constructor.
     *
     * @param agentManager The Agent Manager we will use.
     * @param consolePrinter The console printer.
     */
    InteractionHandler(
        std::shared_ptr<agentManager::AgentManager> agentManager,
        std::shared_ptr<uiManager::ConsolePrinter> consolePrinter);

    /**
     * Utility method to update Agent Summaries from the Agent Manager.
     */
    void updateAgentSummaries();

    /// Our console printer.
    std::shared_ptr<ConsolePrinter> m_consolePrinter;
    /// Our agent manager.
    std::shared_ptr<agentManager::AgentManager> m_agentManager;
    /// The most recent agent summaries acquired from the Agent Manager.
    std::vector<sampleApplication::agentManager::AgentManager::AgentSummary> m_agentSummaries;
};

}  // namespace uiManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UIMANAGER_INTERACTIONHANDLER_H_
