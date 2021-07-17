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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AGENTMANAGER_COMPUTERAGENT_COMPUTERAUDIOREADER_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AGENTMANAGER_COMPUTERAGENT_COMPUTERAUDIOREADER_H_

#include <MultiAgentExperience/Audio/AudioReaderInterface.h>

#include <AVSCommon/AVS/AudioInputStream.h>

#include <memory>
#include <mutex>

namespace multiAgentExperience {
namespace sampleApplication {
namespace agentManager {
namespace computer {

namespace MAX = multiAgentExperience;

class ComputerAudioReader : public MAX::audio::AudioReaderInterface {
public:
    /**
     * Creates a reader to be used by the Computer Agent.
     *
     * @param audioFormat The audio format to be used.
     * @param sdsReader The AVS SDK SDS Reader to use for reading audio data.
     * @return A @c ComputerAudioReader if successful, otherwise nullptr.
     */
    static std::unique_ptr<ComputerAudioReader> create(
        const MAX::audio::AudioFormat& audioFormat,
        std::shared_ptr<alexaClientSDK::avsCommon::avs::AudioInputStream::Reader> sdsReader);

    /**
     * Destructor.
     */
    ~ComputerAudioReader();

    /// @name AudioReaderInterface methods.
    /// @{
    MAX::audio::AudioFormat getAudioFormat() const override;
    ssize_t read(void* buf, size_t nBytes) override;
    void seekToNow() override;
    void close() override;
    /// @}

private:
    /**
     * Constructor.
     *
     * @param audioFormat The audio format to use.
     * @param sdsReader The AVS SDK SDS Reader to use for reading audio data.
     */
    ComputerAudioReader(
        const MAX::audio::AudioFormat& audioFormat,
        std::shared_ptr<alexaClientSDK::avsCommon::avs::AudioInputStream::Reader> sdsReader);

    /// Our audio format.
    audio::AudioFormat m_audioFormat;
    /// Mutex for synchronization.
    std::mutex m_mutex;
    ///  Our AVS SDK SDS Reader.
    std::shared_ptr<alexaClientSDK::avsCommon::avs::AudioInputStream::Reader> m_sdsReader;
};

}  // namespace computer
}  // namespace agentManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AGENTMANAGER_COMPUTERAGENT_COMPUTERAUDIOREADER_H_
