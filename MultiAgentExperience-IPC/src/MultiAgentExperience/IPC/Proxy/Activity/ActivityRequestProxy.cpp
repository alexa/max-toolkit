/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <MultiAgentExperience/Utils/Logger/Logger.h>
#include "MultiAgentExperience/IPC/Proxy/MessageHandlerStore.h"
#include "MultiAgentExperience/IPC/Config/Config.h"
#include "MultiAgentExperience/IPC/Proxy/Activity/ActivityHandlerProxy.h"
#include "MultiAgentExperience/IPC/Proxy/Activity/ActivityRequestProxy.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace activity {

static const std::string MODULE_TAG("ActivityRequestProxy");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ActivityRequestProxy::ActivityRequestProxy(
        std::shared_ptr<::multiAgentExperience::activity::ActivityHandlerInterface> handler,
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<transport::MessageSender> sender,
        std::shared_ptr<MessageHandlerStore> messageHandlerStore) :
        MaxIpcComponentsBaseProxy(std::move(reference), transport::MaxApiType::ACTIVITY_REQUEST, std::move(sender)),
        ActivityRequestInterface(::multiAgentExperience::activity::ActivityType::COMMUNICATION, std::move(handler)),
        m_messageHandlerStore{std::move(messageHandlerStore)} {
}

multiAgentExperience::activity::ActivityType ActivityRequestProxy::getType() const {
    LX(DEBUG0, "");
    auto message = multiAgentExperience::ipc::messaging::createMessage(
            m_reference,
            models::activity::ActivityRequestGetType::FUNCTION,
            multiAgentExperience::ipc::messaging::VoidPayload());

    auto response = m_sender->send<
            models::activity::ActivityRequestFunctionReturns,
            multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::activity::ActivityType>>(message);

    auto status = response.wait_for(config::SYNCHRONOUS_REQUEST_TIMEOUT);
    if (std::future_status::ready == status) {
        auto payload = response.get().getPayload();
        return payload.m_value;
    } else {
        LX(ERROR, "Error while waiting for the sync API, returning default ActivityType::CONTENT.");
        /// ToDo : have to have this not de a default somehow
        return multiAgentExperience::activity::ActivityType::CONTENT;
    }
}

std::shared_ptr<multiAgentExperience::activity::ActivityHandlerInterface> ActivityRequestProxy::getHandler() const {
    LX(DEBUG0, "");
    auto message = multiAgentExperience::ipc::messaging::createMessage(
            m_reference,
            models::activity::ActivityRequestGetHandler::FUNCTION,
            multiAgentExperience::ipc::messaging::VoidPayload());

    auto response = m_sender->send<
            models::activity::ActivityRequestFunctionReturns,
            multiAgentExperience::ipc::messaging::ReferencePayload>(message);

    auto status = response.wait_for(config::SYNCHRONOUS_REQUEST_TIMEOUT);
    if (std::future_status::ready == status) {
        auto payload = response.get().getPayload();

        auto handler = createOrGet(payload.m_reference);
        return handler;
    } else {
        LX(ERROR, "Error while waiting for the sync API, returning default ActivityHandlerProxy with null Reference.");
        /// ToDo : this is a dummy proxy return, error should be handled here
        return std::make_shared<multiAgentExperience::ipc::proxy::activity::ActivityHandlerProxy>(
            multiAgentExperience::ipc::messaging::reference::getNullReference(), m_sender, m_messageHandlerStore);
    }
}

multiAgentExperience::activity::MixabilityType ActivityRequestProxy::getMixabilityType() const {
    LX(DEBUG0, "");
    auto message = multiAgentExperience::ipc::messaging::createMessage(
            m_reference,
            models::activity::ActivityRequestGetMixabilityType::FUNCTION,
            multiAgentExperience::ipc::messaging::VoidPayload());

    auto response = m_sender->send<
            models::activity::ActivityRequestFunctionReturns,
            multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::activity::MixabilityType>>(message);

    auto status = response.wait_for(config::SYNCHRONOUS_REQUEST_TIMEOUT);
    if (std::future_status::ready == status) {
        auto payload = response.get().getPayload();
        return payload.m_value;
    } else {
        LX(ERROR, "Error while waiting for the sync API, returning default MixabilityType::MIXABLE_RESTRICTED.");
        /// ToDo: Edit this default value with correct one or handle it with an error
        return multiAgentExperience::activity::MixabilityType::MIXABLE_RESTRICTED;
    }
}

std::size_t ActivityRequestProxy::getHash() const {
    // We can directly return the Reference for the Proxy object, since it is unique
    return m_reference.getInstance().m_identifier;
}

std::shared_ptr<ActivityHandlerProxy> ActivityRequestProxy::createOrGet (
        const multiAgentExperience::ipc::messaging::Reference& reference) const {
    auto entry = m_activityHandlerProxies.find(reference);
    if (entry != m_activityHandlerProxies.end()) {
        /// Return the activityHandler proxy found for the reference
        return entry->second.lock();
    } else {
        auto activityHandlerProxy = std::make_shared<multiAgentExperience::ipc::proxy::activity::ActivityHandlerProxy>(
                reference, m_sender, m_messageHandlerStore);
        /// The activityHandlerProxy is mapped to the Reference created for @c apiType object
        m_activityHandlerProxies[reference] = activityHandlerProxy;
        return activityHandlerProxy;
    }
}

} // namespace activity
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience