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

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_AUDIO_AUDIOFORMAT_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_AUDIO_AUDIOFORMAT_H_

#include <climits>
#include <cstddef>

namespace multiAgentExperience {
namespace audio {

/**
 * This structure defines an audio format which a multi-agent application can use to ensure alignment between various
 * readers and writers of audio data. This may include microphones, wakeword engines, and agent consumers.
 */
struct AudioFormat {
    /**
     * An enum class used to represent the encoding of audio data.
     */
    enum class Encoding {
        /// Represents LPCM (Linear pulse code modulation) encoding.
        LPCM
    };

    /**
     * An enum class used to represent the endianness of audio data.
     */
    enum class Endianness {
        /// Represents little endianness.
        LITTLE,

        /// Represents big endianness.
        BIG
    };

    /**
     * Default constructor.
     */
    AudioFormat() :
            sampleRateHz{0},
            numChannels{0},
            wordsPerSample{0},
            wordSizeBits{CHAR_BIT},
            encoding{Encoding::LPCM},
            endianness{Endianness::LITTLE} {
    }

    /**
     * Constructor.
     *
     * @param sampleRateHz Sample rate in Hertz.
     * @param numChannels Number of channels (For example, 1 for mono, 2 for stereo, etc.).
     * @param wordsPerSample The number of words (typically bytes) in a given audio sample.
     * @param wordSizeBits The number of bits in a word for this audio format. If not specified, defaults to the
     * commonly used CHAR_BIT.
     */
    AudioFormat(
        std::size_t sampleRateHz,
        std::size_t numChannels,
        std::size_t wordsPerSample,
        std::size_t wordSizeBits = CHAR_BIT,
        Encoding encoding = Encoding::LPCM,
        Endianness endianness = Endianness::LITTLE) :
            sampleRateHz{sampleRateHz},
            numChannels{numChannels},
            wordsPerSample{wordsPerSample},
            wordSizeBits{wordSizeBits},
            encoding{encoding},
            endianness{endianness} {
    }

    /// The sample rate in Hertz.
    std::size_t sampleRateHz;

    /// The number of channels in the audio stream.
    std::size_t numChannels;

    /// The number of words in a given sample for a single audio channel.
    std::size_t wordsPerSample;

    /// The size of a word in the audio stream.
    std::size_t wordSizeBits;

    /// The encoding of the data.
    Encoding encoding;

    /// The endianness of the data.
    Endianness endianness;
};

}  // namespace audio
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_AUDIO_AUDIOFORMAT_H_
