/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_INTEGRATION_APP_ALEXATESTABLEAGENTREGISTRATION_H
#define MULTIAGENTEXPERIENCE_INTEGRATION_APP_ALEXATESTABLEAGENTREGISTRATION_H

#include <SampleApp/SampleApplication.h>
#include <SampleApp/InteractionManager.h>
#include <DefaultClient/DefaultClient.h>
#include <MultiAgentExperience/AlexaAdapter/Agent/AlexaAgentRegistration.h>
#include <MultiAgentExperience/AlexaAdapter/Mediator/MAXFocusMediator.h>
#include "MultiAgentExperience/Agent/AgentRegistrationInterface.h"

#include <utility>

namespace multiAgentExperience {
namespace integrationApp {
namespace alexa {

class AlexaTestableAgentRegistration:
        public multiAgentExperience::agent::AgentRegistrationInterface {

public:

    static std::shared_ptr<AlexaTestableAgentRegistration> create(
            std::string configFile
    );

    explicit AlexaTestableAgentRegistration(
            std::unique_ptr<alexaClientSDK::sampleApp::SampleApplication> sampleApplication):
            m_sampleApplication{std::move(sampleApplication)} {};

    void requestDialog();

    void onReady(
            std::shared_ptr<multiAgentExperience::common::OnCompletionCallbackInterface> onCompletionCallback,
            std::shared_ptr<multiAgentExperience::activity::ActivityManagerInterface> activityManager,
            std::shared_ptr<multiAgentExperience::dialog::DialogManagerInterface> dialogManager,
            std::shared_ptr<multiAgentExperience::experience::StaticExperienceManagerInterface> staticExperienceManager) override;

    actor::ActorId getId() override;

    std::string getName() override;

private:

    std::unique_ptr<alexaClientSDK::sampleApp::SampleApplication> m_sampleApplication;
};

} // namespace alexa
} // namespace integrationApp
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_INTEGRATION_APP_ALEXATESTABLEAGENTREGISTRATION_H
