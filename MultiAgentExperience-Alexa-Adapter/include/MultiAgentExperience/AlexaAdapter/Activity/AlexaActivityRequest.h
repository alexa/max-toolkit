/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_ACTIVITY_ALEXAACTIVITYREQUEST_H
#define MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_ACTIVITY_ALEXAACTIVITYREQUEST_H

#include <MultiAgentExperience/Activity/ActivityRequestInterface.h>

#include "AlexaActivityHandler.h"

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace activity {

class AlexaActivityRequest : public ::multiAgentExperience::activity::ActivityRequestInterface {
public:
    AlexaActivityRequest(
            ::multiAgentExperience::activity::ActivityType activityType,
            std::shared_ptr<alexaClientSDK::multiAgentExperience::activity::AlexaActivityHandler> handler,
            ::multiAgentExperience::activity::MixabilityType mixabilityType) :
            ::multiAgentExperience::activity::ActivityRequestInterface(
                    activityType,
                    handler,
                    mixabilityType),
                    m_handler{handler} {
    }

    void release();
private:
    std::shared_ptr<alexaClientSDK::multiAgentExperience::activity::AlexaActivityHandler> m_handler;

};

} // namespace activity
} // namespace multiAgentExperience
} // namespace alexaClientSDK

#endif //MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_ACTIVITY_ALEXAACTIVITYREQUEST_H
