/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/IPC/gRPC/Connection/GrpcConnectionConfiguration.h"

namespace multiAgentExperience {
namespace ipc {
namespace grpc {
namespace connection {

static const std::string MODULE_TAG("GrpcConnectionConfiguration");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

/// We don't want to allow the creation of this object if the necessary input parameters to the
/// constructor are null or empty strings (or nullptr's in future) and hence we throw an exception
/// to the calling code in order to reflect that
GrpcConnectionConfiguration::GrpcConnectionConfiguration(const std::string& clientUri,
                                                         const std::string& serverUri) {
    if (clientUri.empty()) {
        LX(ERROR, "ClientUri can't be null or empty for a GrpcConnection");
        throw std::invalid_argument("passed clientUri is null or empty");
    }

    if (serverUri.empty()) {
        LX(ERROR, "ServerUri can't be null or empty for a GrpcConnection");
        throw std::invalid_argument("passed serverUri is null or empty");
    }

    m_clientUri = clientUri;
    m_serverUri = serverUri;
}

std::string GrpcConnectionConfiguration::getClientUri() {
    return m_clientUri;
}

std::string GrpcConnectionConfiguration::getServerUri() {
    return m_serverUri;
}

void GrpcConnectionConfiguration::setClientUri(const std::string& clientUri) {
    m_clientUri = clientUri;
}
void GrpcConnectionConfiguration::setServerUri(const std::string& serverUri) {
    m_serverUri = serverUri;
}

} // namespace connection
} // namespace grpc
} // namespace ipc
} // namespace multiAgentExperience