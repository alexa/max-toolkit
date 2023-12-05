/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/AlexaAdapter/Dialog/AlexaDialogTransitionHandler.h"

#include <AVSCommon/Utils/Logger/Logger.h>

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace dialog {

static const std::string TAG("AlexaDialogTransitionHandler");
#define LX(event) alexaClientSDK::avsCommon::utils::logger::LogEntry(TAG, event)

void AlexaDialogTransitionHandler::onStartListening(
        std::shared_ptr<::multiAgentExperience::dialog::DialogControllerInterface> controller) {
    ACSDK_DEBUG7(LX(__func__));
    if(m_alexaControlReceiver) {
        m_alexaControlReceiver->stopExpectingControls();
    }
    resolveTransition();
}

void AlexaDialogTransitionHandler::onStopListening() {
    ACSDK_DEBUG7(LX(__func__));
}

void AlexaDialogTransitionHandler::onStartThinking(
        std::shared_ptr<::multiAgentExperience::dialog::DialogControllerInterface> controller) {
    ACSDK_DEBUG7(LX(__func__));
    resolveTransition();
}

void AlexaDialogTransitionHandler::onStopThinking() {
    ACSDK_DEBUG7(LX(__func__));
}

void AlexaDialogTransitionHandler::onStartSpeaking(
        std::shared_ptr<::multiAgentExperience::dialog::DialogControllerInterface> controller,
        std::shared_ptr<::multiAgentExperience::control::ControlRegistryInterface> controlRegistry) {
    ACSDK_DEBUG7(LX(__func__));
    resolveTransition();
}

void AlexaDialogTransitionHandler::onStopSpeaking() {
    ACSDK_DEBUG7(LX(__func__));
}

void AlexaDialogTransitionHandler::cancel() {
    ACSDK_DEBUG7(LX(__func__));
    auto expected = false;
    if (std::atomic_compare_exchange_strong(&m_transitioned, &expected, true)) {
        //TODO: this should probably return std::errc::owner_dead but this is returning a unique value for bug tracing atm.
        m_transitionPromise->set_value(utils::FocusResult{std::errc::bad_message});
    }
}

void AlexaDialogTransitionHandler::resolveTransition()  {
    ACSDK_DEBUG7(LX(__func__));
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







