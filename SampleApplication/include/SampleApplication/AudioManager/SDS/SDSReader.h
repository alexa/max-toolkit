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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_SDS_SDSREADER_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_SDS_SDSREADER_H_

#include <memory>
#include <mutex>

#include <AVSCommon/AVS/AudioInputStream.h>

#include <MultiAgentExperience/Audio/AudioFormat.h>
#include <MultiAgentExperience/Audio/AudioReaderInterface.h>

namespace multiAgentExperience {
namespace sampleApplication {
namespace audioManager {
namespace sds {

/**
 * A wrapper class for an AVS SDK SDS Reader.
 */
class SDSReader : public multiAgentExperience::audio::AudioReaderInterface {
public:
    /**
     * Constructor.
     *
     * @param readerName Name of the audio reader
     * @param audioFormat Data format of the audio reader
     * @param reader Underlying AVS SDS reader
     * @param enabled Flag to indicate if the audio is enabled or disabled
     */
    SDSReader(
        const std::string& readerName,
        const multiAgentExperience::audio::AudioFormat& audioFormat,
        std::shared_ptr<alexaClientSDK::avsCommon::avs::AudioInputStream::Reader> reader,
        bool enabled);

    /**
     * Destructor.
     */
    ~SDSReader() override;

    /// @name AudioReaderInterface method overrides.
    /// @{
    multiAgentExperience::audio::AudioFormat getAudioFormat() const override;

    ssize_t read(void* buf, size_t nBytes) override;

    void close() override;

    void seekToNow() override;
    /// @}

private:
    /// The name of this reader.
    const std::string m_readerName;
    /// The audio format we shall use.
    const multiAgentExperience::audio::AudioFormat m_audioFormat;
    /// The SDS reader handle.
    std::shared_ptr<alexaClientSDK::avsCommon::avs::AudioInputStream::Reader> m_sdsReader;
    /// underlying SDS Reader uses "words" instead of "bytes" for buffer
    const size_t m_wordSize;
    /// Whether this reader is enabled.
    bool m_isReaderEnabled;
    /// Protects m_isReaderEnabled and m_sdsReader->seek().
    std::mutex m_mutex;
};

}  // namespace sds
}  // namespace audioManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_SDS_SDSREADER_H_
