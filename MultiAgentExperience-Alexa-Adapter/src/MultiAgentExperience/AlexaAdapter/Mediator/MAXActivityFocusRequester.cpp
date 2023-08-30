/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <vector>
#include "MultiAgentExperience/AlexaAdapter/Mediator/MAXActivityFocusRequester.h"

#include "MultiAgentExperience/AlexaAdapter/Utils/ConversionUtils.h"

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace mediator {

void MAXActivityFocusRequester::initialize(
        const std::weak_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface>& mediatorCallbacks) {
    m_mediatorCallbacks = mediatorCallbacks;
}

void MAXActivityFocusRequester::request(
        const avsCommon::avs::FocusRequest &focusRequest,
        std::shared_ptr<std::promise<utils::FocusResult>> promise) {
    auto request = createActivityRequest(focusRequest, promise);
    if (request) {
        m_focusRequestIdToActiveRequests[focusRequest.focusRequestId] = request;
        m_maxActivityManager->request(request);
    } else {
        promise->set_value(utils::FocusResult{std::errc::operation_not_permitted});
    }
}

void MAXActivityFocusRequester::stopRequest(const std::string &focusRequestId) {
    auto entry = m_focusRequestIdToActiveRequests.find(focusRequestId);
    if (entry != m_focusRequestIdToActiveRequests.end()) {
        auto request = entry->second;
        request->release();
        m_maxActivityManager->stop(request);
        m_focusRequestIdToActiveRequests.erase(entry);
    }
}

std::shared_ptr<activity::AlexaActivityRequest>
MAXActivityFocusRequester::createActivityRequest(
        const avsCommon::avs::FocusRequest &focusRequest,
        std::shared_ptr<std::promise<utils::FocusResult>> promise) {
    if (auto mediatorCallbacks = m_mediatorCallbacks.lock()) {
        auto activityType = utils::convertChannelNameToActivityType(focusRequest.focusRequestMetadata.channelName);
        auto mixabilityType = utils::convertContentTypeToMixabilityType(focusRequest.focusRequestMetadata.contentType);

        auto handler =
                std::make_shared<activity::AlexaActivityHandler>(
                        activityType,
                        focusRequest.focusRequestId,
                        std::move(promise),
                        m_mediatorCallbacks);
        //TODO: determine when to potentially clean these up outside of stopRequest
        return std::make_shared<activity::AlexaActivityRequest>(activityType, handler, mixabilityType);
    }
    return nullptr;
}

} // namespace mediator
} // namespace multiAgentExperience
} // namespace alexaClientSDK
