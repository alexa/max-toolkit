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

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_UTILS_LOG_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_UTILS_LOG_H_

#include <chrono>
#include <iomanip>
#include <iostream>
#include <mutex>

namespace multiAgentExperience {
namespace utils {

namespace maxUtils = multiAgentExperience::utils;

/**
 * Logger utility.
 */
class Log {
public:
    /**
     * The available log levels.
     */
    enum Level { NONE, CRITICAL, ERROR, WARN, INFO, DEBUG0, DEBUG1, DEBUG2, DEBUG3 };

    struct LogEntryMetadata {
        std::string componentName;
        std::string moduleName;
        std::string functionName;
    };

    Log() : m_level{Log::WARN} {
    }

    virtual ~Log() = default;

    static bool stringToLevel(const std::string& levelName, Level* level);
    static std::string levelToShortString(Level level);

    void critical(const LogEntryMetadata& metadata, const std::string& text) {
        log(metadata, Log::CRITICAL, text);
    }
    void error(const LogEntryMetadata& metadata, const std::string& text) {
        log(metadata, Log::ERROR, text);
    }
    void warning(const LogEntryMetadata& metadata, const std::string& text) {
        log(metadata, Log::WARN, text);
    }
    void info(const LogEntryMetadata& metadata, const std::string& text) {
        log(metadata, Log::INFO, text);
    }
    void debug0(const LogEntryMetadata& metadata, const std::string& text) {
        log(metadata, Log::DEBUG0, text);
    }
    void debug1(const LogEntryMetadata& metadata, const std::string& text) {
        log(metadata, Log::DEBUG1, text);
    }
    void debug2(const LogEntryMetadata& metadata, const std::string& text) {
        log(metadata, Log::DEBUG2, text);
    }
    void debug3(const LogEntryMetadata& metadata, const std::string& text) {
        log(metadata, Log::DEBUG3, text);
    }

    void setLogLevel(const Level& level) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_level = level;
    }

    void log(const LogEntryMetadata& metadata, multiAgentExperience::utils::Log::Level level, const std::string& text) {
        std::lock_guard<std::mutex> lock(m_mutex);
        logHandler(metadata, level, text);
    }

    virtual void logHandler(
        const LogEntryMetadata& metadata,
        multiAgentExperience::utils::Log::Level level,
        const std::string& text) = 0;

protected:
    Log::Level m_level;

private:
    std::mutex m_mutex;
};

inline bool Log::stringToLevel(const std::string& levelName, Level* level) {
    if (!level) {
        return false;
    }

    if (levelName == "NONE") {
        *level = Level::NONE;
        return true;
    }
    if (levelName == "CRITICAL") {
        *level = Level::CRITICAL;
        return true;
    }
    if (levelName == "ERROR") {
        *level = Level::ERROR;
        return true;
    }
    if (levelName == "WARN") {
        *level = Level::WARN;
        return true;
    }
    if (levelName == "INFO") {
        *level = Level::INFO;
        return true;
    }
    if (levelName == "DEBUG0") {
        *level = Level::DEBUG0;
        return true;
    }
    if (levelName == "DEBUG1") {
        *level = Level::DEBUG1;
        return true;
    }
    if (levelName == "DEBUG2") {
        *level = Level::DEBUG2;
        return true;
    }
    if (levelName == "DEBUG3") {
        *level = Level::DEBUG3;
        return true;
    }

    return false;
}

inline std::string Log::levelToShortString(Level level) {
    switch (level) {
        case Level::NONE:
            return "N";
            break;
        case Level::CRITICAL:
            return "C";
            break;
        case Level::ERROR:
            return "E";
            break;
        case Level::WARN:
            return "W";
            break;
        case Level::INFO:
            return "I";
            break;
        case Level::DEBUG0:
            return "0";
            break;
        case Level::DEBUG1:
            return "1";
            break;
        case Level::DEBUG2:
            return "2";
            break;
        case Level::DEBUG3:
            return "3";
            break;
    }

    return "N";
}

inline std::ostream& operator<<(std::ostream& stream, Log::Level level) {
    switch (level) {
        case Log::Level::NONE:
            stream << "NONE";
            return stream;
        case Log::Level::CRITICAL:
            stream << "CRITICAL";
            return stream;
        case Log::Level::ERROR:
            stream << "ERROR";
            return stream;
        case Log::Level::WARN:
            stream << "WARN";
            return stream;
        case Log::Level::INFO:
            stream << "INFO";
            return stream;
        case Log::Level::DEBUG0:
            stream << "DEBUG0";
            return stream;
        case Log::Level::DEBUG1:
            stream << "DEBUG1";
            return stream;
        case Log::Level::DEBUG2:
            stream << "DEBUG2";
            return stream;
        case Log::Level::DEBUG3:
            stream << "DEBUG3";
            return stream;
    }
    stream << "UNKNOWN_LOG_LEVEL";
    return stream;
}

}  // namespace utils
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_UTILS_LOG_H_
