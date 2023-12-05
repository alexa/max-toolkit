/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/IPC/Proxy/MessageHandlerStore.h"
#include "MultiAgentExperience/IPC/Proxy/Activity/ActivityRequestMessageHandler.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace activity {

static const std::string MODULE_TAG("ActivityRequestMessageHandler");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ActivityRequestMessageHandler::ActivityRequestMessageHandler(
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<MessageHandlerStore> messageHandlerStore,
        std::shared_ptr<multiAgentExperience::activity::ActivityRequestInterface> request):
        transport::MessageHandler(std::move(reference)),
        m_messageHandlerStore{messageHandlerStore},
        m_request(std::move(request)) {}

void ActivityRequestMessageHandler::handle(
        const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestGetType, multiAgentExperience::ipc::messaging::VoidPayload>& message,
        const std::shared_ptr<transport::TransportResponder<models::activity::ActivityRequestFunctionReturns,
                multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::activity::ActivityType>>> &replyTo) {
    LX(DEBUG0, "ActivityRequestGetType::FUNCTION");
    auto type = m_request->getType();
    auto payload = multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::activity::ActivityType>(type);

    replyTo->reply(payload);
}

void ActivityRequestMessageHandler::handle(
        const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestGetHandler, multiAgentExperience::ipc::messaging::VoidPayload>& message,
        const std::shared_ptr<transport::TransportResponder<
                models::activity::ActivityRequestFunctionReturns,
                multiAgentExperience::ipc::messaging::ReferencePayload>> &replyTo) {
    LX(DEBUG0, "ActivityRequestGetHandler::FUNCTION");
    auto handler =  m_request->getHandler();
    auto handlerHandler = m_messageHandlerStore->createOrGet(handler);
    auto payload = multiAgentExperience::ipc::messaging::ReferencePayload(handlerHandler->getReference());

    replyTo->reply(payload);
}

void ActivityRequestMessageHandler::handle(
        const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestGetMixabilityType, multiAgentExperience::ipc::messaging::VoidPayload>& message,
        const std::shared_ptr<transport::TransportResponder<
                models::activity::ActivityRequestFunctionReturns,
                multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::activity::MixabilityType>>> &replyTo){
    LX(DEBUG0, "ActivityRequestGetMixabilityType::FUNCTION");
    auto mixabilityType =  m_request->getMixabilityType();
    auto payload = multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::activity::MixabilityType>(mixabilityType);

    replyTo->reply(payload);
}

} // namespace activity
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience