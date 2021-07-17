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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UTILS_AVSSDK_AVSSDKUTILITIES_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UTILS_AVSSDK_AVSSDKUTILITIES_H_

#include "SampleApplication/Utils/AVSSDK/CustomLogger.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace utils {
namespace avssdk {

/**
 * Initializes the AVS SDK Libraries. Must be invoked before use of AVS SDK components.
 */
void initializeAVSSDK();

/**
 * Initializes the AVS SDK logging system, in particular by registering our own logger with its logging sink.
 * If this is not done, then AVS SDK shall log directly to the console based upon how it has been initialized.
 */
void initializeLogger();

}  // namespace avssdk
}  // namespace utils
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UTILS_AVSSDK_AVSSDKUTILITIES_H_
