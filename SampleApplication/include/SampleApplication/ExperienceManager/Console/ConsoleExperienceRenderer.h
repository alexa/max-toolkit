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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_EXPERIENCEMANAGER_CONSOLE_CONSOLEEXPERIENCERENDERER_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_EXPERIENCEMANAGER_CONSOLE_CONSOLEEXPERIENCERENDERER_H_

#include <memory>
#include <vector>

#include "SampleApplication/ExperienceManager/ExperienceRendererInterface.h"
#include "SampleApplication/UIManager/ConsolePrinter.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace experienceManager {
namespace console {

/**
 * A console-based experience renderer.
 */
class ConsoleExperienceRenderer : public ExperienceRendererInterface {
public:
    /**
     * Constructor.
     *
     * @param consolePrinter The console printer for rendering.
     */
    ConsoleExperienceRenderer(std::shared_ptr<uiManager::ConsolePrinter> consolePrinter);

    /// @name ExperienceObserverInterface methods.
    /// @{
    void onExperienceChange(const std::vector<MAX::experience::Experience>& experiences) override;
    /// @}

private:
    /// Our console printer.
    std::shared_ptr<uiManager::ConsolePrinter> m_consolePrinter;
};

}  // namespace console
}  // namespace experienceManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_EXPERIENCEMANAGER_CONSOLE_CONSOLEEXPERIENCERENDERER_H_
