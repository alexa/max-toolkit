/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_DIALOG_ALEXADIALOGTRANSITIONREQUEST_H
#define MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_DIALOG_ALEXADIALOGTRANSITIONREQUEST_H

#include <future>
#include <utility>

#include <MultiAgentExperience/Dialog/ListeningHandlerInterface.h>
#include <MultiAgentExperience/Dialog/ThinkingHandlerInterface.h>
#include <MultiAgentExperience/Dialog/SpeakingHandlerInterface.h>

#include "MultiAgentExperience/AlexaAdapter/Utils/FocusResult.h"
#include "MultiAgentExperience/AlexaAdapter/Dialog/AlexaControlReceiver.h"

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace dialog {

class AlexaDialogTransitionHandler :
    public ::multiAgentExperience::dialog::ListeningHandlerInterface,
    public ::multiAgentExperience::dialog::ThinkingHandlerInterface,
    public ::multiAgentExperience::dialog::SpeakingHandlerInterface{

public:
    explicit AlexaDialogTransitionHandler(
        std::shared_ptr<std::promise<utils::FocusResult>> transitionPromise,
        std::shared_ptr<AlexaControlReceiver> alexaControlReceiver = nullptr):
            m_transitioned{false},
            m_transitionPromise{std::move(transitionPromise)},
            m_dialogFocusValue{alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusState::FOREGROUND},
            m_dialogMixingValue{alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalMixingBehavior::UNDEFINED},
            m_alexaControlReceiver{alexaControlReceiver} {
    }

    /// ListeningStateHandlerInterface
    void onStartListening(std::shared_ptr<::multiAgentExperience::dialog::DialogControllerInterface> controller) final;

    void onStopListening() final;

    /// ThinkingStateHandlerInterface
    void onStartThinking(std::shared_ptr<::multiAgentExperience::dialog::DialogControllerInterface> controller) final;

    void onStopThinking() final;

    /// SpeakingStateHandlerInterface
    void onStartSpeaking(
            std::shared_ptr<::multiAgentExperience::dialog::DialogControllerInterface> controller,
            std::shared_ptr<::multiAgentExperience::control::ControlRegistryInterface> controlRegistry) final;

    void onStopSpeaking() final;

    void cancel();

private:
    std::atomic_bool m_transitioned;
    std::shared_ptr<std::promise<utils::FocusResult>> m_transitionPromise;
    alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusState m_dialogFocusValue;
    alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalMixingBehavior m_dialogMixingValue;
    std::shared_ptr<AlexaControlReceiver> m_alexaControlReceiver;

    void resolveTransition();
};

} // namespace dialog
} // namespace multiAgentExperience
} // namespace alexaClientSDK

#endif //MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_DIALOG_ALEXADIALOGTRANSITIONREQUEST_H
