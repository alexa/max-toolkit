/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/


#ifndef MULTIAGENTEXPERIENCE_IPC_MESSAGING_VOIDMESSAGETYPES_H
#define MULTIAGENTEXPERIENCE_IPC_MESSAGING_VOIDMESSAGETYPES_H

#include "Message.h"
#include "Payload.h"

namespace multiAgentExperience {
namespace ipc {
namespace messaging {
enum class VoidReturnEnum {
    VOID
};

struct VoidPayload: Payload {
};

using VoidMessage = Message<VoidReturnEnum, VoidPayload>;

inline VoidMessage createVoidMessage(const Reference& reference) {
    return {reference, reference::getNullReference(), VoidReturnEnum::VOID, VoidPayload()};
}

} // namespace messaging
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_MESSAGING_VOIDMESSAGETYPES_H
