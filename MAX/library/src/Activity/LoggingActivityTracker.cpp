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

#include "Activity/LoggingActivityTracker.h"
#include "Utils/Logger/Logger.h"

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
