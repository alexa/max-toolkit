/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_COMMANDLINE_ORCHESTRATOR_ORCHESTRATOR_H
#define MULTIAGENTEXPERIENCE_COMMANDLINE_ORCHESTRATOR_ORCHESTRATOR_H

#include <string>
#include <map>
#include <functional>

namespace multiAgentExperience {
    namespace commandline {
        class Orchestrator {
        public:
            explicit Orchestrator(
                    std::map<std::string, std::pair< std::string, std::function<void()>>> agents)
                    : m_agents{agents} {}
            int orchestrate();
        private:
            void printAgents();
            void startDialog(std::ostream& out, std::string alias);
        private:
            std::map<std::string, std::pair< std::string, std::function<void()>>> m_agents;
        };
    } // commandline
} // multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_COMMANDLINE_ORCHESTRATOR_ORCHESTRATOR_H
