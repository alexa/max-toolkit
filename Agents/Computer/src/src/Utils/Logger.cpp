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

#include "Utils/Logger.h"

namespace multiAgentExperience {
namespace samples {
namespace agents {
namespace computer {
namespace utils {

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
    return g_logger;
}

}  // namespace utils
}  // namespace computer
}  // namespace agents
}  // namespace samples
}  // namespace multiAgentExperience
