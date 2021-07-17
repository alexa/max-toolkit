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

#include "SampleApplication/Utils/AVSSDK/CustomLogger.h"

#include <algorithm>
#include <sstream>

#include "SampleApplication/Utils/RadiantLogger.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace utils {
namespace avssdk {

using MaxLogLevel = multiAgentExperience::utils::Log::Level;
using AvsLogLevel = alexaClientSDK::avsCommon::utils::logger::Level;

/// Metadata parameters that will be passed into our logging system.
static const std::string MODULE_TAG("CustomLogger");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::AVS_SDK_COMPONENT_NAME, MODULE_TAG, __func__, message)

/**
 * Utility function to convert an AVS SDK log level to a MAX log level. Note that MAX log levels stop at DEBUG3, and
 * so AVS SDK log levels DEBUG4-DEBUG9 convert to that maximum.
 *
 * @param logLevel The log level to be converted.
 * @return The converted log level.
 */
static MaxLogLevel avsLogLevelToMaxLogLevel(AvsLogLevel logLevel) {
    switch (logLevel) {
        case AvsLogLevel::UNKNOWN:
            return MaxLogLevel::NONE;
            break;
        case AvsLogLevel::NONE:
            return MaxLogLevel::NONE;
            break;
        case AvsLogLevel::CRITICAL:
            return MaxLogLevel::CRITICAL;
            break;
        case AvsLogLevel::ERROR:
            return MaxLogLevel::ERROR;
            break;
        case AvsLogLevel::WARN:
            return MaxLogLevel::WARN;
            break;
        case AvsLogLevel::INFO:
            return MaxLogLevel::INFO;
            break;
        case AvsLogLevel::DEBUG0:
            return MaxLogLevel::DEBUG0;
            break;
        case AvsLogLevel::DEBUG1:
            return MaxLogLevel::DEBUG1;
            break;
        case AvsLogLevel::DEBUG2:
            return MaxLogLevel::DEBUG2;
            break;
        case AvsLogLevel::DEBUG3:
            return MaxLogLevel::DEBUG3;
            break;
        case AvsLogLevel::DEBUG4:
            return MaxLogLevel::DEBUG3;
            break;
        case AvsLogLevel::DEBUG5:
            return MaxLogLevel::DEBUG3;
            break;
        case AvsLogLevel::DEBUG6:
            return MaxLogLevel::DEBUG3;
            break;
        case AvsLogLevel::DEBUG7:
            return MaxLogLevel::DEBUG3;
            break;
        case AvsLogLevel::DEBUG8:
            return MaxLogLevel::DEBUG3;
            break;
        case AvsLogLevel::DEBUG9:
            return MaxLogLevel::DEBUG3;
            break;
    }

    return MaxLogLevel::NONE;
}

CustomLogger::CustomLogger() : Logger(AvsLogLevel::DEBUG9) {
}

/**
 * A utility function to test if a false-positive error is within the given string.
 * @param testString The string to test.
 * @return Whether the string contains a false-positive message.
 */
static bool containsFalsePositiveErrors(const std::string& testString) {
    std::set<std::string> falsePositiveErrorStrings;

    // This is a benign error from the AVS SDK FocusManager which we may ignore.
    falsePositiveErrorStrings.insert("E:FocusManager:releaseChannelHelper");

    for (auto falsePositive : falsePositiveErrorStrings) {
        if (std::string::npos != testString.find(falsePositive)) {
            return true;
        }
    }

    return false;
}

void CustomLogger::emit(
    alexaClientSDK::avsCommon::utils::logger::Level level,
    std::chrono::system_clock::time_point time,
    const char* threadMoniker,
    const char* text) {
    auto convertedLogLevel = avsLogLevelToMaxLogLevel(level);

    char logLevelChar = alexaClientSDK::avsCommon::utils::logger::convertLevelToChar(level);
    std::stringstream ss;
    ss << logLevelChar << ":" << text;

    // drop our log level from ERROR if it's a false-positive.
    if (containsFalsePositiveErrors(ss.str())) {
        ss << " (FALSE POSITIVE ERROR TRACE DETECTED BY LOGGER)";
        convertedLogLevel = MaxLogLevel::DEBUG3;
    }

    switch (convertedLogLevel) {
        case MaxLogLevel::NONE:
            // no-op
            break;
        case MaxLogLevel::CRITICAL:
            LX(CRITICAL, ss.str());
            break;
        case MaxLogLevel::ERROR:
            LX(ERROR, ss.str());
            break;
        case MaxLogLevel::WARN:
            LX(WARN, ss.str());
            break;
        case MaxLogLevel::INFO:
            LX(INFO, ss.str());
            break;
        case MaxLogLevel::DEBUG0:
            LX(DEBUG0, ss.str());
            break;
        case MaxLogLevel::DEBUG1:
            LX(DEBUG1, ss.str());
            break;
        case MaxLogLevel::DEBUG2:
            LX(DEBUG2, ss.str());
            break;
        case MaxLogLevel::DEBUG3:
            LX(DEBUG3, ss.str());
            break;
    }
}

}  // namespace avssdk
}  // namespace utils
}  // namespace sampleApplication
}  // namespace multiAgentExperience
