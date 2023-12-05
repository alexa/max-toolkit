/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_GRPC_GRPCCLIENTINTERFACE_H
#define MULTIAGENTEXPERIENCE_IPC_GRPC_GRPCCLIENTINTERFACE_H

#include <maxrpc.grpc.pb.h>

namespace multiAgentExperience {
namespace ipc {
namespace grpc {
namespace transport {
class GrpcClientInterface {
public:
    virtual ~GrpcClientInterface() = default;
    virtual void send(MultiAgentExperience::Rpc::Message message) = 0;
    virtual bool isConnected() = 0;
    virtual bool waitForConnectionEstablished(int timeoutInMilliSeconds) = 0;
    virtual bool setupConnectionMonitoring() = 0;
};
} // namespace transport
} // namespace grpc
} // namespace ipc
} // namespace multiAgentExperience
#endif //MULTIAGENTEXPERIENCE_IPC_GRPC_GRPCCLIENTINTERFACE_H
