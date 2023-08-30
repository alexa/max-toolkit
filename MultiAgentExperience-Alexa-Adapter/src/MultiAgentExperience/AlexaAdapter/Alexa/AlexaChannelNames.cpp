/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/AlexaAdapter/Alexa/AlexaChannelNames.h"

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace alexa {

const std::string AlexaChannelNames::DIALOG = "Dialog";
const std::string AlexaChannelNames::COMMUNICATIONS = "Communications";
const std::string AlexaChannelNames::ALERTS = "Alert";
const std::string AlexaChannelNames::NOTIFICATION = "Earcon"; //TODO confirm
const std::string AlexaChannelNames::CONTENT = "Content";

bool AlexaChannelNames::isValidName(const std::string &candidate) {
    return !candidate.empty() &&
        (candidate == AlexaChannelNames::DIALOG ||
        candidate == AlexaChannelNames::COMMUNICATIONS ||
        candidate == AlexaChannelNames::ALERTS ||
        candidate == AlexaChannelNames::NOTIFICATION ||
        candidate == AlexaChannelNames::CONTENT);
}

} // namespace alexa
} // namespace multiAgentExperience
} // namespace alexaClientSDK