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

#include "SampleApplication/AudioManager/Wakeword/WakewordEnginesConfig.h"

#include <AVSCommon/Utils/JSON/JSONUtils.h>

#include "SampleApplication/Utils/RadiantLogger.h"
#include "SampleApplication/Utils/StringUtils.h"

/// JSON key to get the top-level wakeword engines element from the MAX Config file.
static const std::string MAX_CONFIG_JSON_WAKEWORDENGINES_OBJECT_KEY = "wakewordEngines";

/// JSON key to get a wakeword engine name element from the MAX Config file.
static const std::string MAX_CONFIG_JSON_WAKEWORDENGINES_ENGINE_NAME_KEY = "name";

/// JSON key to get a wakeword engine create method element from the MAX Config file.
static const std::string MAX_CONFIG_JSON_WAKEWORDENGINES_ENGINE_CREATE_METHOD_KEY = "createMethod";

/// JSON key to get a wakeword engine wakewords element from the MAX Config file.
static const std::string MAX_CONFIG_JSON_WAKEWORDENGINES_ENGINE_WAKEWORDS_KEY = "wakewords";

/// JSON key to get a wakeword engine resource folder element from the MAX Config file.
static const std::string MAX_CONFIG_JSON_WAKEWORDENGINES_ENGINE_RESOURCE_FOLDER_KEY = "resourceFolder";

namespace multiAgentExperience {
namespace sampleApplication {
namespace audioManager {
namespace wakeword {

/// Metadata parameters that will be passed into our logging system.
static const std::string MODULE_TAG("WakewordEnginesConfig");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, MODULE_TAG, __func__, message)

using namespace rapidjson;
using namespace alexaClientSDK::avsCommon::utils::json;

/**
 * Utility function to print the WakewordEnginesConfig details.
 *
 * @param format The WakewordEnginesConfig to be printed.
 */
static void printConfig(const WakewordEnginesConfig& configs) {
    for (auto config : configs.engineConfigs) {
        LX(DEBUG3, "*********************************** ");
        LX(DEBUG3, "* WAKEWORD ENGINE CONFIG");
        LX(DEBUG3, "* name:" + config.name);
        if (WakewordEngine::CreateMethod::AVS_SDK == config.createMethod) {
            LX(DEBUG3, "* createMethod: AVS SDK");
        } else {
            LX(DEBUG3, "* createMethod: CUSTOM");
        }
        for (auto ww : config.wakewords) {
            LX(DEBUG3, "* wakeword:" + ww);
        }
        LX(DEBUG3, "* resourceFolder:" + config.resourceFolder);
        LX(DEBUG3, "*********************************** ");
    }
}

/**
 * Utility function to normalize strings to lower case.
 *
 * @param enginesConfig The config to normalize.
 */
static void normalizeConfig(WakewordEnginesConfig* enginesConfig) {
    for (auto& config : enginesConfig->engineConfigs) {
        config.name = utils::stringToLowerCase(config.name);
        for (auto& ww : config.wakewords) {
            ww = utils::stringToLowerCase(ww);
        }
    }
}

WakewordEnginesConfig::EngineConfig::EngineConfig() : createMethod{WakewordEngine::CreateMethod::AVS_SDK} {
}

static bool parseEngineObject(rapidjson::Value::ConstValueIterator& engine, WakewordEnginesConfig* config) {
    WakewordEnginesConfig::EngineConfig engineConfig;
    if (!jsonUtils::retrieveValue(*engine, MAX_CONFIG_JSON_WAKEWORDENGINES_ENGINE_NAME_KEY, &(engineConfig.name))) {
        LX(ERROR, "Missing engine name.");
        return false;
    }
    if (!jsonUtils::retrieveValue(
            *engine, MAX_CONFIG_JSON_WAKEWORDENGINES_ENGINE_RESOURCE_FOLDER_KEY, &(engineConfig.resourceFolder))) {
        LX(ERROR, "Missing resource folder.");
        return false;
    }

    std::string createMethod;
    if (!jsonUtils::retrieveValue(*engine, MAX_CONFIG_JSON_WAKEWORDENGINES_ENGINE_CREATE_METHOD_KEY, &createMethod)) {
        LX(ERROR, "Missing create method.");
        return false;
    }

    if ("AVS_SDK" == createMethod) {
        engineConfig.createMethod = WakewordEngine::CreateMethod::AVS_SDK;
    } else if ("CUSTOM" == createMethod) {
        engineConfig.createMethod = WakewordEngine::CreateMethod::CUSTOM;
    } else {
        LX(ERROR, "Unknown create method : " + createMethod);
        return false;
    }

    rapidjson::Value::ConstMemberIterator wwIter;
    if (!jsonUtils::findNode(*engine, MAX_CONFIG_JSON_WAKEWORDENGINES_ENGINE_WAKEWORDS_KEY, &wwIter)) {
        LX(ERROR, "Could not find wakewords element for WakewordEngine config.");
        return false;
    }

    engineConfig.wakewords = jsonUtils::retrieveStringArray<std::vector<std::string>>(wwIter->value);
    if (engineConfig.wakewords.empty()) {
        LX(ERROR, "Missing wakewords.");
        return false;
    }

    normalizeConfig(config);
    config->engineConfigs.push_back(engineConfig);

    return true;
}

bool parseJSONConfig(const rapidjson::Document& document, WakewordEnginesConfig* config) {
    if (!config) {
        LX(ERROR, "Nullptr config.");
        return false;
    }

    if (!jsonUtils::jsonArrayExists(document, MAX_CONFIG_JSON_WAKEWORDENGINES_OBJECT_KEY)) {
        LX(ERROR, "Wakewordengines array not found.");
        return false;
    }

    Value::ConstMemberIterator wakewordEnginesArrayIter;
    if (!jsonUtils::findNode(document, MAX_CONFIG_JSON_WAKEWORDENGINES_OBJECT_KEY, &wakewordEnginesArrayIter)) {
        LX(ERROR, "Missing wakewordEngines object.");
        return false;
    }

    const rapidjson::Value& enginesArray = document[MAX_CONFIG_JSON_WAKEWORDENGINES_OBJECT_KEY];
    if (!enginesArray.IsArray()) {
        LX(ERROR, "Engines config element is not a JSON array.");
        return false;
    }

    for (rapidjson::Value::ConstValueIterator iterator = enginesArray.Begin(); iterator != enginesArray.End();
         ++iterator) {
        parseEngineObject(iterator, config);
    }

    printConfig(*config);

    return true;
}

}  // namespace wakeword
}  // namespace audioManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
