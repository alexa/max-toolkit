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

#include "SampleApplication/UIManager/ConsolePrinter.h"

#include <algorithm>
#include <iostream>
#include <sstream>

#include "SampleApplication/Utils/RadiantLogger.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace uiManager {

/// Metadata parameters that will be passed into our logging system.
static const std::string MODULE_TAG("ConsolePrinter");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, MODULE_TAG, __func__, message)

/// Controls padding length in our pretty print function.
static const size_t PRETTY_PRINT_PADDING_LENGTH = 6;
static const size_t PRETTY_PRINT_LINE_MAX_LENGTH = 79;

void ConsolePrinter::print(const std::string& message) {
    LX(DEBUG3, "");

    std::lock_guard<std::mutex> lock(m_mutex);
    std::cout << message;
}

void ConsolePrinter::prettyPrint(const std::string& message, const char decorationCharacter) {
    LX(DEBUG3, "");

    prettyPrint(std::vector<std::string>{message}, decorationCharacter);
}

void ConsolePrinter::prettyPrint(const std::vector<std::string>& message, const char decorationCharacter) {
    LX(DEBUG3, "");

    size_t maxLength = 0;
    for (auto& line : message) {
        maxLength = std::max(line.size(), maxLength);
    }

    const std::string messageBorder(PRETTY_PRINT_LINE_MAX_LENGTH, decorationCharacter);
    std::stringstream ss;
    ss << messageBorder << std::endl;

    auto padBegin = std::string(1, decorationCharacter);
    padBegin.append(PRETTY_PRINT_PADDING_LENGTH, ' ');
    for (auto& line : message) {
        std::string trailingSpaces =
            std::string(PRETTY_PRINT_LINE_MAX_LENGTH - (2 + PRETTY_PRINT_PADDING_LENGTH + line.size()), ' ');
        ss << padBegin << line << trailingSpaces << decorationCharacter << std::endl;
    }

    ss << messageBorder << std::endl;
    print(ss.str());
}

}  // namespace uiManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
