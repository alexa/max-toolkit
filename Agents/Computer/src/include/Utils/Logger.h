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

#ifndef MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_UTILS_LOGGER_H_
#define MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_UTILS_LOGGER_H_

#include <MultiAgentExperience/Utils/Log.h>

#include <memory>

namespace multiAgentExperience {
namespace samples {
namespace agents {
namespace computer {
namespace utils {

// clang-format off
#ifndef NDEBUG
#define COMPUTER_AGENT_LOG_CRITICAL(COMPONENT, MODULE, FUNCTION, MESSAGE) utils::getLoggerInstance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{utils::getLoggerComponentName(), MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::CRITICAL, MESSAGE);
#define COMPUTER_AGENT_LOG_ERROR(COMPONENT, MODULE, FUNCTION, MESSAGE) utils::getLoggerInstance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{utils::getLoggerComponentName(), MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::ERROR, MESSAGE);
#define COMPUTER_AGENT_LOG_WARN(COMPONENT, MODULE, FUNCTION, MESSAGE) utils::getLoggerInstance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{utils::getLoggerComponentName(), MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::WARN, MESSAGE);
#define COMPUTER_AGENT_LOG_INFO(COMPONENT, MODULE, FUNCTION, MESSAGE) utils::getLoggerInstance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{utils::getLoggerComponentName(), MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::INFO, MESSAGE);
#define COMPUTER_AGENT_LOG_DEBUG0(COMPONENT, MODULE, FUNCTION, MESSAGE) utils::getLoggerInstance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{utils::getLoggerComponentName(), MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::DEBUG0, MESSAGE);
#define COMPUTER_AGENT_LOG_DEBUG1(COMPONENT, MODULE, FUNCTION, MESSAGE) utils::getLoggerInstance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{utils::getLoggerComponentName(), MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::DEBUG1, MESSAGE);
#define COMPUTER_AGENT_LOG_DEBUG2(COMPONENT, MODULE, FUNCTION, MESSAGE) utils::getLoggerInstance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{utils::getLoggerComponentName(), MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::DEBUG2, MESSAGE);
#define COMPUTER_AGENT_LOG_DEBUG3(COMPONENT, MODULE, FUNCTION, MESSAGE) utils::getLoggerInstance()->log(multiAgentExperience::utils::Log::LogEntryMetadata{utils::getLoggerComponentName(), MODULE, FUNCTION}, multiAgentExperience::utils::Log::Level::DEBUG3, MESSAGE);
#else
#define COMPUTER_AGENT_LOG_CRITICAL(COMPONENT, MODULE, FUNCTION, MESSAGE)
#define COMPUTER_AGENT_LOG_ERROR(COMPONENT, MODULE, FUNCTION, MESSAGE)
#define COMPUTER_AGENT_LOG_WARN(COMPONENT, MODULE, FUNCTION, MESSAGE)
#define COMPUTER_AGENT_LOG_INFO(COMPONENT, MODULE, FUNCTION, MESSAGE)
#define COMPUTER_AGENT_LOG_DEBUG0(COMPONENT, MODULE, FUNCTION, MESSAGE)
#define COMPUTER_AGENT_LOG_DEBUG1(COMPONENT, MODULE, FUNCTION, MESSAGE)
#define COMPUTER_AGENT_LOG_DEBUG2(COMPONENT, MODULE, FUNCTION, MESSAGE)
#define COMPUTER_AGENT_LOG_DEBUG3(COMPONENT, MODULE, FUNCTION, MESSAGE)
#endif
// clang-format on

void setLoggerComponentName(const std::string& name);
void setLoggerInstance(std::shared_ptr<multiAgentExperience::utils::Log> logger);

std::string getLoggerComponentName();
std::shared_ptr<multiAgentExperience::utils::Log> getLoggerInstance();

}  // namespace utils
}  // namespace computer
}  // namespace agents
}  // namespace samples
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_UTILS_LOGGER_H_
