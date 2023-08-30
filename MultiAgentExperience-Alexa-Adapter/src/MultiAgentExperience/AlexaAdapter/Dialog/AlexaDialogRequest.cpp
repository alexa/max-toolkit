/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/AlexaAdapter/Dialog/AlexaDialogRequest.h"
#include <AVSCommon/Utils/Logger/Logger.h>

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace dialog {

static const std::string TAG("AlexaDialogRequest");
#define LX(event) alexaClientSDK::avsCommon::utils::logger::LogEntry(TAG, event)

void AlexaDialogRequest::onDenied(const std::string &denialMessage) {
    auto expected = false;
    if (std::atomic_compare_exchange_strong(&m_requestResolved, &expected, true)) {
        m_currentDialogState = DialogState::STOPPED;
        m_grantedPromise->set_value(utils::FocusResult{std::errc::operation_not_permitted});
    }
}

void AlexaDialogRequest::onDialogStarted(
        std::shared_ptr<::multiAgentExperience::dialog::DialogControllerInterface> controller) {
    auto expected = false;
    if (std::atomic_compare_exchange_strong(&m_requestResolved, &expected, true)) {
        auto transitionHandler = std::make_shared<AlexaDialogTransitionHandler>(m_grantedPromise, m_controlReceiver);
        m_controller = controller;

        if (m_controlReceiver) {
            m_controlReceiver->clearAvailableControls();
            m_controlReceiver->expectControls();
        }

        startTransition(m_startingState, transitionHandler);
    }
}

void AlexaDialogRequest::onError(const std::string &errorMessage) {
}

void AlexaDialogRequest::onDialogStopped() {
    if (m_currentDialogState != DialogState::STOPPED) {
        m_currentDialogState = DialogState::STOPPED;
        if (auto mediatorCallbacks = m_mediatorCallbacks.lock()) {
            mediatorCallbacks->mediatorReleaseFocus(m_currentFocusRequestId);
        }
    }
    m_maxDialogManager->removeAllHandlers();
}

bool AlexaDialogRequest::isFinished() {
    return m_currentDialogState == DialogState::STOPPED;
}

::multiAgentExperience::dialog::DialogBargeInPriority
AlexaDialogRequest::getDialogBargeInPriority() const {
    return m_dialogBargeInPriority;
}

void AlexaDialogRequest::transitionTo(
        const std::string &focusRequestId,
        std::shared_ptr<std::promise<utils::FocusResult>> promise,
        DialogState targetState) {
    if (m_currentDialogState == DialogState::STOPPED) {
        // not going to reference this edge case anymore, but an ActiveDialog is not
        // reusable, create another one.
        //TODO: this should probably return std::errc::owner_dead but this is returning a unique value for bug tracing atm.
        promise->set_value(utils::FocusResult{std::errc::already_connected});
        return;
    }
    m_currentFocusRequestId = focusRequestId;

    auto transitionHandler = std::make_shared<AlexaDialogTransitionHandler>(promise);
    startTransition(targetState, transitionHandler);
    m_currentDialogState = targetState;
}

void AlexaDialogRequest::transitionToThinking(std::shared_ptr<std::promise<utils::FocusResult>>
promise) {
    if (m_controlReceiver) {
        m_controlReceiver->clearAvailableControls();
    }
    transitionTo(m_currentFocusRequestId, promise, DialogState::THINKING);
}

void AlexaDialogRequest::stop() {
    m_currentDialogState = DialogState::STOPPED;
    m_controller->stop();
}

DialogState AlexaDialogRequest::getDialogState() {
  return m_currentDialogState;
}

void AlexaDialogRequest::stopAndInvokeControl(
        ::multiAgentExperience::control::ControlType controlType) {
    m_controller->stopAndInvokeControl(controlType);
    m_currentDialogState = DialogState::STOPPED;
}

// private below

void AlexaDialogRequest::startTransition(
        DialogState targetState,
        std::shared_ptr<AlexaDialogTransitionHandler> transitionHandler) {
    ACSDK_DEBUG3(LX(""));
    m_maxDialogManager->removeAllHandlers();
    m_maxDialogManager->setControlReceiver(m_controlReceiver);
    switch (targetState) {
        case DialogState::LISTENING:
            m_maxDialogManager->setListeningHandler(transitionHandler);
            m_controller->startListening();
            break;
        case DialogState::THINKING:
            if (m_controlReceiver) {
                m_controlReceiver->clearAvailableControls();
            }
            m_maxDialogManager->setThinkingHandler(transitionHandler);
            m_controller->startThinking();
            break;
        case DialogState::SPEAKING:
            m_maxDialogManager->setSpeakingHandler(transitionHandler);
            m_controller->startSpeaking();
            break;
        default:
            m_controller->stop();
            transitionHandler->cancel();
            break;
    }
    m_currentDialogState = targetState;
}

} // namespace dialog
} // namespace multiAgentExperience
} // namespace alexaClientSDK
