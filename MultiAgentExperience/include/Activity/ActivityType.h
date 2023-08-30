/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYTYPE_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYTYPE_H_

#include <set>

namespace multiAgentExperience {
namespace library {
namespace activity {

enum class ActivityType { DIALOG, COMMUNICATIONS, ALERTS, NOTIFICATIONS, CONTENT, NONE };

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

template <>
struct std::hash<multiAgentExperience::library::activity::ActivityType> {
    std::size_t operator()(multiAgentExperience::library::activity::ActivityType const& activityType) const noexcept {
        return static_cast<int>(activityType);
    }
};

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYTYPE_H_
