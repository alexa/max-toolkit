/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Logger.h"

namespace multiAgentExperience {
namespace logger {

static const std::string DEFAULT_LOGGER_NAME = "MAX_DEFAULT_LOGGER";

Logger::Logger() : m_outputStream{std::clog} {
}

void Logger::logHandler(
    const LogEntryMetadata& metadata,
    multiAgentExperience::utils::Log::Level level,
    const std::string& text) {
  if (level <= m_level) {
    auto now = std::chrono::system_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    auto timer = std::chrono::system_clock::to_time_t(now);

    std::tm* bt = std::localtime(&timer);

    m_outputStream << std::put_time(bt, "%F %T");
    m_outputStream << '.' << std::setfill('0') << std::setw(3) << ms.count();
    m_outputStream << " " << levelToShortString(level) << " ";
    m_outputStream << metadata.componentName << ":" << metadata.moduleName << ":" << metadata.functionName << " ";
    m_outputStream << text << std::endl;
  }
}

static std::shared_ptr<multiAgentExperience::utils::Log> g_logger;
static std::string g_componentName;

void setLoggerComponentName(const std::string& name) {
  g_componentName = name;
}

void setLoggerInstance(std::shared_ptr<multiAgentExperience::utils::Log> logger) {
  g_logger = logger;
}

std::string getLoggerComponentName() {
  return g_componentName;
}

std::shared_ptr<multiAgentExperience::utils::Log> getLoggerInstance() {
  if (!g_logger) {
    setLoggerInstance(std::make_shared<Logger>());
    setLoggerComponentName(DEFAULT_LOGGER_NAME);
    MAX_LIBRARY_LOG_WARN("utils", "Logger", __func__, "No logger supplied, creating default logger");
  }
  return g_logger;
}

}  // namespace logger
}  // namespace multiAgentExperience
