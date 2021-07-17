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

#include "SampleApplication/AudioManager/SDS/SDSReader.h"
#include "SampleApplication/Utils/RadiantLogger.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace audioManager {
namespace sds {

/// Metadata parameters that will be passed into our logging system.
static const std::string MODULE_TAG("JSONUtils");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, __func__, MODULE_TAG, message)

SDSReader::SDSReader(
    const std::string& readerName,
    const multiAgentExperience::audio::AudioFormat& audioFormat,
    std::shared_ptr<alexaClientSDK::avsCommon::avs::AudioInputStream::Reader> reader,
    bool enabled) :
        m_readerName{readerName},
        m_audioFormat{audioFormat},
        m_sdsReader{reader},
        m_wordSize{reader->getWordSize()},
        m_isReaderEnabled{enabled} {
}

SDSReader::~SDSReader() {
    close();
}

multiAgentExperience::audio::AudioFormat SDSReader::getAudioFormat() const {
    return m_audioFormat;
}

ssize_t SDSReader::read(void* buf, size_t nBytes) {
    std::lock_guard<std::mutex> guard(m_mutex);
    if (!m_isReaderEnabled) {
        LX(WARN, "Reader is not enabled, returning.");
        return 0;
    }

    if (!m_sdsReader) {
        LX(ERROR, "SDS Reader is nullptr, returning.");
        return 0;
    }

    // Convert bytes to words
    size_t nWords = nBytes / m_wordSize;
    ssize_t wordsRead = m_sdsReader->read(buf, nWords);
    if (wordsRead <= 0) {
        return wordsRead;
    }

    // Convert words to bytes
    return wordsRead * m_wordSize;
}

void SDSReader::seekToNow() {
    LX(DEBUG3, "");

    std::lock_guard<std::mutex> guard(m_mutex);

    if (m_sdsReader) {
        LX(DEBUG3, "Seeking.");
        m_sdsReader->seek(0, alexaClientSDK::avsCommon::avs::AudioInputStream::Reader::Reference::BEFORE_WRITER);
    }
}

void SDSReader::close() {
    LX(DEBUG3, "");

    std::lock_guard<std::mutex> guard(m_mutex);

    if (m_sdsReader) {
        LX(DEBUG3, "Closing SDS.");
        m_sdsReader->close();
        m_sdsReader = nullptr;
    }
}

}  // namespace sds
}  // namespace audioManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
