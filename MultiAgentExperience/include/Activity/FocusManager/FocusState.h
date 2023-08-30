/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_FOCUSMANAGER_FOCUSSTATE_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_FOCUSMANAGER_FOCUSSTATE_H_

#include <sstream>
#include <string>

namespace multiAgentExperience {
namespace library {
namespace activity {

/**
 * An enum class used to specify the levels of focus that a Channel can have.
 */
enum class FocusState {
    /// Represents the highest focus a Channel can have.
    FOREGROUND,

    /// Represents the intermediate level focus a Channel can have.
    BACKGROUND,

    /// This focus is used to represent when a Channel is not being used or when an observer should stop.
    NONE
};

/**
 * This function converts the provided @c FocusState to a string.
 *
 * @param state The @c FocusState to convert to a string.
 * @return The string conversion of @c state.
 */
inline std::string focusStateToString(FocusState state) {
    switch (state) {
        case FocusState::FOREGROUND:
            return "FOREGROUND";
        case FocusState::BACKGROUND:
            return "BACKGROUND";
        case FocusState::NONE:
            return "NONE";
    }
    return "Unknown State";
}

/**
 * Write a @c FocusState value to an @c ostream as a string.
 *
 * @param stream The stream to write the value to.
 * @param state The @c FocusState value to write to the @c ostream as a string.
 * @return The @c ostream that was passed in and written to.
 */
inline std::ostream& operator<<(std::ostream& stream, const FocusState& state) {
    return stream << focusStateToString(state);
}

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_FOCUSMANAGER_FOCUSSTATE_H_
