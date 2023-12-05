/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_MEDIATOR_MAXFOCUSMEDIATOR_H
#define MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_MEDIATOR_MAXFOCUSMEDIATOR_H

#include <map>
#include <memory>
#include <utility>
#include <vector>

#include <AVSCommon/AVS/AudioAttributes.h>
#include <AVSCommon/SDKInterfaces/ExternalFocusMediatorInterface.h>
#include <AVSCommon/Utils/Threading/Executor.h>

#include <MultiAgentExperience/Activity/ActivityManagerInterface.h>
#include <MultiAgentExperience/Common/OnCompletionCallbackInterface.h>
#include <MultiAgentExperience/Dialog/DialogManagerInterface.h>

#include "MAXActivityFocusRequester.h"
#include "MAXDialogFocusRequester.h"
#include "MultiAgentExperience/AlexaAdapter/Alexa/AlexaFocusRequestBuffer.h"
#include "MultiAgentExperience/AlexaAdapter/Activity/AlexaActivityHandler.h"
#include "MultiAgentExperience/AlexaAdapter/Dialog/AlexaDialogRequest.h"
#include "MultiAgentExperience/AlexaAdapter/Dialog/AlexaDialogTransitionHandler.h"
#include "MultiAgentExperience/AlexaAdapter/Utils/ConversionUtils.h"

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace mediator {

class MAXFocusMediator
    : public alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorInterface
    , public std::enable_shared_from_this<MAXFocusMediator> {

public:
    explicit MAXFocusMediator(
            const std::shared_ptr<::alexaClientSDK::avsCommon::utils::threading::Executor>& executor =
                std::make_shared<::alexaClientSDK::avsCommon::utils::threading::Executor>(),
            const std::shared_ptr<alexa::AlexaFocusRequestBuffer>& alexaFocusRequestBuffer =
                std::make_shared<alexa::AlexaFocusRequestBuffer>()) :
        m_executor{executor},
        m_focusRequestBuffer{alexaFocusRequestBuffer} {
    }

    bool initialize(
            const std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface> &callbackInterface,
            const std::vector<CallbackChannelConfiguration> &callbackChannelConfigurations) final;

    void onReady(
            std::shared_ptr<MAXActivityFocusRequesterInterface> activityFocusRequester,
            std::shared_ptr<MAXDialogFocusRequesterInterface> dialogFocusRequester,
            std::shared_ptr<::multiAgentExperience::common::OnCompletionCallbackInterface> onCompletionCallback = nullptr);

    alexaClientSDK::avsCommon::utils::threading::Promise<alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusMediatorFocus>
    acquireFocus(const alexaClientSDK::avsCommon::avs::FocusRequest &focusRequest) final;

    void onFocusRelease(const std::string &focusRequestId) final;

    void onThinkingReceived();

    bool isReady();

    void cleanup(const std::string& focusRequestId, const std::size_t& uniqueRequestId);

    /// Resets the focus requesters which makes the state of MAXFocusMediator to not ready, thus initiating default
    /// behavior for focus requests until the MAXFocusMediator is initialized again.
    void changeStateToNotReady();

private:
    std::shared_ptr<alexaClientSDK::avsCommon::utils::threading::Executor> m_executor;
    std::shared_ptr<MAXActivityFocusRequesterInterface> m_activityFocusRequester;
    std::shared_ptr<MAXDialogFocusRequesterInterface> m_dialogFocusRequester;
    std::weak_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface> m_mediatorCallbacks;
    std::map<std::string, std::string> m_focusRequestIdToChannelName;
    std::shared_ptr<alexa::AlexaFocusRequestBuffer> m_focusRequestBuffer;
    std::shared_ptr<::multiAgentExperience::common::OnCompletionCallbackInterface> m_onCompletionCallback;

    alexaClientSDK::avsCommon::utils::threading::Promise<
        alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusMediatorFocus>
    waitForFocusRequestResult(std::string focusRequestId, std::shared_ptr<std::promise<utils::FocusResult>> promise);

    /// Retrieves all focus requests stored in the @c m_focusRequestBuffer and handles them accordingly
    void requestStoredFocusRequests();

    /// Handles the Promise received as a response to the focus request. The success/error is appropriately propagated
    /// to AVS SDK via ExternalFocusMediatorCallbackInterface::changeFocusState
    void updateRequest(
        const alexaClientSDK::avsCommon::avs::FocusRequest& focusRequest,
        avsCommon::utils::threading::Promise<
            avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusMediatorFocus> promise);

    alexaClientSDK::avsCommon::utils::threading::Promise<alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusMediatorFocus>
    handleNotReadyRequest(const alexaClientSDK::avsCommon::avs::FocusRequest& focusRequest);

    alexaClientSDK::avsCommon::utils::threading::Promise<alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusMediatorFocus>
    handleFocusRequest(const alexaClientSDK::avsCommon::avs::FocusRequest& focusRequest);

    void handleFocusRelease(const std::string &focusRequestId);

    void handleThinking();
};

} // namespace mediator
} // namespace multiAgentExperience
} // namespace alexaClientSDK

#endif //MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_MEDIATOR_MAXFOCUSMEDIATOR_H
