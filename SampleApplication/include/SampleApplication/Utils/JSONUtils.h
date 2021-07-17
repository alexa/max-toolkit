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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UTILS_JSONUTILS_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UTILS_JSONUTILS_H_

#include <string>

#include <rapidjson/document.h>

namespace multiAgentExperience {
namespace sampleApplication {
namespace utils {

/**
 * Utility function to perform a rapidjson parse on a JSON string.
 *
 * @param unparsedText The string to be parsed.
 * @param document [out] The rapidjson document if successfully parsed.
 * @return Whether the parse was successful.
 */
bool performInitialJSONParse(const std::string& unparsedText, rapidjson::Document* document);

}  // namespace utils
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UTILS_JSONUTILS_H_
