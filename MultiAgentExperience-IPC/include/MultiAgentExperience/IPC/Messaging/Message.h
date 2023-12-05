/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_MESSAGING__MESSAGE_H
#define MULTIAGENTEXPERIENCE_IPC_MESSAGING__MESSAGE_H

#include "Reference.h"
#include "Payload.h"

namespace multiAgentExperience {
namespace ipc {
namespace messaging {
template<typename FunctionEnumType, typename PayloadType>
class Message {
    static_assert(std::is_base_of<Payload, PayloadType>::value, "PayloadType must derive from Payload");
    static_assert(std::is_enum<FunctionEnumType>::value, "FunctionEnumType must be an enum");
public:
    Message(
            const Reference reference,
            const Reference returnReference,
            FunctionEnumType function,
            const PayloadType payload) :
            m_reference{std::move(reference)},
            m_returnReference{std::move(returnReference)},
            m_function{function},
            m_payload{payload} {
    }

    Message(const Message& rhs):
            m_function{rhs.m_function},
            m_payload{rhs.m_payload},
            m_reference{rhs.m_reference},
            m_returnReference{rhs.m_returnReference}{
    }

    const Reference& getReference() const {
        return m_reference;
    }

    bool hasReturnReference() {
        return !reference::isNullReference(m_returnReference);
    }

    const Reference& getReturnReference() const {
        return m_returnReference;
    }

    FunctionEnumType getFunction() const {
        return m_function;
    }

    const PayloadType& getPayload() const {
        return m_payload;
    }

private:
    const Reference m_reference;
    const Reference m_returnReference;
    const FunctionEnumType m_function;
    const PayloadType m_payload;
};

} // namespace messaging
} // namespace ipc
} // namespace multiAgentExperience


#endif //MULTIAGENTEXPERIENCE_IPC_MESSAGING__MESSAGE_H
