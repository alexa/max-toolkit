/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/


#ifndef MULTIAGENTEXPERIENCE_IPC_MESSAGING_MESSAGEUTILS_H
#define MULTIAGENTEXPERIENCE_IPC_MESSAGING_MESSAGEUTILS_H

#include <string>
#include "Message.h"
#include "Reference.h"


namespace multiAgentExperience {
namespace ipc {
namespace messaging {
template<typename FunctionEnum>
std::string getName(FunctionEnum value);

template<typename FunctionEnum>
std::string getEnum(const std::string& value);

template<typename FunctionEnumType, typename PayloadType>
Message<FunctionEnumType, PayloadType> createMessage(
        const Reference reference,
        const Reference returnReference,
        FunctionEnumType function,
        const PayloadType payload) {
    Message<FunctionEnumType, PayloadType> message(reference, returnReference, function, payload);
    return message;
}

template<typename FunctionEnumType, typename PayloadType>
Message<FunctionEnumType, PayloadType> createMessage(const Reference reference, FunctionEnumType function, const PayloadType payload) {
    return createMessage(reference, reference::getNullReference(), function, payload);
}

} // namespace messaging
} // namespace ipc
} // namespace multiAgentExperience


#endif //MULTIAGENTEXPERIENCE_IPC_MESSAGING_MESSAGEUTILS_H
