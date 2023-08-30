/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <functional>
#include <cstring>

#include <MultiAgentExperience/Application/MAXBuilder.h>
#include <MultiAgentExperience/Agent/AgentManagerInterface.h>
#include <MultiAgentExperience/Actor/ActorId.h>
#include <MultiAgentExperience-CommandLine-Orchestrator/Orchestrator.h>

#ifdef MULTI_AGENT_EXPERIENCE
#include "Alexa/AlexaTestableAgentRegistration.h"
#endif

#include <Log/AppLogger.h>

int main(int argc, char** argv)
{
    if (0 >= argc) {
        std::cout << "Missing argument! Please pass the path to AlexaClientSDKConfig.json as the command line argument." << std::endl;
        return 0;
    }
    std::string pathToAlexaConfig;
    for (int i = 0; i < argc; ++i) {
        if(NULL != std::strstr(argv[i], "AlexaClientSDKConfig.json")) {
            pathToAlexaConfig = argv[i];
            break;
        }
    }
    if("" == pathToAlexaConfig) {
        std::cout << "Missing argument! Please pass the path to AlexaClientSDKConfig.json as the command line argument." << std::endl;
        return 0;
    }

    // All the max stuff
    multiAgentExperience::actor::ActorId sampleAppActorId("SampleDevice");
    auto log = std::make_shared<multiAgentExperience::integrationApp::log::AppLogger>();
    log->setComponentLevel(
            multiAgentExperience::integrationApp::log::AppLogger::MAX_LIB_COMPONENT_NAME,
            multiAgentExperience::utils::Log::Level::DEBUG3);

    multiAgentExperience::application::MAXBuilder builder;
    auto max = builder
            .withNormalPriorityCrossAgentBargeIn(multiAgentExperience::application::NormalPriorityCrossAgentBargeInPolicy::NOT_SUPPORTED)
            .withHighPriorityCrossAgentBargeIn(multiAgentExperience::application::HighPriorityCrossAgentBargeInPolicy::SUPPORTED)
            .setActivitySchedulingPolicy(multiAgentExperience::activity::ActivityType::ALERTS, multiAgentExperience::application::ActivitySchedulingPolicy::STACK)
            .setLogComponentName(multiAgentExperience::integrationApp::log::AppLogger::MAX_LIB_COMPONENT_NAME)
            .setLogger(log)
            .build();
    if (!max) {
        std::cout << "Error creating the MAX Interface." << std::endl;
        return 0;
    }

#ifdef MULTI_AGENT_EXPERIENCE
    // Alexa
    auto testableAgent1 =
            multiAgentExperience::integrationApp::alexa::AlexaTestableAgentRegistration::create(
                pathToAlexaConfig);
#endif

    // Register the agents with MAX
    std::set<std::shared_ptr<multiAgentExperience::agent::AgentRegistrationInterface>> agents = {
#ifdef MULTI_AGENT_EXPERIENCE
            testableAgent1
#endif
    };
    max->getAgentManager()->registerAgents(agents);

    // Orchestrator stuff
    /**
     * Put it in a form
     * {
     *    "1": ["Agent1", <AGENT INVOKER>],
     *    "2": ["Agent2", <AGENT INVOKER>],
     *  }
     */
    std::map<std::string, std::pair< std::string, std::function<void()>>> testableAgentDetail;
#ifdef MULTI_AGENT_EXPERIENCE
    testableAgentDetail["1"] = std::pair< std::string, std::function<void()>>(std::string("Alexa"), [testableAgent1]{testableAgent1->requestDialog();});
#endif
    auto orchestrator = std::make_shared<multiAgentExperience::commandline::Orchestrator>(testableAgentDetail);
    orchestrator->orchestrate();

    return 0;
}

