/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_INTEGRATION_APP_APPLOGGER_H
#define MULTIAGENTEXPERIENCE_INTEGRATION_APP_APPLOGGER_H

#include <map>
#include <MultiAgentExperience/Utils/Log.h>
#include <memory>

namespace multiAgentExperience {
namespace integrationApp {
namespace log {

class AppLogger : public utils::Log {
public:
    /// Our definition for the MAX Sample Application component name to be used within Log metadata.
    static const std::string MAX_APP_COMPONENT_NAME;
    /// Our definition for the MAX Library component name to be used within Log metadata.
    static const std::string MAX_LIB_COMPONENT_NAME;

    /**
     * Method to acquire the logger instance, of which there must be only one in a given application.
     *
     * @return The logger instance.
     */
    static AppLogger& instance();

    /**
     * Sets the log level for a component, identified by a string. If componentName does not match one of the
     * expected component names, then the request is ignored.
     *
     * @param componentName The component name that shall have the log level.
     * @param level The log level to use.
     */
    void setComponentLevel(const std::string& componentName, utils::Log::Level level);

    /// @name Log method overrides.
    /// @{
    void logHandler(const LogEntryMetadata& metadata, utils::Log::Level level, const std::string& text) override;
    /// @}

private:
    static std::shared_ptr<utils::Log> m_AppLogger;

    /// Our map of log levels per component.
    static std::map<std::string, utils::Log::Level> m_componentLevels;

    /// Mutex to contol access to the log levels.
    std::mutex m_mutex;
};
} // namespace log
} // namespace integrationApp
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_INTEGRATION_APP_APPLOGGER_H
