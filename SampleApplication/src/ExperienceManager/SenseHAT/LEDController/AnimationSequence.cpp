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

#include "SampleApplication/ExperienceManager/SenseHAT/LEDController/AnimationSequence.h"

#include <fstream>
#include <iostream>
#include <string>
#include <utility>

#include "SampleApplication/ExperienceManager/SenseHAT/LEDController/Utils.h"
#include "SampleApplication/Utils/RadiantLogger.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace experienceManager {
namespace senseHat {
namespace ledController {

static const std::string MODULE_TAG("AnimationSequence");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, MODULE_TAG, __func__, message)

AnimationSequence::AnimationSequence(const std::string& file) : m_currentIndex{0}, m_jumpIndex{-1} {
    LX(DEBUG3, "File:" + file);
    std::ifstream fs(file);
    if (fs.fail()) {
        LX(ERROR, "Unable to open file:" + file);
        std::cout << "AnimationEngine unable to open " << file << std::endl;
        throw std::runtime_error("Can't open file");
    }

    std::string str;
    int i = 0;
    while (std::getline(fs, str)) {
        if (str.empty()) {
            continue;
        }

        if (str.compare("loop") == 0) {
            m_jumpIndex = i;
        } else {
            auto line = AnimationLine::parseAnimationSpec(str);
            if (line.isValid()) {
                m_lines.push_back(std::move(line));
                i++;
            }
        }
    }
}

void AnimationSequence::reset() {
    m_currentIndex = 0;
}

bool AnimationSequence::frameComplete() {
    m_currentIndex++;

    if (m_currentIndex < static_cast<int>(m_lines.size())) {
        return false;
    } else if ((m_currentIndex == static_cast<int>(m_lines.size())) && (m_jumpIndex != -1)) {
        m_currentIndex = m_jumpIndex;
        return false;
    }

    return true;
}

const AnimationLine AnimationSequence::getCurrentFrame() {
    if (m_currentIndex < static_cast<int>(m_lines.size())) {
        return m_lines[m_currentIndex];
    } else {
        return AnimationLine::INVALID();
    }
}

}  // namespace ledController
}  // namespace senseHat
}  // namespace experienceManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
