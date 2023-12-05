/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_IPC_TRANSPORT_TRANSPORTHANDLERINTERFACE_H
#define MULTIAGENTEXPERIENCE_IPC_TRANSPORT_TRANSPORTHANDLERINTERFACE_H

#include <future>

#include "TransportFutureResponse.h"
#include "TransportResponder.h"

namespace multiAgentExperience {
namespace ipc {
namespace transport {

/**
 * Responsible for handling requests sent by @c TransportSenderInterface.
 *
 * Each @c TransportSenderInterface::send should have a corresponding @c handle in this class. The method should accept
 * the same @c Message object sent in @c TransportSenderInterface::send. The handle methods, for APIs that are deemed
 * to be "synchronous", should also accept a replyTo parameter, which they can use to send back a response.
 */
class TransportHandlerInterface {
public:
    /// @c ActivityManagerInterface
    /// @{

    /// For @c request, @c stop methods.
    virtual void handle(const multiAgentExperience::ipc::messaging::Message
            <models::activity::ActivityManagerFunctions,multiAgentExperience::ipc::messaging::ReferencePayload>& message) = 0;

    /// @}

    /// @c ActivityRequestInterface
    /// @{

    /// For handling @c getType method response from Agent
    virtual void handle(
            const multiAgentExperience::ipc::messaging::Message<
                    models::activity::ActivityRequestFunctionReturns,
                    multiAgentExperience::ipc::messaging::EnumPayload<::multiAgentExperience::activity::ActivityType>>& message) = 0;

    /// For handling @c getHandler method response from Agent
    virtual void handle(
            const multiAgentExperience::ipc::messaging::Message<
                    models::activity::ActivityRequestFunctionReturns,
                    multiAgentExperience::ipc::messaging::ReferencePayload>& message) = 0;

    /// For handling @c getMixabilityType method response from Agent
    virtual void handle(
            const multiAgentExperience::ipc::messaging::Message<
                    models::activity::ActivityRequestFunctionReturns,
                    multiAgentExperience::ipc::messaging::EnumPayload<::multiAgentExperience::activity::MixabilityType>>& message) = 0;

    /// For handling @c getType method request from MAX
    virtual void handle(
            const multiAgentExperience::ipc::messaging::Message<
            models::activity::ActivityRequestGetType,
            multiAgentExperience::ipc::messaging::VoidPayload>& message,
            std::shared_ptr<transport::TransportResponder<
                    models::activity::ActivityRequestFunctionReturns,
                    multiAgentExperience::ipc::messaging::EnumPayload<::multiAgentExperience::activity::ActivityType>>> replyTo) = 0;

    /// For handling @c getHandler method request from MAX
    virtual void handle(
            const multiAgentExperience::ipc::messaging::Message<
            models::activity::ActivityRequestGetHandler,
            multiAgentExperience::ipc::messaging::VoidPayload>& message,
            std::shared_ptr<transport::TransportResponder<
                    models::activity::ActivityRequestFunctionReturns,
                    multiAgentExperience::ipc::messaging::ReferencePayload>> replyTo) = 0;

    /// For handling @c getMixabilityType method request from MAX
    virtual void handle(
          const multiAgentExperience::ipc::messaging::Message<
                  models::activity::ActivityRequestGetMixabilityType,
                  multiAgentExperience::ipc::messaging::VoidPayload>& message,
          std::shared_ptr<transport::TransportResponder<
                  models::activity::ActivityRequestFunctionReturns,
                  multiAgentExperience::ipc::messaging::EnumPayload<::multiAgentExperience::activity::MixabilityType>>> replyTo) = 0;

    /// @}

    /// @c ActivityHandlerInterface
    /// @{

    /// For handling @c onFocusStateChange method
    virtual void handle(
            const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityHandlerFunctions,
                    multiAgentExperience::ipc::messaging::EnumTuplePayload<::multiAgentExperience::activity::ActivityFocus,
                            multiAgentExperience::activity::MixingBehavior>>& message) = 0;

    /// For handling @c onGranted method
    virtual void handle(
            const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityHandlerFunctions,
                    multiAgentExperience::ipc::messaging::ReferenceListPayload> &message) = 0;

