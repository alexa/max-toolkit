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

#include "SampleApplication/ExperienceManager/SenseHAT/LEDController/Utils.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace experienceManager {
namespace senseHat {
namespace ledController {

static uint8_t hex2int(const char hex) {
    uint8_t ret = 0;
    if ((hex >= '0') && (hex <= '9')) {
        ret = hex - '0';
    } else if ((hex >= 'A') && (hex <= 'F')) {
        ret = hex - 'A' + 10;
    } else if ((hex >= 'a') && (hex <= 'f')) {
        ret = hex - 'a' + 10;
    }
    return ret;
}

uint16_t rgb888_to_rgb565(uint8_t r, uint8_t g, uint8_t b) {
    uint16_t b2 = b >> 3;
    uint16_t g2 = (g >> 2) << 5;
    uint16_t r2 = (r >> 3) << 11;

    return r2 | g2 | b2;
}

uint16_t parse_rgb888_to_rgb565(const std::string& rgbStr) {
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    // We could use std::stoul, however, we need component-wise values
    for (int j = 0, i = rgbStr.size() - 1; i >= 0; i--, j++) {
        uint8_t z = hex2int(rgbStr[i]);
        switch (j) {
            case 0: {
                b = z;
                break;
            }
            case 1: {
                b = (z << 4) | b;
                break;
            }
            case 2: {
                g = z;
                break;
            }
            case 3: {
                g = (z << 4) | g;
                break;
            }
            case 4: {
                r = z;
                break;
            }
            case 5: {
                r = (z << 4) | r;
                break;
            }
            default:
                i = -1;  // break out of loop
        }
    }

    return rgb888_to_rgb565(r, g, b);
}

}  // namespace ledController
}  // namespace senseHat
}  // namespace experienceManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
