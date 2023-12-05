/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_MEDIATOR_MAXACTIVITYFOCUSREQUESTER_H
#define MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_MEDIATOR_MAXACTIVITYFOCUSREQUESTER_H

#include <future>
#include <map>
#include <memory>

#include <AVSCommon/SDKInterfaces/ExternalFocusMediatorCallbackInterface.h>

#include <MultiAgentExperience/Activity/ActivityManagerInterface.h>

#include "MultiAgentExperience/AlexaAdapter/Activity/AlexaActivityRequest.h"
#include "MultiAgentExperience/AlexaAdapter/Alexa/AlexaFocusRequestBuffer.h"
#include "MultiAgentExperience/AlexaAdapter/Mediator/MAXActivityFocusRequesterInterface.h"
#include "MultiAgentExperience/AlexaAdapter/Utils/FocusResult.h"

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace mediator {

class MAXActivityFocusRequester : public MAXActivityFocusRequesterInterface {

public:
    explicit MAXActivityFocusRequester(
            std::shared_ptr<::multiAgentExperience::activity::ActivityManagerInterface> maxActivityManager) :
            m_maxActivityManager{std::move(maxActivityManager)},
            m_focusRequestIdToActiveRequests{} {
    }

    void initialize(
            const std::weak_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface> &mediatorCallbacks,
            const std::shared_ptr<alexa::AlexaFocusRequestBuffer>& focusRequestBuffer,
            const std::shared_ptr<avsCommon::utils::threading::Executor>& executor) final;

    void request(
            const avsCommon::avs::FocusRequest &focusRequest,
            std::shared_ptr<std::promise<utils::FocusResult>> promise,
            std::shared_ptr<MAXFocusMediatorCleanupCallback> cleanupCallback) final;

    void stopRequest(const std::string &focusRequestId) final;

private:
    std::shared_ptr<::multiAgentExperience::activity::ActivityManagerInterface> m_maxActivityManager;
    std::shared_ptr<avsCommon::utils::threading::Executor> m_executor;
    std::weak_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface> m_mediatorCallbacks;
    std::map<std::string, std::shared_ptr<activity::AlexaActivityRequest>> m_focusRequestIdToActiveRequests;
    std::shared_ptr<alexa::AlexaFocusRequestBuffer> m_focusRequestBuffer;

    std::shared_ptr<activity::AlexaActivityRequest> createActivityRequest(
            const alexaClientSDK::avsCommon::avs::FocusRequest &focusRequest,
            std::shared_ptr<std::promise<utils::FocusResult>> promise,
            std::shared_ptr<MAXFocusMediatorCleanupCallback> cleanupCallback);
};

} // namespace mediator
} // namespace multiAgentExperience
} // namespace alexaClientSDK

#endif //MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_MEDIATOR_MAXACTIVITYFOCUSREQUESTER_H
