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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UTILS_AVSSDK_CUSTOMLOGGER_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UTILS_AVSSDK_CUSTOMLOGGER_H_

#include <AVSCommon/Utils/Logger/Logger.h>

namespace multiAgentExperience {
namespace sampleApplication {
namespace utils {
namespace avssdk {

/**
 * A Logger which specializes the AVS SDK Logger interface, allowing us to then re-direct AVS SDK logs as we wish.
 */
class CustomLogger : public alexaClientSDK::avsCommon::utils::logger::Logger {
public:
    /**
     * Constructor.
     */
    CustomLogger();

    /// @name Logger method overrides.
    /// @{
    void emit(
        alexaClientSDK::avsCommon::utils::logger::Level level,
        std::chrono::system_clock::time_point time,
        const char* threadMoniker,
        const char* text) override;
    /// @}
};

}  // namespace avssdk
}  // namespace utils
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UTILS_AVSSDK_CUSTOMLOGGER_H_
