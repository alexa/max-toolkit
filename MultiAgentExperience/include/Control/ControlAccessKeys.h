/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CONTROLACCESSKEYS_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CONTROLACCESSKEYS_H_

#include <mutex>
#include <set>

#include "ControlAccessKey.h"

namespace multiAgentExperience {
namespace library {
namespace control {

class ControlAccessKeys {
public:
    const ControlAccessKey requestAccessKey();

    bool hasAccess(const ControlAccessKey& accessKey);

    void revokeAccess(const ControlAccessKey& accessKey);

private:
    std::mutex m_keyMutex;
    std::set<ControlAccessKey> m_validKeys;
};

}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CONTROLACCESSKEYS_H_
