/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <MultiAgentExperience/Application/MAXBuilder.h>
#include <MultiAgentExperience/Agent/AgentManagerInterface.h>
#include <MultiAgentExperience/Actor/ActorId.h>
#include <MultiAgentExperience/IPC/gRPC/Connection/AgentRegistrationAdapter.h>
#include <MultiAgentExperience/IPC/gRPC/Connection/GrpcConnectionConfiguration.h>

#include "Device/ConsoleExperienceRenderer.h"
#include "Log/AppLogger.h"

void printUsage(std::string error) {
    if (error != "") {
        std::cout << error << std::endl;
    }

    std::cout << "Usage: MultiAgentExperience-Integration-App [sound device name] [Alexa 1 clientUri] [Alexa 1 serverUri] [Alexa 2 clientUri] [Alexa 2 serverUri]" << std::endl
              << "[sound device name] - The device name" << std::endl
              << "[Alexa 1 clientUri] - The host:port for the gRPC server in Alexa 1" << std::endl
              << "[Alexa 1 serverUri] - The host:port for the gRPC server in MAX that communicates with Alexa 1" << std::endl
              << "[Alexa 2 clientUri] - [Optional] The host:port for the gRPC server in Alexa 2" << std::endl
              << "[Alexa 2 serverUri] - [Optional] The host:port for the gRPC server in MAX that communicates with Alexa 2" << std::endl
              << "MultiAgentExperience-Integration-App will create a MAX object and register two Alexas and Lex"<< std::endl;
}

int main(int argc, char** argv)
{
	std::cout << "All logs in this application are intended for debugging and development purposes only." << std::endl;

    if (argc != 4 && argc != 6) {
        printUsage("");
        return -1;
    }

    /**
     * For testing IPC scenarios when we execute MultiAgentExperience-Integration-App we need to supply 5 parameters
     * on the command line that are as follows:
     *
     * 1) deviceName
     * 2) Alexa 1: clientUri
     * 3) Alexa 1: serverUri
     * 4) Alexa 2: clientUri
     * 5) Alexa 2: serverUri
    */
    std::string deviceName;
    // Alexa 1
    std::string clientUri1;
    std::string serverUri1;
    // Alexa 2
    std::string clientUri2;
    std::string serverUri2;
    bool createSecondAlexa = false;

    if (argc >= 4) {
        deviceName = argv[1];
        clientUri1 = argv[2];
        serverUri1 = argv[3];
        std::cout << "Request to create 1 alexa with the following details ." << clientUri1 << " " << serverUri1 << std::endl;
    }
    if (argc == 6) {
        clientUri2 = argv[4];
        serverUri2 = argv[5];
        std::cout << "Request to create 2 alexa with the following details ." << clientUri2 << " " << serverUri2 << std::endl;
        createSecondAlexa = true;
    }

    /// ActorId
    multiAgentExperience::actor::ActorId sampleAppActorId("SampleDevice");

    /// Application Logger creation
    auto log = std::make_shared<multiAgentExperience::integrationApp::log::AppLogger>();
    log->setComponentLevel(
            multiAgentExperience::integrationApp::log::AppLogger::MAX_LIB_COMPONENT_NAME,
            multiAgentExperience::utils::Log::Level::DEBUG3);
    multiAgentExperience::logger::setLoggerInstance(log);

    /// MAX object instantiation
    multiAgentExperience::application::MAXBuilder builder;
    auto max = builder
            .withNormalPriorityCrossAgentBargeIn(multiAgentExperience::application::NormalPriorityCrossAgentBargeInPolicy::NOT_SUPPORTED)
            .withHighPriorityCrossAgentBargeIn(multiAgentExperience::application::HighPriorityCrossAgentBargeInPolicy::SUPPORTED)
            .setActivitySchedulingPolicy(multiAgentExperience::activity::ActivityType::ALERTS, multiAgentExperience::application::ActivitySchedulingPolicy::STACK)
            .setLogComponentName(multiAgentExperience::integrationApp::log::AppLogger::MAX_LIB_COMPONENT_NAME)
            .setLogger(log)
            .build();
    if (!max) {
        std::cerr << "Error creating MAX interface object" << std::endl;
        return 0;
    }

    std::set<std::shared_ptr<multiAgentExperience::agent::AgentRegistrationInterface>> agents = {
    };

    /**
     * Alexa 1:
     * The AgentRegistrationAdapter helps start the gRPC server for MAX Shim at the URI specified in serverUri1. It also
     * connects to the Alexa gRPC server specified in clientUri1. The GrpcConnectionConfiguration holds these URI details.
     */
    auto connectionConfig1 = multiAgentExperience::ipc::grpc::connection::GrpcConnectionConfiguration(clientUri1, serverUri1);
    auto alexaAgent1 = std::make_shared<multiAgentExperience::ipc::grpc::connection::AgentRegistrationAdapter>(
        max->getAgentManager(), connectionConfig1);
    if (alexaAgent1->connect()) {
        agents.insert(alexaAgent1);
    } else {
        std::cout << "Unable to create an instance of Alexa. Exiting..." << std::endl;
        return -1;
    }

    std::shared_ptr<multiAgentExperience::ipc::grpc::connection::AgentRegistrationAdapter> alexaAgent2;

    if (createSecondAlexa) {
        std::cout << "Creating second Alexa  ." << std::endl;
        /**
         * Alexa 2
         */
        auto connectionConfig2 = multiAgentExperience::ipc::grpc::connection::GrpcConnectionConfiguration(clientUri2, serverUri2);
        alexaAgent2 = std::make_shared<multiAgentExperience::ipc::grpc::connection::AgentRegistrationAdapter>(
            max->getAgentManager(), connectionConfig2);
        if (alexaAgent2->connect()) {
            // Insert the second alexa agent into the set for agent registration
            agents.insert(alexaAgent2);
        } else {
            std::cout << "Unable to create the second instance of Alexa. Exiting..." << std::endl;
            return -1;
        }

    }

    std::cout << "Registering a total of " << agents.size() << " agents!" << std::endl;
    max->getAgentManager()->registerAgents(agents);

    // Register an experience observer so that any experience related changes are printed to console.
    auto experienceObserver = std::make_shared<multiAgentExperience::integrationApp::device::ConsoleExperienceRenderer>();
    max->getExperienceManager()->addObserver(experienceObserver);

    // The following code will block the process from exiting.

    getchar();

    return 0;
}

