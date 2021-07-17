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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_MICROPHONEINTERFACE_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_MICROPHONEINTERFACE_H_

#include <MultiAgentExperience/Utils/Data/DataWriterInterface.h>

namespace multiAgentExperience {
namespace sampleApplication {
namespace audioManager {
namespace microphone {

/**
 * The microphone interface that shall be used by the MAX Sample Application.
 */
class MicrophoneInterface : public multiAgentExperience::utils::data::DataWriterInterface {
public:
    /**
     * Destructor.
     */
    virtual ~MicrophoneInterface() = default;

    /**
     * Start streaming data from the microphone.
     *
     * @return Whether the start was successful.
     */
    virtual bool startStreamingData() = 0;

    /**
     * Stop streaming data from the microphone.
     *
     * @return Whether the stop was successful.
     */
    virtual bool stopStreamingData() = 0;

    /**
     * When muted, all data returned from the microphone will be zeroed out.
     *
     * @param enabled true to mute the microphone, false to unmute
     */
    virtual void mute(bool enabled) = 0;

    /**
     * Queries if the microphone is muted
     *
     * @return Whether the microphone is muted
     */
    virtual bool isMuted() = 0;
};

}  // namespace microphone
}  // namespace audioManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_MICROPHONEINTERFACE_H_
