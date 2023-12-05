/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <Log/AppLogger.h>
#include <sstream>

#include "AVSCommon/Utils/Logger/ThreadMoniker.h"
#include "AVSCommon/Utils/Logger/Level.h"

namespace multiAgentExperience {
namespace integrationApp {
namespace log {

using namespace alexaClientSDK::avsCommon::utils::logger;

std::map<std::string, multiAgentExperience::utils::Log::Level> AppLogger::m_componentLevels;

const std::string AppLogger::MAX_LIB_COMPONENT_NAME = "MAX_LIB";

AppLogger& AppLogger::instance() {
    static AppLogger instance;

    return instance;
}

Level getAVSLoggerLevel(multiAgentExperience::utils::Log::Level level) {
    switch(level) {
        //NONE, CRITICAL, ERROR, WARN, INFO, DEBUG0, DEBUG1, DEBUG2, DEBUG3
        case multiAgentExperience::utils::Log::Level::NONE:
            return Level::NONE;
        case multiAgentExperience::utils::Log::Level::CRITICAL:
            return Level::CRITICAL;
        case multiAgentExperience::utils::Log::Level::ERROR:
            return Level::ERROR;
        case multiAgentExperience::utils::Log::Level::WARN:
            return Level::WARN;
        case multiAgentExperience::utils::Log::Level::INFO:
            return Level::INFO;
        case multiAgentExperience::utils::Log::Level::DEBUG0:
            return Level::DEBUG0;
        case multiAgentExperience::utils::Log::Level::DEBUG1:
            return Level::DEBUG1;
        case multiAgentExperience::utils::Log::Level::DEBUG2:
            return Level::DEBUG2;
        case multiAgentExperience::utils::Log::Level::DEBUG3:
            return Level::DEBUG3;
        default:
            return Level::UNKNOWN;
    }
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

    //std::cout << ss.str();
    m_logger->emit(getAVSLoggerLevel(level), std::chrono::system_clock::now(), ThreadMoniker::getThisThreadMoniker().c_str(), ss.str().c_str());
}

void AppLogger::setComponentLevel(const std::string& componentName, multiAgentExperience::utils::Log::Level level) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_componentLevels[componentName] = level;
}

} // namespace log
} // namespace integrationApp
} // namespace multiAgentExperience
