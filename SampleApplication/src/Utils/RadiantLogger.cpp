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

#include "SampleApplication/Utils/RadiantLogger.h"

#include <iostream>
#include <sstream>

namespace multiAgentExperience {
namespace sampleApplication {
namespace utils {

// define our class static members.
std::map<std::string, multiAgentExperience::utils::Log::Level> RadiantLogger::m_componentLevels;
const std::string RadiantLogger::MAX_APP_COMPONENT_NAME = "MAX_APP";
const std::string RadiantLogger::AVS_SDK_COMPONENT_NAME = "AVS_SDK";
const std::string RadiantLogger::MAX_LIB_COMPONENT_NAME = "MAX_LIB";
const std::string RadiantLogger::COMPUTER_AGENT_COMPONENT_NAME = "COMPUTER_AGENT";

std::shared_ptr<RadiantLogger> RadiantLogger::instance() {
    static std::mutex mutex;
    static std::shared_ptr<RadiantLogger> instance;

    std::lock_guard<std::mutex> lock(mutex);
    if (!instance) {
        instance = std::make_shared<RadiantLogger>();
    }

    return instance;
}

void RadiantLogger::logHandler(
    const RadiantLogger::LogEntryMetadata& metadata,
    multiAgentExperience::utils::Log::Level level,
    const std::string& text) {
    if (m_componentLevels.find(metadata.componentName) == m_componentLevels.end()) {
        std::cout << "RadiantLogger::log : metadata component " << metadata.componentName
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

void RadiantLogger::setComponentLevel(const std::string& componentName, multiAgentExperience::utils::Log::Level level) {
    if ((RadiantLogger::MAX_APP_COMPONENT_NAME != componentName) &&
        (RadiantLogger::AVS_SDK_COMPONENT_NAME != componentName) &&
        (RadiantLogger::MAX_LIB_COMPONENT_NAME != componentName) &&
        (RadiantLogger::COMPUTER_AGENT_COMPONENT_NAME != componentName)) {
        std::cout << "RadiantLogger::setComponentLevel : Unhandled component name, ignoring:" << componentName
                  << std::endl;
        return;
    }

    std::lock_guard<std::mutex> lock(m_mutex);
    m_componentLevels[componentName] = level;
}

}  // namespace utils
}  // namespace sampleApplication
}  // namespace multiAgentExperience
