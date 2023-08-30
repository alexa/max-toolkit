/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/AlexaAdapter/Alexa/AlexaExperienceIds.h"

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace alexa {

const ::multiAgentExperience::experience::ExperienceId AlexaExperienceIds::COMMUNICATIONS =
        ::multiAgentExperience::experience::ExperienceId("communications");
const ::multiAgentExperience::experience::ExperienceId AlexaExperienceIds::ALERTS =
        ::multiAgentExperience::experience::ExperienceId("alerting");
const ::multiAgentExperience::experience::ExperienceId AlexaExperienceIds::PENDING_NOTIFICATION =
        ::multiAgentExperience::experience::ExperienceId("pending_notification");
const ::multiAgentExperience::experience::ExperienceId AlexaExperienceIds::DND =
        ::multiAgentExperience::experience::ExperienceId("do_not_disturb");

} // namespace alexa
} // namespace multiAgentExperience
} // namespace alexaClientSDK