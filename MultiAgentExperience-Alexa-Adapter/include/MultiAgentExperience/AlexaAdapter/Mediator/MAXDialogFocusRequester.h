/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_MEDIATOR_MAXDIALOGFOCUSREQUESTER_H
#define MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_MEDIATOR_MAXDIALOGFOCUSREQUESTER_H

#include <future>
#include <memory>
#include <utility>

#include <AVSCommon/SDKInterfaces/ExternalFocusMediatorCallbackInterface.h>
#include <MultiAgentExperience/Dialog/DialogBargeInPriority.h>
#include <MultiAgentExperience/Dialog/DialogManagerInterface.h>

#include "MultiAgentExperience/AlexaAdapter/Dialog/AlexaControlReceiver.h"
#include "MultiAgentExperience/AlexaAdapter/Dialog/AlexaDialogRequest.h"
#include "MultiAgentExperience/AlexaAdapter/Mediator/MAXFocusMediatorCleanupCallback.h"
#include "MultiAgentExperience/AlexaAdapter/Utils/FocusResult.h"

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace mediator {

class MAXDialogFocusRequesterInterface {
public:
    virtual ~MAXDialogFocusRequesterInterface() = default;

    virtual void initialize(const std::weak_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface>& mediatorCallbacks) = 0;

    virtual void request(
            const alexaClientSDK::avsCommon::avs::FocusRequest& focusRequest,
            std::shared_ptr<std::promise<utils::FocusResult>> promise,
            std::shared_ptr<MAXFocusMediatorCleanupCallback> cleanupCallback) = 0;

    virtual void requestThinking(std::shared_ptr<std::promise<utils::FocusResult>> promise) = 0;

    virtual std::weak_ptr<dialog::AlexaDialogRequest> getCurrentDialog() = 0;

    virtual void stopRequest() = 0;
};

class MAXDialogFocusRequester : public MAXDialogFocusRequesterInterface{
public:
    MAXDialogFocusRequester(
            std::shared_ptr<::multiAgentExperience::dialog::DialogManagerInterface> maxDialogManager,
            std::shared_ptr<dialog::AlexaControlReceiver> controlReceiver) :
            m_maxDialogManager{std::move(maxDialogManager)},
            m_controlReceiver{std::move(controlReceiver)} {
    }

    void initialize(const std::weak_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface>& mediatorCallbacks) final;

    void request(
            const alexaClientSDK::avsCommon::avs::FocusRequest& focusRequest,
            std::shared_ptr<std::promise<utils::FocusResult>> promise,
            std::shared_ptr<MAXFocusMediatorCleanupCallback> cleanupCallback) final;

    void requestThinking(std::shared_ptr<std::promise<utils::FocusResult>> promise);

    std::weak_ptr<dialog::AlexaDialogRequest> getCurrentDialog() final;

    void stopRequest() final;

private:
    std::shared_ptr<::multiAgentExperience::dialog::DialogManagerInterface> m_maxDialogManager;
    std::shared_ptr<dialog::AlexaControlReceiver> m_controlReceiver;
    std::weak_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface> m_mediatorCallbacks;
    std::shared_ptr<dialog::AlexaDialogRequest> m_activeDialogRequest;

    alexaClientSDK::multiAgentExperience::dialog::DialogState getFocusRequestDialogStateAffinity(
            const alexaClientSDK::avsCommon::avs::FocusRequest& focusRequest);

    ::multiAgentExperience::dialog::DialogBargeInPriority getDialogBargeInPriorityFromFocusRequest(
        const alexaClientSDK::avsCommon::avs::FocusRequest& focusRequest);
};

} // namespace mediator
} // namespace multiAgentExperience
} // namespace alexaClientSDK

#endif //MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_MEDIATOR_MAXDIALOGFOCUSREQUESTER_H
