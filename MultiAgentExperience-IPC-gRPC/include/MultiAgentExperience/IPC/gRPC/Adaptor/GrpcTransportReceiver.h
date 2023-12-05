/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_IPC_GRPCTRANSPORT_H
#define MULTIAGENTEXPERIENCE_IPC_GRPCTRANSPORT_H

#include <utility>

#include <MultiAgentExperience/IPC/Messaging/MessageUtils.h>
#include <MultiAgentExperience/IPC/Messaging/ReferencePayload.h>
#include <MultiAgentExperience/Activity/ActivityFocus.h>
#include <MultiAgentExperience/Activity/ActivityType.h>
#include <MultiAgentExperience/IPC/gRPC/Transport/GrpcReceiverInterface.h>
#include <MultiAgentExperience/IPC/Models/Activity/ActivityHandlerModel.h>
#include <MultiAgentExperience/IPC/Transport/TransportReceiverInterface.h>
#include <MultiAgentExperience/IPC/Transport/TransportHandlerInterface.h>
#include <MultiAgentExperience/Thread/Executor/Threading/Executor.h>

#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <maxrpc.grpc.pb.h>

namespace multiAgentExperience {
namespace ipc {
namespace grpc {
namespace adaptor {

/**
 * GrpcTransportReceiver is the adaptor for the Messaging layer in the MultiAgentExperience-IPC. The information
 * coming through from gRPC is converted and passed on to the MessageHandlers./
 */
class GrpcTransportReceiver:
        public MultiAgentExperience::Rpc::MultiAgentExperienceService::Service,
        public multiAgentExperience::ipc::transport::TransportReceiverInterface,
        public transport::GrpcReceiverInterface {

public:
    GrpcTransportReceiver(
        std::shared_ptr<multiAgentExperience::ipc::transport::TransportHandlerInterface> handler,
        std::shared_ptr<multiAgentExperience::ipc::transport::TransportSenderInterface> sender) :
        multiAgentExperience::ipc::transport::TransportReceiverInterface(std::move(handler)),
        m_sender(std::move(sender)) {
    }

    /// @c GrpcReceiverInterface overrides
    /// @{
    void receiveAndHandle(const ::MultiAgentExperience::Rpc::Message* request) override;
    bool waitForReady() override;
    /// @}

private:
    std::shared_ptr<multiAgentExperience::ipc::transport::TransportSenderInterface> m_sender;
    /// Waits for the gRPC client in the process to  RPC
    /// Waits for the other process's client to connect to our server by sending the CONNECTED_TO_MAX message
    std::promise<void> m_connectionWaiter;

    void handleMaxMessage(const ::MultiAgentExperience::Rpc::Message* request);

    void handleActivityManagerMessage(
        const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference);

    void handleActivityRequestGetTypeMessage(
        const MultiAgentExperience::Rpc::Message *request,multiAgentExperience::ipc::messaging::Reference &reference);

    void handleActivityRequestGetHandlerMessage(
        const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference);

    void handleActivityRequestGetMixabilityTypeMessage(
        const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference);

    void handleActivityRequestReturnMessage(
        const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference);

    void handleActivityHandlerMessage(
        const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference);

    void handleActivityControllerMessage(multiAgentExperience::ipc::messaging::Reference &reference);

    void handleDialogControllerMessage(
        const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference);

    void handleDialogManagerMessage(
        const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference);

    void handleDialogRequestMessage(
        const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference);

    void handleDialogRequestGetDialogBargeInPriorityMessage(
        const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference);

    void handleDialogRequestReturnMessage(
        const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference);

    void handleListeningHandlerMessage(
        const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference);

    void handleThinkingHandlerMessage(
        const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference);

    void handleSpeakingHandlerMessage(
        const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference);

    void handleStartListeningCallbackMessage(
        const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference);

    void handleExperienceControllerMessage(
        const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference);

    void handleStaticExperienceManagerMessage(
        const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference);

    void handleControlMessage(
        const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference);

    void handleControlRegistryMessage(
        const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference);

    void handleControlReceiverMessage(
        const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference);

    void handleOnCompletionCallbackMessage(
        const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference);

    void handleAgentRegistrationMessage(
        const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference);

    void handleAgentRegistrationGetIdMessage(
        const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference);

    void handleAgentRegistrationGetNameMessage(
        const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference);

    void handleAgentRegistrationReturnMessage(
        const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference);

    void handleDeleteMessageHandlerMessage(
        const MultiAgentExperience::Rpc::Message *request, multiAgentExperience::ipc::messaging::Reference &reference);
};

} // namespace adaptor
} // namespace grpc
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_GRPCTRANSPORT_H
