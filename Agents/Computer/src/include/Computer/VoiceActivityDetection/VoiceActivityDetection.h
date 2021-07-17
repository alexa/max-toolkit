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

#ifndef MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_VOICEACTIVITYDETECTION_VOICEACTIVITYDETECTION_H_
#define MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_VOICEACTIVITYDETECTION_VOICEACTIVITYDETECTION_H_

#include <stdint.h>
#include <stdlib.h>

namespace multiAgentExperience {
namespace samples {
namespace agents {
namespace computer {

/**
 * This class detects a signal that transitions from silence
 * into active speaking and then silence.
 * Detecting silence following an utterance is used to start
 * the ASR process.
 */
class VoiceActivityDetector {
public:
    VoiceActivityDetector();

    /**
     * Initialize voice activity detector
     * @param samplesPerSecond Sample rate in Hz.
     */
    void initialize(size_t samplesPerSecond);

    /**
     * Go back to the waiting for voice state
     */
    void reset();

    /**
     *
     * Process a frame and return true if silence is detected
     * or the state machine times out
     */
    bool processFrame(int16_t* frame, size_t frameSize);

    /**
     * Indicates whether the state machine has reached a terminal
     * state.
     */
    bool isSilenced();

private:
    size_t m_totalSlackTime;
    size_t m_totalSilenceTime;
    size_t m_timeInSlack;
    size_t m_timeInSilence;
    bool m_silenced;
    bool m_waitingInSlack;
};

}  // namespace computer
}  // namespace agents
}  // namespace samples
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_VOICEACTIVITYDETECTION_VOICEACTIVITYDETECTION_H_
