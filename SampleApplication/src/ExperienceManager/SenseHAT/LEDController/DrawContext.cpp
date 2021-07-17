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

#include "SampleApplication/ExperienceManager/SenseHAT/LEDController/DrawContext.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace experienceManager {
namespace senseHat {
namespace ledController {

void DrawContext::clear() {
    fill(0);
}

void DrawContext::fill(PixelValue color) {
    for (size_t i = 0; i < m_buffer.getWidth(); i++) {
        for (size_t j = 0; j < m_buffer.getHeight(); j++) {
            m_buffer[i][j] = 0;
        }
    }
}

void DrawContext::setPenColor(PixelValue color) {
    m_penColor = color;
}

void DrawContext::drawHLine(size_t row) {
    for (size_t i = 0; i < m_buffer.getWidth(); i++) {
        m_buffer[row][i] = m_penColor;
    }
}

}  // namespace ledController
}  // namespace senseHat
}  // namespace experienceManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
