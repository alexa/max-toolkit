/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Device/ConsoleExperienceRenderer.h"

#include <iostream>

#include <MultiAgentExperience/Experience/ExperienceId.h>

namespace multiAgentExperience {
namespace integrationApp {
namespace device {

void ConsoleExperienceRenderer::onExperienceChange(
    const std::vector<::multiAgentExperience::experience::Experience> &experiences) {

    if (experiences.empty()) {
        prettyPrint("MAX EXPERIENCE: EMPTY");
    } else {
        for (auto& experience : experiences) {
            std::string agentName = static_cast<std::string>(experience.actorId);
            std::string str = "MAX EXPERIENCE: " + agentName + " - " + experience.experienceId.get();
            prettyPrint(str);
        }
    }
}

void ConsoleExperienceRenderer::prettyPrint(std::string str) {
    std::string border(str.length() + (PADDING_LENGTH * 2), '*');

    std::cout << border << std::endl
              << PADDING_STR << str << PADDING_STR << std::endl
              << border << std::endl;
}

} // namespace device
} // namespace integrationApp
} // namespace multiAgentExperience

