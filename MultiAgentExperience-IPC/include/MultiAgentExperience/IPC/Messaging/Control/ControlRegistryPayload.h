/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_CONTROLREGISTRYPAYLOAD_H
#define MULTIAGENTEXPERIENCE_IPC_CONTROLREGISTRYPAYLOAD_H
#include <list>
#include <tuple>

#include <MultiAgentExperience/IPC/Messaging/Payload.h>
#include <MultiAgentExperience/IPC/Messaging/Reference.h>

#include <MultiAgentExperience/Control/Control.h>

namespace multiAgentExperience {
namespace ipc {
namespace messaging {
namespace control {

struct ControlRegistryPayload: multiAgentExperience::ipc::messaging::Payload {
    ControlRegistryPayload(std::list<std::tuple<
            multiAgentExperience::ipc::messaging::Reference,
            multiAgentExperience::control::ControlType>> referenceControlTypesList)
        : m_referenceControlTypesList{referenceControlTypesList} {
    }

    std::list<
        std::tuple<
                multiAgentExperience::ipc::messaging::Reference,
            multiAgentExperience::control::ControlType>> m_referenceControlTypesList;
};

} // namespace control
} // namespace messaging
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_CONTROLREGISTRYPAYLOAD_H
