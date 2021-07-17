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

#ifdef RPI_LED_SENSE_HAT

#include "SampleApplication/ExperienceManager/SenseHAT/SenseHatExperienceRenderer.h"

#include <iostream>

#include "SampleApplication/Utils/RadiantLogger.h"
#include "SampleApplication/Utils/StringUtils.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace experienceManager {
namespace senseHat {

static const std::string MODULE_TAG("SenseHatExperienceManager");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, MODULE_TAG, __func__, message)

using namespace multiAgentExperience::experience;
using namespace multiAgentExperience::sampleApplication::experienceManager::senseHat::ledController;

/// Internal definitons for our supported demo animations.
enum ANIMATIONS {
    COMPUTER_LISTENING,
    COMPUTER_THINKING,
    COMPUTER_SPEAKING,
    COMPUTER_ALERTING,
    COMPUTER_END,
    ALEXA_LISTENING,
    ALEXA_THINKING,
    ALEXA_SPEAKING,
    ALEXA_ALERTING,
    ALEXA_END
};

static const std::string COMPUTER_LISTENING_ANIMATION_FILE = "computer_listening.animation";
static const std::string COMPUTER_THINKING_ANIMATION_FILE = "computer_thinking.animation";
static const std::string COMPUTER_RESPONDING_ANIMATION_FILE = "computer_responding.animation";
static const std::string COMPUTER_END_ANIMATION_FILE = "computer_end.animation";

static const std::string ALEXA_LISTENING_ANIMATION_FILE = "alexa_listening.animation";
static const std::string ALEXA_THINKING_ANIMATION_FILE = "alexa_thinking.animation";
static const std::string ALEXA_RESPONDING_ANIMATION_FILE = "alexa_responding.animation";
static const std::string ALEXA_ALERTING_ANIMATION_FILE = "alexa_alerting.animation";
static const std::string ALEXA_END_ANIMATION_FILE = "alexa_end.animation";

/// Good ole' stringification macros ...
#define xstr(a) str(a)
#define str(a) #a

SenseHatExperienceRenderer::SenseHatExperienceRenderer() {
    m_animationEngine = std::unique_ptr<ledController::AnimationEngine>(new ledController::AnimationEngine());

    m_animationEngine->loadAnimation(
        std::string(xstr(RPI_LED_ANIMATIONS)) + COMPUTER_LISTENING_ANIMATION_FILE, ANIMATIONS::COMPUTER_LISTENING);
    m_animationEngine->loadAnimation(
        std::string(xstr(RPI_LED_ANIMATIONS)) + COMPUTER_THINKING_ANIMATION_FILE, ANIMATIONS::COMPUTER_THINKING);
    m_animationEngine->loadAnimation(
        std::string(xstr(RPI_LED_ANIMATIONS)) + COMPUTER_RESPONDING_ANIMATION_FILE, ANIMATIONS::COMPUTER_SPEAKING);
    m_animationEngine->loadAnimation(
        std::string(xstr(RPI_LED_ANIMATIONS)) + COMPUTER_END_ANIMATION_FILE, ANIMATIONS::COMPUTER_END);

    m_animationEngine->loadAnimation(
        std::string(xstr(RPI_LED_ANIMATIONS)) + ALEXA_LISTENING_ANIMATION_FILE, ANIMATIONS::ALEXA_LISTENING);
    m_animationEngine->loadAnimation(
        std::string(xstr(RPI_LED_ANIMATIONS)) + ALEXA_THINKING_ANIMATION_FILE, ANIMATIONS::ALEXA_THINKING);
    m_animationEngine->loadAnimation(
        std::string(xstr(RPI_LED_ANIMATIONS)) + ALEXA_RESPONDING_ANIMATION_FILE, ANIMATIONS::ALEXA_SPEAKING);
    m_animationEngine->loadAnimation(
        std::string(xstr(RPI_LED_ANIMATIONS)) + ALEXA_ALERTING_ANIMATION_FILE, ANIMATIONS::ALEXA_ALERTING);
    m_animationEngine->loadAnimation(
        std::string(xstr(RPI_LED_ANIMATIONS)) + ALEXA_END_ANIMATION_FILE, ANIMATIONS::ALEXA_END);
}

void SenseHatExperienceRenderer::onExperienceChange(const std::vector<Experience>& experiences) {
    LX(DEBUG3, "");

    if (experiences.empty()) {
        if (Agent::ALEXA == m_currentlyAnimating) {
            m_animationEngine->playAnimation(ANIMATIONS::ALEXA_END);
        } else if (Agent::COMPUTER == m_currentlyAnimating) {
            m_animationEngine->playAnimation(ANIMATIONS::COMPUTER_END);
        }
        m_currentlyAnimating = Agent::NONE;
    } else {
        auto& experience = experiences.front();

        std::string agentName = utils::stringToLowerCase(static_cast<std::string>(experience.actorId));
        LX(DEBUG3,
           "Agent name:" + static_cast<std::string>(experience.actorId) +
               ", experience:" + static_cast<std::string>(experience.experienceId));

        if (agentName == "computer") {
            m_currentlyAnimating = Agent::COMPUTER;
            if (experience.experienceId == commonIds::LISTENING) {
                m_animationEngine->playAnimation(ANIMATIONS::COMPUTER_LISTENING);
            } else if (experience.experienceId == commonIds::THINKING) {
                m_animationEngine->playAnimation(ANIMATIONS::COMPUTER_THINKING);
            } else if (experience.experienceId == commonIds::SPEAKING) {
                m_animationEngine->playAnimation(ANIMATIONS::COMPUTER_SPEAKING);
            }
        } else if (agentName == "alexa") {
            m_currentlyAnimating = Agent::ALEXA;
            if (experience.experienceId == commonIds::LISTENING) {
                m_animationEngine->playAnimation(ANIMATIONS::ALEXA_LISTENING);
            } else if (experience.experienceId == commonIds::THINKING) {
                m_animationEngine->playAnimation(ANIMATIONS::ALEXA_THINKING);
            } else if (experience.experienceId == commonIds::SPEAKING) {
                m_animationEngine->playAnimation(ANIMATIONS::ALEXA_SPEAKING);
            } else {
                // ERROR
            }
        }
    }
}

}  // namespace senseHat
}  // namespace experienceManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif
