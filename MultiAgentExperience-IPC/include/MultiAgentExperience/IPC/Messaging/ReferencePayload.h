/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/


#ifndef MULTIAGENTEXPERIENCE_IPC_MESSAGING_REFERENCEPAYLOAD_H
#define MULTIAGENTEXPERIENCE_IPC_MESSAGING_REFERENCEPAYLOAD_H

#include "Reference.h"
#include "Payload.h"


namespace multiAgentExperience {
namespace ipc {
namespace messaging {
struct ReferencePayload: Payload {
    ReferencePayload(Reference reference): m_reference{reference} {
    }
    Reference m_reference;
};
} // namespace messaging
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_MESSAGING_REFERENCEPAYLOAD_H
