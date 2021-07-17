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
