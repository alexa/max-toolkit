/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_TRANSPORTFACTORYINTERFACE_H
#define MULTIAGENTEXPERIENCE_IPC_TRANSPORTFACTORYINTERFACE_H

#include <memory>
#include "TransportSenderInterface.h"
#include "TransportHandlerInterface.h"

namespace multiAgentExperience {
namespace ipc {
namespace transport {

class TransportFactoryInterface {
public:
    virtual ~TransportFactoryInterface() = default;

    virtual std::shared_ptr<TransportSenderInterface> createSender() = 0;
};

} // namespace transport
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_TRANSPORTFACTORYINTERFACE_H
