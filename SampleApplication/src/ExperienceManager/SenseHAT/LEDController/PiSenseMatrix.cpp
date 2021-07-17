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

#include "SampleApplication/ExperienceManager/SenseHAT/LEDController/PiSenseMatrix.h"

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

namespace multiAgentExperience {
namespace sampleApplication {
namespace experienceManager {
namespace senseHat {
namespace ledController {

const uint16_t SENSEFB_FBIORESET_GAMMA = 61698;
const uint8_t SENSE_HAT_FB_GAMMA_DEFAULT = 0;

std::shared_ptr<PiSenseMatrix> PiSenseMatrix::s_senseMatrix;
std::mutex PiSenseMatrix::s_createMutex;

std::shared_ptr<PiSenseMatrix> PiSenseMatrix::create(const std::string& device) {
    std::lock_guard<std::mutex> lock(s_createMutex);

    if (s_senseMatrix) {
        return s_senseMatrix;
    }

    int fd = open(device.c_str(), O_RDWR);
    if (fd < 1) {
        return nullptr;
    }

    int ret = ioctl(fd, SENSEFB_FBIORESET_GAMMA, SENSE_HAT_FB_GAMMA_DEFAULT);
    if (ret < 0) {
        close(fd);
        return nullptr;
    }

    s_senseMatrix = std::shared_ptr<PiSenseMatrix>(new PiSenseMatrix(fd));
    return s_senseMatrix;
}

PiSenseMatrix::PiSenseMatrix(int fd) : m_fd{fd} {
}

PiSenseMatrix::~PiSenseMatrix() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_fd) {
        close(m_fd);
    }
}

void PiSenseMatrix::commit(Buffer& buffer) {
    std::lock_guard<std::mutex> lock(m_mutex);
    lseek(m_fd, 0, SEEK_SET);
    write(m_fd, buffer.getRawBuffer(), buffer.getSizeInBytes());
    fsync(m_fd);
}

}  // namespace ledController
}  // namespace senseHat
}  // namespace experienceManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