    /// For handling @c onDenied @c onStop method
    virtual void handle(const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityHandlerFunctions,
            multiAgentExperience::ipc::messaging::VoidPayload> &message) = 0;

    /// @}

    /// @c ActivityControllerInterface
    /// @{

    /// For handling @c stop method
    virtual void handle(const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityControllerFunctions,
            multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;

    /// @}

    /// @c DialogControllerInterface
    /// @{
    virtual void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogControllerFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;

    /// For @c invokeControlAndStartSpeaking, @c stopAndInvokeControl methods
    virtual void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogControllerFunctions,
        multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::control::ControlType>>& message) = 0;
    /// @}

    /// @c DialogManagerInterface
    /// @{

    /// For @c request, @c stop etc.
    virtual void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogManagerFunctions,
        multiAgentExperience::ipc::messaging::ReferencePayload>& message) = 0;

    /// For @c setAllHandlers method
    virtual void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogManagerFunctions,
        multiAgentExperience::ipc::messaging::ReferenceListPayload>& message) = 0;

    /// For @c removeAllHandlers, @c removeControlReceiver etc.
    virtual void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogManagerFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;

    /// @}

    /// @c DialogRequestInterface
    /// @{

    /// For @c onDenied, @c onError
    virtual void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctions,
        multiAgentExperience::ipc::messaging::StringPayload>& message) = 0;

