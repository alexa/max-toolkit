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

#include "SampleApplication/ExperienceManager/SenseHAT/LEDController/AnimationEngine.h"

#include <array>
#include <chrono>
#include <iostream>
#include <thread>

namespace multiAgentExperience {
namespace sampleApplication {
namespace experienceManager {
namespace senseHat {
namespace ledController {

/*
 * The RPi SenseHAT we use has an 8x8 grid of LEDs we can control.
 */
static constexpr size_t RPI_LED_SENSE_HAT_WIDTH = 8;
static constexpr size_t RPI_LED_SENSE_HAT_HEIGHT = 8;

/*
 * The SenseHAT Leds are accessible on the RPi by accessing the "FrameBuffer 1" device file handle
 */
static constexpr char RPI_LED_SENSE_HAT_DEVICE_NAME[] = "/dev/fb1";

typedef std::pair<size_t, size_t> Point;

std::vector<std::array<Point, 2>> pixelLocations = {{{{0, 1}, {0, 2}}},
                                                    {{{0, 3}, {0, 4}}},
                                                    {{{0, 5}, {0, 6}}},

                                                    {{{1, 7}, {2, 7}}},
                                                    {{{3, 7}, {4, 7}}},
                                                    {{{5, 7}, {6, 7}}},

                                                    {{{7, 5}, {7, 6}}},
                                                    {{{7, 3}, {7, 4}}},
                                                    {{{7, 1}, {7, 2}}},

                                                    {{{5, 0}, {6, 0}}},
                                                    {{{3, 0}, {4, 0}}},
                                                    {{{1, 0}, {2, 0}}}};

AnimationEngine::AnimationEngine() :
        m_screenBuffer{RPI_LED_SENSE_HAT_WIDTH, RPI_LED_SENSE_HAT_HEIGHT},
        // TODO This create call can fail, need to insert error checking. VII-359
        // Should have a create function for AnimationEngine as well.
        m_matrix{ledController::PiSenseMatrix::create(RPI_LED_SENSE_HAT_DEVICE_NAME)},
        m_running{false},
        m_currentAnimation{0} {
}

AnimationEngine::~AnimationEngine() {
    stopAll();
}
void AnimationEngine::loadAnimation(const std::string& file, size_t id) {
    std::lock_guard<std::recursive_mutex> guard(m_mutex);
    m_animations[id] = AnimationSequence(file);
}

void AnimationEngine::playAnimation(size_t id) {
    std::lock_guard<std::recursive_mutex> guard(m_mutex);
    if (m_running && m_currentAnimation == id) {
        // Already animating this animation
        return;
    }
    stopAll();
    render(id);
}

void AnimationEngine::stopAll() {
    std::lock_guard<std::recursive_mutex> guard(m_mutex);
    if (m_running) {
        m_running = false;
        m_shouldStop.notify_all();
        m_thread.join();
        clear();
    }
}

void AnimationEngine::render(size_t id) {
    std::lock_guard<std::recursive_mutex> guard(m_mutex);
    m_running = true;
    m_currentAnimation = id;
    AnimationSequence sequence = m_animations[id];
    sequence.reset();

    m_thread = std::thread([this, sequence]() mutable {
        while (m_running) {
            std::unique_lock<std::mutex> lock(m_threadMutex);
            auto frame = sequence.getCurrentFrame();
            draw(frame);
            m_shouldStop.wait_for(lock, (std::chrono::milliseconds(frame.getDwellTime())));
            if (sequence.frameComplete()) {
                break;
            }
        }
    });
}

void AnimationEngine::draw(AnimationLine frame) {
    auto pixels = frame.getPixels();

    for (int i = 0; i < 12; i++) {
        auto location = pixelLocations[i];
        auto p0 = location[0];
        auto p1 = location[1];
        m_screenBuffer[p0.first][p0.second] = pixels[i];
        m_screenBuffer[p1.first][p1.second] = pixels[i];
    }

    m_matrix->commit(m_screenBuffer);
}

void AnimationEngine::clear() {
    Buffer emptyBuffer(m_screenBuffer.getWidth(), m_screenBuffer.getHeight());
    m_matrix->commit(emptyBuffer);
}

}  // namespace ledController
}  // namespace senseHat
}  // namespace experienceManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
