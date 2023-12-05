/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_TRANSPORTRESPONDER_H
#define MULTIAGENTEXPERIENCE_IPC_TRANSPORTRESPONDER_H

#include <memory>
#include <utility>

#include <MultiAgentExperience/IPC/Messaging/Message.h>
#include <MultiAgentExperience/IPC/Messaging/MessageUtils.h>
#include <MultiAgentExperience/IPC/Messaging/Reference.h>

#include "TransportSenderInterface.h"

namespace multiAgentExperience {
namespace ipc {
namespace transport {

template<typename ReturnEnum, typename Payload>
class TransportResponder {
public:
    explicit TransportResponder(
            multiAgentExperience::ipc::messaging::Reference reference,
            ReturnEnum returnEnum,
            std::shared_ptr<TransportSenderInterface> sender) :
            m_reference{std::move(reference)},
            m_returnEnum{returnEnum},
            m_sender{std::move(sender)} {
    }

    void reply(const Payload& payload) {
        auto message = multiAgentExperience::ipc::messaging::createMessage(m_reference, m_returnEnum, payload);
        m_sender->send(message);
    }
private:
    multiAgentExperience::ipc::messaging::Reference m_reference;
    ReturnEnum m_returnEnum;
    std::shared_ptr<TransportSenderInterface> m_sender;
};

} // namespace transport
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_TRANSPORTRESPONDER_H
