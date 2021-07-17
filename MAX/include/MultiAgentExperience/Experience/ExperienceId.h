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

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_EXPERIENCE_EXPERIENCEIDENTIFIER_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_EXPERIENCE_EXPERIENCEIDENTIFIER_H_

#include <string>

#include "MultiAgentExperience/Utils/StrongTypeWrapper.h"

namespace multiAgentExperience {
namespace experience {

using ExperienceId = utils::StrongTypeWrapper<std::string, struct ExperienceIdTag>;

namespace commonIds {

/// A mandatory experience an agent must implement. To be used when the agent is actively listening to audio.
const ExperienceId LISTENING{"listening"};
/// A common experience for an agent to implement. To be used when an agent is speaking.
const ExperienceId SPEAKING{"speaking"};
/// A common experience for an agent to implement. To be used when processing user requests or otherwise "busy".
const ExperienceId THINKING{"thinking"};

}  // namespace commonIds
}  // namespace experience
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_EXPERIENCE_EXPERIENCEIDENTIFIER_H_
