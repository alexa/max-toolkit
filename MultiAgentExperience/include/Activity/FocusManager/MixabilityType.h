/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_FOCUSMANAGER_MIXABILITYTYPE_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_FOCUSMANAGER_MIXABILITYTYPE_H_

#include <string>

namespace multiAgentExperience {
namespace library {
namespace activity {

/**
 * Provided with each Activity request to classify its requirements for mixing with
 * other Activity output.
 */
enum class MixabilityType {

    /**
     * Indicates that the corresponding Activity is mixable with other channels, and
     * requires Activities in the background to attenuate their output appropriately.
     * For example such Activities may duck, pause, or reduce frequency of ouput.
     */
    MIXABLE_RESTRICTED,

    /// Indicates that the corresponding Activity is not mixable with other channels in
    /// any situation.
    NONMIXABLE,

    /// Indicates that the corresponding Activity can play without any restrictions
    /// alongside other activity output. This applies to specific Activity use cases.
    MIXABLE_UNRESTRICTED
};

/**
 * This function converts the provided @c MixabilityType to a string.
 *
 * @param mixabilityType The @c MixabilityType to convert to a string.
 * @return The string conversion of @c mixabilityType.
 */
inline std::string mixabilityTypeToString(MixabilityType mixabilityType) {
    switch (mixabilityType) {
        case MixabilityType::MIXABLE_RESTRICTED:
            return "MIXABLE_RESTRICTED";
        case MixabilityType::NONMIXABLE:
            return "NONMIXABLE";
        case MixabilityType::MIXABLE_UNRESTRICTED:
            return "MIXABLE_UNRESTRICTED";
        default:
            return "UNKNOWN";
    }
}

/**
 * Write a @c MixabilityType value to an @c ostream as a string.
 *
 * @param stream The stream to write the value to.
 * @param mixabilityType The @c MixabilityType value to write to the @c ostream as a string.
 * @return The @c ostream that was passed in and written to.
 */
inline std::ostream& operator<<(std::ostream& stream, const MixabilityType& mixabilityType) {
    return stream << mixabilityTypeToString(mixabilityType);
}

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_FOCUSMANAGER_MIXABILITYTYPE_H_
