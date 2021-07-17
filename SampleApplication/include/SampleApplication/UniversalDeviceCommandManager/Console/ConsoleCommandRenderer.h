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


#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UNIVERSALDEVICECOMMANDMANAGER_CONSOLE_CONSOLECOMMANDRENDERER_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UNIVERSALDEVICECOMMANDMANAGER_CONSOLE_CONSOLECOMMANDRENDERER_H_

#include "SampleApplication/UniversalDeviceCommandManager/UniversalDeviceCommandRendererInterface.h"

#include "SampleApplication/UIManager/ConsolePrinter.h"

#include <memory>

namespace multiAgentExperience {
namespace sampleApplication {
namespace universalDeviceCommandManager {
namespace console {

class ConsoleCommandRenderer : public UniversalDeviceCommandRendererInterface {
public:
    ConsoleCommandRenderer(std::shared_ptr<uiManager::ConsolePrinter> consolePrinter);

    void onControlChange(const std::set<MAX::control::ControlType>& controls) override;

private:
    /// Our console printer.
    std::shared_ptr<uiManager::ConsolePrinter> m_consolePrinter;
};

}  // namespace console
}  // namespace universalDeviceCommandManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UNIVERSALDEVICECOMMANDMANAGER_CONSOLE_CONSOLECOMMANDRENDERER_H_
