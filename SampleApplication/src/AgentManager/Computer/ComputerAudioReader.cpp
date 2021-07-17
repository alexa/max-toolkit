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

#include "SampleApplication/AgentManager/Computer/ComputerAudioReader.h"

#include "SampleApplication/Utils/RadiantLogger.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace agentManager {
namespace computer {

namespace avs = alexaClientSDK::avsCommon::avs;

/// Metadata parameters that will be passed into our logging system.
static const std::string MODULE_TAG("ComputerAudioReader");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, MODULE_TAG, __func__, message)

std::unique_ptr<ComputerAudioReader> ComputerAudioReader::create(
    const audio::AudioFormat& audioFormat,
    std::shared_ptr<avs::AudioInputStream::Reader> sdsReader) {
    LX(DEBUG3, "");

    if (!sdsReader) {
        LX(ERROR, "SDS reader is nullptr.");
        return nullptr;
    }

    auto reader = std::unique_ptr<ComputerAudioReader>(new ComputerAudioReader(audioFormat, sdsReader));

    return reader;
}

ComputerAudioReader::ComputerAudioReader(
    const audio::AudioFormat& audioFormat,
    std::shared_ptr<avs::AudioInputStream::Reader> sdsReader) :
        m_audioFormat{audioFormat},
        m_sdsReader{sdsReader} {
    seekToNow();
}

ComputerAudioReader::~ComputerAudioReader() {
    close();
}

audio::AudioFormat ComputerAudioReader::getAudioFormat() const {
    return m_audioFormat;
}

ssize_t ComputerAudioReader::read(void* buf, size_t nBytes) {
    std::lock_guard<std::mutex> guard(m_mutex);
    if (!m_sdsReader) {
        LX(ERROR, "SDS reader is nullptr - cannot read.");
        return 0;
    }

    size_t wordsToRead = nBytes / m_audioFormat.wordsPerSample;
    auto wordsRead = m_sdsReader->read(buf, wordsToRead);
    return wordsRead;
}

void ComputerAudioReader::seekToNow() {
    std::lock_guard<std::mutex> guard(m_mutex);
    if (!m_sdsReader) {
        LX(ERROR, "SDS reader is nullptr - cannot seek to now.");
        return;
    }

    m_sdsReader->seek(0, avs::AudioInputStream::Reader::Reference::BEFORE_WRITER);
}

void ComputerAudioReader::close() {
    std::lock_guard<std::mutex> guard(m_mutex);

    if (m_sdsReader) {
        m_sdsReader->close();
        m_sdsReader = nullptr;
    }
}

}  // namespace computer
}  // namespace agentManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
