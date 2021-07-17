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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_WAKEWORD_KITTAI_SNOWBOYWRAPPER_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_WAKEWORD_KITTAI_SNOWBOYWRAPPER_H_

#include <memory>

namespace multiAgentExperience {
namespace sampleApplication {
namespace audioManager {
namespace wakeword {
namespace kittai {

/**
 * The wrapper class for snowboy::SnowboyDetect class.
 *
 * Since the original API exposes std::string which will be ABI incompatible with GCC 5.1, this class replaces them with
 * const char*.
 *
 * We keep the actual instantiation in a void* pointer in this header, to prevent from other files to include
 * snowboy-detect.h file.
 *
 * Thanks to this community for the original idea:
 * https://github.com/Kitt-AI/snowboy/issues/99
 */
class SnowboyWrapper {
public:
    /**
     * Constructor.
     *
     * @param resourceFilename for the first argument of the original API call.
     * @param model for the second argument of the original API call.
     */
    SnowboyWrapper(const char* resourceFilename, const char* model);

    /**
     * Destructor.
     */
    ~SnowboyWrapper() = default;

    /**
     * Calls snowboy::SnowboyDetect::RunDetection.
     *
     * @param data for the first argument of the original API call.
     * @param arrayLength for the second argument of the original API call.
     * @param isEnd for the third argument of the original API call.
     * @return the value of the original API call result.
     */
    int RunDetection(const int16_t* const data, const int arrayLength, bool isEnd = false);

    /**
     * Calls snowboy::SnowboyDetect::SetSensitivity.
     *
     * @param sensitivity for the first argument of the original API call.
     */
    void SetSensitivity(const char* sensitivity);

    /**
     * Calls snowboy::SnowboyDetect::SetAudioGain.
     *
     * @param audioGain for the first argument of the original API call.
     */
    void SetAudioGain(const float audioGain);

    /**
     * Calls snowboy::SnowboyDetect::ApplyFrontend.
     *
     * @param applyFrontend for the first argument of the original API call.
     */
    void ApplyFrontend(const bool applyFrontend);

    /**
     * Calls snowboy::SnowboyDetect::SampleRate.
     *
     * @return the value of the original API call result.
     */
    int SampleRate() const;

    /**
     * Calls snowboy::SnowboyDetect::NumChannels.
     *
     * @return the value of the original API call result.
     */
    int NumChannels() const;

    /**
     * Calls snowboy::SnowboyDetect::BitsPerSample.
     *
     * @return the value of the original API call result.
     */
    int BitsPerSample() const;

private:
    /// A pointer to the actual Kitt.ai engine.
    void* m_snowboy;
};

}  // namespace kittai
}  // namespace wakeword
}  // namespace audioManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_WAKEWORD_KITTAI_SNOWBOYWRAPPER_H_
