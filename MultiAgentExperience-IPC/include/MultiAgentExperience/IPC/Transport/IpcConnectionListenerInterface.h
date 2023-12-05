/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_TRANSPORT_IPCCONNECTIONLISTENERINTERFACE_H
#define MULTIAGENTEXPERIENCE_IPC_TRANSPORT_IPCCONNECTIONLISTENERINTERFACE_H

#include <memory>

namespace multiAgentExperience {
namespace ipc {
namespace transport {

class IpcConnectionListenerInterface {
public:
    virtual ~IpcConnectionListenerInterface() = default;
    virtual void onConnectionDisruption() = 0;
};

} // namespace transport
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_TRANSPORT_IPCCONNECTIONLISTENERINTERFACE_H
