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

#include "Computer/VoiceActivityDetection/VoiceActivityDetection.h"

#include <chrono>
#include <cmath>
#include <iostream>

#include "Utils/Logger.h"

static const std::string MODULE_TAG("VoiceActivityDetector");
#define LX(logCommand, message) COMPUTER_AGENT_LOG_##logCommand("", MODULE_TAG, __func__, message)

namespace multiAgentExperience {
namespace samples {
namespace agents {
namespace computer {

// If the type of these constants changes to fractionals, be careful to properly cast to float/double for e.g.
// so values aren't truncated to 0.
const size_t SLACKTIME_SECONDS = 3;
const size_t SILENCE_TIME_SECONDS = 1;

// The below values is copied from, and in experimentation it works well:
// https://github.com/aws-samples/amazon-lex-conversational-interface-for-twilio/blob/master/voice_and_silence_detecting_lex_wrapper.py
const float RMS_THRESHOLD = 500.f;

static float computeRMS(int16_t* frame, size_t frameSize) {
    // return zero if no data provided
    if ((!frame) || (frameSize == 0)) {
        return 0.0f;
    }

    float sum = 0;
    for (size_t i = 0; i < frameSize; i++) {
        sum += std::pow((float)frame[i], 2.0f);
    }

    sum = sum / (float)frameSize;
    return std::sqrt(sum);
}

VoiceActivityDetector::VoiceActivityDetector() :
        m_totalSlackTime{0},
        m_totalSilenceTime{0},
        m_timeInSlack{0},
        m_timeInSilence{0},
        m_silenced{false},
        m_waitingInSlack{false} {
}

void VoiceActivityDetector::initialize(size_t samplesPerSecond) {
    LX(DEBUG3, "");
    m_totalSlackTime = samplesPerSecond * SLACKTIME_SECONDS;
    m_totalSilenceTime = samplesPerSecond * SILENCE_TIME_SECONDS;
    reset();
}

void VoiceActivityDetector::reset() {
    LX(DEBUG3, "");
    m_timeInSlack = m_timeInSilence = 0;
    m_silenced = false;
    m_waitingInSlack = true;
}

bool VoiceActivityDetector::processFrame(int16_t* frame, size_t frameSize) {
    if (m_silenced) {
        return true;
    }

    auto rms = computeRMS(frame, frameSize);

    // If we are waiting and the signal breaks the the threshold, transition to listening
    if (m_waitingInSlack && (rms > RMS_THRESHOLD)) {
        m_waitingInSlack = false;
        LX(DEBUG3, "speechStart");
    } else if (m_waitingInSlack) {
        m_timeInSlack += frameSize;

        // If we are waiting and the signal never breaks the threshold, then set silenced = true and return
        if (m_timeInSlack > m_totalSlackTime) {
            LX(DEBUG3, "TimeOut");
            m_silenced = true;
            return true;
        }

        return false;
    }

    if (rms < RMS_THRESHOLD) {
        m_timeInSilence += frameSize;
    } else {
        // reset silence time, since it needs to be consecutive especially if frameSizes are smaller
        m_timeInSilence = 0;
    }

    if (m_timeInSilence > m_totalSilenceTime) {
        LX(DEBUG3, "silenceEnd");
        m_silenced = true;
    }

    return m_silenced;
}

bool VoiceActivityDetector::isSilenced() {
    LX(DEBUG3, "");
    return m_silenced;
}

}  // namespace computer
}  // namespace agents
}  // namespace samples
}  // namespace multiAgentExperience
