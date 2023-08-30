/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_UTILS_ACTORID_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_UTILS_ACTORID_H_

#include <string>

#include "MultiAgentExperience/Utils/StrongTypeWrapper.h"

namespace multiAgentExperience {
namespace actor {

/**
 * In the MAX Toolkit an Actor can be an agent or a device.
 * When required, an ActorId can be used to uniquely identify an Actor
 */
using ActorId = utils::StrongTypeWrapper<std::string, struct ActorIdTag>;

}  // namespace actor
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_UTILS_ACTORID_H_
