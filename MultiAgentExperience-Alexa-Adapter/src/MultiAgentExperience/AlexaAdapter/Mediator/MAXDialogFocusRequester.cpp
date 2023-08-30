/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/AlexaAdapter/Mediator/MAXDialogFocusRequester.h"

#include "MultiAgentExperience/AlexaAdapter/Alexa/AlexaChannelNames.h"
#include "MultiAgentExperience/AlexaAdapter/Utils/ConversionUtils.h"

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace mediator {

static const std::string TAG("MAXDialogFocusRequester");
#define LX(event) alexaClientSDK::avsCommon::utils::logger::LogEntry(TAG, event)

void MAXDialogFocusRequester::initialize(
        const std::weak_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface> &mediatorCallbacks) {
    m_mediatorCallbacks = mediatorCallbacks;
}

void MAXDialogFocusRequester::request(
        const avsCommon::avs::FocusRequest &focusRequest,
        std::shared_ptr<std::promise<utils::FocusResult>> promise) {
    if (auto mediatorCallbacks = m_mediatorCallbacks.lock()) {
        auto dialogState = getFocusRequestDialogStateAffinity(focusRequest);
        if (!m_activeDialogRequest || m_activeDialogRequest->isFinished()) {
            auto dialogBargeInPriority = getDialogBargeInPriorityFromFocusRequest(focusRequest);
            m_activeDialogRequest =
                    std::make_shared<dialog::AlexaDialogRequest>(
                            m_maxDialogManager,
                            focusRequest.focusRequestId,
                            dialogState,
                            promise,
                            m_controlReceiver,
                            m_mediatorCallbacks,
                            dialogBargeInPriority);

            ACSDK_DEBUG3(LX(__func__).m("Creating a new dialog request"));

            m_maxDialogManager->request(m_activeDialogRequest);
        } else {
            ACSDK_DEBUG3(LX(__func__)
                .m("Transitioning current dialog to a new state")
                .d("dialogState", dialogStateToString(dialogState)));
            m_activeDialogRequest->transitionTo(focusRequest.focusRequestId, promise, dialogState);
        }
    } else {
        ACSDK_WARN(LX(__func__).m("Unable to create a dialog request. Operation not permitted."));
        promise->set_value(utils::FocusResult{std::errc::operation_not_permitted});
    }
}

void MAXDialogFocusRequester::requestThinking(std::shared_ptr<std::promise<utils::FocusResult>>
promise) {
  if (!m_activeDialogRequest || m_activeDialogRequest->isFinished()) {
    promise->set_value(utils::FocusResult{std::errc::operation_not_permitted});

    return;
  }

  if (m_activeDialogRequest->getDialogState() == dialog::DialogState::SPEAKING) {
    promise->set_value(utils::FocusResult{std::errc::operation_not_permitted});

    return;
  }

  m_activeDialogRequest->transitionToThinking(promise);
}

std::weak_ptr<dialog::AlexaDialogRequest> MAXDialogFocusRequester::getCurrentDialog() {
    return m_activeDialogRequest;
}

void MAXDialogFocusRequester::stopRequest() {
    if (m_activeDialogRequest) {
        m_activeDialogRequest->stop();
        m_activeDialogRequest = nullptr;
    }
}

alexaClientSDK::multiAgentExperience::dialog::DialogState MAXDialogFocusRequester::getFocusRequestDialogStateAffinity(
        const alexaClientSDK::avsCommon::avs::FocusRequest& focusRequest) {
    auto usage = focusRequest.focusRequestMetadata.audioAttributes.usage;
    switch(usage) {
        case alexaClientSDK::avsCommon::avs::AudioAttributes::Usage::AUDIO_CAPTURE:
            return alexaClientSDK::multiAgentExperience::dialog::DialogState::LISTENING;
        case alexaClientSDK::avsCommon::avs::AudioAttributes::Usage::SPEECH:
            return alexaClientSDK::multiAgentExperience::dialog::DialogState::SPEAKING;
        default:
            return alexaClientSDK::multiAgentExperience::dialog::DialogState::UNKNOWN;
    }
}

::multiAgentExperience::dialog::DialogBargeInPriority MAXDialogFocusRequester::getDialogBargeInPriorityFromFocusRequest(
    const alexaClientSDK::avsCommon::avs::FocusRequest& focusRequest) {
    auto usage = focusRequest.focusRequestMetadata.audioAttributes.usage;
    switch(usage) {
        case alexaClientSDK::avsCommon::avs::AudioAttributes::Usage::SPEECH:
            return ::multiAgentExperience::dialog::DialogBargeInPriority::HIGH;
        case alexaClientSDK::avsCommon::avs::AudioAttributes::Usage::AUDIO_CAPTURE:
        default:
            return ::multiAgentExperience::dialog::DialogBargeInPriority::NORMAL;
    }
}

} // namespace mediator
} // namespace multiAgentExperience
} // namespace alexaClientSDK