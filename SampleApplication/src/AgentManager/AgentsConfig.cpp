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

#include "SampleApplication/AgentManager/AgentsConfig.h"

#include <AVSCommon/Utils/JSON/JSONUtils.h>

#include "SampleApplication/Utils/RadiantLogger.h"
#include "SampleApplication/Utils/StringUtils.h"

/// JSON key to get the agents element from the MAX Config file.
static const std::string MAX_CONFIG_JSON_AGENTS_OBJECT_KEY = "agents";

/// JSON key to get the agent name element from the MAX Config file.
static const std::string MAX_CONFIG_JSON_AGENT_NAME_KEY = "name";

/// JSON key to get the agent wakewords element from the MAX Config file.
static const std::string MAX_CONFIG_JSON_AGENT_WAKEWORDS_KEY = "wakewords";

/// JSON key to get the agent config file path element from the MAX Config file.
static const std::string MAX_CONFIG_JSON_AGENT_CONFIGFILEPATH_KEY = "configFilePath";

namespace multiAgentExperience {
namespace sampleApplication {
namespace agentManager {

/// Metadata parameters that will be passed into our logging system.
static const std::string MODULE_TAG("AgentsConfig");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, MODULE_TAG, __func__, message)

using namespace rapidjson;
using namespace alexaClientSDK::avsCommon::utils::json;

/**
 * Utility function to print the AgentsConfig details.
 *
 * @param configs The AgentsConfig to be printed.
 */
static void printConfig(const AgentsConfig& configs) {
    for (auto config : configs.agentConfigs) {
        LX(DEBUG3, "************************** ");
        LX(DEBUG3, "* AGENT CONFIG");
        LX(DEBUG3, "* name:" + config.name);
        for (auto ww : config.wakewords) {
            LX(DEBUG3, "* wakeword:" + ww);
        }
        LX(DEBUG3, "* configFilePath:" + config.configFilePath);
        LX(DEBUG3, "************************** ");
    }
}

/**
 * Utility function to normalize strings within a config.
 *
 * @param agentConfig The config to normalize.
 */
static void normalizeConfig(AgentsConfig::AgentConfig* agentConfig) {
    agentConfig->name = utils::stringToLowerCase(agentConfig->name);
    for (auto& ww : agentConfig->wakewords) {
        ww = utils::stringToLowerCase(ww);
    }
}

static bool parseAgentObject(rapidjson::Value::ConstValueIterator& agent, AgentsConfig* config) {
    LX(DEBUG3, "");

    AgentsConfig::AgentConfig agentConfig;
    if (!jsonUtils::retrieveValue(*agent, MAX_CONFIG_JSON_AGENT_NAME_KEY, &(agentConfig.name))) {
        LX(ERROR, "Missing agent name");
        return false;
    }

    rapidjson::Value::ConstMemberIterator wwIter;
    if (!jsonUtils::findNode(*agent, MAX_CONFIG_JSON_AGENT_WAKEWORDS_KEY, &wwIter)) {
        LX(ERROR, "Could not find wakewords element for Agent config.");
        return false;
    }

    agentConfig.wakewords = jsonUtils::retrieveStringArray<std::vector<std::string>>(wwIter->value);
    if (agentConfig.wakewords.empty()) {
        LX(INFO, "parseAgentObject : missing wakewords");
        // no issue if this is missing.
    }

    if (!jsonUtils::retrieveValue(*agent, MAX_CONFIG_JSON_AGENT_CONFIGFILEPATH_KEY, &(agentConfig.configFilePath))) {
        LX(DEBUG3, "Missing config file path.");
        // no issue if this is missing.
    }

    // ensure all config string fields, apart from file path, is set to lower case.
    normalizeConfig(&agentConfig);

    config->agentConfigs.push_back(agentConfig);

    return true;
}

bool parseJSONConfig(const rapidjson::Document& document, AgentsConfig* config) {
    LX(DEBUG3, "");

    if (!config) {
        LX(ERROR, "Config is nullptr.");
        return false;
    }

    if (!jsonUtils::jsonArrayExists(document, MAX_CONFIG_JSON_AGENTS_OBJECT_KEY)) {
        LX(ERROR, "Missing element : " + MAX_CONFIG_JSON_AGENTS_OBJECT_KEY);
        return false;
    }

    Value::ConstMemberIterator agentsArrayIter;
    if (!jsonUtils::findNode(document, MAX_CONFIG_JSON_AGENTS_OBJECT_KEY, &agentsArrayIter)) {
        LX(ERROR, "Missing element: " + MAX_CONFIG_JSON_AGENTS_OBJECT_KEY);
        return false;
    }

    const rapidjson::Value& agentsArray = document[MAX_CONFIG_JSON_AGENTS_OBJECT_KEY];
    if (!agentsArray.IsArray()) {
        LX(ERROR, "Agents config element is not a JSON array.");
        return false;
    }

    for (rapidjson::Value::ConstValueIterator iterator = agentsArray.Begin(); iterator != agentsArray.End();
         ++iterator) {
        parseAgentObject(iterator, config);
    }

    printConfig(*config);

    return true;
}

std::string getAgentPrimaryWakeword(const AgentsConfig::AgentConfig& config) {
    if (config.wakewords.empty()) {
        return "";
    } else {
        return config.wakewords.front();
    }
}

}  // namespace agentManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
