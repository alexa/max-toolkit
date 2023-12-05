/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_ALEXA_ALEXAREQUESTBUFFER_H
#define MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_ALEXA_ALEXAREQUESTBUFFER_H

#include <functional>
#include <map>
#include <mutex>
#include <string>

#include <AVSCommon/AVS/FocusRequest.h>

#include "MultiAgentExperience/AlexaAdapter/Activity/AlexaActivityRequest.h"

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace alexa {

class CompositeFocusRequest {
public:
    CompositeFocusRequest() {}

    std::shared_ptr<alexaClientSDK::avsCommon::avs::FocusRequest> m_focusRequest;

    /// Used in activity request flows only.
    std::shared_ptr<alexaClientSDK::multiAgentExperience::activity::AlexaActivityRequest> m_activityRequest;

    /// Has a value >= 1. Since AVS SDK uses the same focusRequestIds for the same activity types, this m_uniqueRequestId
    /// makes the entry uniquely identifiable.
    std::size_t m_uniqueRequestId;
};

/// This class is used for storing the focusRequest and other related objects. Also used for storing
/// any focus requests received from AVS SDK, so that they may be re-requested to MAX in the event of a Alexa/MAX process crash.
class AlexaFocusRequestBuffer {

public:
    /// Inserts an entry for the focusRequestId in the m_focusRequestBuffer. A uniqueRequestId (>= 1) is created and stored too.
    void insert(const std::string& focusRequestId, const alexaClientSDK::avsCommon::avs::FocusRequest& focusRequest);

    /// Updates the entry for focusRequestId with the given alexaActivityRequest. Not expected to used for dialog requests,
    void insert(
        const std::string& focusRequestId,
        std::shared_ptr<alexaClientSDK::multiAgentExperience::activity::AlexaActivityRequest> alexaActivityRequest);

    /// Retrieves the channelName for the focusRequestId. Empty string is returned in case the entry does not exist.
    std::string getChannelName(const std::string& focusRequestId);

    /// Retrieves the AlexaActivityRequest for the focusRequestId. A nullptr is returned in case the entry does not exist.
    std::shared_ptr<alexaClientSDK::multiAgentExperience::activity::AlexaActivityRequest> getActivityRequest(const std::string& focusRequestId);

    /// Retrieves the UniqueRequestId for the focusRequestId. 0 is returned in case the entry does not exist.
    std::size_t getUniqueRequestId(const std::string& focusRequestId);

    /// Deletes the entry with key - focusRequestId from the @c m_focusRequestBuffer, based on the uniqueRequestId
    void remove(const std::string& focusRequestId, std::size_t uniqueRequestId);

    /// Deletes the entry with key - focusRequestId from the @c m_focusRequestBuffer
    void remove(const std::string& focusRequestId);

    std::vector<alexaClientSDK::avsCommon::avs::FocusRequest> getAllFocusRequests();

    /// Fetches the number of entries in the @c m_focusRequestBuffer
    std::size_t size();

private:
    /// A map of focusRequestIds (string) -> CompositeFocusRequest objects
    std::map<std::string, CompositeFocusRequest> m_focusRequestBuffer;

    /// Mutex to serialize access to @c m_focusRequestBuffer
    std::mutex m_mutex;
};

} // namespace alexa
} // namespace multiAgentExperience
} // namespace alexaClientSDK

#endif //MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_ALEXA_ALEXAREQUESTBUFFER_H
