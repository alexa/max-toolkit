/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#include "MultiAgentExperience/AlexaAdapter/Agent/MAXConnection.h"

#include <AVSCommon/Utils/Logger/Logger.h>
#include <MultiAgentExperience/IPC/gRPC/Connection/GrpcConnectionConfiguration.h>

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace agent {

static const std::string TAG("MAXConnection");
#define LX(event) alexaClientSDK::avsCommon::utils::logger::LogEntry(TAG, event)

bool MAXConnection::connect() {
    ACSDK_DEBUG5(LX(__func__));

    if (m_clientUri.empty() || m_serverUri.empty()) {
        ACSDK_ERROR(LX(__func__).m("Connection details required for MAX IPC are incorrect!"));
        return false;
    }

    // Create the configuration object required for the MAX IPC connection, by extracting the client and server URIs
    ::multiAgentExperience::ipc::grpc::connection::GrpcConnectionConfiguration grpcConfig { m_clientUri, m_serverUri };

    ACSDK_DEBUG5(LX(__func__)
        .m("Connection details")
        .d("clientUri", grpcConfig.getClientUri())
        .d("serverUri", grpcConfig.getServerUri()));

    // Creates the connection to the MAX process
    m_maxConnectionAdapter = std::make_shared<::multiAgentExperience::ipc::grpc::connection::MaxConnectionAdapter>(
        m_agentRegistration, grpcConfig);

    m_maxConnectionAdapter->setServiceAvailabilityObserver(shared_from_this());
    m_maxConnectionAdapter->connect();

    return true;
}

void MAXConnection::onServiceUnavailable() {
    ACSDK_DEBUG5(LX(__func__));
    m_maxFocusMediator->changeStateToNotReady();
}

} // namespace agent
} // namespace multiAgentExperience
} // namespace alexaClientSDK