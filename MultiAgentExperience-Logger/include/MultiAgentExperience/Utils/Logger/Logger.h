/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_UTILS_LOGGER_LOGGER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_UTILS_LOGGER_LOGGER_H_

#include <MultiAgentExperience/Utils/Log.h>

#include <memory>

namespace multiAgentExperience {
namespace logger {

// clang-format off
#ifndef NDEBUG
#define MAX_LIBRARY_LOG_CRITICAL(COMPONENT, MODULE, FUNCTION, MESSAGE) logger::getLoggerInstance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{logger::getLoggerComponentName(), MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::CRITICAL, MESSAGE);
#define MAX_LIBRARY_LOG_ERROR(COMPONENT, MODULE, FUNCTION, MESSAGE) logger::getLoggerInstance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{logger::getLoggerComponentName(), MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::ERROR, MESSAGE);
#define MAX_LIBRARY_LOG_WARN(COMPONENT, MODULE, FUNCTION, MESSAGE) logger::getLoggerInstance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{logger::getLoggerComponentName(), MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::WARN, MESSAGE);
#define MAX_LIBRARY_LOG_INFO(COMPONENT, MODULE, FUNCTION, MESSAGE) logger::getLoggerInstance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{logger::getLoggerComponentName(), MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::INFO, MESSAGE);
#define MAX_LIBRARY_LOG_DEBUG0(COMPONENT, MODULE, FUNCTION, MESSAGE) logger::getLoggerInstance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{logger::getLoggerComponentName(), MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::DEBUG0, MESSAGE);
#define MAX_LIBRARY_LOG_DEBUG1(COMPONENT, MODULE, FUNCTION, MESSAGE) logger::getLoggerInstance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{logger::getLoggerComponentName(), MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::DEBUG1, MESSAGE);
#define MAX_LIBRARY_LOG_DEBUG2(COMPONENT, MODULE, FUNCTION, MESSAGE) logger::getLoggerInstance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{logger::getLoggerComponentName(), MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::DEBUG2, MESSAGE);
#define MAX_LIBRARY_LOG_DEBUG3(COMPONENT, MODULE, FUNCTION, MESSAGE) logger::getLoggerInstance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{logger::getLoggerComponentName(), MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::DEBUG3, MESSAGE);
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

/// Please don't change the signature of these functions without discussion
void setLoggerComponentName(const std::string& name);
void setLoggerInstance(std::shared_ptr<multiAgentExperience::utils::Log> logger);

std::string getLoggerComponentName();
std::shared_ptr<multiAgentExperience::utils::Log> getLoggerInstance();

}  // namespace logger
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_UTILS_LOGGER_LOGGER_H_
