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

#include "SampleApplication/AudioManager/Microphone/MicrophoneConfig.h"

#include <AVSCommon/Utils/JSON/JSONUtils.h>

#include "SampleApplication/Utils/RadiantLogger.h"

/// JSON key to get the global microphone element from the MAX Config file.
static const std::string MAX_CONFIG_JSON_MICROPHONE_OBJECT_KEY = "microphone";

/// JSON key to get the suggested latency in seconds from the microphone element from the MAX Config file.
static const std::string MAX_CONFIG_JSON_MICROPHONE_SUGGESTED_LATENCY_SECONDS_KEY = "suggestedLatencySeconds";

namespace multiAgentExperience {
namespace sampleApplication {
namespace audioManager {
namespace microphone {

/// Metadata parameters that will be passed into our logging system.
static const std::string MODULE_TAG("MicrophoneConfig");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, MODULE_TAG, __func__, message)

using namespace rapidjson;
using namespace alexaClientSDK::avsCommon::utils::json;

/**
 * Utility function to print the microphone details.
 *
 * @param format The format to be printed.
 */
static void printConfig(MicrophoneConfig* config) {
    LX(DEBUG3, "************************** ");
    LX(DEBUG3, "* MICROPHONE CONFIG");
    LX(DEBUG3, "* suggestedLatencySeconds:" + std::to_string(config->suggestedLatencySeconds));
    LX(DEBUG3, "************************** ");
}

MicrophoneConfig::MicrophoneConfig() : suggestedLatencySeconds{0} {
}

bool parseJSONConfig(const rapidjson::Document& document, MicrophoneConfig* config) {
    if (!config) {
        LX(ERROR, "nullptr config.");
        return false;
    }

    Value::ConstMemberIterator microphoneIter;
    if (!jsonUtils::findNode(document, MAX_CONFIG_JSON_MICROPHONE_OBJECT_KEY, &microphoneIter)) {
        LX(ERROR, "missing microphone object.");
        return false;
    }

    double suggestedLatencySeconds = 0;
    if (!jsonUtils::retrieveValue(
            microphoneIter->value,
            MAX_CONFIG_JSON_MICROPHONE_SUGGESTED_LATENCY_SECONDS_KEY,
            &suggestedLatencySeconds)) {
        LX(ERROR, "missing log level option.");
        return false;
    }

    config->suggestedLatencySeconds = suggestedLatencySeconds;

    printConfig(config);

    return true;
}

}  // namespace microphone
}  // namespace audioManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
