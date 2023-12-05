/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_PROXY_MESSAGEROUTER_H
#define MULTIAGENTEXPERIENCE_IPC_PROXY_MESSAGEROUTER_H

#include <memory>
#include <utility>

#include <MultiAgentExperience/IPC/Messaging/Message.h>
#include <MultiAgentExperience/IPC/Messaging/MessageUtils.h>
#include <MultiAgentExperience/IPC/Messaging/ReferencePayload.h>
#include <MultiAgentExperience/IPC/Messaging/VoidMessageTypes.h>
#include <MultiAgentExperience/Activity/ActivityFocus.h>

#include "MultiAgentExperience/IPC/Proxy/Activity/ActivityRequestMessageHandler.h"
#include "MultiAgentExperience/IPC/Proxy/Activity/ActivityRequestMessageHandler.h"
#include "MultiAgentExperience/IPC/Proxy/Activity/ActivityControllerMessageHandler.h"
#include "MultiAgentExperience/IPC/Proxy/Activity/ActivityManagerMessageHandler.h"
#include "MultiAgentExperience/IPC/Proxy/Activity/ActivityHandlerMessageHandler.h"
#include "MultiAgentExperience/IPC/Proxy/MessageHandlerStore.h"
#include "MultiAgentExperience/IPC/Transport/TransportFutureResponseStore.h"
#include "MultiAgentExperience/IPC/Transport/TransportHandlerInterface.h"
#include "MultiAgentExperience/IPC/Transport/TransportResponder.h"
#include "MultiAgentExperience/Thread/Executor/Threading/Executor.h"
#include <MultiAgentExperience/Utils/Logger/Logger.h>

namespace multiAgentExperience {
namespace ipc {
namespace proxy {

static const std::string MODULE_TAG_MR("MessageRouter");
#define LX_MR(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG_MR, __func__, message)

/**
 * This class implements @c TransportHandlerInterface and contains definitions for all the @c handle methods. An instance
 * of MessageRouter is expected to be created by both sides (agent and MAX library) in order to handle any requests received.
 */
class MessageRouter : public transport::TransportHandlerInterface {

public:
    MessageRouter(
        std::shared_ptr<MessageHandlerStore> messageHandlerStore,
        std::shared_ptr<transport::TransportFutureResponseStore> transportFutureResponseStore,
        std::shared_ptr<multiAgentExperience::thread::executor::threading::Executor> executor =
            std::make_shared<multiAgentExperience::thread::executor::threading::Executor>(),
        std::shared_ptr<multiAgentExperience::thread::executor::threading::Executor> callbackExecutor =
            std::make_shared<multiAgentExperience::thread::executor::threading::Executor>()):
                m_messageHandlerStore{std::move(messageHandlerStore)},
                m_transportFutureResponseStore{std::move(transportFutureResponseStore)},
                m_executor{std::move(executor)},
                m_callbackExecutor{std::move(callbackExecutor)} {
    }

    /// @c ActivityManagerInterface
    /// @{

    /// For @c request, @c stop methods.
    void handle(const multiAgentExperience::ipc::messaging::Message
            <models::activity::ActivityManagerFunctions, multiAgentExperience::ipc::messaging::ReferencePayload> &message) override {
        executeHandle(message);
    }

    /// @}

    /// @c ActivityRequestInterface
    /// @{

    /// For handling @c getType method request from MAX
    void handle(
        const multiAgentExperience::ipc::messaging::Message<
            models::activity::ActivityRequestGetType, multiAgentExperience::ipc::messaging::VoidPayload> &message,
        std::shared_ptr<transport::TransportResponder<
            models::activity::ActivityRequestFunctionReturns,
            multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::activity::ActivityType>>> replyTo) override {
        executeHandleAndRespond(message, replyTo);
    }

    /// For handling @c getHandler method request from MAX
    void handle(
        const multiAgentExperience::ipc::messaging::Message<
            models::activity::ActivityRequestGetHandler, multiAgentExperience::ipc::messaging::VoidPayload> &message,
        std::shared_ptr<transport::TransportResponder<
            models::activity::ActivityRequestFunctionReturns, multiAgentExperience::ipc::messaging::ReferencePayload>> replyTo) override {
        executeHandleAndRespond(message, replyTo);
    }

    /// For handling @c getMixabilityType method request from MAX
    void handle(
        const multiAgentExperience::ipc::messaging::Message<
            models::activity::ActivityRequestGetMixabilityType, multiAgentExperience::ipc::messaging::VoidPayload> &message,
        std::shared_ptr<transport::TransportResponder<
            models::activity::ActivityRequestFunctionReturns,
            multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::activity::MixabilityType>>> replyTo) override {
        executeHandleAndRespond(message, replyTo);
    }

    /// For handling response of @c getHandler method from Agent
    /// Since this is handling the response for a synchronous API, we implement it in the MessageRouter instead of the
    /// respective MessageHandler class. This is because we require access to the @c m_transportFutureResponseStore.
    void
    handle(const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestFunctionReturns,
            multiAgentExperience::ipc::messaging::ReferencePayload> &message) override {

        // Send the return value of the sync API (containing the Reference for ActivityHandler object) invoked by the ActivityRequestProxy.
        executeReply(message);
    }

    /// For handling @c getType method response from Agent
    void
    handle(const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestFunctionReturns,
            multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::activity::ActivityType>> &message) override {

        // Send the return value of the sync API (containing the ActivityType value) invoked by the ActivityRequestProxy.
        executeReply(message);
    }

    /// For handling @c getMixabilityType method response from Agent
    void
    handle(const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestFunctionReturns,
            multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::activity::MixabilityType>> &message) override {

        // Send the return value of the sync API (containing the MixabilityType value) invoked by the ActivityRequestProxy.
        executeReply(message);
    }

    /// @}

    /// @c ActivityHandlerInterface
    /// @{

    /// For handling @c onFocusStateChange method
    void handle(
            const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityHandlerFunctions,
                    multiAgentExperience::ipc::messaging::EnumTuplePayload<::multiAgentExperience::activity::ActivityFocus,
                            multiAgentExperience::activity::MixingBehavior>>& message) override {
        executeHandle(message);
    }

    /// For handling @c onGranted method
    void handle(
            const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityHandlerFunctions,
                    multiAgentExperience::ipc::messaging::ReferenceListPayload> &message) override {
        executeHandle(message);
    }

    /// For handling @c onDenied @c onStop method
    void
    handle(const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityHandlerFunctions,
           multiAgentExperience::ipc::messaging::VoidPayload> &message) override {
        executeHandle(message);
    }

    /// @}

    /// @c ActivityControllerInterface
    /// @{

    /// For handling @c stop method
    void
    handle(const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityControllerFunctions,
           multiAgentExperience::ipc::messaging::VoidPayload> &message) override {
        executeHandle(message);
    }

    /// @}

    /// @c DialogControllerInterface
    /// @{

    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogControllerFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message) override {
        executeHandle(message);
    }

    /// For @c invokeControlAndStartSpeaking, @c stopAndInvokeControl methods
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogControllerFunctions,
        multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::control::ControlType>>& message) override {
        executeHandle(message);
    }
    /// @}

    /// @c DialogManagerInterface
    /// @{

    /// For @c request, @c stop etc.
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogManagerFunctions,
        multiAgentExperience::ipc::messaging::ReferencePayload>& message) override {
        executeHandle(message);
    }

    /// For @c setAllHandlers method
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogManagerFunctions,
        multiAgentExperience::ipc::messaging::ReferenceListPayload>& message) override {
        executeHandle(message);
    }

    /// For @c removeAllHandlers, @c removeControlReceiver etc.
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogManagerFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message) override {
        executeHandle(message);
    }

    /// @}

    /// @c DialogRequestInterface
    /// @{

    /// For @c onDenied, @c onError
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctions,
        multiAgentExperience::ipc::messaging::StringPayload>& message) override {
        executeHandle(message);
    }

    /// For @c onDialogStarted method
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctions,
        multiAgentExperience::ipc::messaging::ReferencePayload>& message) override {
        executeHandle(message);
    }

    /// For @c onDialogStopped
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message) override {
        executeHandle(message);
    }

    /**
     * Used by an agent to handle the MAX library request (for @c getDialogBargeInPriority)
     *
     * @c getDialogBargeInPriority is a synchronous API (with non-void return type). MAX library uses the @c DialogRequestProxy
     * to invoke the getDialogBargeInPriority API, and expects a response containing the DialogBargeInPriority.
     *
     * This handle method for the above is implemented on the agent's side and services the request from MAX library. When the
     * agent receives a request, it retrieves the correct DialogRequestMessageHandler and handles it.
     *
     * @param message The message object sent by the agent in the request.
     * @param replyTo The transport responder object. We (the agent) will use this object to send back
     * the response (DialogBargeInPriority enum value) since we are handling a synchronous request.
     */
    void handle(
        const multiAgentExperience::ipc::messaging::Message<
            models::dialog::DialogRequestFunctionGetDialogBargeInPriority, multiAgentExperience::ipc::messaging::VoidPayload>& message,
        std::shared_ptr<transport::TransportResponder<models::dialog::DialogRequestFunctionReturns,
            multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::dialog::DialogBargeInPriority>>> replyTo) override {
        executeHandleAndRespond(message, replyTo);
    }

    /**
     * Used by MAX library to handle the agent response (for @c getDialogBargeInPriority).
     *
     * @c getDialogBargeInPriority is a synchronous API (with non-void return type).
     *
     * This handle method is implemented on the MAX library side and services the response from the agent (which is
     * another request in itself). When the MAX library receives this response, it retrieves the DialogBargeInPriority
     * value from the payload and sends it to the DialogRequestProxy that was waiting for it.
     *
     */
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctionReturns,
        multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::dialog::DialogBargeInPriority>>& message) override {

        // Send the return value of the sync API (containing the DialogBargeInPriority value) invoked by the DialogRequestProxy.
        executeReply(message);
    }
    /// @}

    /// @c ListeningHandlerInterface
    /// @{

    /// For @c onStartListening
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::ListeningHandlerFunctions,
        multiAgentExperience::ipc::messaging::ReferencePayload>& message) override {
        executeHandle(message);
    }

    /// For @c onStopListening
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::ListeningHandlerFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message) override {
        executeHandle(message);
    }
    /// @}

    /// @c ThinkingHandlerInterface
    /// @{

    /// For @c onStartThinking
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::ThinkingHandlerFunctions,
        multiAgentExperience::ipc::messaging::ReferencePayload>& message) override {
        executeHandle(message);
    }

    /// For @c onStopThinking
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::ThinkingHandlerFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message) override {
        executeHandle(message);
    }
    /// @}

    /// @c SpeakingHandlerInterface
    /// @{

    /// For @c onStartSpeaking
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::SpeakingHandlerFunctions,
        multiAgentExperience::ipc::messaging::ReferenceListPayload>& message) override {
        executeHandle(message);
    }

    /// For @c onStopSpeaking
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::SpeakingHandlerFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message) override {
        executeHandle(message);
    }
    /// @}

    /// @c StartListeningCallback
    /// @{

    /// For @c startListening
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::StartListeningCallbackFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message) override {
        executeHandleForCallbacks(message);
    }
    /// @}

    /// @c ExperienceController
    /// @{

    /// For @c startExperience
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::experience::ExperienceControllerFunctions,
                                               multiAgentExperience::ipc::messaging::StringPayload>& message) override {
        executeHandle(message);
    }

    /// For @c endExperience
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::experience::ExperienceControllerFunctions,
                                               multiAgentExperience::ipc::messaging::VoidPayload>& message) override {
        executeHandle(message);
    }

    /// @}

    /// @c StaticExperienceManager
    /// @{

    /// For @c addStaticExperience
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::experience::StaticExperienceManagerFunctions,
                                               multiAgentExperience::ipc::messaging::StringIntTuplePayload>& message) override {
        executeHandle(message);
    }

    /// For @c removeStaticExperience
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::experience::StaticExperienceManagerFunctions,
                                               multiAgentExperience::ipc::messaging::StringPayload>& message) override {
        executeHandle(message);
    }

    /// For @c removeAllStaticExperiences
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::experience::StaticExperienceManagerFunctions,
                                               multiAgentExperience::ipc::messaging::VoidPayload>& message) override {
        executeHandle(message);
    }

    /// @}

    /// @c OnCompletionCallback
    /// @{

    /// For @c completed
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::common::OnCompletionCallbackFunctions,
                                               multiAgentExperience::ipc::messaging::VoidPayload>& message) override {
        executeHandleForCallbacks(message);
    }

    /// @}

    /// @c AgentRegistrationInterface
    /// @{

    /// For @c onReady
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::agent::AgentRegistrationFunctions,
        multiAgentExperience::ipc::messaging::ReferenceListPayload>& message) override {
        executeHandle(message);
    }

    /**
     * Used by an Agent to handle the MAX library request (for @c getId)
     *
     * @c getId is a synchronous API (with non-void return type). MAX library uses the @c
     * AgentRegistrationProxy to invoke the getId API, and expects a response containing the
     * actor::ActorId (which is essentially a std::string packed in StringPayload).
     *
     * This handle method is implemented on the Agent's side and services the request from
     * MAX library. When the agent receives a request, it retrieves the correct
     * AgentRegistrationMessageHandler and handles it.
     *
     * @param message The message object sent by the MAX in the request.
     * @param replyTo The transport responder object. The agent will use this object to send back
     * the response (actor::ActorId StringPayload value) since we are handling a synchronous
     * request.
     */
    void handle(
        const multiAgentExperience::ipc::messaging::Message<
            models::agent::AgentRegistrationFunctionGetId, multiAgentExperience::ipc::messaging::VoidPayload>&
            message, std::shared_ptr<transport::TransportResponder<models::agent::AgentRegistrationFunctionReturns,
            multiAgentExperience::ipc::messaging::StringPayload>> replyTo) override {
        executeHandleAndRespond(message, replyTo);
    }

    /**
     * Used by an Agent to handle the MAX library request (for @c getName)
     *
     * @c getName is a synchronous API (with non-void return type). MAX library uses the @c
     * AgentRegistrationProxy to invoke the getName API, and expects a response containing the
     * std::string (packed in StringPayload).
     *
     * This handle method is implemented on the Agent's side and services the request from
     * MAX library. When the agent receives a request, it retrieves the correct
     * AgentRegistrationMessageHandler and handles it.
     *
     * @param message The message object sent by the MAX in the request.
     * @param replyTo The transport responder object. The agent will use this object to send back
     * the response (StringPayload value) since we are handling a synchronous
     * request.
     */
    void handle(const multiAgentExperience::ipc::messaging::Message<models::agent::AgentRegistrationFunctionGetName,
                multiAgentExperience::ipc::messaging::VoidPayload>& message,
                std::shared_ptr<transport::TransportResponder<models::agent::AgentRegistrationFunctionReturns,
                multiAgentExperience::ipc::messaging::StringPayload>> replyTo) override {
        executeHandleAndRespond(message, replyTo);
    }

    /**
     * Used by MAX library to handle the agent response (for @c getId & @c getName).
     *
     * @c getId & @c getName is a synchronous API (with non-void return type).
     *
     * This handle method is implemented on the MAX library side and services the response from the agent (which is
     * another request in itself). When the MAX library receives this response, it retrieves the
     * getId & getName values from the payload and sends it to the AgentRegistrationProxy that was
     * waiting for it.
     *
     */
    void handle(const multiAgentExperience::ipc::messaging::Message<models::agent::AgentRegistrationFunctionReturns,
                multiAgentExperience::ipc::messaging::StringPayload>& message) override {

        // Send the return value of the sync API (containing the Actor ID or Actor Name) invoked by the AgentRegistrationProxy.
        executeReply(message);
    }
    /// @}

    /// @c Control
    /// @{

    /// For @c task
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::control::ControlFunctions,
            multiAgentExperience::ipc::messaging::VoidPayload>& message) override {
        executeHandle(message);
    }
    /// @}

    /// @c ControlRegistryInterface
    /// @{

    /// For @c update
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::control::ControlRegistryFunctions,
            messaging::control::ControlRegistryPayload>& message) override {
        executeHandle(message);
    }
    /// @}

    /// @c ControlReceiverInterface
    /// @{

    /// For @c onControlsReceived
    void handle(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::ControlReceiverFunctions,
            messaging::dialog::ControlReceiverPayload>& message) override {
        executeHandle(message);
    }
    /// @}

    /// @c DeleteMessageHandler
    /// @{

    /// For @c MessageHandlerDeletion
    void handle(
            const multiAgentExperience::ipc::messaging::Message<transport::MaxApiType,
                    multiAgentExperience::ipc::messaging::VoidPayload>& message) override {
        m_executor->template submit([this, message]{
            m_messageHandlerStore->removeMessageHandler(message);
        });
    }
    /// @}

