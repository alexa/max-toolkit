/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_ALEXA_ACTIVITYCHANNELNAMES_H
#define MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_ALEXA_ACTIVITYCHANNELNAMES_H

#include <string>

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace alexa {

struct AlexaChannelNames {
    static const std::string DIALOG;
    static const std::string COMMUNICATIONS;
    static const std::string ALERTS;
    static const std::string NOTIFICATION;
    static const std::string CONTENT;

    static bool isValidName(const std::string& candidate);
    static bool isActivityChannel(const std::string& candidate);
};

} // namespace alexa
} // namespace multiAgentExperience
} // namespace alexaClientSDK

#endif //MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_ALEXA_ACTIVITYCHANNELNAMES_H
