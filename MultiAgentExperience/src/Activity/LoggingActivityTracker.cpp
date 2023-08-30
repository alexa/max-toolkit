/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Activity/LoggingActivityTracker.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

static const std::string MODULE_TAG("LoggingActivityTracker");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

void LoggingActivityTracker::notifyOfActivityUpdates(const std::vector<Channel::State>& channelStates) {
    for (auto& channelState : channelStates) {
        auto logValue = std::string("FocusManagerINTERNAL    channel: ");
        logValue.append("name=");
        logValue.append(channelState.name);
        logValue.append(", interfaceName=");
        logValue.append(channelState.interfaceName);
        logValue.append(", focusState=");
        logValue.append(focusStateToString(channelState.focusState));
        LX(DEBUG3, logValue);
    }
}

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience
