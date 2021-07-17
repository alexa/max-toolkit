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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_EXPERIENCEMANAGER_SENSEHAT_LEDCONTROLLER_ANIMATIONENGINE_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_EXPERIENCEMANAGER_SENSEHAT_LEDCONTROLLER_ANIMATIONENGINE_H_

#include "SampleApplication/ExperienceManager/SenseHAT/LEDController/NonCopyable.h"
#include "SampleApplication/ExperienceManager/SenseHAT/LEDController/Buffer.h"
#include "SampleApplication/ExperienceManager/SenseHAT/LEDController/PiSenseMatrix.h"
#include "SampleApplication/ExperienceManager/SenseHAT/LEDController/AnimationSequence.h"

#include <array>
#include <atomic>
#include <condition_variable>
#include <string>
#include <vector>
#include <map>
#include <mutex>
#include <thread>

namespace multiAgentExperience {
namespace sampleApplication {
namespace experienceManager {
namespace senseHat {
namespace ledController {

/**
 * This class loads animation files into memory and then draws them on a buffer which is written into the LED SenseHat.
 *
 * TODO: Rewrite for safety and clarity. VII-359
 */
class AnimationEngine {
public:
    /**
     * Constructor
     */
    AnimationEngine();

    /**
     * Destructor
     */
    ~AnimationEngine();

    /**
     * Takes an animation file and stores it in memory mapped to an Id
     *
     * @param file The animation file to load
     * @param id The Id to map to the animation, supplying an already used Id will overwrite it.
     */
    void loadAnimation(const std::string& file, size_t id);

    /**
     * Plays an animation mapped to the provided id
     *
     * Undefined behavior if the Id is not mapped to a loaded animation
     *
     * TODO: make safe. VII-359
     *
     * @param id The Id of the animation to play
     */
    void playAnimation(size_t id);

    /**
     * Stops all playing animation and clears the LEDs
     */
    void stopAll();

private:
    void draw(AnimationLine frame);

    void clear();

    void render(size_t id);

    Buffer m_screenBuffer;
    std::shared_ptr<PiSenseMatrix> m_matrix;
    std::map<size_t, AnimationSequence> m_animations;
    std::atomic<bool> m_running;
    size_t m_currentAnimation;
    std::recursive_mutex m_mutex;
    std::mutex m_threadMutex;
    std::thread m_thread;
    std::condition_variable m_shouldStop;
};

}  // namespace ledController
}  // namespace senseHat
}  // namespace experienceManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_EXPERIENCEMANAGER_SENSEHAT_LEDCONTROLLER_ANIMATIONENGINE_H_
