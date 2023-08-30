/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYTYPETOCHANNELUTILS_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYTYPETOCHANNELUTILS_H_

#include <vector>

#include "ActivityType.h"
#include "FocusManager/FocusManager.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

static const std::string getChannelForActivityType(const ActivityType& activityType) {
    switch (activityType) {
        case ActivityType::DIALOG:
            return "dialog";
        case ActivityType::COMMUNICATIONS:
            return "communications";
        case ActivityType::ALERTS:
            return "alerts";
        case ActivityType::NOTIFICATIONS:
            return "notifications";
        case ActivityType::CONTENT:
            return "content";
        default:
            return "unknown";
    }
}

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITYTYPETOCHANNELUTILS_H_
