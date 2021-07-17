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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UTILS_AUDIODATADIRECTACCESSINTERFACE_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UTILS_AUDIODATADIRECTACCESSINTERFACE_H_

#include <memory>

#include <AVSCommon/AVS/AudioInputStream.h>

namespace multiAgentExperience {
namespace sampleApplication {
namespace utils {

/**
 * This interface defines an explicit access point to a managed SDS buffer, and the creation of readers from it.
 */
class AudioDataDirectAccessInterface {
public:
    /**
     * Destructor.
     */
    virtual ~AudioDataDirectAccessInterface() = default;

    /**
     * Provides a handle to managed SDS buffer.
     *
     * @return A handle to managed SDS buffer.
     */
    virtual std::shared_ptr<alexaClientSDK::avsCommon::avs::AudioInputStream> getSDSHandle() = 0;

    /**
     * Provides a handle to a reader created from a managed SDS buffer.
     *
     * @return A handle to a reader created from a managed SDS buffer.
     */
    virtual std::shared_ptr<alexaClientSDK::avsCommon::avs::AudioInputStream::Reader> createSDSReader() = 0;
};

}  // namespace utils
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UTILS_AUDIODATADIRECTACCESSINTERFACE_H_
