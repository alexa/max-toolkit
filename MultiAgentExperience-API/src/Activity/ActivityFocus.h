/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_ACTIVITY_ACTIVITYFOCUS_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_ACTIVITY_ACTIVITYFOCUS_H_

namespace multiAgentExperience {
namespace activity {

/// The different types of focus an activity may have.
enum class ActivityFocus {
    /// With foreground focus, an activity has the primary experience from the user perspective.
    FOREGROUND,
    /// With background focus, an activity has secondary focus and should attenuate its experience to
    /// not interrupt the primary experience.
    BACKGROUND
};

}  // namespace activity
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_ACTIVITY_ACTIVITYFOCUS_H_
