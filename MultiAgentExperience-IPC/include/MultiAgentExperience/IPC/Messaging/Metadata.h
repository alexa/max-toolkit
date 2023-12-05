/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/


#ifndef MULTIAGENTEXPERIENCE_IPC_MESSAGING_METADATA_H
#define MULTIAGENTEXPERIENCE_IPC_MESSAGING_METADATA_H

#include "Reference.h"
#include "Version.h"


namespace multiAgentExperience {
namespace ipc {
namespace messaging {
class Metadata {
public:
    Metadata(const Reference reference):
            m_version{VERSION},
            m_reference{reference} {
    }

    Version getVersion() const {
        return m_version;
    }

    Reference getReference() const {
        return m_reference;
    }

private:
    const Version m_version;
    const Reference m_reference;
};
} // namespace messaging
} // namespace ipc
} // namespace multiAgentExperience


#endif //MULTIAGENTEXPERIENCE_IPC_MESSAGING_METADATA_H
