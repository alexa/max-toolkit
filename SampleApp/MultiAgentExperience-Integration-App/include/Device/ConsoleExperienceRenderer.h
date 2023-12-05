/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_INTEGRATION_APP_CONSOLEEXPERIENCERENDERER_H
#define MULTIAGENTEXPERIENCE_INTEGRATION_APP_CONSOLEEXPERIENCERENDERER_H

#include <MultiAgentExperience/Experience/ExperienceObserverInterface.h>

#include <utility>

namespace multiAgentExperience {
namespace integrationApp {
namespace device {

class ConsoleExperienceRenderer: public ::multiAgentExperience::experience::ExperienceObserverInterface {
public:

    void onExperienceChange(const std::vector<::multiAgentExperience::experience::Experience>& experiences) override;

    void prettyPrint(std::string str);
};

static const int PADDING_LENGTH = 5;
static const std::string PADDING_STR(PADDING_LENGTH, ' ');

} // namespace device
} // namespace integrationApp
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_INTEGRATION_APP_CONSOLEEXPERIENCERENDERER_H
