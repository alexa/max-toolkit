/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <vector>
#include "MultiAgentExperience/AlexaAdapter/Mediator/MAXActivityFocusRequester.h"

#include "AVSCommon/Utils/Logger/Logger.h"
#include "MultiAgentExperience/AlexaAdapter/Mediator/MAXFocusMediatorCleanupCallback.h"
#include "MultiAgentExperience/AlexaAdapter/Utils/ConversionUtils.h"

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace mediator {

static const std::string TAG("MAXActivityFocusRequester");
#define LX(event) alexaClientSDK::avsCommon::utils::logger::LogEntry(TAG, event)

void MAXActivityFocusRequester::initialize(
        const std::weak_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface>& mediatorCallbacks,
        const std::shared_ptr<alexa::AlexaFocusRequestBuffer>& focusRequestBuffer,
        const std::shared_ptr<avsCommon::utils::threading::Executor>& executor) {
    ACSDK_DEBUG5(LX(__func__));
    m_mediatorCallbacks = mediatorCallbacks;
    m_focusRequestBuffer = focusRequestBuffer;
    m_executor = executor;
}

void MAXActivityFocusRequester::request(
        const avsCommon::avs::FocusRequest &focusRequest,
        std::shared_ptr<std::promise<utils::FocusResult>> promise,
        std::shared_ptr<MAXFocusMediatorCleanupCallback> cleanupCallback) {
    ACSDK_DEBUG5(LX(__func__));
    auto request = createActivityRequest(focusRequest, promise, cleanupCallback);
    if (request) {
        m_focusRequestBuffer->insert(focusRequest.focusRequestId, request);
        m_maxActivityManager->request(request);
    } else {
        ACSDK_ERROR(LX(__func__).m("Unable to create activity request").d("focusRequestId", focusRequest.focusRequestId));
        promise->set_value(utils::FocusResult{std::errc::operation_not_permitted});
    }
}

void MAXActivityFocusRequester::stopRequest(const std::string &focusRequestId) {
    ACSDK_DEBUG5(LX(__func__));

    auto request = m_focusRequestBuffer->getActivityRequest(focusRequestId);
    if (request) {
        request->release();
        m_maxActivityManager->stop(request);
    } else {
        ACSDK_ERROR(LX(__func__).m("Focus request entry not found. Unable to stop activity request")
                                .d("focusRequestId", focusRequestId));
    }
}

std::shared_ptr<activity::AlexaActivityRequest>
MAXActivityFocusRequester::createActivityRequest(
        const avsCommon::avs::FocusRequest &focusRequest,
        std::shared_ptr<std::promise<utils::FocusResult>> promise,
        std::shared_ptr<MAXFocusMediatorCleanupCallback> cleanupCallback) {
    ACSDK_DEBUG5(LX(__func__));
    if (auto mediatorCallbacks = m_mediatorCallbacks.lock()) {
        auto activityType = utils::convertChannelNameToActivityType(focusRequest.focusRequestMetadata.channelName);
        auto mixabilityType = utils::convertContentTypeToMixabilityType(focusRequest.focusRequestMetadata.contentType);

        auto handler = std::make_shared<activity::AlexaActivityHandler>(
            activityType,
            focusRequest.focusRequestId,
            std::move(promise),
            m_mediatorCallbacks,
            cleanupCallback);

        //TODO: determine when to potentially clean these up outside of stopRequest
        return std::make_shared<activity::AlexaActivityRequest>(activityType, handler, mixabilityType);
    }
    return nullptr;
}

} // namespace mediator
} // namespace multiAgentExperience
} // namespace alexaClientSDK
