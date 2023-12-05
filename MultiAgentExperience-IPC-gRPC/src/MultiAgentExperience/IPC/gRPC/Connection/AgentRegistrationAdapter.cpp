/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/IPC/gRPC/Connection/AgentRegistrationAdapter.h"

#include <MultiAgentExperience/IPC/Proxy/Agent/AgentRegistrationProxy.h>
#include <utility>

namespace multiAgentExperience {
namespace ipc {
namespace grpc {
namespace connection {

static const std::string MODULE_TAG("AgentRegistrationAdapter");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

AgentRegistrationAdapter::AgentRegistrationAdapter(
    std::shared_ptr<agent::AgentManagerInterface> agentManagerInterface,
    GrpcConnectionConfiguration grpcConnectionConfiguration,
    std::shared_ptr<GrpcConnectionBuilderInterface> connectionBuilder,
    std::shared_ptr<multiAgentExperience::thread::executor::threading::Executor> executor):
    m_agentManager{std::move(agentManagerInterface)},
    m_grpcConnectionConfiguration{std::move(grpcConnectionConfiguration)},
    m_grpcConnectionBuilder{std::move(connectionBuilder)},
    m_executor{std::move(executor)} {
}

bool AgentRegistrationAdapter::connect() {
    LX(DEBUG3, "");

    m_grpcConnectionBuilder->setGrpcConnectionConfiguration(m_grpcConnectionConfiguration);
    m_grpcConnectionBuilder->setIpcConnectionListeners({shared_from_this()});
    // This connection is initiated in the MAX process
    m_grpcConnectionBuilder->setConnectionInitiator(GrpcConnection::ConnectionInitiator::MAX);
    m_grpcConnection = m_grpcConnectionBuilder->build();

    if (!m_grpcConnection->establishConnection()) {
        LX(ERROR, "Unable to establish connection.");
        return false;
    }

    LX(INFO, "Creating AgentRegistrationProxy for that will be used for the purposes of agent registration");
    /*
     * For AgentRegistration, we use a hard-coded Reference in multiAgentExperience::ipc::models::agent::AgentRegistrationModel.
     * Regardless of the object passed in createReference<multiAgentExperience::agent::AgentRegistrationInterface>, the
     * hard-coded Reference is used. A nullptr is passed in createReference to indicate that logically, the
     * AgentRegistrationAdapter will not have the actual AgentRegistrationInterface object. This object is implemented by
     * the agent (for example, in AlexaAdapter).
     */
    m_agentRegistration = std::make_shared<maxIpcNamespace::proxy::agent::AgentRegistrationProxy>(
        multiAgentExperience::ipc::messaging::reference::createReference<multiAgentExperience::agent::AgentRegistrationInterface>(nullptr),
        m_grpcConnection->getMessageSender(),
        m_grpcConnection->getMessageHandlerStore());

    return true;
}

void AgentRegistrationAdapter::disconnect() {
    LX(DEBUG3, "")
    if (m_grpcConnection) {
        // TODO: instead of manually clearing the MessageHandlerStore, we should change the MessageHandlers to hold
        //  weak references of the MessageHandlerStore, so that it gets destructed automatically.
        m_grpcConnection->getMessageHandlerStore()->clearStores();
        m_grpcConnection->shutdownServer();
        m_grpcConnection.reset();
    }
}

void AgentRegistrationAdapter::onReady(
        std::shared_ptr<multiAgentExperience::common::OnCompletionCallbackInterface> onCompletionCallback,
        std::shared_ptr<multiAgentExperience::activity::ActivityManagerInterface> activityManager,
        std::shared_ptr<multiAgentExperience::dialog::DialogManagerInterface> dialogManager,
        std::shared_ptr<multiAgentExperience::experience::StaticExperienceManagerInterface> staticExperienceManager) {
    LX(DEBUG3, "");
    m_onReadyCompletionCallback = onCompletionCallback;
    m_agentRegistration->onReady(onCompletionCallback, activityManager, dialogManager, staticExperienceManager);
}

actor::ActorId AgentRegistrationAdapter::getId() {
    LX(DEBUG3, "");
    return m_agentRegistration->getId();
}

std::string AgentRegistrationAdapter::getName() {
    LX(DEBUG3, "");
    return m_agentRegistration->getName();
}

void AgentRegistrationAdapter::onConnectionDisruption() {
    if (!m_mutex.try_lock()) {
        LX(DEBUG3, "Re-connection is ongoing");
        return;
    }

    LX(ERROR, "Connection is disrupted. Trying to establish the connection again.");
    m_executor->submit([this]() {

        if (m_onReadyCompletionCallback) {
            LX(DEBUG3, "Triggering the OnCompletionCallback for onReady before de-registration");
            // Trigger the callback before de-registering the agent to not block the MAX process waiting for it during agent registration
            m_onReadyCompletionCallback->completed();
        }

        // Deregister the agent. On connection disruption because we must re-register the agent for MAX to invoke onReady
        // on the agent again.
        m_agentManager->deregisterAgent(shared_from_this());

        // This connect() method makes sure that all the gRPC related objects are reinitialised and a gRPC connection is fully up.
        // After which we will re-register the agent.
        disconnect();
        if (!connect()) {
            LX(ERROR, "Unable to connect");
            m_mutex.unlock();
            return;
        }
        LX(DEBUG3, "Successfully connected trying to register the agent");

        // We can safely register the same agentRegistration object since it was deregistered previously.
        const bool isRegistered = m_agentManager->registerAgent(shared_from_this());
        if(!isRegistered) {
            LX(ERROR, "registerAgentFailed: unable to register agent");
        }
        m_mutex.unlock();
    });
}

} // namespace connection
} // namespace grpc
} // namespace ipc
} // namespace multiAgentExperience