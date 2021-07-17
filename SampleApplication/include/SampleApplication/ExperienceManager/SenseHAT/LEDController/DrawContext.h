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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_EXPERIENCEMANAGER_SENSEHAT_LEDCONTROLLER_DRAWCONTEXT_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_EXPERIENCEMANAGER_SENSEHAT_LEDCONTROLLER_DRAWCONTEXT_H_

#include "SampleApplication/ExperienceManager/SenseHAT/LEDController/Buffer.h"
#include "SampleApplication/ExperienceManager/SenseHAT/LEDController/NonCopyable.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace experienceManager {
namespace senseHat {
namespace ledController {

class DrawContext : public NonCopyable {
public:
    DrawContext(Buffer& buffer) : m_buffer{buffer}, m_penColor{0} {
    }

    void clear();

    void fill(PixelValue value);

    void setPenColor(PixelValue value);

    void drawHLine(size_t row);

private:
    Buffer& m_buffer;
    PixelValue m_penColor;
};

}  // namespace ledController
}  // namespace senseHat
}  // namespace experienceManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_EXPERIENCEMANAGER_SENSEHAT_LEDCONTROLLER_DRAWCONTEXT_H_
