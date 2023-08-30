/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CONTROLNAME_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CONTROLNAME_H_

#include <functional>

namespace multiAgentExperience {
namespace library {
namespace control {

enum class ControlName { UNDEFINED, STOP };

}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience

template <>
struct std::hash<multiAgentExperience::library::control::ControlName> {
    std::size_t operator()(multiAgentExperience::library::control::ControlName const& controlName) const noexcept {
        return static_cast<int>(controlName);
    }
};

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CONTROLNAME_H_
