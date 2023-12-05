/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_MESSAGEHANDLER_H
#define MULTIAGENTEXPERIENCE_IPC_MESSAGEHANDLER_H

#include <memory>
#include <MultiAgentExperience/IPC/Messaging/Reference.h>

namespace multiAgentExperience {
namespace ipc {
namespace transport {

class MessageHandler {
public:
    explicit MessageHandler(multiAgentExperience::ipc::messaging::Reference  reference) : m_reference{std::move(reference)} {
    }
    virtual ~MessageHandler() = default;

    const multiAgentExperience::ipc::messaging::Reference& getReference() {
        return m_reference;
    }
private:
    multiAgentExperience::ipc::messaging::Reference m_reference;
};

} // namespace messaging
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_MESSAGEHANDLER_H
