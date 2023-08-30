/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_EXPERIENCE_EXPERIENCE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_EXPERIENCE_EXPERIENCE_H_

#include <string>

#include "MultiAgentExperience/Actor/ActorId.h"

#include "ExperienceId.h"

namespace multiAgentExperience {
namespace experience {

/**
 * An Experience contains all the data required to describe a particular 'user experience'
 */
struct Experience {
    using SessionId = unsigned int;
    /// The id of the actor requesting the 'user experience'
    actor::ActorId actorId;
    /// The id of the experience session corresponding to this experience
    SessionId sessionId;
    /// The name or unique identifier for the experience among any other experiences the agent may request
    ExperienceId experienceId;
};

}  // namespace experience
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_EXPERIENCE_EXPERIENCE_H_
