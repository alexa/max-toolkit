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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_EXPERIENCEMANAGER_SENSEHAT_LEDCONTROLLER_BUFFER_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_EXPERIENCEMANAGER_SENSEHAT_LEDCONTROLLER_BUFFER_H_

#include <stdlib.h>

#include "SampleApplication/ExperienceManager/SenseHAT/LEDController/NonCopyable.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace experienceManager {
namespace senseHat {
namespace ledController {

/**
 * This class is specialized for 16-bit RGB565 values.
 */
class Buffer : public NonCopyable {
public:
    Buffer(size_t width, size_t height);

    ~Buffer();

    size_t getWidth();

    size_t getHeight();

    size_t getSizeInBytes();

    uint16_t* operator[](size_t i);

    uint16_t* getRawBuffer();

private:
    uint16_t* m_buffer;
    uint16_t** m_rows;
    size_t m_width;
    size_t m_height;
    size_t m_sizeInBytes;
};

}  // namespace ledController
}  // namespace senseHat
}  // namespace experienceManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_EXPERIENCEMANAGER_SENSEHAT_LEDCONTROLLER_BUFFER_H_
