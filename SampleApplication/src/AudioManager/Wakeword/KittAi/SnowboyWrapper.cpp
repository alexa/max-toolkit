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

#define KWD_KITTAI_LEGACY

#ifdef KWD_KITTAI_LEGACY
/// To match with C++ ABI used in Snowboy binary
#undef _GLIBCXX_USE_CXX11_ABI
#define _GLIBCXX_USE_CXX11_ABI 0
#endif

// This include must be below the defines above or linking issues are introduced on RPI.
#include "SampleApplication/AudioManager/Wakeword/KittAi/SnowboyWrapper.h"

#include <snowboy-detect.h>

namespace multiAgentExperience {
namespace sampleApplication {
namespace audioManager {
namespace wakeword {
namespace kittai {

/**
 * Static cast the void* pointer to snowboy::SnowboyDetect.
 *
 * @param p the pointer to snowboy::SnowboyDetect instantiation.
 * @return snowboy::SnowboyDetect object.
 */
static snowboy::SnowboyDetect* cast(void* p) {
    return reinterpret_cast<snowboy::SnowboyDetect*>(p);
}

SnowboyWrapper::SnowboyWrapper(const char* resourceFilename, const char* model) :
        m_snowboy{new snowboy::SnowboyDetect(resourceFilename, model)} {
}

int SnowboyWrapper::RunDetection(const int16_t* const data, const int arrayLength, bool isEnd) {
    return cast(m_snowboy)->RunDetection(data, arrayLength, isEnd);
}

void SnowboyWrapper::SetSensitivity(const char* sensitivity) {
    cast(m_snowboy)->SetSensitivity(sensitivity);
}

void SnowboyWrapper::SetAudioGain(const float audioGain) {
    cast(m_snowboy)->SetAudioGain(audioGain);
}

void SnowboyWrapper::ApplyFrontend(const bool applyFrontend) {
    cast(m_snowboy)->ApplyFrontend(applyFrontend);
}

int SnowboyWrapper::SampleRate() const {
    return cast(m_snowboy)->SampleRate();
}

int SnowboyWrapper::NumChannels() const {
    return cast(m_snowboy)->NumChannels();
}

int SnowboyWrapper::BitsPerSample() const {
    return cast(m_snowboy)->BitsPerSample();
}

}  // namespace kittai
}  // namespace wakeword
}  // namespace audioManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
