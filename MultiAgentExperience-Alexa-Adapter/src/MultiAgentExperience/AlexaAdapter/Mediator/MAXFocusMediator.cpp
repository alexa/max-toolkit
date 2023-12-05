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

static const std::string TAG("MAXFocusMediator");
#define LX(event) alexaClientSDK::avsCommon::utils::logger::LogEntry(TAG, event)

bool MAXFocusMediator::initialize(
        const std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface> &callbackInterface,
        const std::vector<CallbackChannelConfiguration> &callbackChannelConfigurations) {
    ACSDK_DEBUG5(LX(__func__));

    m_mediatorCallbacks = callbackInterface;

    if (m_activityFocusRequester) {
        m_activityFocusRequester->initialize(m_mediatorCallbacks, m_focusRequestBuffer, m_executor);
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
        std::shared_ptr<MAXDialogFocusRequesterInterface> dialogFocusRequester,
        std::shared_ptr<::multiAgentExperience::common::OnCompletionCallbackInterface> onCompletionCallback) {
    ACSDK_DEBUG5(LX(__func__));

    m_activityFocusRequester = std::move(activityFocusRequester);
    m_dialogFocusRequester = std::move(dialogFocusRequester);
    m_onCompletionCallback = std::move(onCompletionCallback);

    if (auto mediatorCallbacks = m_mediatorCallbacks.lock()) {
        // we have been initialized by the efm.
        if (m_activityFocusRequester) {
            m_activityFocusRequester->initialize(m_mediatorCallbacks, m_focusRequestBuffer, m_executor);
        }

        if (m_dialogFocusRequester) {
            m_dialogFocusRequester->initialize(m_mediatorCallbacks);
        }
    }

    requestStoredFocusRequests();
}

alexaClientSDK::avsCommon::utils::threading::Promise<alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusMediatorFocus>
MAXFocusMediator::acquireFocus(const avsCommon::avs::FocusRequest &focusRequest) {
    ACSDK_DEBUG5(LX(__func__).d("focusRequestId", focusRequest.focusRequestId));

    /*
     * Any access related to the m_focusRequestBuffer must be submitted to the Executor queue to ensure the order of
     * requests are preserved. Focus requests should be stored right when acquireFocus() is invoked. This is to help
     * in re-requesting these requests in the scenario that MAX is unavailable.
     */
    m_executor->submit([this, focusRequest]() {
        m_focusRequestBuffer->insert(focusRequest.focusRequestId, focusRequest);
    });

    if (isReady()) {
        return {*m_executor, [this, focusRequest]() { return this->handleFocusRequest(focusRequest); }};
    } else {
        return handleNotReadyRequest(focusRequest);
    }
}

void MAXFocusMediator::onFocusRelease(const std::string &focusRequestId) {
    ACSDK_DEBUG5(LX(__func__).d("focusRequestId", focusRequestId));

    /*
     * The isReady() check should occur the task is submitted to the executor.
     *
     * If the isReady() check was inside the executor, and MAX is up by the time the task is getting executed, we would
     * up sending a stop request to MAX when there are no ongoing activities. We want to prevent this.
     */
    if (isReady()) {
        m_executor->submit([this, focusRequestId](){
            handleFocusRelease(focusRequestId);

            // We can safely remove the entry for the focusRequestId here
            m_focusRequestBuffer->remove(focusRequestId);
        });
    } else {
        // If MAX is unavailable, the respective focusRequesters are expected to be nullptrs, hence we manually perform a cleanup
        m_executor->submit([this, focusRequestId](){
            m_focusRequestBuffer->remove(focusRequestId);
        });
    }
}

void MAXFocusMediator::onThinkingReceived() {
    ACSDK_DEBUG5(LX(__func__));

    if (isReady()) {
        m_executor->submit([this]() {
            handleThinking();
        });
    }
}

bool MAXFocusMediator::isReady() {
    ACSDK_DEBUG5(LX(__func__));
    return m_mediatorCallbacks.lock() && m_activityFocusRequester && m_dialogFocusRequester;
}

alexaClientSDK::avsCommon::utils::threading::Promise<
    alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusMediatorFocus>
MAXFocusMediator::waitForFocusRequestResult(std::string focusRequestId, std::shared_ptr<std::promise<utils::FocusResult>> promise) {
    auto future = promise->get_future();
    auto status = future.wait_for(std::chrono::milliseconds(1000)); //TODO: finalize this timeout

    if (status == std::future_status::ready) {
        auto result = future.get();
        if (result.isSuccess()) {
            ACSDK_DEBUG5(LX(__func__).m("Success: focus request was granted").d("focusRequestId", focusRequestId));
            return alexaClientSDK::avsCommon::utils::threading::Promise<
                alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusMediatorFocus>::resolveEmplace(
                result.getFocusState(),
                result.getMixingBehavior());
        } else {
            ACSDK_WARN(LX(__func__).m("Failure: focus request was denied").d("focusRequestId", focusRequestId));
            return alexaClientSDK::avsCommon::utils::threading::Promise<
                alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusMediatorFocus>::reject(
                result.getError());
        }
    } else {
        ACSDK_WARN(LX(__func__).m("Failure: focus request timed out").d("focusRequestId", focusRequestId));
        return alexaClientSDK::avsCommon::utils::threading::Promise<
            alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusMediatorFocus>::reject(
            std::errc::timed_out);
    }
}

void MAXFocusMediator::requestStoredFocusRequests() {
    ACSDK_INFO(LX(__func__).m("Requesting stored focus requests to MAX").d("totalStoredRequests", m_focusRequestBuffer->size()));

    /*
     * This method accomplishes 3 related tasks:
     * 1. All stored activity focus requests are sent to MAX asynchronously, without waiting for a response. This is
     * because MAX is expecting Alexa to trigger the OnCompletionCallback before processing any requests.
     * 2. Once the focus requests are sent, we trigger the OnCompletionCallback.
     * 3. We wait for MAX to send back an onGranted or onDenied response for all the focus requests.
     */
    m_executor->submit([this]() {

        std::vector<std::pair<
            alexaClientSDK::avsCommon::avs::FocusRequest, std::shared_ptr<std::promise<utils::FocusResult>>>> promiseList;

        auto focusRequests = m_focusRequestBuffer->getAllFocusRequests();

        // Send each stored focusRequest to MAX
        for (auto const& focusRequest: focusRequests) {
            if (alexa::AlexaChannelNames::isActivityChannel(focusRequest.focusRequestMetadata.channelName)) {
                auto cleanupCallback = std::make_shared<MAXFocusMediatorCleanupCallback>(
                    shared_from_this(),
                    focusRequest.focusRequestId,
                    m_focusRequestBuffer->getUniqueRequestId(focusRequest.focusRequestId));

                auto promise = std::make_shared<std::promise<utils::FocusResult>>();
                promiseList.emplace_back(focusRequest, promise);
                m_activityFocusRequester->request(focusRequest, promise, cleanupCallback);

            } else {
                ACSDK_DEBUG5(LX("requestStoredFocusRequests").m("Not requesting dialog request to MAX, deleting entry."));
                m_focusRequestBuffer->remove(focusRequest.focusRequestId);
            }
        }

        // Trigger OnCompletionCallback to indicate to MAX that Alexa has requested all stored focus requests
        if (m_onCompletionCallback) {
            ACSDK_DEBUG5(LX("requestStoredFocusRequests").m("Sending the OnCompletionCallback to MAX"));
            m_onCompletionCallback->completed();
        } else {
            ACSDK_WARN(LX("requestStoredFocusRequests").m("OnCompletionCallback was not provided, it must already be executed."));
        }

        // Wait for response for each focusRequest, and send back the response to AVS SDK
        for (auto& entry: promiseList) {
            auto promise = waitForFocusRequestResult(entry.first.focusRequestId, entry.second);
            updateRequest(entry.first, promise);
        }
    });
}

void MAXFocusMediator::updateRequest(
    const alexaClientSDK::avsCommon::avs::FocusRequest& focusRequest,
    avsCommon::utils::threading::Promise<
        avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusMediatorFocus> promise) {
    ACSDK_DEBUG5(LX(__func__).d("focusRequestId", focusRequest.focusRequestId));

    auto onSuccess = [this, focusRequest](
        const avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusMediatorFocus& externalFocus) {

        if (auto mediatorCallbacks = m_mediatorCallbacks.lock()) {
            // On success, we send the focus determined by MAX, to the agent.
            ACSDK_INFO(LX("updateRequest")
                .m("Sending the external focus to AVS SDK")
                .d("focusRequestId", focusRequest.focusRequestId)
                .d("externalFocusState", externalFocus.externalFocusState)
                .d("externalMixingBehavior", externalFocus.externalMixingBehavior));
            mediatorCallbacks->changeFocusState(focusRequest.focusRequestId, externalFocus);
        }

    };

    auto onError = [this, focusRequest](const std::error_condition& error) {

        // On error, we must stop the activity. This is done by sending the FocusState::BACKGROUND and MixingBehavior::MUST_PAUSE.
        avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusMediatorFocus focus {
            avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusState::BACKGROUND,
            avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalMixingBehavior::MUST_PAUSE
        };

        if (auto mediatorCallbacks = m_mediatorCallbacks.lock()) {
            // Update the focus to the agent
            ACSDK_INFO(LX("updateRequest")
                .m("Error occurred: sending background focus to AVS SDK").d("focusRequestId", focusRequest.focusRequestId));
            mediatorCallbacks->changeFocusState(focusRequest.focusRequestId, focus);
        }
    };

    promise.finally(*m_executor, onSuccess, onError);
}

alexaClientSDK::avsCommon::utils::threading::Promise<
        alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusMediatorFocus>
MAXFocusMediator::handleNotReadyRequest(const avsCommon::avs::FocusRequest &focusRequest) {
    ACSDK_DEBUG5(LX(__func__).d("focusRequestId", focusRequest.focusRequestId));

    auto channelName = focusRequest.focusRequestMetadata.channelName;
    if (!alexa::AlexaChannelNames::isActivityChannel(channelName)) {
        ACSDK_DEBUG5(LX(__func__).m("Denying the focus request by default."));

        /*
         * We should clean up the entry for the dialog focusRequest, because we don't want to store it, if MAX is unavailable.
         *
         * Note: it is important to submit this task to the executor, since we are accessing the m_focusRequestBuffer in
         * the getUniqueRequestId() call. Any access of the m_focusRequestBuffer should be made via the Executor queue.
         */
        m_executor->submit([this, focusRequest]() {
            m_focusRequestBuffer->remove(focusRequest.focusRequestId);
        });

        //TODO: this should probably return std::errc::owner_dead but this is returning a unique value for bug tracing atm.
        return alexaClientSDK::avsCommon::utils::threading::Promise<
                alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusMediatorFocus>
        ::reject(std::errc::connection_aborted);
    } else {
        ACSDK_DEBUG5(LX(__func__).m("Granting the focus request by default."));
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
    ACSDK_DEBUG5(LX(__func__).d("focusRequestId", focusRequest.focusRequestId));

    //TODO: we should check for valid channel names first and fail the request if invalid.
    auto channelName = focusRequest.focusRequestMetadata.channelName;

    auto promise = std::make_shared<std::promise<utils::FocusResult>>();

    auto cleanupCallback = std::make_shared<MAXFocusMediatorCleanupCallback>(
        shared_from_this(), focusRequest.focusRequestId, m_focusRequestBuffer->getUniqueRequestId(focusRequest.focusRequestId));

    if (alexa::AlexaChannelNames::isActivityChannel(channelName)) {
        m_activityFocusRequester->request(focusRequest, promise, cleanupCallback);
    } else {
        m_dialogFocusRequester->request(focusRequest, promise, cleanupCallback);
    }

    return waitForFocusRequestResult(focusRequest.focusRequestId, promise);
}

void MAXFocusMediator::handleFocusRelease(const std::string &focusRequestId) {
    ACSDK_DEBUG5(LX(__func__).d("focusRequestId", focusRequestId));

    // TODO: possibly use the ExternalFocusMediatorCallbackInterface to clean up any others which are no longer active.
    auto channelName = m_focusRequestBuffer->getChannelName(focusRequestId);
    if (channelName.empty()) {
        ACSDK_ERROR(LX(__func__)
            .m("Unable to stop activity/dialog. Entry not found for the given focusRequestId.")
            .d("focusRequestId", focusRequestId));
        return;
    }

    if (alexa::AlexaChannelNames::isActivityChannel(channelName)) {
        // for example, this should likely have its own type to manage.
        m_activityFocusRequester->stopRequest(focusRequestId);
    } else {
        m_dialogFocusRequester->stopRequest();
    }
}

void MAXFocusMediator::handleThinking() {
    ACSDK_DEBUG5(LX(__func__));

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

void MAXFocusMediator::cleanup(const std::string& focusRequestId, const std::size_t& uniqueRequestId) {
    ACSDK_DEBUG5(LX(__func__));
    m_executor->submit([this, focusRequestId, uniqueRequestId]() {
        m_focusRequestBuffer->remove(focusRequestId, uniqueRequestId);
        ACSDK_DEBUG5(LX("cleanup").m("Cleanup finished"));
    });
}

void MAXFocusMediator::changeStateToNotReady() {
    ACSDK_DEBUG5(LX(__func__).m("Resetting focus requester objects"));
    // Any future focus requests will be granted/denied using the default behavior logic, until MAX invokes onReady again
    m_activityFocusRequester = nullptr;
    m_dialogFocusRequester = nullptr;
}

} // namespace mediator
} // namespace multiAgentExperience
} // namespace alexaClientSDK