    /// For @c onDialogStarted method
    virtual void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctions,
        multiAgentExperience::ipc::messaging::ReferencePayload>& message) = 0;

    /// For @c onDialogStopped
    virtual void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;

    /**
     * Used by the agent to handle a MAX library request (for @c getDialogBargeInPriority)
     *
     * @param message The message object sent by the agent in the request.
     * @param replyTo The transport responder object. We use this object to send back the response (DialogBargeInPriority enum value)
     * since we are handling a synchronous request.
     */
    virtual void handle(
        const multiAgentExperience::ipc::messaging::Message<
            models::dialog::DialogRequestFunctionGetDialogBargeInPriority, multiAgentExperience::ipc::messaging::VoidPayload>& message,
        std::shared_ptr<TransportResponder<
            models::dialog::DialogRequestFunctionReturns, multiAgentExperience::ipc::messaging::EnumPayload<dialog::DialogBargeInPriority>>> replyTo) = 0;

    /// Used by MAX library to handle the agent response (for @c getDialogBargeInPriority)
    virtual void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctionReturns,
        multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::dialog::DialogBargeInPriority>>& message) = 0;
    /// @}

    /// @c ListeningHandlerInterface
    /// @{

    /// For @c onStartListening
    virtual void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::ListeningHandlerFunctions,
        multiAgentExperience::ipc::messaging::ReferencePayload>& message) = 0;

    /// For @c onStopListening
    virtual void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::ListeningHandlerFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;
    /// @}

    /// @c ThinkingHandlerInterface
    /// @{

    /// For @c onStartThinking
    virtual void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::ThinkingHandlerFunctions,
        multiAgentExperience::ipc::messaging::ReferencePayload>& message) = 0;

    /// For @c onStopThinking
    virtual void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::ThinkingHandlerFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;
    /// @}

    /// @c SpeakingHandlerInterface
    /// @{

    /// For @c onStartSpeaking
    virtual void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::SpeakingHandlerFunctions,
        multiAgentExperience::ipc::messaging::ReferenceListPayload>& message) = 0;

    /// For @c onStopSpeaking
    virtual void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::SpeakingHandlerFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;
    /// @}

    /// @c StartListeningCallback
    /// @{

    /// For @c startListening
    virtual void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::StartListeningCallbackFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;
    /// @}

    /// ExperienceControllerInterface
    /// @{

    /// For @c startExperience
    virtual void handle(
        const multiAgentExperience::ipc::messaging::Message<models::experience::ExperienceControllerFunctions,
        multiAgentExperience::ipc::messaging::StringPayload>& message) = 0;

    /// For @c endExperience
    virtual void handle(
        const multiAgentExperience::ipc::messaging::Message<models::experience::ExperienceControllerFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;

    /// @}

    /// StaticExperienceManagerInterface
    /// {@

    /// For @c addStaticExperience
    virtual void handle(const multiAgentExperience::ipc::messaging::Message<models::experience::StaticExperienceManagerFunctions,
                        multiAgentExperience::ipc::messaging::StringIntTuplePayload>& message) = 0;

    /// For @c removeStaticExperience
    virtual void handle(const multiAgentExperience::ipc::messaging::Message<models::experience::StaticExperienceManagerFunctions,
                        multiAgentExperience::ipc::messaging::StringPayload>& message) = 0;

    /// For @c removeAllStaticExperiences
    virtual void handle(const multiAgentExperience::ipc::messaging::Message<models::experience::StaticExperienceManagerFunctions,
                        multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;
    /// @}

    /// onCompletionCallbackInterface
    /// {@
    virtual void handle(
        const multiAgentExperience::ipc::messaging::Message<models::common::OnCompletionCallbackFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;
    /// @}

    /// AgentRegistrationInterface
    /// @{
    virtual void handle(
        const multiAgentExperience::ipc::messaging::Message<models::agent::AgentRegistrationFunctions,
        multiAgentExperience::ipc::messaging::ReferenceListPayload>& message) = 0;

    /**
     * Used by Agent to handle a MAX request (for @c getId)
     *
     * @param message The message object sent by MAX in the request.
     * @param replyTo The transport responder object. We use this object to send back the
     * response (actor::ActorId which is sent as std::string in StringPayload value)
     * since we are handling a synchronous request.
     */
    virtual void handle(
        const multiAgentExperience::ipc::messaging::Message<
            models::agent::AgentRegistrationFunctionGetId, multiAgentExperience::ipc::messaging::VoidPayload>&
        message, std::shared_ptr<transport::TransportResponder<
        models::agent::AgentRegistrationFunctionReturns,
        multiAgentExperience::ipc::messaging::StringPayload>> replyTo) = 0;

    /**
    * Used by Agent to handle a MAX request (for @c getName)
    *
    * @param message The message object sent by MAX in the request.
    * @param replyTo The transport responder object. We use this object to send back the
    * response (ActorName which is sent as std::string in StringPayload value)
    * since we are handling a synchronous request.
    */
    virtual void handle(
        const multiAgentExperience::ipc::messaging::Message<
            models::agent::AgentRegistrationFunctionGetName, multiAgentExperience::ipc::messaging::VoidPayload>&
        message, std::shared_ptr<transport::TransportResponder<
        models::agent::AgentRegistrationFunctionReturns,
        multiAgentExperience::ipc::messaging::StringPayload>> replyTo) = 0;

    /// Used by MAX to handle the Agent library response (for @c getId & @c getName)
    virtual void handle(
        const multiAgentExperience::ipc::messaging::Message<models::agent::AgentRegistrationFunctionReturns,
        multiAgentExperience::ipc::messaging::StringPayload>& message) = 0;

    /// @}

    /// @c Control
    /// @{

    /// For @c task
    virtual void handle(
        const multiAgentExperience::ipc::messaging::Message<models::control::ControlFunctions,
            multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;
    /// @}

    /// @c ControlRegistryInterface
    /// @{

    /// For @c update
    virtual void handle(
        const multiAgentExperience::ipc::messaging::Message<models::control::ControlRegistryFunctions,
            messaging::control::ControlRegistryPayload>& message) = 0;
    /// @}

    /// @c ControlReceiverInterface
    /// @{

    /// For @c onControlsReceived
    virtual void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::ControlReceiverFunctions,
            messaging::dialog::ControlReceiverPayload>& message) = 0;
    /// @}

    /// @c DeleteMessageHandler
    /// @{

    /// For @c MessageHandlerDeletion
    virtual void handle(
        const multiAgentExperience::ipc::messaging::Message<transport::MaxApiType,
            multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;
    /// @}

};
} // namespace transport
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_TRANSPORT_TRANSPORTHANDLERINTERFACE_H
