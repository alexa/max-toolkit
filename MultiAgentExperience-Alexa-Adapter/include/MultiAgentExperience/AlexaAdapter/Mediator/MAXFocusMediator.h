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
#include <MultiAgentExperience/Dialog/DialogManagerInterface.h>

#include "MAXActivityFocusRequester.h"
#include "MultiAgentExperience/AlexaAdapter/Activity/AlexaActivityHandler.h"
#include "MAXDialogFocusRequester.h"
#include "MultiAgentExperience/AlexaAdapter/Dialog/AlexaDialogRequest.h"
#include "MultiAgentExperience/AlexaAdapter/Dialog/AlexaDialogTransitionHandler.h"
#include "MultiAgentExperience/AlexaAdapter/Utils/ConversionUtils.h"

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace mediator {

class MAXFocusMediator : public alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorInterface {
public:
    explicit MAXFocusMediator(
            const std::shared_ptr<::alexaClientSDK::avsCommon::utils::threading::Executor>& executor =
                std::make_shared<::alexaClientSDK::avsCommon::utils::threading::Executor>()) :
            m_executor{executor} {
    }

    bool initialize(
            const std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface> &callbackInterface,
            const std::vector<CallbackChannelConfiguration> &callbackChannelConfigurations) final;

    void onReady(
            std::shared_ptr<MAXActivityFocusRequesterInterface> activityFocusRequester,
            std::shared_ptr<MAXDialogFocusRequesterInterface> dialogFocusRequester);

    alexaClientSDK::avsCommon::utils::threading::Promise<alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusMediatorFocus>
    acquireFocus(const alexaClientSDK::avsCommon::avs::FocusRequest &focusRequest) final;

    void onFocusRelease(const std::string &focusRequestId) final;

    void onThinkingReceived();

    bool isReady();

private:
    std::shared_ptr<alexaClientSDK::avsCommon::utils::threading::Executor> m_executor;
    std::shared_ptr<MAXActivityFocusRequesterInterface> m_activityFocusRequester;
    std::shared_ptr<MAXDialogFocusRequesterInterface> m_dialogFocusRequester;
    std::weak_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface> m_mediatorCallbacks;
    std::map<std::string, std::string> m_focusRequestIdToChannelName;

    alexaClientSDK::avsCommon::utils::threading::Promise<alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusMediatorFocus>
    handleNotReadyRequest(const alexaClientSDK::avsCommon::avs::FocusRequest& focusRequest);

    alexaClientSDK::avsCommon::utils::threading::Promise<alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusMediatorFocus>
    handleFocusRequest(const alexaClientSDK::avsCommon::avs::FocusRequest& focusRequest);

    void handleFocusRelease(const std::string &focusRequestId);

    void handleThinking();

    static bool isActivityChannel(const std::string& channelName);
};

} // namespace mediator
} // namespace multiAgentExperience
} // namespace alexaClientSDK

#endif //MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_MEDIATOR_MAXFOCUSMEDIATOR_H
