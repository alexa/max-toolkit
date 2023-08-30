/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Alexa/AlexaTestableAgentRegistration.h"

namespace multiAgentExperience {
namespace integrationApp {
namespace alexa {

std::shared_ptr<AlexaTestableAgentRegistration> AlexaTestableAgentRegistration::create(
        std::string configFile) {
    auto logLevel = "DEBUG3";
    auto sampleApplication = alexaClientSDK::sampleApp::SampleApplication::create(
            std::make_shared<alexaClientSDK::sampleApp::ConsoleReader>(),
            { configFile },
            logLevel);

    return std::make_shared<AlexaTestableAgentRegistration>(std::move(sampleApplication));
}

void AlexaTestableAgentRegistration::requestDialog() {
    m_sampleApplication->getInteractionManager()->tap();
}

void AlexaTestableAgentRegistration::onReady(
        std::shared_ptr<multiAgentExperience::common::OnCompletionCallbackInterface> onCompletionCallback,
        std::shared_ptr<multiAgentExperience::activity::ActivityManagerInterface> activityManager,
        std::shared_ptr<multiAgentExperience::dialog::DialogManagerInterface> dialogManager,
        std::shared_ptr<multiAgentExperience::experience::StaticExperienceManagerInterface> staticExperienceManager) {
    auto registration = m_sampleApplication->getAgentRegistration();
    registration->onReady(
            onCompletionCallback,
            activityManager,
            dialogManager,
            staticExperienceManager);
}

actor::ActorId AlexaTestableAgentRegistration::getId() {
    return m_sampleApplication->getAgentRegistration()->getId();
}

std::string AlexaTestableAgentRegistration::getName() {
    return m_sampleApplication->getAgentRegistration()->getName();
}

} // namespace alexa
} // namespace integrationApp
} // namespace multiAgentExperience