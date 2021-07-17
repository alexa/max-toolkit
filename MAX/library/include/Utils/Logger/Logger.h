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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_UTILS_LOGGER_LOGGER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_UTILS_LOGGER_LOGGER_H_

#include <MultiAgentExperience/Utils/Log.h>

#include <memory>

namespace multiAgentExperience {
namespace library {
namespace utils {
namespace logger {

// clang-format off
#ifndef NDEBUG
#define MAX_LIBRARY_LOG_CRITICAL(COMPONENT, MODULE, FUNCTION, MESSAGE) utils::logger::getLoggerInstance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{utils::logger::getLoggerComponentName(), MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::CRITICAL, MESSAGE);
#define MAX_LIBRARY_LOG_ERROR(COMPONENT, MODULE, FUNCTION, MESSAGE) utils::logger::getLoggerInstance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{utils::logger::getLoggerComponentName(), MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::ERROR, MESSAGE);
#define MAX_LIBRARY_LOG_WARN(COMPONENT, MODULE, FUNCTION, MESSAGE) utils::logger::getLoggerInstance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{utils::logger::getLoggerComponentName(), MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::WARN, MESSAGE);
#define MAX_LIBRARY_LOG_INFO(COMPONENT, MODULE, FUNCTION, MESSAGE) utils::logger::getLoggerInstance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{utils::logger::getLoggerComponentName(), MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::INFO, MESSAGE);
#define MAX_LIBRARY_LOG_DEBUG0(COMPONENT, MODULE, FUNCTION, MESSAGE) utils::logger::getLoggerInstance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{utils::logger::getLoggerComponentName(), MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::DEBUG0, MESSAGE);
#define MAX_LIBRARY_LOG_DEBUG1(COMPONENT, MODULE, FUNCTION, MESSAGE) utils::logger::getLoggerInstance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{utils::logger::getLoggerComponentName(), MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::DEBUG1, MESSAGE);
#define MAX_LIBRARY_LOG_DEBUG2(COMPONENT, MODULE, FUNCTION, MESSAGE) utils::logger::getLoggerInstance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{utils::logger::getLoggerComponentName(), MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::DEBUG2, MESSAGE);
#define MAX_LIBRARY_LOG_DEBUG3(COMPONENT, MODULE, FUNCTION, MESSAGE) utils::logger::getLoggerInstance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{utils::logger::getLoggerComponentName(), MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::DEBUG3, MESSAGE);
#else
#define MAX_LIBRARY_LOG_CRITICAL(COMPONENT, MODULE, FUNCTION, MESSAGE)
#define MAX_LIBRARY_LOG_ERROR(COMPONENT, MODULE, FUNCTION, MESSAGE)
#define MAX_LIBRARY_LOG_WARN(COMPONENT, MODULE, FUNCTION, MESSAGE)
#define MAX_LIBRARY_LOG_INFO(COMPONENT, MODULE, FUNCTION, MESSAGE)
#define MAX_LIBRARY_LOG_DEBUG0(COMPONENT, MODULE, FUNCTION, MESSAGE)
#define MAX_LIBRARY_LOG_DEBUG1(COMPONENT, MODULE, FUNCTION, MESSAGE)
#define MAX_LIBRARY_LOG_DEBUG2(COMPONENT, MODULE, FUNCTION, MESSAGE)
#define MAX_LIBRARY_LOG_DEBUG3(COMPONENT, MODULE, FUNCTION, MESSAGE)
#endif
// clang-format on

/**
 *
 */
class Logger : public multiAgentExperience::utils::Log {
public:
    Logger();

    /// @name Log method overrides.
    /// @{
    void logHandler(
        const LogEntryMetadata& metadata,
        multiAgentExperience::utils::Log::Level level,
        const std::string& text) override;
    /// @}

private:
    std::ostream& m_outputStream;
};

void setLoggerComponentName(const std::string& name);
void setLoggerInstance(std::shared_ptr<multiAgentExperience::utils::Log> logger);

std::string getLoggerComponentName();
std::shared_ptr<multiAgentExperience::utils::Log> getLoggerInstance();

}  // namespace logger
}  // namespace utils
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_UTILS_LOGGER_LOGGER_H_
