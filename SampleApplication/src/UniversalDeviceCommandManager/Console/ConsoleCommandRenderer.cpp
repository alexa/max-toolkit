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

#include "SampleApplication/UniversalDeviceCommandManager/Console/ConsoleCommandRenderer.h"

#include "SampleApplication/UIManager/ConsoleInputs.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace universalDeviceCommandManager {
namespace console {

// static const std::string NO_COMMANDS_AVAILABLE_MESSAGE =
//" No universal device commands are available.";
static const std::string COMMANDS_AVAILABLE_MESSAGE =
    " Available universal device commands:";
static const std::string UDC_STOP_NAME_MESSAGE = "STOP";

ConsoleCommandRenderer::ConsoleCommandRenderer(
    std::shared_ptr<uiManager::ConsolePrinter> consolePrinter)
    : m_consolePrinter{consolePrinter} {}

void ConsoleCommandRenderer::onControlChange(
    const std::set<MAX::control::ControlType>& controls) {
    if (!controls.empty()) {
        m_consolePrinter->prettyPrint(COMMANDS_AVAILABLE_MESSAGE);
        for (auto control : controls) {
            std::string inputForControl;
            std::string prettyNameOfControl;
            switch (control) {
                case MAX::control::ControlType::STOP:
                    inputForControl =
                        sampleApplication::uiManager::consoleInputs::UDC_STOP;
                    prettyNameOfControl = UDC_STOP_NAME_MESSAGE;
                    break;
            }
            m_consolePrinter->print("    Press '" + inputForControl + "' for " +
                                    prettyNameOfControl);
            m_consolePrinter->print("\n");
        }
    }
}

}  // namespace console
}  // namespace universalDeviceCommandManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
