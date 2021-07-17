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
