/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/


#ifndef MULTIAGENTEXPERIENCE_IPC_MESSAGING_REFERENCE_H
#define MULTIAGENTEXPERIENCE_IPC_MESSAGING_REFERENCE_H

#include <string>

#include "Types/TypeName.h"
#include "Types/TypeInstance.h"
#include "Types/TypeUtils.h"

namespace multiAgentExperience {
namespace ipc {
namespace messaging {
class Reference {
public:
    Reference(std::string nspace, std::string name, std::size_t identifier) :
            m_name{nspace, name},
            m_instance{identifier} {
    }

    Reference(const Reference& rhs) {
        m_name.m_nspace = rhs.m_name.m_nspace;
        m_name.m_name = rhs.m_name.m_name;
        m_instance.m_identifier = rhs.m_instance.m_identifier;
    }

    const types::TypeName& getTypeName() const {
        return m_name;
    }

    const types::TypeInstance& getInstance() const {
        return m_instance;
    }

    inline bool operator< (const Reference& rhs) const {
        return std::tie(m_name.m_nspace, m_name.m_name, m_instance.m_identifier) < std::tie(rhs.m_name.m_nspace, rhs.m_name.m_name, rhs.m_instance.m_identifier);
    }

    inline bool operator== (const Reference& rhs) const {
        return std::tie(m_name.m_nspace, m_name.m_name, m_instance.m_identifier) == std::tie(rhs.m_name.m_nspace, rhs.m_name.m_name, rhs.m_instance.m_identifier);
    }
private:
    types::TypeInstance m_instance;
    types::TypeName m_name;
};

inline bool operator> (const Reference& lhs, const Reference& rhs) { return rhs < lhs; }
inline bool operator<=(const Reference& lhs, const Reference& rhs) { return !(lhs > rhs); }
inline bool operator>=(const Reference& lhs, const Reference& rhs) { return !(lhs < rhs); }
inline bool operator!=(const Reference& lhs, const Reference& rhs) { return !(lhs == rhs); }

namespace reference {

template<typename T>
inline Reference createReference(std::string nspace, std::string name, std::shared_ptr<T> const &t) {
    auto identifier = types::getIdentifier<T>(t);
    Reference r(nspace, name, identifier);
    return r;
}

template<typename T>
inline Reference createReference(std::shared_ptr<T> const &t) {
    auto nspace = types::getNamespace<T>(t);
    auto name = types::getName<T>(t);
    return createReference(nspace, name, t);
}

inline Reference getNullReference() {
    static Reference nullReference("", "", 0);
    return nullReference;
}

inline bool isNullReference(const Reference &reference) {
    return reference.getTypeName().m_nspace.empty() && reference.getTypeName().m_name.empty();
}

} // namespace reference
} // namespace messaging
} // namespace ipc
} // namespace multiAgentExperience


#endif //MULTIAGENTEXPERIENCE_IPC_MESSAGING_REFERENCE_H
