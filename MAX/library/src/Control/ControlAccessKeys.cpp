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

#include "Control/ControlAccessKeys.h"

namespace multiAgentExperience {
namespace library {
namespace control {

struct ControlAccessKeyFactory {
    static ControlAccessKey create() {
        static ControlAccessKey id = 1;
        return id++;
    }
};

const ControlAccessKey ControlAccessKeys::requestAccessKey() {
    std::unique_lock<std::mutex> lock(m_keyMutex);
    auto key = ControlAccessKeyFactory::create();
    m_validKeys.insert(key);
    return key;
}

bool ControlAccessKeys::hasAccess(const ControlAccessKey& accessKey) {
    std::unique_lock<std::mutex> lock(m_keyMutex);
    return m_validKeys.find(accessKey) != m_validKeys.end();
}

void ControlAccessKeys::revokeAccess(const ControlAccessKey& accessKey) {
    std::unique_lock<std::mutex> lock(m_keyMutex);
    m_validKeys.erase(accessKey);
}

}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience
