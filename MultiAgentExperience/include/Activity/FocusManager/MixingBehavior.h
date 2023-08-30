/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_FOCUSMANAGER_MIXINGBEHAVIOR_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_FOCUSMANAGER_MIXINGBEHAVIOR_H_

#include <string>

namespace multiAgentExperience {
namespace library {
namespace activity {

/// Provided along with ActivityFocus, and changes whenever multiple Activity
/// requirements have impact on each others mixability.
/// Note: order needs to be maintained here, since FocusManager::getMixingBehavior relies on it.
enum class MixingBehavior {

    /// Indicates there are no restrictions on output.
    UNRESTRICTED,

    /**
     * Indicates that the corresponding Activity may attenuate its output instead
     * of pausing it. This may include duck volume, play less frequently,
     * or otherwise reduce output appropriately.
     */
    MUST_ATTENUATE,

    /// Indicates that the corresponding Activity must pause or stop output.
    MUST_PAUSE
};


/**
 * This function converts the provided @c MixingBehavior to a string.
 *
 * @param behavior The @c MixingBehavior to convert to a string.
 * @return The string conversion of @c behavior.
 */
inline std::string mixingBehaviorToString(MixingBehavior behavior) {
    switch (behavior) {
        case MixingBehavior::MUST_ATTENUATE:
            return "MUST_ATTENUATE";
        case MixingBehavior::MUST_PAUSE:
            return "MUST_PAUSE";
        case MixingBehavior::UNRESTRICTED:
            return "UNRESTRICTED";
        default:
            return "UNKNOWN";
    }
}

/**
 * Write a @c MixingBehavior value to an @c ostream as a string.
 *
 * @param stream The stream to write the value to.
 * @param behavior The @c MixingBehavior value to write to the @c ostream as a string.
 * @return The @c ostream that was passed in and written to.
 */
inline std::ostream& operator<<(std::ostream& stream, const MixingBehavior& behavior) {
    return stream << mixingBehaviorToString(behavior);
}

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  //  MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_FOCUSMANAGER_MIXINGBEHAVIOR_H_
