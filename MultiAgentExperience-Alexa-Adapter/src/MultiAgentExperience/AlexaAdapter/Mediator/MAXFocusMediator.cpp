/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/AlexaAdapter/Mediator/MAXFocusMediator.h"

#include <utility>

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace mediator {

bool MAXFocusMediator::initialize(
        const std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface> &callbackInterface,
        const std::vector<CallbackChannelConfiguration> &callbackChannelConfigurations) {
    m_mediatorCallbacks = callbackInterface;

    if (m_activityFocusRequester) {
        m_activityFocusRequester->initialize(m_mediatorCallbacks);
    }

    if (m_dialogFocusRequester) {
        m_dialogFocusRequester->initialize(m_mediatorCallbacks);
    }

//        for (auto& config : callbackChannelConfigurations) {
//            // TODO: log this, make sure there isnt something weird in the priorities;
//        }

    return true;
}

void MAXFocusMediator::onReady(
        std::shared_ptr<MAXActivityFocusRequesterInterface> activityFocusRequester,
        std::shared_ptr<MAXDialogFocusRequesterInterface> dialogFocusRequester) {
    m_activityFocusRequester = std::move(activityFocusRequester);
    m_dialogFocusRequester = std::move(dialogFocusRequester);

    if (auto mediatorCallbacks = m_mediatorCallbacks.lock()) {
        // we have been initialized by the efm.
        if (m_activityFocusRequester) {
            m_activityFocusRequester->initialize(m_mediatorCallbacks);
        }

        if (m_dialogFocusRequester) {
            m_dialogFocusRequester->initialize(m_mediatorCallbacks);
        }
    }
}

alexaClientSDK::avsCommon::utils::threading::Promise<alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusMediatorFocus>
MAXFocusMediator::acquireFocus(const avsCommon::avs::FocusRequest &focusRequest) {
    if (isReady()) {
        return {*m_executor, [this, focusRequest]() { return this->handleFocusRequest(focusRequest); }};
    } else {
        return handleNotReadyRequest(focusRequest);
    }
}

void MAXFocusMediator::onFocusRelease(const std::string &focusRequestId) {
    if (isReady()) {
        m_executor->submit([this, focusRequestId](){
            handleFocusRelease(focusRequestId);
        });
    }
}

void MAXFocusMediator::onThinkingReceived() {
  if (isReady()) {
    m_executor->submit([this]() {
      handleThinking();
    });
  }
}

bool MAXFocusMediator::isReady() {
    return m_mediatorCallbacks.lock() && m_activityFocusRequester && m_dialogFocusRequester;
}

alexaClientSDK::avsCommon::utils::threading::Promise<
        alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusMediatorFocus>
MAXFocusMediator::handleNotReadyRequest(const avsCommon::avs::FocusRequest &focusRequest) {
    auto channelName = focusRequest.focusRequestMetadata.channelName;
    if (!isActivityChannel(channelName)) {
        //TODO: this should probably return std::errc::owner_dead but this is returning a unique value for bug tracing atm.
        return alexaClientSDK::avsCommon::utils::threading::Promise<
                alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusMediatorFocus>
        ::reject(std::errc::connection_aborted);
    } else {
        //TODO: verify these are the right values expected by EFM for this use case.
        return alexaClientSDK::avsCommon::utils::threading::Promise<
                alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusMediatorFocus>
        ::resolveEmplace(
                alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusState::FOREGROUND,
                alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalMixingBehavior::UNDEFINED);
    }
}

alexaClientSDK::avsCommon::utils::threading::Promise<alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusMediatorFocus>
MAXFocusMediator::handleFocusRequest(const avsCommon::avs::FocusRequest &focusRequest) {
    //TODO: we should check for valid channel names first and fail the request if invalid.
    auto channelName = focusRequest.focusRequestMetadata.channelName;
    m_focusRequestIdToChannelName[focusRequest.focusRequestId] = focusRequest.focusRequestMetadata.channelName;

    auto promise = std::make_shared<std::promise<utils::FocusResult>>();

    if (isActivityChannel(channelName)) {
        m_activityFocusRequester->request(focusRequest, promise);
    } else {
        m_dialogFocusRequester->request(focusRequest, promise);
    }

    auto future = promise->get_future();
    auto status = future.wait_for(std::chrono::milliseconds(1000)); //TODO: finalize this timeout

    if (status == std::future_status::ready) {
        auto result = future.get();
        if (result.isSuccess()) {
            return alexaClientSDK::avsCommon::utils::threading::Promise<
                    alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusMediatorFocus>::resolveEmplace(
                    result.getFocusState(),
                    result.getMixingBehavior());
        } else {
            return alexaClientSDK::avsCommon::utils::threading::Promise<
                    alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusMediatorFocus>::reject(
                    result.getError());
        }
    } else {
        return alexaClientSDK::avsCommon::utils::threading::Promise<
                alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusMediatorFocus>::reject(
                std::errc::timed_out);
    }
}

void MAXFocusMediator::handleFocusRelease(const std::string &focusRequestId) {
    // TODO: possibly use the ExternalFocusMediatorCallbackInterface to clean up any others which are no longer active.
    auto channelName = m_focusRequestIdToChannelName[focusRequestId];
    m_focusRequestIdToChannelName.erase(focusRequestId);
    if (channelName.empty()) {
        return;
    }

    if (isActivityChannel(channelName)) {
        // for example, this should likely have its own type to manage.
        m_activityFocusRequester->stopRequest(focusRequestId);
    } else {
        m_dialogFocusRequester->stopRequest();
    }
}

void MAXFocusMediator::handleThinking() {
  auto promise = std::make_shared<std::promise<utils::FocusResult>>();

  /// try transitioning to THINKING state using the MAXDialogFocusRequester
  m_dialogFocusRequester->requestThinking(promise);

  auto future = promise->get_future();
  auto status = future.wait_for(std::chrono::milliseconds(1000)); //TODO: finalize this timeout

  if (status == std::future_status::ready) {
    auto result = future.get();
    if (result.isSuccess()) {
      /// TODO : need to add success logs once the logger is live
    } else {
      /// TODO : need to add failure logs once the logger is live
    }
  } else {
    /// TODO : need to add timed_out logs once the logger is live
  }
}

bool MAXFocusMediator::isActivityChannel(const std::string& channelName) {
    return alexa::AlexaChannelNames::isValidName(channelName) && channelName !=  alexa::AlexaChannelNames::DIALOG;
}

} // namespace mediator
} // namespace multiAgentExperience
} // namespace alexaClientSDK

