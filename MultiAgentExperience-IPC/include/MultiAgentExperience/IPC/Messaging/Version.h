/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/


#ifndef MULTIAGENTEXPERIENCE_IPC_MESSAGING_VERSION_H
#define MULTIAGENTEXPERIENCE_IPC_MESSAGING_VERSION_H


namespace multiAgentExperience {
namespace ipc {
namespace messaging {
struct Version {
    constexpr Version(int major, int minor, int patch) : m_major{major}, m_minor{minor}, m_patch{patch} {
    }
    int m_major;
    int m_minor;
    int m_patch;
};

constexpr Version VERSION = Version(1,0,0);
} // namespace messaging
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_MESSAGING_VERSION_H
