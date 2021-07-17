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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UTILS_STRINGUTILS_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UTILS_STRINGUTILS_H_

#include <string>
#include <vector>

#include <rapidjson/document.h>

namespace multiAgentExperience {
namespace sampleApplication {
namespace utils {

/**
 * Utility function to convert a string to lower case.
 *
 * @param input The string to be converted.
 * @return The converted string.
 */
std::string stringToLowerCase(const std::string& input);

/**
 * Utility function to convert a printf-style string signature, and its parameters, into a single std::string.
 *
 * @tparam Args The type parameter pack. Must be types which can convert to strings as snprintf requires.
 * @param format The c-style format string.
 * @param args The parameters which should be applied to the format string.
 * @return The formatted string, or empty string on error.
 */
template <typename... Args>
std::string stringFormat(const char* format, Args... args) {
    int length = std::snprintf(nullptr, 0, format, args...);
    if (length <= 0) {
        return "";
    }

    char* buffer = new char[length + 1];
    std::snprintf(buffer, length + 1, format, args...);
    std::string formattedString(buffer);
    delete[] buffer;

    return formattedString;
}

}  // namespace utils
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UTILS_STRINGUTILS_H_
