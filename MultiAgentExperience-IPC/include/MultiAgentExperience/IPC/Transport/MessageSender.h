/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_TESTABLEDEVICE_MESSAGESENDER_H
#define MULTIAGENTEXPERIENCE_TESTABLEDEVICE_MESSAGESENDER_H

#include <future>
#include <utility>
#include "TransportSenderInterface.h"


namespace multiAgentExperience {
namespace ipc {
namespace transport {

class MessageSender {
public:
    explicit MessageSender(std::shared_ptr<transport::TransportSenderInterface> transport) :
        m_transport{std::move(transport)} {
    }

    template<typename FunctionEnum, typename Payload>
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(const multiAgentExperience::ipc::messaging::Message<FunctionEnum, Payload>& message) {
        return send<multiAgentExperience::ipc::messaging::VoidReturnEnum, multiAgentExperience::ipc::messaging::VoidPayload, FunctionEnum, Payload>(message);
    }

    template<typename ReturnEnum, typename ReturnPayload, typename FunctionEnum, typename Payload>
    std::future<multiAgentExperience::ipc::messaging::Message<ReturnEnum, ReturnPayload>> send(const multiAgentExperience::ipc::messaging::Message<FunctionEnum, Payload>& message) {
        auto response = m_transport->send(message);
        return response;
    }

    void updateTransportSender(std::shared_ptr<transport::TransportSenderInterface> transport) {
        m_transport = transport;
    }

private:
    std::shared_ptr<transport::TransportSenderInterface> m_transport;
};

} // namespace transport
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_TESTABLEDEVICE_MESSAGESENDER_H
