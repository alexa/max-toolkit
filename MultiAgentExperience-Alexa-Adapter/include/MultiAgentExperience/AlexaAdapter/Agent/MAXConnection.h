/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_AGENT_MAXCONNECTION_H
#define MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_AGENT_MAXCONNECTION_H

#include <string>
#include <utility>
#include <vector>

#include <MultiAgentExperience/Agent/AgentRegistrationInterface.h>
#include <MultiAgentExperience/IPC/gRPC/Connection/MaxConnectionAdapter.h>

#include "MultiAgentExperience/AlexaAdapter/Mediator/MAXFocusMediator.h"

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace agent {

/**
 * @class MAXConnection
 * @brief Represents a class for establishing and managing IPC connections with the MAX process.
 *
 * The MAXConnection class provides functionality to establish the initial connection
 * with the MAX process via Inter-Process Communication (IPC). It abstracts the low-level
 * details of IPC, making it easy for a component to start communicating with the MAX process.
 *
 */
class MAXConnection
    : public ::multiAgentExperience::ipc::transport::MAXServiceAvailabilityObserverInterface
    , public std::enable_shared_from_this<MAXConnection> {
public:
    /**
     * Constructor.
     *
     * @param agentRegistration The Alexa AgentRegistrationInterface object.
     * @param clientUri The host:port string that represents the URI of the gRPC server in the other process.
     * @param serverUri The host:port string that represents the URI of the gRPC server for this process.
     */
    explicit MAXConnection(
        std::shared_ptr<::multiAgentExperience::agent::AgentRegistrationInterface> agentRegistration,
        std::shared_ptr<mediator::MAXFocusMediator> maxFocusMediator,
        const std::string& clientUri,
        const std::string& serverUri):
            m_agentRegistration{std::move(agentRegistration)},
            m_maxFocusMediator{std::move(maxFocusMediator)},
            m_clientUri{clientUri},
            m_serverUri{serverUri} {
    }

    /**
     * This function initiates the connection to the MAX process using IPC mechanisms.
     *
     * @return True if the connection was successfully established, false otherwise.
     */
    bool connect();

    /// @name MAXServiceAvailabilityObserverInterface method overrides.
    /// @{
    void onServiceUnavailable() override;
    /// @}

private:
    std::shared_ptr<::multiAgentExperience::agent::AgentRegistrationInterface> m_agentRegistration;
    std::shared_ptr<mediator::MAXFocusMediator> m_maxFocusMediator;
    std::string m_clientUri;
    std::string m_serverUri;
    /// Hold a reference to the MaxConnectionAdapter so that it does not get destructed and the IPC connection stays alive
    std::shared_ptr<::multiAgentExperience::ipc::grpc::connection::MaxConnectionAdapter> m_maxConnectionAdapter;
};

} // namespace agent
} // namespace multiAgentExperience
} // namespace alexaClientSDK

#endif //MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_AGENT_MAXCONNECTION_H
