/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_ACTIVITY_MIXABILITYTYPE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_ACTIVITY_MIXABILITYTYPE_H_

#include <string>

namespace multiAgentExperience {
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

    /// Indicates that the corresponding Activity can play without imposing any restrictions on
    /// any other activity output. This applies to specific Activity use cases.
    MIXABLE_UNRESTRICTED
};

}  // namespace activity
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_ACTIVITY_MIXABILITYTYPE_H_
