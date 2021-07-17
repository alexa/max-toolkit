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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_EXPERIENCEMANAGER_SENSEHAT_SENSEHATEXPERIENCERENDERER_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_EXPERIENCEMANAGER_SENSEHAT_SENSEHATEXPERIENCERENDERER_H_

#ifdef RPI_LED_SENSE_HAT

#include <memory>

#include <SampleApplication/ExperienceManager/SenseHAT/LEDController/AnimationEngine.h>

#include "SampleApplication/ExperienceManager/ExperienceRendererInterface.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace experienceManager {
namespace senseHat {

/**
 * A Raspberry pi SenseHAT-based experience renderer. Hardware details here:
 * https://www.raspberrypi.org/products/sense-hat/
 *
 * Note that this code is NOT expected to work upon any other platform or LED hardware.
 */
class SenseHatExperienceRenderer : public ExperienceRendererInterface {
public:
    /**
     * Constructor.
     */
    SenseHatExperienceRenderer();

    /// @name ExperienceRendererInterface method overrides.
    /// @{
    void onExperienceChange(const std::vector<MAX::experience::Experience>& experiences) override;
    /// @}

private:
    /// Agent types for internal tracking purposes.
    enum class Agent {
        /// No agent.
        NONE,
        /// The Alexa agent.
        ALEXA,
        /// The computer agent.
        COMPUTER
    };

    /// The current agent being animated.
    Agent m_currentlyAnimating = Agent::NONE;
    /// Handle to our underlying animation engine.
    std::unique_ptr<ledController::AnimationEngine> m_animationEngine;
};

}  // namespace senseHat
}  // namespace experienceManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // RPI_LED_SENSE_HAT

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_EXPERIENCEMANAGER_SENSEHAT_SENSEHATEXPERIENCERENDERER_H_
