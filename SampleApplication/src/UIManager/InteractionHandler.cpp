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

#include "SampleApplication/UIManager/InteractionHandler.h"

#include "SampleApplication/Utils/RadiantLogger.h"
#include "SampleApplication/Utils/StringUtils.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace uiManager {

using namespace multiAgentExperience::sampleApplication::agentManager;

static const std::string MODULE_TAG("InteractionHandler");
#define LX(logCommand, message)                                               \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, \
                                MODULE_TAG, __func__, message)

// clang-format off
/// Our welcome message!
static const std::string MAX_SAMPLE_APPLICATION_WELCOME_MESSAGE =
"+----------------------------------------------------------------------------+\n"
"|                                                                            |\n"
"|              ooo        ooooo       .o.       ooooooo  ooooo               |\n"
"|              `88.       .888'      .888.       `8888    d8'                |\n"
"|               888b     d'888      .8\"888.        Y888..8P                  |\n"
"|               8 Y88. .P  888     .8' `888.        `8888'                   |\n"
"|               8  `888'   888    .88ooo8888.      .8PY888.                  |\n"
"|               8    Y     888   .8'     `888.    d8'  `888b                 |\n"
"|              o8o        o888o o88o     o8888o o888o  o88888o               |\n"
"|                                                                            |\n"
"+----------------------------------------------------------------------------+\n"
"|                  Multi-Agent Experience Sample Application                 |\n"
"|                                 Version 0.4                                |\n"
"+----------------------------------------------------------------------------+\n";

/// An empty (new) line.
static const std::string EMPTY_LINE = "\n";

/// The strings following may be combined to present options to the user.
static const std::string HELP_MESSAGE_PREAMBLE_TEXT =
"------------------------------------------------------------------------------\n"
"                                  Options:                                    \n"
"                                                                              \n";

static const std::string HELP_MESSAGE_TAP_TO_TALK_PREAMBLE_TEXT =
" Tap to talk:                                                                 \n";

static const std::string HELP_MESSAGE_TAP_TO_TALK_TEMPLATE =
"       Press '%s' followed by 'Enter' and then speak to %s.                   \n";

static const std::string HELP_MESSAGE_WAKEWORD_PREAMBLE_TEXT =
" Wake word:                                                                   \n";

static const std::string HELP_MESSAGE_WAKEWORD_TEXT_TEMPLATE =
"       Say '%s' and then speak to %s.                                         \n";

static const std::string HELP_MESSAGE_MUTE_TEXT_TEMPLATE =
" Mute:                                                                        \n"
"       Press 'm' followed by 'Enter' to toggle the microphone on or off.      \n";

static const std::string HELP_MESSAGE_MICROPHONE_ENABLED =
" Microphone is enabled.                                                       \n";

static const std::string HELP_MESSAGE_MICROPHONE_DISABLED =
" Microphone is disabled.                                                      \n";

static const std::string HELP_MESSAGE_CONCLUSION_TEXT =
" Info:                                                                        \n"
"       Press 'h' followed by 'Enter' at any time to see the help screen.      \n"
"                                                                              \n"
" Quit:                                                                        \n"
"       Press 'q' followed by 'Enter' at any time to quit the application.     \n"
"------------------------------------------------------------------------------\n";

static const std::string UDC_STOP_INVOKED_MESSAGE =
        " Invoking STOP\n";
// clang-format on

std::unique_ptr<InteractionHandler> InteractionHandler::create(
    std::shared_ptr<agentManager::AgentManager> agentManager,
    std::shared_ptr<uiManager::ConsolePrinter> consolePrinter) {
    LX(DEBUG3, "");

    if (!agentManager) {
        LX(ERROR, "agentManager is nullptr.");
        return nullptr;
    }

    if (!consolePrinter) {
        LX(ERROR, "consolePrinter is nullptr.");
        return nullptr;
    }

    std::unique_ptr<InteractionHandler> handler =
        std::unique_ptr<InteractionHandler>(
            new InteractionHandler(agentManager, consolePrinter));
    return handler;
}

InteractionHandler::InteractionHandler(
    std::shared_ptr<agentManager::AgentManager> agentManager,
    std::shared_ptr<uiManager::ConsolePrinter> consolePrinter)
    : m_consolePrinter{consolePrinter}, m_agentManager{agentManager} {}

