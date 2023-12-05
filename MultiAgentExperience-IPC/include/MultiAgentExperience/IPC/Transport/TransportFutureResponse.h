/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_TRANSPORTFUTURERESPONSE_H
#define MULTIAGENTEXPERIENCE_IPC_TRANSPORTFUTURERESPONSE_H

#include <memory>
#include <future>
#include <utility>

#include <MultiAgentExperience/IPC/Messaging/Reference.h>

#include "MultiAgentExperience/IPC/Config/Config.h"

namespace multiAgentExperience {
namespace ipc {
namespace transport {

/**
 * This class is used by synchronous APIs with non-void return type. For example - ActivityRequestInterface::getType().
 * When such a method is invoked (by process A), it expects to receive a value immediately. However, it must wait until the process
 * on the other side (process B) processes the request and sends back a response. This "wait" is facilitated by a std::future.
 * This is done in the @c waitForResponse method.
 *
 * Once process B receives the request, it processes it and sends back the response as a separate request. Now,
 * process A handles this and retrieves the value. It then sends this value to the waiting future via the corresponding
 * std::promise associated with it. This is done in the @c reply method.
 */
template<typename ExpectedMessage>
class TransportFutureResponse : public std::enable_shared_from_this<TransportFutureResponse<ExpectedMessage>> {
public:
    multiAgentExperience::ipc::messaging::Reference getReference() {
        if (!m_reference) {
            //TODO: we could use the templates instead, but this may work ok.
            m_reference =
                    std::make_shared<multiAgentExperience::ipc::messaging::Reference>(
                            multiAgentExperience::ipc::messaging::reference::createReference("transport", "TransportResponder", this->shared_from_this()));
        }
        return *m_reference;
    }

    void reply(const ExpectedMessage& message) {
        m_promisedMessage.set_value(message);
    }

    ExpectedMessage waitForResponse() {
        //TODO: this needs to handle other cases.
        auto future = m_promisedMessage.get_future();
        //TODO: check if this timeout is correct.
        auto status = future.wait_for(config::SYNCHRONOUS_REQUEST_TIMEOUT);
        return future.get();
    }

private:
    std::shared_ptr<multiAgentExperience::ipc::messaging::Reference> m_reference;
    std::promise<ExpectedMessage> m_promisedMessage;
};

} // namespace transport
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_TRANSPORTFUTURERESPONSE_H
