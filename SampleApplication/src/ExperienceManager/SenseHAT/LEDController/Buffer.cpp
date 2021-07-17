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

#include "SampleApplication/ExperienceManager/SenseHAT/LEDController/Buffer.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace experienceManager {
namespace senseHat {
namespace ledController {

Buffer::Buffer(size_t width, size_t height) : m_width{width}, m_height{height} {
    m_buffer = new uint16_t[width * height];
    for (size_t i = 0; i < width * height; i++) {
        m_buffer[i] = 0;
    }

    m_rows = new uint16_t*[height];
    for (size_t i = 0; i < height; i++) {
        m_rows[i] = &(m_buffer[i * width]);
    }

    m_sizeInBytes = width * height * 2;
}

uint16_t* Buffer::operator[](size_t i) {
    return m_rows[i];
}

Buffer::~Buffer() {
    delete[] m_rows;
    delete[] m_buffer;
}

size_t Buffer::getWidth() {
    return m_width;
}

size_t Buffer::getHeight() {
    return m_height;
}

size_t Buffer::getSizeInBytes() {
    return m_sizeInBytes;
}

uint16_t* Buffer::getRawBuffer() {
    return m_buffer;
}

}  // namespace ledController
}  // namespace senseHat
}  // namespace experienceManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