private:
    /**
     * Retrieves the respective MessageHandler and invokes the handle method for the API (passed in FunctionEnum).
     *
     * @tparam FunctionEnum The API whose request needs to be handled
     * @tparam Payload The payload for the API request
     * @param message The Message object for the corresponding API and its Payload
     */
    template<typename FunctionEnum, typename Payload>
    void executeHandle(const multiAgentExperience::ipc::messaging::Message<FunctionEnum, Payload>& message) {

        LX_MR(DEBUG3, "");
        auto handler = m_messageHandlerStore->get(message);

        m_executor->template submit([message, handler]() {
            LX_MR(DEBUG3, "Calling the handle of the respective message handler");
            handler->handle(message);
        });
    }

    /**
     * Similar to executeHandle, but processes the request on a different executor. This is to prevent deadlocks, when
     * callback tasks get queued behind the tasks waiting for those callbacks. This method is expected to be used for
     * any MAX APIs that are intended to signal any threads to stop waiting (for example, StartListeningCallback).
     */
    template<typename FunctionEnum, typename Payload>
    void executeHandleForCallbacks(const multiAgentExperience::ipc::messaging::Message<FunctionEnum, Payload>& message) {

        auto handler = m_messageHandlerStore->get(message);

        m_callbackExecutor->template submit([message, handler]() {
            handler->handle(message);
        });
    }

    /**
     * Retrieves the respective MessageHandler and invokes the handle method for the API (associated to the Message object).
     *
     * @tparam Message The Message object which contains an API name and its Payload
     * @tparam Payload The TransportResponder object using which this method can send back the response. This is
     * mainly used for synchronous API requests.
     */
    template<typename Message, typename Responder>
    void executeHandleAndRespond(Message message, Responder responder) {

        auto handler = m_messageHandlerStore->get(message);

        m_executor->template submit([message, responder, handler]() {
            handler->handle(message, responder);
        });
    }

    /**
     * Sends the return value of the sync API invoked by the Proxy. This is accomplished by using the
     * TransportFutureResponse object's reply method, which sets the std::promise that the Proxy is waiting on.
     *
     * @tparam Message The Message object which contains an API name and its Payload
     */
    template<typename Message>
    void executeReply(Message message) {

        /**
         * Retrieve the @c TransportFutureResponse object from the store, for the @c reference in the message.
         * We will use the @c TransportFutureResponse object to send the return value for the sync API invoked by
         * the Proxy. By invoking the @c TransportFutureResponse::reply method, we set the promise, enabling any
         * waiting Proxy to stop waiting for this request.
         */
        auto response = m_transportFutureResponseStore->get<Message>(message.getReference());

        m_callbackExecutor->template submit([response, message](){
            if (auto validResponse = response.lock()) {
                /**
                 * Send the message which contains the value of the response (string, enum etc.), by setting the
                 * std::promise. The Proxy will extract it from the message. The Proxy was using the
                 * TransportFutureResponse object to wait for a response. The reply method here tells the
                 * TransportFutureResponse object to stop waiting and retrieve the value.
                 */
                validResponse->reply(message);
            }
        });
    }

    std::shared_ptr<::multiAgentExperience::thread::executor::threading::Executor> m_executor;
    std::shared_ptr<::multiAgentExperience::thread::executor::threading::Executor> m_callbackExecutor;
    std::shared_ptr<MessageHandlerStore> m_messageHandlerStore;
    std::shared_ptr<transport::TransportFutureResponseStore> m_transportFutureResponseStore;
};

} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_PROXY_MESSAGEROUTER_H
