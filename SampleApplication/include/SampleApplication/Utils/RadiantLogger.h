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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UTILS_RADIANTLOGGER_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UTILS_RADIANTLOGGER_H_

#include <map>
#include <string>
#include <memory>

#include <MultiAgentExperience/Utils/Log.h>

namespace multiAgentExperience {
namespace sampleApplication {
namespace utils {

namespace MAX = multiAgentExperience;

/**
 * A logger which allows different levels for components which may invoke it. This is based around the
 * @c Log::LogEntryMetadata structure as defined within MAX. Applications may thereby adapt other library loggers to
 * this definition, allowing dynamic changing of the log level within such a metadata filter.
 */
class RadiantLogger : public multiAgentExperience::utils::Log {
public:
    /// Our definition for the MAX Sample Application component name to be used within Log metadata.
    static const std::string MAX_APP_COMPONENT_NAME;
    /// Our definition for the AVS SDK component name to be used within Log metadata.
    static const std::string AVS_SDK_COMPONENT_NAME;
    /// Our definition for the MAX Library component name to be used within Log metadata.
    static const std::string MAX_LIB_COMPONENT_NAME;
    /// Our definition for the Computer Agent component name to be used within Log metadata.
    static const std::string COMPUTER_AGENT_COMPONENT_NAME;

    /**
     * Method to acquire the logger instance, of which there must be only one in a given application.
     *
     * @return The logger instance.
     */
    static std::shared_ptr<RadiantLogger> instance();

    /**
     * Sets the log level for a component, identified by a string. If componentName does not match one of the
     * expected component names, then the request is ignored.
     *
     * @param componentName The component name that shall have the log level.
     * @param level The log level to use.
     */
    void setComponentLevel(const std::string& componentName, MAX::utils::Log::Level level);

    /// @name Log method overrides.
    /// @{
    void logHandler(const LogEntryMetadata& metadata, MAX::utils::Log::Level level, const std::string& text) override;
    /// @}

private:
    /// Our map of log levels per component.
    static std::map<std::string, MAX::utils::Log::Level> m_componentLevels;

    /// Mutex to contol access to the log levels.
    std::mutex m_mutex;
};

// clang-format off
#ifndef MAX_RADIANT_LOGGER_DISABLED
#define SAMPLE_APP_LOG_CRITICAL(COMPONENT, MODULE, FUNCTION, MESSAGE) utils::RadiantLogger::instance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{COMPONENT, MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::CRITICAL, MESSAGE);
#define SAMPLE_APP_LOG_ERROR(COMPONENT, MODULE, FUNCTION, MESSAGE) utils::RadiantLogger::instance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{COMPONENT, MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::ERROR, MESSAGE);
#define SAMPLE_APP_LOG_WARN(COMPONENT, MODULE, FUNCTION, MESSAGE) utils::RadiantLogger::instance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{COMPONENT, MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::WARN, MESSAGE);
#define SAMPLE_APP_LOG_INFO(COMPONENT, MODULE, FUNCTION, MESSAGE) utils::RadiantLogger::instance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{COMPONENT, MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::INFO, MESSAGE);
#define SAMPLE_APP_LOG_DEBUG0(COMPONENT, MODULE, FUNCTION, MESSAGE) utils::RadiantLogger::instance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{COMPONENT, MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::DEBUG0, MESSAGE);
#define SAMPLE_APP_LOG_DEBUG1(COMPONENT, MODULE, FUNCTION, MESSAGE) utils::RadiantLogger::instance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{COMPONENT, MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::DEBUG1, MESSAGE);
#define SAMPLE_APP_LOG_DEBUG2(COMPONENT, MODULE, FUNCTION, MESSAGE) utils::RadiantLogger::instance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{COMPONENT, MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::DEBUG2, MESSAGE);
#define SAMPLE_APP_LOG_DEBUG3(COMPONENT, MODULE, FUNCTION, MESSAGE) utils::RadiantLogger::instance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{COMPONENT, MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::DEBUG3, MESSAGE);
#else
#define SAMPLE_APP_LOG_CRITICAL(COMPONENT, MODULE, FUNCTION, MESSAGE)
#define SAMPLE_APP_LOG_ERROR(COMPONENT, MODULE, FUNCTION, MESSAGE)
#define SAMPLE_APP_LOG_WARN(COMPONENT, MODULE, FUNCTION, MESSAGE)
#define SAMPLE_APP_LOG_INFO(COMPONENT, MODULE, FUNCTION, MESSAGE)
#define SAMPLE_APP_LOG_DEBUG0(COMPONENT, MODULE, FUNCTION, MESSAGE)
#define SAMPLE_APP_LOG_DEBUG1(COMPONENT, MODULE, FUNCTION, MESSAGE)
#define SAMPLE_APP_LOG_DEBUG2(COMPONENT, MODULE, FUNCTION, MESSAGE)
#define SAMPLE_APP_LOG_DEBUG3(COMPONENT, MODULE, FUNCTION, MESSAGE)
#endif
// clang-format on

}  // namespace utils
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UTILS_RADIANTLOGGER_H_
