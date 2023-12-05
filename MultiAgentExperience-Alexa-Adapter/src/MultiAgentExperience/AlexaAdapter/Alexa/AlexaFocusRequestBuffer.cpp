/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#include "MultiAgentExperience/AlexaAdapter/Alexa/AlexaFocusRequestBuffer.h"

#include <utility>

#include <AVSCommon/Utils/Logger/Logger.h>

#include "MultiAgentExperience/AlexaAdapter/Alexa/AlexaChannelNames.h"

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace alexa {

static const std::string TAG("AlexaFocusRequestBuffer");
#define LX(event) alexaClientSDK::avsCommon::utils::logger::LogEntry(TAG, event)

#define NOT_FOUND 0

static std::size_t generateID() {
    static std::size_t id = 1;
    return id++;
}

void AlexaFocusRequestBuffer::insert(const std::string& focusRequestId, const alexaClientSDK::avsCommon::avs::FocusRequest& focusRequest) {
    std::unique_lock<std::mutex> lock(m_mutex);

    auto uniqueRequestId = generateID();
    ACSDK_DEBUG5(LX(__func__).m("Storing focusRequest along with its uniqueRequestId").d("focusRequestId", focusRequestId).d("uniqueRequestId", uniqueRequestId));

    // When we store the focusRequest, we also want to generate the uniqueRequestId and store it. We generate the
    // uniqueRequestId here, because this method is the first method that is invoked when AVS SDK acquires focus.

    // Overwrite the entry if the key already exists
    m_focusRequestBuffer[focusRequestId].m_focusRequest = std::make_shared<alexaClientSDK::avsCommon::avs::FocusRequest>(focusRequest);
    m_focusRequestBuffer[focusRequestId].m_uniqueRequestId = uniqueRequestId;
}

void AlexaFocusRequestBuffer::insert(
    const std::string &focusRequestId,
    std::shared_ptr<alexaClientSDK::multiAgentExperience::activity::AlexaActivityRequest> alexaActivityRequest) {
    ACSDK_DEBUG5(LX(__func__).m("Storing alexaActivityRequest").d("focusRequestId", focusRequestId));
    std::unique_lock<std::mutex> lock(m_mutex);

    m_focusRequestBuffer[focusRequestId].m_activityRequest = std::move(alexaActivityRequest);
}

std::string AlexaFocusRequestBuffer::getChannelName(const std::string& focusRequestId) {
    ACSDK_DEBUG9(LX(__func__));
    std::unique_lock<std::mutex> lock(m_mutex);

    auto it = m_focusRequestBuffer.find(focusRequestId);
    if (it != m_focusRequestBuffer.end()) {
        return m_focusRequestBuffer[focusRequestId].m_focusRequest->focusRequestMetadata.channelName;
    } else {
        ACSDK_ERROR(LX(__func__).m("Entry not found for the given focusRequestId").d("focusRequestId", focusRequestId));
        return "";
    }
}

std::shared_ptr<alexaClientSDK::multiAgentExperience::activity::AlexaActivityRequest> AlexaFocusRequestBuffer::getActivityRequest(
    const std::string& focusRequestId) {
    ACSDK_DEBUG9(LX(__func__));
    std::unique_lock<std::mutex> lock(m_mutex);

    auto it = m_focusRequestBuffer.find(focusRequestId);
    if (it != m_focusRequestBuffer.end()) {
        return m_focusRequestBuffer[focusRequestId].m_activityRequest;
    } else {
        ACSDK_ERROR(LX(__func__).m("Entry not found for the given focusRequestId").d("focusRequestId", focusRequestId));
        return nullptr;
    }
}

std::size_t AlexaFocusRequestBuffer::getUniqueRequestId(const std::string& focusRequestId) {
    ACSDK_DEBUG9(LX(__func__));
    std::unique_lock<std::mutex> lock(m_mutex);

    auto it = m_focusRequestBuffer.find(focusRequestId);
    if (it != m_focusRequestBuffer.end()) {
        return m_focusRequestBuffer[focusRequestId].m_uniqueRequestId;
    } else {
        ACSDK_ERROR(LX(__func__).m("Entry not found for the given focusRequestId").d("focusRequestId", focusRequestId));
        return NOT_FOUND;
    }
}

void AlexaFocusRequestBuffer::remove(const std::string& focusRequestId, std::size_t uniqueRequestId) {
    ACSDK_DEBUG5(LX(__func__).d("focusRequestId", focusRequestId).d("uniqueRequestId", uniqueRequestId));
    std::unique_lock<std::mutex> lock(m_mutex);

    if (m_focusRequestBuffer.find(focusRequestId) != m_focusRequestBuffer.end()) {
        if (m_focusRequestBuffer[focusRequestId].m_uniqueRequestId == uniqueRequestId) {
            m_focusRequestBuffer.erase(focusRequestId);
        } else {
            ACSDK_DEBUG5(LX(__func__).m("Not deleting, since the entry for the focusRequestId passed was updated.").d("focusRequestId", focusRequestId));
        }
    } else {
         ACSDK_WARN(LX(__func__).m("Unable to find the focus request for the focusRequestId passed").d("focusRequestId", focusRequestId));
    }
}

void AlexaFocusRequestBuffer::remove(const std::string& focusRequestId) {
    ACSDK_DEBUG5(LX(__func__).m("Removing entry regardless of uniqueRequestId").d("focusRequestId", focusRequestId));
    std::unique_lock<std::mutex> lock(m_mutex);

    if (m_focusRequestBuffer.find(focusRequestId) != m_focusRequestBuffer.end()) {
        m_focusRequestBuffer.erase(focusRequestId);
    } else {
        ACSDK_WARN(LX(__func__).m("Unable to find the focus request for the focusRequestId passed").d("focusRequestId", focusRequestId));
    }
}

std::vector<alexaClientSDK::avsCommon::avs::FocusRequest> AlexaFocusRequestBuffer::getAllFocusRequests() {
    ACSDK_DEBUG5(LX(__func__));
    std::unique_lock<std::mutex> lock(m_mutex);

    std::vector<alexaClientSDK::avsCommon::avs::FocusRequest> focusRequests;
    for (auto const& entry: m_focusRequestBuffer) {
        focusRequests.push_back(*entry.second.m_focusRequest);
    }

    return focusRequests;
}

std::size_t AlexaFocusRequestBuffer::size() {
    std::unique_lock<std::mutex> lock(m_mutex);

    return m_focusRequestBuffer.size();
}

} // namespace alexa
} // namespace multiAgentExperience
} // namespace alexaClientSDK
