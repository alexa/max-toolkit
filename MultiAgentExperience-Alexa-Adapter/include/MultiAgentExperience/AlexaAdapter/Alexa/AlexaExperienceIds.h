/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_ALEXA_EXPERIENCEIDS_H
#define MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_ALEXA_EXPERIENCEIDS_H

#include <string>

#include <MultiAgentExperience/Experience/ExperienceId.h>

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace alexa {

struct AlexaExperienceIds {
    static const ::multiAgentExperience::experience::ExperienceId COMMUNICATIONS;
    static const ::multiAgentExperience::experience::ExperienceId ALERTS;
    static const ::multiAgentExperience::experience::ExperienceId PENDING_NOTIFICATION;
    static const ::multiAgentExperience::experience::ExperienceId DND;
};

} // namespace alexa
} // namespace multiAgentExperience
} // namespace alexaClientSDK

#endif //MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_ALEXA_EXPERIENCEIDS_H
