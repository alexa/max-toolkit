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
    /// Content activities should be used for any long form audio which may or may not have an end, such as music.
    CONTENT
};

}  // namespace activity
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_ACTIVITY_ACTIVITYTYPE_H_
