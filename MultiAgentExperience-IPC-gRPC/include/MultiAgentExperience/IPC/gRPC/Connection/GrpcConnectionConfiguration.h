/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_GRPCCONNECTIONCONFIGURATION_H
#define MULTIAGENTEXPERIENCE_IPC_GRPCCONNECTIONCONFIGURATION_H

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include <string>

namespace multiAgentExperience {
namespace ipc {
namespace grpc {
namespace connection {

/// Timeout value specifying how long the gRPC channel should wait to be connected to the gRPC server in the other process
static const int CONNECTION_TIMEOUT_MILLISECONDS = 10*1000;
/// The time duration between consecutive "gRPC connection state" checks
static const int CONNECTION_STATUS_CHECK_INTERVAL_MILLISECONDS = 2*1000;
/// Timeout value specifying how long the client should wait for a CONNECTED_TO_MAX message from the other process
static const int CONNECTED_TO_MAX_TIMEOUT_MILLISECONDS = 10*1000;

/// This class will be used to store different parameters that define a Grpc connection for instance
/// URI's, Port Addresses, Timeouts etc. Currently there are only two parameters clientUri &
/// serverUri (this list might or might not be expanded in the near future)
class GrpcConnectionConfiguration {
public:
    /// Constructors
    GrpcConnectionConfiguration() = default;
    GrpcConnectionConfiguration(const std::string& clientUri, const std::string& serverUri);

    std::string getClientUri();
    std::string getServerUri();

    void setClientUri(const std::string& clientUri);
    void setServerUri(const std::string& serverUri);

private:
    /// Fields that are important for a gRPC connection
    std::string m_clientUri;
    std::string m_serverUri;
};

} // namespace connection
} // namespace grpc
} // namespace ipc
} // namespace multiAgentExperience

#endif // MULTIAGENTEXPERIENCE_IPC_GRPCCONNECTIONCONFIGURATION_H