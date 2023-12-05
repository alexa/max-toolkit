/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_GRPC_GRPCRECEIVERINTERFACE_H
#define MULTIAGENTEXPERIENCE_IPC_GRPC_GRPCRECEIVERINTERFACE_H

#include <maxrpc.grpc.pb.h>

namespace multiAgentExperience {
namespace ipc {
namespace grpc {
namespace transport {
class GrpcReceiverInterface {
public:
    virtual ~GrpcReceiverInterface() = default;
    virtual void receiveAndHandle(const MultiAgentExperience::Rpc::Message* message) = 0;
    virtual bool waitForReady() = 0;
};
} // namespace transport
} // namespace grpc
} // namespace ipc
} // namespace multiAgentExperience


#endif //MULTIAGENTEXPERIENCE_IPC_GRPC_GRPCRECEIVERINTERFACE_H
