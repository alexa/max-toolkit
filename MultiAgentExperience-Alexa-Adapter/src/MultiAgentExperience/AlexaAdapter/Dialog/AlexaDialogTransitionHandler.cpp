/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/AlexaAdapter/Dialog/AlexaDialogTransitionHandler.h"

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace dialog {

void AlexaDialogTransitionHandler::onStartListening(
        std::shared_ptr<::multiAgentExperience::dialog::DialogControllerInterface> controller) {
    if(m_alexaControlReceiver) {
        m_alexaControlReceiver->stopExpectingControls();
    }
    resolveTransition();
}

void AlexaDialogTransitionHandler::onStopListening() {
}

void AlexaDialogTransitionHandler::onStartThinking(
        std::shared_ptr<::multiAgentExperience::dialog::DialogControllerInterface> controller) {
    resolveTransition();
}

void AlexaDialogTransitionHandler::onStopThinking() {
}

void AlexaDialogTransitionHandler::onStartSpeaking(
        std::shared_ptr<::multiAgentExperience::dialog::DialogControllerInterface> controller,
        std::shared_ptr<::multiAgentExperience::control::ControlRegistryInterface> controlRegistry) {
    resolveTransition();
}

void AlexaDialogTransitionHandler::onStopSpeaking() {
}

void AlexaDialogTransitionHandler::cancel() {
    auto expected = false;
    if (std::atomic_compare_exchange_strong(&m_transitioned, &expected, true)) {
        //TODO: this should probably return std::errc::owner_dead but this is returning a unique value for bug tracing atm.
        m_transitionPromise->set_value(utils::FocusResult{std::errc::bad_message});
    }
}

void AlexaDialogTransitionHandler::resolveTransition()  {
    auto expected = false;
    if (std::atomic_compare_exchange_strong(&m_transitioned, &expected, true)) {
        m_transitionPromise->set_value(
                utils::FocusResult{
                        m_dialogFocusValue,
                        m_dialogMixingValue
                });
    }
}

} // namespace dialog
} // namespace multiAgentExperience
} // namespace alexaClientSDK







