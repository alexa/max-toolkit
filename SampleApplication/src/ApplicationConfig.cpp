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

#include "SampleApplication/ApplicationConfig.h"

#include <AVSCommon/Utils/JSON/JSONUtils.h>

#include "SampleApplication/Utils/RadiantLogger.h"

/// JSON key to get the runtime options element from the MAX Config file.
static const std::string MAX_CONFIG_JSON_RUNTIME_OPTIONS_KEY = "runtimeOptions";

/// JSON key to get the log levels element from the MAX Config file.
static const std::string MAX_CONFIG_JSON_RUNTIME_OPTIONS_LOG_LEVELS_KEY = "logLevels";

/// JSON key to get the global log levels element from the MAX Config file.
static const std::string MAX_CONFIG_JSON_RUNTIME_OPTIONS_LOG_GLOBAL_LOG_LEVEL_KEY = "global";

/// JSON key to get the log level overrides element from the MAX Config file.
static const std::string MAX_CONFIG_JSON_RUNTIME_OPTIONS_LOG_COMPONENT_OVERRIDES_KEY = "componentOverrides";

/// JSON key to get the application log level override element from the MAX Config file.
static const std::string MAX_CONFIG_JSON_RUNTIME_OPTIONS_LOG_COMPONENT_OVERRIDES_APPLICATION_KEY = "application";

/// JSON key to get the MAX Library log level override element from the MAX Config file.
static const std::string MAX_CONFIG_JSON_RUNTIME_OPTIONS_LOG_COMPONENT_OVERRIDES_MAX_KEY = "MAX";

/// JSON key to get the AVS SDK log level override element from the MAX Config file.
static const std::string MAX_CONFIG_JSON_RUNTIME_OPTIONS_LOG_COMPONENT_OVERRIDES_AVSSDK_KEY = "avssdk";

/// JSON key to get the Computer Agent log level override element from the MAX Config file.
static const std::string MAX_CONFIG_JSON_RUNTIME_OPTIONS_LOG_COMPONENT_OVERRIDES_COMPUTER_AGENT_KEY = "computerAgent";

