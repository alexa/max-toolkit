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

#include "SampleApplication/ExperienceManager/Console/ConsoleExperienceRenderer.h"
#include "SampleApplication/Utils/RadiantLogger.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace experienceManager {
namespace console {

static const std::string MODULE_TAG("ConsoleExperienceRenderer");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, MODULE_TAG, __func__, message)

ConsoleExperienceRenderer::ConsoleExperienceRenderer(std::shared_ptr<uiManager::ConsolePrinter> consolePrinter) :
        m_consolePrinter{consolePrinter} {
}

void ConsoleExperienceRenderer::onExperienceChange(const std::vector<experience::Experience>& experiences) {
    LX(DEBUG3, "");

    if (experiences.empty()) {
        // TODO : this is broken, as this will be invoked inbetween valid dialog states. Fix under VII-256.
        //        m_consolePrinter->prettyPrint("Agents are idle.");
        //        m_consolePrinter->print("\n");
    } else {
        for (auto& experience : experiences) {
            std::string camelCaseAgentName = static_cast<std::string>(experience.actorId);
            if (!camelCaseAgentName.empty()) {
                camelCaseAgentName[0] = ::toupper(camelCaseAgentName[0]);
            }
            m_consolePrinter->prettyPrint(camelCaseAgentName + " is " + experience.experienceId.get() + "...");
            m_consolePrinter->print("\n");
        }
    }
}

}  // namespace console
}  // namespace experienceManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
