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

#include "Utils/Base64.h"

#include <vector>

namespace multiAgentExperience {
namespace samples {
namespace agents {
namespace computer {
namespace utils {

static const std::string ENCODING_STRING_MAP = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};

std::string base64_encode(const std::string& in) {
    std::string out;
    int val = 0;
    int valb = -6;

    for (unsigned char c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back(ENCODING_STRING_MAP[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }

    if (valb > -6) {
        out.push_back(ENCODING_STRING_MAP[((val << 8) >> (valb + 8)) & 0x3F]);
    }

    while (out.size() % 4) {
        out.push_back('=');
    }

    return out;
}

std::string base64_decode(const std::string& in) {
    std::string out;
    std::vector<int> T(256, -1);

    for (int i = 0; i < 64; i++) {
        T[ENCODING_STRING_MAP[i]] = i;
    }

    int val = 0;
    int valb = -8;

    for (unsigned char c : in) {
        if (T[c] == -1) {
            break;
        }

        val = (val << 6) + T[c];
        valb += 6;

        if (valb >= 0) {
            out.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }

    return out;
}

}  // namespace utils
}  // namespace computer
}  // namespace agents
}  // namespace samples
}  // namespace multiAgentExperience
