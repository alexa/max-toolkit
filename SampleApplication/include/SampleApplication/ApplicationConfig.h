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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UTILS_APPLICATIONCONFIG_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UTILS_APPLICATIONCONFIG_H_

#include <map>
#include <ostream>
#include <string>
#include <vector>

#include <rapidjson/document.h>

#include <MultiAgentExperience/Utils/Log.h>

namespace multiAgentExperience {
namespace sampleApplication {

namespace MAX = multiAgentExperience;

/**
 * A struct that captures the top-level application configuration.
 */
struct ApplicationConfig {
    /**
     * Constructor.
     *
     * @param defaultLevel A default value for our log level.
     */
    ApplicationConfig(MAX::utils::Log::Level defaultLevel);

    /// The global log level setting for the application.
    MAX::utils::Log::Level globalLogLevel;
    /// Per-component overrides for the global log level.
    std::map<std::string, MAX::utils::Log::Level> componentOverrides;
};

/**
 * Utility function to acquire the MAX log level for the application. If no override is set, the global value is
 * returned.
 *
 * @param config The config object to be used.
 * @return The log level.
 */
MAX::utils::Log::Level getApplicationLogLevel(const ApplicationConfig& config);

/**
 * Utility function to acquire the MAX log level for the MAX Library. If no override is set, the global value is
 * returned.
 *
 * @param config The config object to be used.
 * @return The log level.
 */
MAX::utils::Log::Level getMAXLogLevel(const ApplicationConfig& config);

/**
 * Utility function to acquire the MAX log level for the AVS SDK. If no override is set, the global value is
 * returned.
 *
 * @param config The config object to be used.
 * @return The log level.
 */
MAX::utils::Log::Level getAVSSDKLogLevel(const ApplicationConfig& config);

/**
 * Utility function to acquire the MAX log level for the Computer agent. If no override is set, the global value is
 * returned.
 *
 * @param config The config object to be used.
 * @return The log level.
 */
MAX::utils::Log::Level getComputerAgentLogLevel(const ApplicationConfig& config);

/**
 * A utility function to parse a given rapidjson document and produce an @c ApplicationConfig object.
 *
 * @param document The rapidjson document.
 * @param config [out] The config object to be set.
 * @return Whether the parse was successful.
 */
bool parseJSONConfig(const rapidjson::Document& document, ApplicationConfig* config);

}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UTILS_APPLICATIONCONFIG_H_
