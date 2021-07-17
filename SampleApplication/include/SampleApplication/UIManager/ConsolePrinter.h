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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UIMANAGER_CONSOLEPRINTER_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UIMANAGER_CONSOLEPRINTER_H_

#include <mutex>
#include <string>
#include <vector>

namespace multiAgentExperience {
namespace sampleApplication {
namespace uiManager {

/**
 * A simple class which can print text to the console in a thread-safe manner.
 */
class ConsolePrinter {
public:
    /**
     * Prints a message to the console as-is.
     *
     * @param message The message to be printed.
     */
    void print(const std::string& message);

    /**
     * Prints a message surrounded by a box populated with the provided decoration character.
     *
     * @param message The message to be printed.
     * @param decorationCharacter The decoration character to use.
     */
    void prettyPrint(const std::string& message, const char decorationCharacter = '#');

    /**
     * Prints a multi-line message surrounded by a box populated with the provided decoration character.
     *
     * @param message The multi-line message to be printed.
     * @param decorationCharacter The decoration character to use.
     */
    void prettyPrint(const std::vector<std::string>& message, const char decorationCharacter = '#');

private:
    /// Our mutex for thread-safety.
    std::mutex m_mutex;
};

}  // namespace uiManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UIMANAGER_CONSOLEPRINTER_H_
