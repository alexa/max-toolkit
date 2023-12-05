/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_CONTROLRECEIVERPAYLOAD_H
#define MULTIAGENTEXPERIENCE_IPC_CONTROLRECEIVERPAYLOAD_H

#include <list>
#include <set>

#include <MultiAgentExperience/IPC/Messaging/Payload.h>
#include <MultiAgentExperience/IPC/Messaging/Reference.h>

#include <MultiAgentExperience/Control/Control.h>

namespace multiAgentExperience {
namespace ipc {
namespace messaging {
namespace dialog {

struct ControlReceiverPayload: multiAgentExperience::ipc::messaging::Payload {
    ControlReceiverPayload(multiAgentExperience::ipc::messaging::Reference reference,
                           std::set<multiAgentExperience::control::ControlType> controlTypes)
                           : m_reference{reference} {
        std::copy(controlTypes.begin(), controlTypes.end(), std::back_inserter(m_controlTypes));
    }

    multiAgentExperience::ipc::messaging::Reference m_reference;
    std::list<multiAgentExperience::control::ControlType> m_controlTypes;
};

} // namespace dialog
} // namespace messaging
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_CONTROLRECEIVERPAYLOAD_H
