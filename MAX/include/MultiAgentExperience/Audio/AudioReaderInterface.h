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

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_AUDIO_AUDIOREADERINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_AUDIO_AUDIOREADERINTERFACE_H_

#include <chrono>
#include <memory>

#include "MultiAgentExperience/Audio/AudioFormat.h"

namespace multiAgentExperience {
namespace audio {

/**
 * Provide audio data (such as user speech) to the requester.
 */
class AudioReaderInterface {
public:
    /**
     * Destructor.
     */
    virtual ~AudioReaderInterface() = default;

    /**
     * Get the audio format of the data
     *
     * @return AudioFormat The format of audio
     */
    virtual AudioFormat getAudioFormat() const = 0;

    /**
     * Reads audio data from the underlying stream and copies it to the provided buffer.
     *
     * @param buf A buffer to copy the consumed data to.  This buffer must be large enough to hold @c nBytes bytes
     * @param nBytes The maximum number of bytes to copy
     * @param timeout The maximum time to wait for data.  If this parameter is zero,
     *     there is no timeout and blocking reads will wait forever.
     * @return ssize_t The number of @c nBytes bytes copied if data was consumed.
     * @retval 0 if the reader is disabled
     * @retval -1 if the data requested has been overwritten and is invalid
     * @retval -3 if no data becomes available before the specified timeout
     * @retval -4 if any parameter is invalid
     */
    virtual ssize_t read(void* buf, size_t nBytes) = 0;

    /**
     * Seeks the underlying data to now.
     *
     * TODO: This will be removed in favor of a more general way of handling audio. VII-2020.
     */
    virtual void seekToNow() = 0;

    /// Close the reader. No further read possible.
    virtual void close() = 0;
};

}  // namespace audio
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_AUDIO_AUDIOREADERINTERFACE_H_
