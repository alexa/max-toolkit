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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_EXPERIENCEMANAGER_SENSEHAT_LEDCONTROLLER_ANIMATIONSEQUENCE_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_EXPERIENCEMANAGER_SENSEHAT_LEDCONTROLLER_ANIMATIONSEQUENCE_H_

#include "SampleApplication/ExperienceManager/SenseHAT/LEDController/AnimationLine.h"

#include <string>
#include <vector>

namespace multiAgentExperience {
namespace sampleApplication {
namespace experienceManager {
namespace senseHat {
namespace ledController {

/**
 * This class handles the details of what to show next. This includes looping.
 */
class AnimationSequence {
public:
    AnimationSequence(const std::string& file);

    AnimationSequence(const AnimationSequence&) = default;

    AnimationSequence() = default;

    void reset();

    const AnimationLine getCurrentFrame();

    bool frameComplete();

private:
    std::vector<AnimationLine> m_lines;
    int m_currentIndex;
    int m_jumpIndex;
};

}  // namespace ledController
}  // namespace senseHat
}  // namespace experienceManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_EXPERIENCEMANAGER_SENSEHAT_LEDCONTROLLER_ANIMATIONSEQUENCE_H_
