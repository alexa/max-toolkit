/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_TRANSPORTFUTURERESPONSESTORE_H
#define MULTIAGENTEXPERIENCE_IPC_TRANSPORTFUTURERESPONSESTORE_H

#include <MultiAgentExperience/IPC/Messaging/EnumPayload.h>
#include <MultiAgentExperience/Activity/ActivityType.h>
#include <MultiAgentExperience/IPC/Messaging/Message.h>
#include <MultiAgentExperience/IPC/Messaging/ReferencePayload.h>

#include <map>
#include <memory>

#include "TransportFutureResponse.h"
#include "MultiAgentExperience/IPC/Models/Activity/ActivityRequestModel.h"

namespace multiAgentExperience {
namespace ipc {
namespace transport {

/**
 * This class stores the @c TransportFutureResponse objects for the particular Message type sent in a request (using its Reference).
 */
class TransportFutureResponseStore {
public:

    /**
     * Creates a FutureResponse object and stores it in the store. The object is created based on the Reference in the ExpectedMessage.
     * This method will likely by used by the transport layer (for example - GrpcTransportSender).
     * @tparam ExpectedMessage The Message object that is sent in an API request
     * @return The TransportFutureResponse object
     */
    template<typename ExpectedMessage>
    std::shared_ptr<transport::TransportFutureResponse<ExpectedMessage>> createFutureResponse() {

        std::unique_lock<std::mutex> lock(m_mutex);

        auto future = std::make_shared<transport::TransportFutureResponse<ExpectedMessage>>();
        auto reference = future->getReference();
        auto& map = getMapForReturnType<ExpectedMessage>();
        map[reference] = future;

        // Iterate over the map and remove expired entries. This operation should be quick, since we don't expect too
        // many entries in the map. Hence, this should be safe to perform synchronously.
        auto it = map.begin();
        while (it != map.end()) {
            auto weakTransportFutureResponse = it->second;
            if (weakTransportFutureResponse.expired()) {
                it = map.erase(it);
            } else {
                ++it;
            }
        }

        return future;
    }

    template<typename ExpectedMessage>
    std::weak_ptr<transport::TransportFutureResponse<ExpectedMessage>> get(
            const multiAgentExperience::ipc::messaging::Reference& reference) {

        std::unique_lock<std::mutex> lock(m_mutex);

        auto& map = getMapForReturnType<ExpectedMessage>();
        auto entry = map.find(reference);
        if (entry != map.end()) {
            auto handler = entry->second;
            if (auto validHandler = handler.lock()) {
                return handler;
            } else {
                map.erase(entry);
            }
        }
        return std::weak_ptr<transport::TransportFutureResponse<ExpectedMessage>>();
    }

private:

    /// Mutex to serialize access to all the TransportFutureResponse maps like m_activityRequestGetTypeFutures,
    /// m_agentRegistrationGetIdAndGetNameFutures etc.
    std::mutex m_mutex;

    /**
     * These maps contain the TransportFutureResponse objects for each request. The requests are APIs
     * that are synchronous (with non-void return type).
     */
    std::map<
        multiAgentExperience::ipc::messaging::Reference,
        std::weak_ptr<transport::TransportFutureResponse<
            multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestFunctionReturns,
                multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::activity::ActivityType>>>>> m_activityRequestGetTypeFutures;
    std::map<
        multiAgentExperience::ipc::messaging::Reference,
        std::weak_ptr<transport::TransportFutureResponse<
            multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestFunctionReturns,
                multiAgentExperience::ipc::messaging::ReferencePayload>>>> m_activityRequestGetHandlerFutures;

    std::map<
        multiAgentExperience::ipc::messaging::Reference,
        std::weak_ptr<transport::TransportFutureResponse<
            multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestFunctionReturns,
                multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::activity::MixabilityType>>>>> m_activityRequestGetMixabilityTypeFutures;

    std::map<multiAgentExperience::ipc::messaging::Reference,
        std::weak_ptr<transport::TransportFutureResponse<
            multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctionReturns,
                multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::dialog::DialogBargeInPriority>>>>> m_dialogRequestGetDialogBargeInPriorityFutures;

    std::map<multiAgentExperience::ipc::messaging::Reference,
             std::weak_ptr<transport::TransportFutureResponse<
                 multiAgentExperience::ipc::messaging::Message<models::agent::AgentRegistrationFunctionReturns,
                                                  multiAgentExperience::ipc::messaging::StringPayload>>>>
                                                  m_agentRegistrationGetIdAndGetNameFutures;

    template<typename ExpectedMessage>
    std::map<
        multiAgentExperience::ipc::messaging::Reference,
        std::weak_ptr<transport::TransportFutureResponse<ExpectedMessage>>>& getMapForReturnType();
};

} // namespace transport
} // namespace ipc
} // namespace multiAgentExperience

template<>
inline std::map<
    multiAgentExperience::ipc::messaging::Reference,
    std::weak_ptr<multiAgentExperience::ipc::transport::TransportFutureResponse<
        multiAgentExperience::ipc::messaging::Message<multiAgentExperience::ipc::models::activity::ActivityRequestFunctionReturns,
            multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::activity::ActivityType>>>>>
            &multiAgentExperience::ipc::transport::TransportFutureResponseStore::getMapForReturnType() {
    return m_activityRequestGetTypeFutures;
}

template<>
inline std::map<
    multiAgentExperience::ipc::messaging::Reference,
    std::weak_ptr<multiAgentExperience::ipc::transport::TransportFutureResponse<
        multiAgentExperience::ipc::messaging::Message<multiAgentExperience::ipc::models::activity::ActivityRequestFunctionReturns,
            multiAgentExperience::ipc::messaging::ReferencePayload>>>>
            &multiAgentExperience::ipc::transport::TransportFutureResponseStore::getMapForReturnType() {
    return m_activityRequestGetHandlerFutures;
}

template<>
inline std::map<
    multiAgentExperience::ipc::messaging::Reference,
    std::weak_ptr<multiAgentExperience::ipc::transport::TransportFutureResponse<
        multiAgentExperience::ipc::messaging::Message<multiAgentExperience::ipc::models::activity::ActivityRequestFunctionReturns,
            multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::activity::MixabilityType>>>>>
            &multiAgentExperience::ipc::transport::TransportFutureResponseStore::getMapForReturnType() {
    return m_activityRequestGetMixabilityTypeFutures;
}

template<>
inline std::map<
    multiAgentExperience::ipc::messaging::Reference,
    std::weak_ptr<multiAgentExperience::ipc::transport::TransportFutureResponse<
        multiAgentExperience::ipc::messaging::Message<multiAgentExperience::ipc::models::dialog::DialogRequestFunctionReturns,
            multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::dialog::DialogBargeInPriority>>>>>
            &multiAgentExperience::ipc::transport::TransportFutureResponseStore::getMapForReturnType() {
    return m_dialogRequestGetDialogBargeInPriorityFutures;
}

template<>
inline std::map<
    multiAgentExperience::ipc::messaging::Reference,
    std::weak_ptr<multiAgentExperience::ipc::transport::TransportFutureResponse<
        multiAgentExperience::ipc::messaging::Message<multiAgentExperience::ipc::models::agent
        ::AgentRegistrationFunctionReturns,
        multiAgentExperience::ipc::messaging::StringPayload>>>>
        &multiAgentExperience::ipc::transport::TransportFutureResponseStore::getMapForReturnType() {
    return m_agentRegistrationGetIdAndGetNameFutures;
}

#endif //MULTIAGENTEXPERIENCE_IPC_TRANSPORTFUTURERESPONSESTORE_H
