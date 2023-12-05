/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_IPC_GRPCTRANSPORTSENDER_H
#define MULTIAGENTEXPERIENCE_IPC_GRPCTRANSPORTSENDER_H

#include <MultiAgentExperience/IPC/Messaging/ReferencePayload.h>
#include <MultiAgentExperience/IPC/Transport/TransportSenderInterface.h>
#include <MultiAgentExperience/IPC/Models/Activity/ActivityHandlerModel.h>
#include <MultiAgentExperience/IPC/Transport/TransportHandlerInterface.h>
#include <MultiAgentExperience/IPC/gRPC/Transport/GrpcClientInterface.h>
#include <MultiAgentExperience/Thread/Executor/Threading/Executor.h>
#include <MultiAgentExperience/Activity/ActivityFocus.h>
#include <MultiAgentExperience/Activity/ActivityType.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <maxrpc.grpc.pb.h>
#include <utility>

#include "MultiAgentExperience/IPC/gRPC/Utils/FunctionToMessageType.h"

namespace multiAgentExperience {
namespace ipc {
namespace grpc {
namespace adaptor {

/**
 * The GrpcTransportSender is the adaptor for the messaging layer in MultiAgentExperience-IPC package.
 * This class converts the data from the Proxy later and sends it to the grpc sender for sending across
 * process boundaries
 */
class GrpcTransportSender: public multiAgentExperience::ipc::transport::TransportSenderInterface {

private:
    template<typename ExpectedEnum, typename ExpectedPayload, typename Message>
    std::future<multiAgentExperience::ipc::messaging::Message<ExpectedEnum, ExpectedPayload>> execute(
            ExpectedEnum expectedEnum,
            Message message,
            std::shared_ptr<multiAgentExperience::ipc::transport::TransportFutureResponse<multiAgentExperience::ipc::messaging::Message<ExpectedEnum, ExpectedPayload>>> futureResponse) {
        return m_executor->submit([this, expectedEnum, message, futureResponse](){
            this->m_grpcClient->send(message);
            return futureResponse->waitForResponse();
        });
    }

    template<typename Message>
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> execute(Message message, multiAgentExperience::ipc::messaging::VoidMessage voidMessage) {
        auto voidPromise = std::make_shared<std::promise<multiAgentExperience::ipc::messaging::VoidMessage>>();
        m_executor->submit([this, message, voidMessage, voidPromise]() {
            this->m_grpcClient->send(message);
            voidPromise->set_value(voidMessage);
        });
        return voidPromise->get_future();
    }

public:
    GrpcTransportSender(
            std::shared_ptr<multiAgentExperience::ipc::grpc::transport::GrpcClientInterface> grpcClient,
            std::shared_ptr<multiAgentExperience::ipc::transport::TransportFutureResponseStore> responderStore,
            std::shared_ptr<thread::executor::threading::Executor> executor = std::make_shared<thread::executor::threading::Executor>()):
        TransportSenderInterface(std::move(responderStore)),
        m_grpcClient{std::move(grpcClient)},
        m_executor{std::move(executor)} {
    }

    std::future<multiAgentExperience::ipc::messaging::VoidMessage> sendConnectedToMaxMessage() override;

    /// @c ActivityManagerInterface
    /// @{

    /// For @c request, @c stop methods
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(const multiAgentExperience::ipc::messaging::Message
            <models::activity::ActivityManagerFunctions,multiAgentExperience::ipc::messaging::ReferencePayload>& message) override;

    ///@}

    /// @c ActivityRequestInterface
    /// @{

    /// For @c getHandler (for Agent response)
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(const multiAgentExperience::ipc::messaging::Message<
            models::activity::ActivityRequestFunctionReturns, multiAgentExperience::ipc::messaging::ReferencePayload>& message) override;

    /// For @c getType (for Agent response)
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(const multiAgentExperience::ipc::messaging::Message<
            models::activity::ActivityRequestFunctionReturns,
            multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::activity::ActivityType>>& message) override;

    /// For @c GetMixabilityType (for Agent response)
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(const multiAgentExperience::ipc::messaging::Message<
            models::activity::ActivityRequestFunctionReturns,
            multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::activity::MixabilityType>>& message) override;

    /// For @c getType (for MAX request)
    std::future<multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestFunctionReturns,
            multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::activity::ActivityType>>> send(
            const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestGetType,
                    multiAgentExperience::ipc::messaging::VoidPayload>& message) override;

    /// For @c getHandler (for MAX request)
    std::future<multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestFunctionReturns,
            multiAgentExperience::ipc::messaging::ReferencePayload>> send(const multiAgentExperience::ipc::messaging::Message<
                    models::activity::ActivityRequestGetHandler,
                    multiAgentExperience::ipc::messaging::VoidPayload>& message) override;

