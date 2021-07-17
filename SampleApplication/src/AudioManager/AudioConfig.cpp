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

#include "SampleApplication/AudioManager/AudioConfig.h"

#include <AVSCommon/Utils/JSON/JSONUtils.h>

#include "SampleApplication/Utils/RadiantLogger.h"

/// JSON key to get the global audio format element from the MAX Config file.
static const std::string MAX_CONFIG_JSON_AUDIOFORMAT_OBJECT_KEY = "audioFormat";

/// JSON key to get the sample rate element within the audio format element from the MAX Config file.
static const std::string MAX_CONFIG_JSON_AUDIOFORMAT_SAMPLE_RATE_HZ_KEY = "sampleRateHz";

/// JSON key to get the input channels element within the audio format element from the MAX Config file.
static const std::string MAX_CONFIG_JSON_AUDIOFORMAT_NUM_INPUT_CHANNELS_KEY = "numInputChannels";

namespace multiAgentExperience {
namespace sampleApplication {
namespace audioManager {

/// Metadata parameters that will be passed into our logging system.
static const std::string MODULE_TAG("AudioConfig");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, MODULE_TAG, __func__, message)

using namespace rapidjson;
using namespace alexaClientSDK::avsCommon::utils::json;

/**
 * Utility function to print the audio format details.
 *
 * @param format The format to be printed.
 */
static void printConfig(const audio::AudioFormat& format) {
    LX(DEBUG3, "************************** ");
    LX(DEBUG3, "* AUDIO CONFIG");
    LX(DEBUG3, "* sampleRateHz:" + std::to_string(format.sampleRateHz));
    LX(DEBUG3, "* numInputChannels:" + std::to_string(format.numChannels));
    LX(DEBUG3, "************************** ");
}

bool parseJSONConfig(const rapidjson::Document& document, audio::AudioFormat* format) {
    if (!format) {
        LX(ERROR, "parseJSONConfigFailed : nullptr format");
        return false;
    }

    Value::ConstMemberIterator audioFormatIter;
    if (!jsonUtils::findNode(document, MAX_CONFIG_JSON_AUDIOFORMAT_OBJECT_KEY, &audioFormatIter)) {
        LX(ERROR, "parseJSONConfigFailed : missing audioFormatIter object");
        return false;
    }

    int64_t sampleRateHz = 0;
    if (!jsonUtils::retrieveValue(
            audioFormatIter->value, MAX_CONFIG_JSON_AUDIOFORMAT_SAMPLE_RATE_HZ_KEY, &sampleRateHz)) {
        LX(ERROR, "parseJSONConfigFailed : missing sampleRateHz value");
        return false;
    }

    int64_t numInputChannels = 0;
    if (!jsonUtils::retrieveValue(
            audioFormatIter->value, MAX_CONFIG_JSON_AUDIOFORMAT_NUM_INPUT_CHANNELS_KEY, &numInputChannels)) {
        LX(ERROR, "parseJSONConfigFailed : missing numInputChannels value");
        return false;
    }

    format->sampleRateHz = sampleRateHz;
    format->numChannels = numInputChannels;

    printConfig(*format);

    return true;
}

}  // namespace audioManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
