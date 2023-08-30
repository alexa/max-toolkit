/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_DIALOG_ALEXADIALOGREQUEST_H
#define MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_DIALOG_ALEXADIALOGREQUEST_H

#include <memory>
#include <utility>

#include <MultiAgentExperience/Dialog/DialogManagerInterface.h>
#include <MultiAgentExperience/Dialog/DialogRequestInterface.h>

#include <MultiAgentExperience/Experience/ExperienceControllerInterface.h>

#include "AlexaDialogTransitionHandler.h"
#include "AlexaControlReceiver.h"
#include "DialogState.h"
#include "MultiAgentExperience/AlexaAdapter/Utils/FocusResult.h"

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace dialog {

class AlexaDialogRequest :
        public ::multiAgentExperience::dialog::DialogRequestInterface  {
public:
    AlexaDialogRequest(
            std::shared_ptr<::multiAgentExperience::dialog::DialogManagerInterface> maxDialogManager,
            std::string focusRequestId,
            DialogState startingState,
            std::shared_ptr<std::promise<utils::FocusResult>> promise,
            std::shared_ptr<AlexaControlReceiver> controlReceiver,
            std::weak_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface> mediatorCallbacks,
            ::multiAgentExperience::dialog::DialogBargeInPriority dialogBargeInPriority) :
            m_maxDialogManager{std::move(maxDialogManager)},
            m_currentFocusRequestId{std::move(focusRequestId)},
            m_startingState{startingState},
            m_requestResolved{false},
            m_grantedPromise{std::move(promise)},
            m_controlReceiver{std::move(controlReceiver)},
            m_mediatorCallbacks{std::move(mediatorCallbacks)},
            m_dialogBargeInPriority{dialogBargeInPriority},
            m_currentDialogState{DialogState::UNKNOWN} {
    }


    void onDenied(const std::string &denialMessage) final;

    void onDialogStarted(std::shared_ptr<::multiAgentExperience::dialog::DialogControllerInterface> controller) final;

    void onError(const std::string &errorMessage) final;

    void onDialogStopped() final;

    bool isFinished();

    ::multiAgentExperience::dialog::DialogBargeInPriority getDialogBargeInPriority() const final;

    void transitionTo(
            const std::string& focusRequestId,
            std::shared_ptr<std::promise<utils::FocusResult>> promise,
            DialogState targetState);

    void transitionToThinking(std::shared_ptr<std::promise<utils::FocusResult>> promise);

    virtual void stop();

    DialogState getDialogState();

    virtual void stopAndInvokeControl(::multiAgentExperience::control::ControlType controlType);

private:
    std::shared_ptr<::multiAgentExperience::dialog::DialogManagerInterface> m_maxDialogManager;
    std::string m_currentFocusRequestId;
    DialogState m_startingState;
    std::atomic_bool m_requestResolved;
    std::shared_ptr<std::promise<utils::FocusResult>> m_grantedPromise;
    std::shared_ptr<std::promise<utils::FocusResult>> m_transitionPromise;
    std::shared_ptr<AlexaControlReceiver> m_controlReceiver;
    std::weak_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface> m_mediatorCallbacks;
    ::multiAgentExperience::dialog::DialogBargeInPriority m_dialogBargeInPriority;

    std::shared_ptr<::multiAgentExperience::dialog::DialogControllerInterface> m_controller;

    DialogState m_currentDialogState;

    void startTransition(
            DialogState targetState,
            std::shared_ptr<AlexaDialogTransitionHandler> transitionHandler);
};

} // namespace dialog
} // namespace multiAgentExperience
} // namespace alexaClientSDK

#endif //MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_DIALOG_ALEXADIALOGREQUEST_H
