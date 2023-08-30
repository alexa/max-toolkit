/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <Log/AppLogger.h>
#include <sstream>

namespace multiAgentExperience {
namespace integrationApp {
namespace log {

std::map<std::string, multiAgentExperience::utils::Log::Level> AppLogger::m_componentLevels;

const std::string AppLogger::MAX_LIB_COMPONENT_NAME = "MAX_LIB";

AppLogger& AppLogger::instance() {
    static AppLogger instance;

    return instance;
}

void AppLogger::logHandler(
        const AppLogger::LogEntryMetadata& metadata,
        multiAgentExperience::utils::Log::Level level,
        const std::string& text) {
    if (m_componentLevels.find(metadata.componentName) == m_componentLevels.end()) {
        std::cout << "AppLogger::log : metadata component " << metadata.componentName
                  << " not found, cannot log correctly. "
                  << " moduleName:" << metadata.moduleName << ", functionName:" << metadata.functionName
                  << ", message:" << text << std::endl;
        return;
    }
    if (level > m_componentLevels[metadata.componentName]) {
        return;
    }

    auto now = std::chrono::system_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    auto timer = std::chrono::system_clock::to_time_t(now);

    std::tm* bt = std::localtime(&timer);

    std::stringstream ss;
    ss << std::put_time(bt, "%F %T");
    ss << '.' << std::setfill('0') << std::setw(3) << ms.count();
    ss << " " << levelToShortString(level) << " ";
    ss << metadata.componentName << ":" << metadata.moduleName << ":" << metadata.functionName << " " << text
       << std::endl;

    std::cout << ss.str();
}

void AppLogger::setComponentLevel(const std::string& componentName, multiAgentExperience::utils::Log::Level level) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_componentLevels[componentName] = level;
}

} // namespace log
} // namespace integrationApp
} // namespace multiAgentExperience