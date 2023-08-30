/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_TRANSFORMEDREQUESTSTORE_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_TRANSFORMEDREQUESTSTORE_H_

#include <memory>
#include <mutex>
#include <unordered_map>

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

template <typename Request, typename TransformedRequest, typename Identifier>
class TransformedRequestStore {
public:
    void storeTransformedRequest(
        std::shared_ptr<Request> request,
        std::shared_ptr<TransformedRequest> transformedRequest) {
        auto hashOfRequest = std::hash<std::shared_ptr<Request>>()(request);
        auto idOfRequest = transformedRequest->getID();
        {
            std::unique_lock<std::mutex> lock{m_activeRequestsMutex};
            m_activeRequestHashToIDs.insert({hashOfRequest, idOfRequest});
        }
    }

    Identifier getTransformedRequestId(std::shared_ptr<Request> request) {
        auto hashOfRequest = std::hash<std::shared_ptr<Request>>()(request);
        {
            std::unique_lock<std::mutex> lock{m_activeRequestsMutex};
            if (m_activeRequestHashToIDs.find(hashOfRequest) != m_activeRequestHashToIDs.end()) {
                return m_activeRequestHashToIDs[hashOfRequest];
            } else {
                return 0;
            }
        }
    }

    void cleanupTransformedRequest(std::shared_ptr<Request> request) {
        auto hashOfRequest = std::hash<std::shared_ptr<Request>>()(request);

        {
            std::unique_lock<std::mutex> lock{m_activeRequestsMutex};
            m_activeRequestHashToIDs.erase(hashOfRequest);
        }
    }

private:
    using RequestHashValue = std::size_t;

    std::mutex m_activeRequestsMutex;
    std::unordered_map<RequestHashValue, Identifier> m_activeRequestHashToIDs;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_TRANSFORMEDREQUESTSTORE_H_
