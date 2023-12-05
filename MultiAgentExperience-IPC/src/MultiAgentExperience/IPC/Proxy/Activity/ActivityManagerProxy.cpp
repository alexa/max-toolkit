/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/IPC/Proxy/Activity/ActivityManagerProxy.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace activity {

static const std::string MODULE_TAG("ActivityManagerProxy");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ActivityManagerProxy::ActivityManagerProxy(
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<transport::MessageSender> sender,
        std::shared_ptr<MessageHandlerStore> messageHandlerStore):
        MaxIpcComponentsBaseProxy(std::move(reference), transport::MaxApiType::ACTIVITY_MANAGER, std::move(sender)),
        m_messageHandlerStore{std::move(messageHandlerStore)} {}

void ActivityManagerProxy::request
        (std::shared_ptr<multiAgentExperience::activity::ActivityRequestInterface> request) {
    LX(DEBUG0, "");
    auto requestWrapper = m_messageHandlerStore->createOrGet(request);
    auto packagedArguments = m_packager.package(request);
    auto message =
            multiAgentExperience::ipc::messaging::createMessage<models::activity::ActivityManagerFunctions, multiAgentExperience::ipc::messaging::ReferencePayload>(
                    m_reference,
                    models::activity::ActivityManagerFunctions::REQUEST,
                    packagedArguments);

    m_sender->send(message);
}

void ActivityManagerProxy::stop(std::shared_ptr<multiAgentExperience::activity
::ActivityRequestInterface> request) {
    LX(DEBUG0, "");
    // Ideally this needs to be done for every API. createorGet the messageHandler from the message store
    // Consider a case where an agent creates an ActivityRequest and calls request API. The max library
    // uses the id from the request and then does not use the instance, this causes the corresponding
    // proxy go out of scope. The corresponding message handler will also go out of scope.
    // In a UDC when the stop is called on the Control task, the agent manager stop
    // api is called with the request again. If the proxy is created without the corresponding message handler
    // it will cause this api to fail.
    auto requestWrapper = m_messageHandlerStore->createOrGet(request);
    auto reference = multiAgentExperience::ipc::messaging::reference::createReference(request);
    auto packagedArguments = m_packager.package(request);
    auto message =
            multiAgentExperience::ipc::messaging::createMessage<models::activity::ActivityManagerFunctions, multiAgentExperience::ipc::messaging::ReferencePayload>(
                    m_reference,
                    models::activity::ActivityManagerFunctions::STOP,
                    packagedArguments);

    m_sender->send(message);
}

} // namespace activity
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience