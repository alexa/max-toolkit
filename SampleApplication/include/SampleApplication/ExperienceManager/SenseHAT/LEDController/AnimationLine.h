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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_EXPERIENCEMANAGER_SENSEHAT_LEDCONTROLLER_ANIMATIONLINE_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_EXPERIENCEMANAGER_SENSEHAT_LEDCONTROLLER_ANIMATIONLINE_H_

#include "SampleApplication/ExperienceManager/SenseHAT/LEDController/NonCopyable.h"

#include <array>
#include <string>

namespace multiAgentExperience {
namespace sampleApplication {
namespace experienceManager {
namespace senseHat {
namespace ledController {

typedef std::array<PixelValue, 12> PixelArray;

/**
 * Represents a single snapshot.
 */
class AnimationLine {
public:
    static AnimationLine parseAnimationSpec(const std::string& line);

    static AnimationLine INVALID();

    AnimationLine(int dwellTime, PixelArray pixels);

    AnimationLine();

    const PixelArray& getPixels();

    int getDwellTime();

    bool isValid();

private:
    bool m_valid;
    int m_dwellTime;
    PixelArray m_pixels;
};

}  // namespace ledController
}  // namespace senseHat
}  // namespace experienceManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_EXPERIENCEMANAGER_SENSEHAT_LEDCONTROLLER_ANIMATIONLINE_H_
