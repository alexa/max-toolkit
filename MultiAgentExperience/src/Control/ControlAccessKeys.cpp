/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
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
