/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <MultiAgentExperience/IPC/Messaging/VoidMessageTypes.h>
#include <MultiAgentExperience/IPC/Messaging/Message.h>
#include <MultiAgentExperience/IPC/Messaging/MessageUtils.h>

#include <MultiAgentExperience/Utils/Logger/Logger.h>
#include "MultiAgentExperience/IPC/Transport/MaxIpcComponentsBaseProxy.h"
#include "MultiAgentExperience/Thread/Executor/Threading/Executor.h"

namespace multiAgentExperience {
namespace ipc {
namespace transport {

static const std::string MODULE_TAG("BaseProxy");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

MaxIpcComponentsBaseProxy::MaxIpcComponentsBaseProxy(
        multiAgentExperience::ipc::messaging::Reference reference,
        transport::MaxApiType maxApiType,
        std::shared_ptr<transport::MessageSender> sender) :
        m_reference{std::move(reference)},
        m_maxApiType{maxApiType},
        m_sender{std::move(sender)} {}

MaxIpcComponentsBaseProxy::~MaxIpcComponentsBaseProxy() {
    LX(DEBUG3, "destructor called for proxy with reference name = " + m_reference.getTypeName().m_name
    + " and nameSpace = " + m_reference.getTypeName().m_nspace);
    auto message = multiAgentExperience::ipc::messaging::createMessage(
            m_reference,
            m_maxApiType,
            multiAgentExperience::ipc::messaging::VoidPayload());
    m_sender->send(message);
}

} // namespace transport
} // namespace ipc
} // namespace multiAgentExperience