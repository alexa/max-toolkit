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

#include "SampleApplication/ExperienceManager/SenseHAT/LEDController/AnimationLine.h"

#include <fstream>
#include <string>
#include <utility>

#include "SampleApplication/ExperienceManager/SenseHAT/LEDController/Utils.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace experienceManager {
namespace senseHat {
namespace ledController {

AnimationLine AnimationLine::parseAnimationSpec(const std::string& line) {
    int dwellTime = -1;
    size_t i = 0;

    for (i = 0; i < line.length(); i++) {
        if (line[i] == ':') {
            dwellTime = std::stoi(line.substr(0, i), nullptr, 10);
            break;
        }
    }

    if (dwellTime == -1) {
        return AnimationLine::INVALID();
    }

    PixelArray pixels;
    int pixelCount = 0;

    size_t j = 0;
    for (i += 1, j = i; i < line.length(); i++) {
        bool isLastChar = i == (line.length() - 1);
        if ((line[i] == ',') || isLastChar) {
            if (isLastChar) {  // substr takes length, so advance by 1
                i++;
            }
            auto color = line.substr(j, (i - j));
            j = i + 1;
            pixels[pixelCount] = parse_rgb888_to_rgb565(color);
            pixelCount++;
            if (pixelCount == 12) {
                break;
            }
        }
    }

    return AnimationLine(dwellTime, std::move(pixels));
}

bool AnimationLine::isValid() {
    return m_valid;
}

AnimationLine AnimationLine::INVALID() {
    return AnimationLine();
}

AnimationLine::AnimationLine(int dwellTime, PixelArray pixels) :
        m_valid{true},
        m_dwellTime(dwellTime),
        m_pixels{std::forward<PixelArray>(pixels)} {
}

AnimationLine::AnimationLine() : m_valid{false} {
}

int AnimationLine::getDwellTime() {
    return m_dwellTime;
}

const PixelArray& AnimationLine::getPixels() {
    return m_pixels;
}

}  // namespace ledController
}  // namespace senseHat
}  // namespace experienceManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