namespace multiAgentExperience {
namespace sampleApplication {

using namespace rapidjson;
using namespace alexaClientSDK::avsCommon::utils::json;

/// Metadata parameters that will be passed into our logging system.
static const std::string MODULE_TAG("ApplicationConfig");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, MODULE_TAG, __func__, message)

/**
 * Utility function to conditionally read each override element. If all are absent, this is not an error and no such
 * trace will be logged.
 *
 * @param overrides The rapidjson element containing the overrides.
 * @param componentOverrides [out] A map of override names to values.
 */
static void parseLogComponentOverrideObject(
    Value::ConstMemberIterator& overrides,
    std::map<std::string, std::string>* componentOverrides) {
    LX(DEBUG3, "");

    std::string overrideValue;
    if (jsonUtils::retrieveValue(
            overrides->value,
            MAX_CONFIG_JSON_RUNTIME_OPTIONS_LOG_COMPONENT_OVERRIDES_APPLICATION_KEY,
            &overrideValue)) {
        (*componentOverrides)[MAX_CONFIG_JSON_RUNTIME_OPTIONS_LOG_COMPONENT_OVERRIDES_APPLICATION_KEY] = overrideValue;
    }
    if (jsonUtils::retrieveValue(
            overrides->value, MAX_CONFIG_JSON_RUNTIME_OPTIONS_LOG_COMPONENT_OVERRIDES_MAX_KEY, &overrideValue)) {
        (*componentOverrides)[MAX_CONFIG_JSON_RUNTIME_OPTIONS_LOG_COMPONENT_OVERRIDES_MAX_KEY] = overrideValue;
    }
    if (jsonUtils::retrieveValue(
            overrides->value, MAX_CONFIG_JSON_RUNTIME_OPTIONS_LOG_COMPONENT_OVERRIDES_AVSSDK_KEY, &overrideValue)) {
        (*componentOverrides)[MAX_CONFIG_JSON_RUNTIME_OPTIONS_LOG_COMPONENT_OVERRIDES_AVSSDK_KEY] = overrideValue;
    }
    if (jsonUtils::retrieveValue(
            overrides->value,
            MAX_CONFIG_JSON_RUNTIME_OPTIONS_LOG_COMPONENT_OVERRIDES_COMPUTER_AGENT_KEY,
            &overrideValue)) {
        (*componentOverrides)[MAX_CONFIG_JSON_RUNTIME_OPTIONS_LOG_COMPONENT_OVERRIDES_COMPUTER_AGENT_KEY] =
            overrideValue;
    }
}

ApplicationConfig::ApplicationConfig(MAX::utils::Log::Level defaultLevel) {
    globalLogLevel = defaultLevel;
}

bool parseJSONConfig(const rapidjson::Document& document, ApplicationConfig* config) {
    LX(DEBUG3, "");

    if (!config) {
        LX(ERROR, "Config is nullptr.");
        return false;
    }

    Value::ConstMemberIterator optionsIter;
    if (!jsonUtils::findNode(document, MAX_CONFIG_JSON_RUNTIME_OPTIONS_KEY, &optionsIter)) {
        LX(ERROR, "Missing runtimeOptions object : " + MAX_CONFIG_JSON_RUNTIME_OPTIONS_KEY);
        return false;
    }

    Value::ConstMemberIterator logLevelsIter;
    if (!jsonUtils::findNode(optionsIter->value, MAX_CONFIG_JSON_RUNTIME_OPTIONS_LOG_LEVELS_KEY, &logLevelsIter)) {
        LX(ERROR, "Missing logLevels element : " + MAX_CONFIG_JSON_RUNTIME_OPTIONS_LOG_LEVELS_KEY);
        return false;
    }

    std::string globalLogLevelString;
    if (jsonUtils::retrieveValue(
            logLevelsIter->value, MAX_CONFIG_JSON_RUNTIME_OPTIONS_LOG_GLOBAL_LOG_LEVEL_KEY, &globalLogLevelString)) {
        MAX::utils::Log::Level maxGlobalLogLevel;
        if (!MAX::utils::Log::stringToLevel(globalLogLevelString, &maxGlobalLogLevel)) {
            LX(ERROR, "Invalid log level : " + globalLogLevelString);
            return false;
        }
        config->globalLogLevel = maxGlobalLogLevel;
    } else {
        LX(DEBUG3, "Global log level not found.");
    }

    Value::ConstMemberIterator logLevelOverridesIter;
    if (jsonUtils::findNode(
            logLevelsIter->value,
            MAX_CONFIG_JSON_RUNTIME_OPTIONS_LOG_COMPONENT_OVERRIDES_KEY,
            &logLevelOverridesIter)) {
        std::map<std::string, std::string> componentOverrides;
        parseLogComponentOverrideObject(logLevelOverridesIter, &componentOverrides);

        for (auto override : componentOverrides) {
            MAX::utils::Log::Level logLevelOverride;
            if (!MAX::utils::Log::stringToLevel(override.second, &logLevelOverride)) {
                LX(ERROR, "Invalid log level : " + override.second);
                return false;
            }
            config->componentOverrides[override.first] = logLevelOverride;
        }
    } else {
        LX(DEBUG3, "component log overrides object not found.");
    }

    return true;
}

MAX::utils::Log::Level getApplicationLogLevel(const ApplicationConfig& config) {
    LX(DEBUG3, "");

    if (config.componentOverrides.find(MAX_CONFIG_JSON_RUNTIME_OPTIONS_LOG_COMPONENT_OVERRIDES_APPLICATION_KEY) !=
        config.componentOverrides.end()) {
        return config.componentOverrides.at(MAX_CONFIG_JSON_RUNTIME_OPTIONS_LOG_COMPONENT_OVERRIDES_APPLICATION_KEY);
    }
    return config.globalLogLevel;
}

MAX::utils::Log::Level getMAXLogLevel(const ApplicationConfig& config) {
    LX(DEBUG3, "");

    if (config.componentOverrides.find(MAX_CONFIG_JSON_RUNTIME_OPTIONS_LOG_COMPONENT_OVERRIDES_MAX_KEY) !=
        config.componentOverrides.end()) {
        return config.componentOverrides.at(MAX_CONFIG_JSON_RUNTIME_OPTIONS_LOG_COMPONENT_OVERRIDES_MAX_KEY);
    }
    return config.globalLogLevel;
}

MAX::utils::Log::Level getAVSSDKLogLevel(const ApplicationConfig& config) {
    LX(DEBUG3, "");

    if (config.componentOverrides.find(MAX_CONFIG_JSON_RUNTIME_OPTIONS_LOG_COMPONENT_OVERRIDES_AVSSDK_KEY) !=
        config.componentOverrides.end()) {
        return config.componentOverrides.at(MAX_CONFIG_JSON_RUNTIME_OPTIONS_LOG_COMPONENT_OVERRIDES_AVSSDK_KEY);
    }
    return config.globalLogLevel;
}

MAX::utils::Log::Level getComputerAgentLogLevel(const ApplicationConfig& config) {
    LX(DEBUG3, "");

    if (config.componentOverrides.find(MAX_CONFIG_JSON_RUNTIME_OPTIONS_LOG_COMPONENT_OVERRIDES_COMPUTER_AGENT_KEY) !=
        config.componentOverrides.end()) {
        return config.componentOverrides.at(MAX_CONFIG_JSON_RUNTIME_OPTIONS_LOG_COMPONENT_OVERRIDES_COMPUTER_AGENT_KEY);
    }
    return config.globalLogLevel;
}

}  // namespace sampleApplication
}  // namespace multiAgentExperience