void InteractionHandler::begin() {
    LX(DEBUG3, "");

    printWelcomeScreen();

    updateAgentSummaries();

    printHelpMessage();
}

void InteractionHandler::printWelcomeScreen() {
    auto agentSummaries = m_agentManager->getAgentSummaries();
    m_consolePrinter->print(MAX_SAMPLE_APPLICATION_WELCOME_MESSAGE);
}

void InteractionHandler::printHelpMessage() {
    LX(DEBUG3, "");

    m_consolePrinter->print(HELP_MESSAGE_PREAMBLE_TEXT);

    if (!m_agentSummaries.empty()) {
        // Print tap to talk options.
        m_consolePrinter->print(HELP_MESSAGE_TAP_TO_TALK_PREAMBLE_TEXT);
        // TODO VII-361: Replace usage of AgentNumber with ActorIds
        int agentNumber = 1;
        for (auto const& agentSummary : m_agentSummaries) {
            m_consolePrinter->print(
                utils::stringFormat(HELP_MESSAGE_TAP_TO_TALK_TEMPLATE.c_str(),
                                    std::to_string(agentNumber++).c_str(),
                                    agentSummary.id.get().c_str()));
        }
        m_consolePrinter->print(EMPTY_LINE);

        // Print available wakewords
        bool wakewordPreamblePrinted = false;
        for (auto const& agentSummary : m_agentSummaries) {
            if (hasWakeword(agentSummary)) {
                if (!wakewordPreamblePrinted) {
                    m_consolePrinter->print(
                        HELP_MESSAGE_WAKEWORD_PREAMBLE_TEXT);
                    wakewordPreamblePrinted = true;
                }
                std::set<std::string> agentWakewords = agentSummary.wakewords;
                std::string agentWakewordsString;
                for (auto iterator = agentWakewords.begin();
                     iterator != agentWakewords.end(); iterator++) {
                    if (iterator != agentWakewords.begin()) {
                        agentWakewordsString += "or ";
                    }
                    agentWakewordsString += *iterator;
                }
                std::string agentName = agentSummary.id.get();
                agentName[0] = std::toupper(agentName[0]);
                m_consolePrinter->print(utils::stringFormat(
                    HELP_MESSAGE_WAKEWORD_TEXT_TEMPLATE.c_str(),
                    agentWakewordsString.c_str(), agentName.c_str()));
            }
        }

        m_consolePrinter->print(EMPTY_LINE);
    }

    m_consolePrinter->print(HELP_MESSAGE_MUTE_TEXT_TEMPLATE);

    m_consolePrinter->print(HELP_MESSAGE_CONCLUSION_TEXT);
}

void InteractionHandler::printMicrophoneStatus(bool isMuted) {
    LX(DEBUG3, "");
    if (isMuted) {
        m_consolePrinter->print(HELP_MESSAGE_MICROPHONE_DISABLED);
    } else {
        m_consolePrinter->print(HELP_MESSAGE_MICROPHONE_ENABLED);
    }
}

void InteractionHandler::printInvokingStop() {
    LX(DEBUG3, "");
    m_consolePrinter->print(UDC_STOP_INVOKED_MESSAGE);
}

void InteractionHandler::updateAgentSummaries() {
    LX(DEBUG3, "");

    m_agentSummaries.clear();

    auto agentSummaries = m_agentManager->getAgentSummaries();

    for (auto agentSummary : agentSummaries) {
        // Convert agent name and wakewords to title case in place.
        agentSummary.id.get()[0] = toupper(agentSummary.id.get()[0]);
        std::set<std::string> agentWakewords;
        for (auto wakeword : agentSummary.wakewords) {
            wakeword[0] = toupper(wakeword[0]);
            agentWakewords.insert(wakeword);
        }
        agentSummary.wakewords = agentWakewords;
        m_agentSummaries.push_back(agentSummary);
    }

    std::sort(m_agentSummaries.begin(), m_agentSummaries.end(),
              [](AgentManager::AgentSummary const& a,
                 AgentManager::AgentSummary const& b) {
                  return static_cast<std::string>(a.id) <
                         static_cast<std::string>(b.id);
              });
}

}  // namespace uiManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
