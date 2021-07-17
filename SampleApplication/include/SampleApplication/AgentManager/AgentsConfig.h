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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AGENTMANAGER_AGENTSCONFIG_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AGENTMANAGER_AGENTSCONFIG_H_

#include <string>
#include <vector>

#include <rapidjson/document.h>

namespace multiAgentExperience {
namespace sampleApplication {
namespace agentManager {

/**
 * A struct that captures the application configuration of Agents.
 */
struct AgentsConfig {
    /**
     * A struct which reflects the configuration of a single Agent.
     */
    struct AgentConfig {
        /// The name of the agent.
        std::string name;
        /// The wakewords associated with the agent.
        std::vector<std::string> wakewords;
        /// A path to a config file which the agent may require.
        std::string configFilePath;
    };

    /// All agents in the current configuration.
    std::vector<AgentConfig> agentConfigs;
};

/**
 * A utility function to parse a given rapidjson document and produce an @c AgentsConfig object.
 *
 * TODO: VII-357 Improve verification of parsed config input.
 *
 * @param document The rapidjson document.
 * @param config [out] The config object to be set.
 * @return Whether the parse was successful.
 */
bool parseJSONConfig(const rapidjson::Document& document, AgentsConfig* config);

/**
 * A utility function which returns a valid value for the agent's primary wake word based on the parsed json. This will
 * be the first wakeword if one or more are successfully parsed, or empty string if there are no configured wake words.
 *
 * @param config The agent configuration to get the primary wakeword from
 * @return A valid wakeword value, either the first configured wakeword, or empty string if no wakewords are configured.
 */
std::string getAgentPrimaryWakeword(const AgentsConfig::AgentConfig& config);

}  // namespace agentManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AGENTMANAGER_AGENTSCONFIG_H_
