/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_TRANSPORTRECEIVERINTERFACE_H
#define MULTIAGENTEXPERIENCE_IPC_TRANSPORTRECEIVERINTERFACE_H

#include <memory>

#include "TransportHandlerInterface.h"

namespace multiAgentExperience {
namespace ipc {
namespace transport {

class TransportReceiverInterface {
public:
    TransportReceiverInterface(std::shared_ptr<TransportHandlerInterface> handler) : m_handler{handler} {
    }

    virtual ~TransportReceiverInterface() = default;

protected:
    std::shared_ptr<TransportHandlerInterface> m_handler;
};

} // namespace transport
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_TRANSPORTRECEIVERINTERFACE_H
