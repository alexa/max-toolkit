/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <Orchestrator.h>
#include <cli/cli.h>
#include <cli/clifilesession.h>
#include <string>

int multiAgentExperience::commandline::Orchestrator::orchestrate() {
    printAgents();
    auto rootMenu = std::make_unique< cli::Menu >( "max" );
    rootMenu -> Insert(
            "t",
            [this](std::ostream& out, const std::string& alias){
                this->startDialog(out, alias);
            },
            "Start a dialog with the agent" );

    rootMenu -> Insert(
            "p",
            [this](std::ostream& out){
                this->printAgents();
            },
            "Prints the available agent details" );

    cli::Cli cli( std::move(rootMenu) );
    cli.EnterAction([](auto& out){ out << "Use help to see the list of commands.\n"; } );
    // global exit action
    cli.ExitAction( [](auto& out){ out << "Thanks for testing.\n"; } );

    cli::CliFileSession input(cli);
    input.Start();

    return 0;
}

void multiAgentExperience::commandline::Orchestrator::printAgents() {
    std::cout << "Agents available - " << m_agents.size() << std::endl;
    for (auto const& agent : m_agents)
    {
        std::cout << "Agent alias:"
                  << agent.first  // string (key)
                  << ", "
                  << "Agent Name: "
                  << agent.second.first // string's value
                  << std::endl;
    }
}

void multiAgentExperience::commandline::Orchestrator::startDialog(std::ostream& out, std::string alias) {
    out << "Figuring out the agent for the alias " << alias << std::endl;

    if (m_agents.count(alias)) {
        auto &agent = m_agents[alias];
        out << "Agent " << agent.first << " found for alias " << alias << std::endl;
        out << "Initiating the dialog" << std::endl;
        agent.second();
    } else {
        out << "No agents for the alias " << alias << std::endl;
    }
}