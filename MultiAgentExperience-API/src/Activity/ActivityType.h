/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_ACTIVITY_ACTIVITYTYPE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_ACTIVITY_ACTIVITYTYPE_H_

namespace multiAgentExperience {
namespace activity {

/**
 * The types of supported activities.
 */
enum class ActivityType {
    /// Communication activities should be used for user communication, such as a call.
    COMMUNICATION,
    /// Alerts activities should be used for immediate notification of the user, such as a timer or alarm.
    ALERTS,
    /// Notifications activities should be used for short audio experiences which
    /// notify the customer to take action.
    NOTIFICATIONS,
    /// Content activities should be used for any long form audio which may or may not have an end, such as music.
    CONTENT
};

}  // namespace activity
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_ACTIVITY_ACTIVITYTYPE_H_
