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
