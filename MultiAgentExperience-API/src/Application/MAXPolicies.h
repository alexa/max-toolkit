/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_APPLICATION_MAXPOLICIES_H
#define MULTI_AGENT_EXPERIENCE_INCLUDE_APPLICATION_MAXPOLICIES_H

namespace multiAgentExperience {
namespace application {

/// Cross-agent barge-in policy for Dialogs with DialogBargeInPriority::HIGH.
enum class HighPriorityCrossAgentBargeInPolicy { SUPPORTED, NOT_SUPPORTED };

/// Cross-agent barge-in policy for Dialogs with DialogBargeInPriority::NORMAL
enum class NormalPriorityCrossAgentBargeInPolicy { SUPPORTED, NOT_SUPPORTED };

/**
 * Policy for scheduling simultaneous activities of a particular activity type
 */
enum class ActivitySchedulingPolicy {
    /// Simultaneous activities will stack. A new activity will put any ongoing activity of the same type in the
    /// BACKGROUND. The new activity is moved to the FOREGROUND. On its completion, the most recent BACKGROUND activity
    /// is moved back to the FOREGROUND. The maximum number of activities that may be stacked is 100.
    STACK,

    /// Simultaneous activities will replace the ongoing activity
    REPLACE
};

}  // namespace application
}  // namespace multiAgentExperience

#endif // MULTI_AGENT_EXPERIENCE_INCLUDE_APPLICATION_MAXPOLICIES_H
