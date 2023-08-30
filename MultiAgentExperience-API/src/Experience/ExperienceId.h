/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
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