    /// For @c GetMixabilityType (for MAX request)
    std::future<multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestFunctionReturns,
            multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::activity::MixabilityType>>> send(
            const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestGetMixabilityType,
                    multiAgentExperience::ipc::messaging::VoidPayload>& message) override;

    /// @}

    /// @c ActivityHandlerInterface
    /// @{

    /// For @c onFocusStateChange method
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
            const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityHandlerFunctions,
                    multiAgentExperience::ipc::messaging::EnumTuplePayload<::multiAgentExperience::activity::ActivityFocus,
                            multiAgentExperience::activity::MixingBehavior>>& message) override;

    /// For @c onGranted method
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
            const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityHandlerFunctions,
                    multiAgentExperience::ipc::messaging::ReferenceListPayload>& message) override;

    /// For @c onDenied @c onStop method
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
            const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityHandlerFunctions,
            multiAgentExperience::ipc::messaging::VoidPayload>& message) override;

    /// @}

    /// @c ActivityControllerInterface
    /// @{

    /// For @c stop method
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
            const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityControllerFunctions,
            multiAgentExperience::ipc::messaging::VoidPayload>& message) override;

    /// @}

    /// @c DialogControllerInterface
    /// @{

    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogControllerFunctions,
            multiAgentExperience::ipc::messaging::VoidPayload>& message) override;

    /// For @c invokeControlAndStartSpeaking, @c stopAndInvokeControl methods
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogControllerFunctions,
            multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::control::ControlType>>& message) override;

    /// @}

    /// @c DialogManagerInterface
    /// @{

    /// For @c request, @c stop, @c setControlReceiver, @c setListeningHandler, @c setThinkingHandler, @c setSpeakingHandler
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogManagerFunctions,
            multiAgentExperience::ipc::messaging::ReferencePayload>& message) override;

    /// For @c setAllHandlers method
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogManagerFunctions,
            multiAgentExperience::ipc::messaging::ReferenceListPayload>& message) override;

    /// For @c removeAllHandlers, @c removeControlReceiver, @c removeListeningHandler, @c removeThinkingHandler, @c removeSpeakingHandler
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogManagerFunctions,
            multiAgentExperience::ipc::messaging::VoidPayload>& message) override;

    /// @}

    /// @c DialogRequestInterface
    /// @{

    /// For @c onDenied, @c onError
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctions,
            multiAgentExperience::ipc::messaging::StringPayload>& message) override;

    /// For @c onDialogStarted method
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctions,
            multiAgentExperience::ipc::messaging::ReferencePayload>& message) override;

    /// For @c onDialogStopped
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctions,
            multiAgentExperience::ipc::messaging::VoidPayload>& message) override;

    /// For @c getDialogBargeInPriority (for MAX library request)
    std::future<multiAgentExperience::ipc::messaging::Message<
        models::dialog::DialogRequestFunctionReturns,
        multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::dialog::DialogBargeInPriority>>> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctionGetDialogBargeInPriority,
            multiAgentExperience::ipc::messaging::VoidPayload>& message) override;

    /// For @c getDialogBargeInPriority (for agent response)
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctionReturns,
            multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::dialog::DialogBargeInPriority>>& message) override;
    /// @}

    /// @c ListeningHandlerInterface
    /// @{

    /// For @c onStartListening
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::ListeningHandlerFunctions,
            multiAgentExperience::ipc::messaging::ReferencePayload>& message) override;

    /// For @c onStopListening
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::ListeningHandlerFunctions,
            multiAgentExperience::ipc::messaging::VoidPayload>& message) override;

    /// @}

    /// @c ThinkingHandlerInterface
    /// @{

    /// For @c onStartThinking
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::ThinkingHandlerFunctions,
            multiAgentExperience::ipc::messaging::ReferencePayload>& message) override;

    /// For @c onStopThinking
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::ThinkingHandlerFunctions,
            multiAgentExperience::ipc::messaging::VoidPayload>& message) override;

    /// @}

    /// @c SpeakingHandlerInterface
    /// @{

    /// For @c onStartSpeaking
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::SpeakingHandlerFunctions,
            multiAgentExperience::ipc::messaging::ReferenceListPayload>& message) override;

    /// For @c onStopSpeaking
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::SpeakingHandlerFunctions,
            multiAgentExperience::ipc::messaging::VoidPayload>& message) override;
    /// @}

    /// @c StartListeningCallback
    /// @{

    /// For @c startListening
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::StartListeningCallbackFunctions,
            multiAgentExperience::ipc::messaging::VoidPayload>& message) override;

    /// @}

    /// @c Control
    /// @{

    /// For @c task
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::control::ControlFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message) override;
    /// @}

    /// @c ControlRegistryInterface
    /// @{

    /// For @c update
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::control::ControlRegistryFunctions,
        multiAgentExperience::ipc::messaging::control::ControlRegistryPayload>& message) override;
    /// @}

    /// @c ControlReceiverInterface
    /// @{

    /// For @c onControlsReceived
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::ControlReceiverFunctions,
        multiAgentExperience::ipc::messaging::dialog::ControlReceiverPayload>& message) override;
    /// @}

    /// ExperienceControllerInterface
    /// @{

    /// For @c startExperience
    std::future<multiAgentExperience::ipc::messaging::VoidMessage>
    send(const multiAgentExperience::ipc::messaging::Message<models::experience
    ::ExperienceControllerFunctions, multiAgentExperience::ipc::messaging::StringPayload>& message) override;

    /// For @c endExperience and @c invalidate
    std::future<multiAgentExperience::ipc::messaging::VoidMessage>
    send(const multiAgentExperience::ipc::messaging::Message<models::experience
    ::ExperienceControllerFunctions, multiAgentExperience::ipc::messaging::VoidPayload>& message) override;

    /// @}

    /// StaticExperienceManagerInterface
    /// {@

    /// For @c addStaticExperience
    std::future<multiAgentExperience::ipc::messaging::VoidMessage>
    send(const multiAgentExperience::ipc::messaging::Message<models::experience
    ::StaticExperienceManagerFunctions, multiAgentExperience::ipc::messaging::StringIntTuplePayload>& message) override;

    /// For @c removeStaticExperience
    std::future<multiAgentExperience::ipc::messaging::VoidMessage>
    send(const multiAgentExperience::ipc::messaging::Message<models::experience::StaticExperienceManagerFunctions, multiAgentExperience::ipc::messaging::StringPayload>& message) override;

    /// For @c removeAllStaticExperiences
    std::future<multiAgentExperience::ipc::messaging::VoidMessage>
    send(const multiAgentExperience::ipc::messaging::Message<models::experience::StaticExperienceManagerFunctions, multiAgentExperience::ipc::messaging::VoidPayload>& message) override;

    /// @}

    /// onCompletionCallbackInterface
    /// @{
    std::future<multiAgentExperience::ipc::messaging::VoidMessage>
    send(const multiAgentExperience::ipc::messaging::Message<models::common::OnCompletionCallbackFunctions,
       multiAgentExperience::ipc::messaging::VoidPayload>& message) override;
    /// @}

    /// AgentRegistrationInterface
    /// @{

    /// @c onReady()
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::agent::AgentRegistrationFunctions,
        multiAgentExperience::ipc::messaging::ReferenceListPayload>& message) override;

    /// @c getId()
    std::future<multiAgentExperience::ipc::messaging::Message<
        models::agent::AgentRegistrationFunctionReturns, multiAgentExperience::ipc::messaging::StringPayload>> send(
            const multiAgentExperience::ipc::messaging::Message<models::agent::AgentRegistrationFunctionGetId,
            multiAgentExperience::ipc::messaging::VoidPayload>& message) override;

    /// @c getName()
    std::future<multiAgentExperience::ipc::messaging::Message<
        models::agent::AgentRegistrationFunctionReturns, multiAgentExperience::ipc::messaging::StringPayload>> send(
            const multiAgentExperience::ipc::messaging::Message<models::agent::AgentRegistrationFunctionGetName,
            multiAgentExperience::ipc::messaging::VoidPayload>& message) override;

    /// Used for the response for the above two methods (getId() and getName())
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::agent::AgentRegistrationFunctionReturns,
        multiAgentExperience::ipc::messaging::StringPayload>& message) override;
    /// @}

    /// MessageHandlerDeletion
    /// @{
    std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
            const multiAgentExperience::ipc::messaging::Message<multiAgentExperience::ipc::transport::MaxApiType,
            multiAgentExperience::ipc::messaging::VoidPayload>& message) override;
    /// @}

private:
    std::shared_ptr<thread::executor::threading::Executor> m_executor;
    std::shared_ptr<multiAgentExperience::ipc::grpc::transport::GrpcClientInterface> m_grpcClient;
};

} // namespace adaptor
} // namespace grpc
} // namespace ipc
} // namespace multiAgentExperience


#endif //MULTIAGENTEXPERIENCE_IPC_GRPCTRANSPORTSENDER_H
