/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_ALEXA_ALEXAAGENTNAMES_H
#define MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_ALEXA_ALEXAAGENTNAMES_H

#include <string>

#include <MultiAgentExperience/Actor/ActorId.h>

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace alexa {

static const std::string ALEXA_AGENT_NAME = "Alexa";

static const ::multiAgentExperience::actor::ActorId ALEXA_ACTOR_ID = ::multiAgentExperience::actor::ActorId{"alexa"};

} // namespace alexa
} // namespace multiAgentExperience
} // namespace alexaClientSDK

#endif //MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_ALEXA_ALEXAAGENTNAMES_H
