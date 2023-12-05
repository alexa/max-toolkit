/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_REFERENCELISTPAYLOAD_H
#define MULTIAGENTEXPERIENCE_IPC_REFERENCELISTPAYLOAD_H

#include <vector>
#include "Reference.h"
#include "Payload.h"


namespace multiAgentExperience {
namespace ipc {
namespace messaging {
struct ReferenceListPayload: Payload {
    ReferenceListPayload(std::vector<Reference> references): m_references{references} {
    }

    std::vector<Reference> m_references;
};
} // namespace messaging
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_REFERENCELISTPAYLOAD_H
