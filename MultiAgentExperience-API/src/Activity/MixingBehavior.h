/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_ACTIVITY_MIXINGBEHAVIOR_H
#define MULTI_AGENT_EXPERIENCE_INCLUDE_ACTIVITY_MIXINGBEHAVIOR_H

#include <string>

namespace multiAgentExperience {
namespace activity {

/// Provided along with ActivityFocus, and changes whenever multiple Activity
/// requirements have impact on each others mixability.
enum class MixingBehavior {

    /**
     * Indicates that the corresponding Activity may attenuate its output instead
     * of pausing it. This may include duck volume, play less frequently,
     * or otherwise reduce output appropriately.
     */
    MUST_ATTENUATE,

    /// Indicates that the corresponding Activity must pause or stop output.
    MUST_PAUSE,

    /// Indicates there are no restrictions on output.
    UNRESTRICTED
};

}  // namespace activity
}  // namespace multiAgentExperience

#endif //MULTI_AGENT_EXPERIENCE_INCLUDE_ACTIVITY_MIXINGBEHAVIOR_H
