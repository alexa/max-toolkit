/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_IPC_PROXY_MESSAGEHANDLERSTORE_H
#define MULTIAGENTEXPERIENCE_IPC_PROXY_MESSAGEHANDLERSTORE_H

#include <map>
#include <memory>
#include <utility>

#include <MultiAgentExperience/IPC/Messaging/MessageUtils.h>
#include <MultiAgentExperience/IPC/Messaging/Message.h>

#include "MultiAgentExperience/IPC/Models/Activity/ActivityRequestModel.h"
#include "MultiAgentExperience/IPC/Models/Activity/ActivityManagerModel.h"
#include "MultiAgentExperience/IPC/Models/Activity/ActivityHandlerModel.h"
#include "MultiAgentExperience/IPC/Models/Activity/ActivityControllerModel.h"
#include "MultiAgentExperience/IPC/Proxy/Activity/ActivityControllerMessageHandler.h"
#include "MultiAgentExperience/IPC/Proxy/Activity/ActivityHandlerMessageHandler.h"
#include "MultiAgentExperience/IPC/Proxy/Activity/ActivityManagerMessageHandler.h"
#include "MultiAgentExperience/IPC/Proxy/Activity/ActivityRequestMessageHandler.h"
#include "MultiAgentExperience/IPC/Proxy/Agent/AgentRegistrationMessageHandler.h"
#include "MultiAgentExperience/IPC/Proxy/Common/OnCompletionCallbackMessageHandler.h"
#include "MultiAgentExperience/IPC/Proxy/Control/ControlMessageHandler.h"
#include "MultiAgentExperience/IPC/Proxy/Control/ControlRegistryMessageHandler.h"
#include "MultiAgentExperience/IPC/Proxy/Dialog/ControlReceiverMessageHandler.h"
#include "MultiAgentExperience/IPC/Proxy/Dialog/DialogControllerMessageHandler.h"
#include "MultiAgentExperience/IPC/Proxy/Dialog/DialogManagerMessageHandler.h"
#include "MultiAgentExperience/IPC/Proxy/Dialog/DialogRequestMessageHandler.h"
#include "MultiAgentExperience/IPC/Proxy/Dialog/ListeningHandlerMessageHandler.h"
#include "MultiAgentExperience/IPC/Proxy/Dialog/SpeakingHandlerMessageHandler.h"
#include "MultiAgentExperience/IPC/Proxy/Dialog/StartListeningCallbackMessageHandler.h"
#include "MultiAgentExperience/IPC/Proxy/Dialog/ThinkingHandlerMessageHandler.h"
#include "MultiAgentExperience/IPC/Proxy/Experience/ExperienceControllerMessageHandler.h"
#include "MultiAgentExperience/IPC/Proxy/Experience/StaticExperienceManagerMessageHandler.h"
#include "MultiAgentExperience/IPC/Transport/MessageSender.h"
#include "MultiAgentExperience/IPC/Transport/MessageHandler.h"
#include "MultiAgentExperience/IPC/Utils/MessageHandlerMapType.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {

/**
 * This class is responsible for creating and storing handlers (of type @c MessageHandler) for Activity/Control/Experience/Dialog APIs.
 * This class contains maps for each handler type (for example, m_activityManagerMessageHandlers). Such a map will contain
 * handler objects for each Reference sent in a API request. The MessageHandlerStore also contains utility methods for creating
 * handlers and retrieving them, for a particular Reference.
 *
 * @note There is a circular dependency in the MessageHandlerStore and any classes that implement MessageHandler.
 * To mitigate issues related to this, one must forward declare the MessageHandlerStore class in the respective
 * MessageHandler class (in the header file). Also, one must only include the MessageHandlerStore.h file in the
 * respective MessageHandler's implementation file (.cpp).
 */
class MessageHandlerStore : public std::enable_shared_from_this<MessageHandlerStore> {

public:
    MessageHandlerStore(std::shared_ptr<transport::MessageSender> sender):
        m_sender{sender} {
    }

    /**
     * Clears all the message handler instances stored in the internal maps.
     */
    void clearStores() {
        /// Handlers for Activity APIs
        m_activityManagerMessageHandlers.clear();
        m_activityRequestMessageHandlers.clear();
        m_activityHandlerMessageHandlers.clear();
        m_activityControllerMessageHandlers.clear();
        m_agentRegistrationMessageHandlers.clear();
        m_onCompletionCallbackMessageHandlers.clear();

        /// Handlers for Control APIs
        m_controlMessageHandlers.clear();
        m_controlRegistryMessageHandlers.clear();

        /// Handlers for Dialog APIs
        m_controlReceiverMessageHandlers.clear();
        m_dialogControllerMessageHandlers.clear();
        m_dialogManagerMessageHandlers.clear();
        m_dialogRequestMessageHandlers.clear();
        m_listeningHandlerMessageHandlers.clear();
        m_speakingHandlerMessageHandlers.clear();
        m_thinkingHandlerMessageHandlers.clear();
        m_startListeningCallbackMessageHandlers.clear();

        /// Handlers for Experience APIs
        m_experienceControllerMessageHandlers.clear();
        m_staticExperienceManagerMessageHandlers.clear();
    }

    /**
     * Clears all the stored objects from internal maps & resets the passed objects.
     */
     void clearAndReset(std::shared_ptr<transport::MessageSender> sender) {
         clearStores();
         m_sender = sender;
     }

    /**
     * Creates a handler of type - ApiType to handle its messages. A unique handler object is created for each request.
     * This handler object is mapped to the Reference created from the shared_ptr to the ApiType. The handler is stored
     * in the store for future access.
     *
     * @param apiType The API object for which the corresponding handler should be created
     * @return The corresponding MessageHandler object
     */
    template<typename ApiType>
    std::shared_ptr<transport::MessageHandler> createOrGet(std::shared_ptr<ApiType> apiType) {

        std::unique_lock<std::mutex> lock(m_mutex);

        /// Create a Reference for the @c apiType object passed
        auto reference = multiAgentExperience::ipc::messaging::reference::createReference(apiType);

        auto& map = getMapForType(apiType);

        /// If we do not find a handler for this @c apiType object, we create one and store it the corresponding map.
        auto entry = map.find(reference);
        if (entry != map.end()) {
            /// Return the handler found for the reference
            return entry->second;
        } else {
            auto handler = createHandler(reference, apiType);

            /// The handler is mapped to the Reference created for @c apiType object
            map[reference] = handler;
            return handler;
        }
    }

    /**
     * These @c get() methods retrieve the unique MessageHandler object associated with the @c Reference for a
     * particular API request.
     */
    template<typename Payload>
    std::shared_ptr<activity::ActivityManagerMessageHandler> get(
        const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityManagerFunctions, Payload>& message) {

        std::unique_lock<std::mutex> lock(m_mutex);

        auto reference = message.getReference();
        return m_activityManagerMessageHandlers[reference];
    }

    template<typename Payload>
    std::shared_ptr<activity::ActivityRequestMessageHandler> get(
        const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestGetType, Payload>& message) {

        std::unique_lock<std::mutex> lock(m_mutex);

        auto reference = message.getReference();
        return m_activityRequestMessageHandlers[reference];
    }

    template<typename Payload>
    std::shared_ptr<activity::ActivityRequestMessageHandler> get(
        const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestGetHandler, Payload>& message) {

        std::unique_lock<std::mutex> lock(m_mutex);

        auto reference = message.getReference();
        return m_activityRequestMessageHandlers[reference];
    }

    template<typename Payload>
    std::shared_ptr<activity::ActivityRequestMessageHandler> get(
            const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestGetMixabilityType, Payload>& message) {

        std::unique_lock<std::mutex> lock(m_mutex);

        auto reference = message.getReference();
        return m_activityRequestMessageHandlers[reference];
    }

    template<typename Payload>
    std::shared_ptr<activity::ActivityHandlerMessageHandler> get(
        const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityHandlerFunctions, Payload>& message) {

        std::unique_lock<std::mutex> lock(m_mutex);

        auto reference = message.getReference();
        return m_activityHandlerMessageHandlers[reference];
    }

    template<typename Payload>
    std::shared_ptr<activity::ActivityControllerMessageHandler> get(
        const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityControllerFunctions, Payload>& message) {

        std::unique_lock<std::mutex> lock(m_mutex);

        auto reference = message.getReference();
        return m_activityControllerMessageHandlers[reference];
    }

    /// For Agent APIs
    template<typename Payload>
    std::shared_ptr<agent::AgentRegistrationMessageHandler> get(
        const multiAgentExperience::ipc::messaging::Message<models::agent::AgentRegistrationFunctions,
        Payload>& message) {

        std::unique_lock<std::mutex> lock(m_mutex);

        auto reference = message.getReference();
        return m_agentRegistrationMessageHandlers[reference];
    }

    /// For @c AgentRegistrationInterface's getId
    template<typename Payload>
    std::shared_ptr<multiAgentExperience::ipc::proxy::agent::AgentRegistrationMessageHandler> get(
        const multiAgentExperience::ipc::messaging::Message<models::agent::AgentRegistrationFunctionGetId, Payload>& message) {

        std::unique_lock<std::mutex> lock(m_mutex);

        auto reference = message.getReference();
        return m_agentRegistrationMessageHandlers[reference];
    }

    /// For @c AgentRegistrationInterface's getName
    template<typename Payload>
    std::shared_ptr<multiAgentExperience::ipc::proxy::agent::AgentRegistrationMessageHandler> get(
        const multiAgentExperience::ipc::messaging::Message<models::agent::AgentRegistrationFunctionGetName, Payload>& message) {

        std::unique_lock<std::mutex> lock(m_mutex);

        auto reference = message.getReference();
        return m_agentRegistrationMessageHandlers[reference];
    }

    /// For Common APIs
    template<typename Payload>
    std::shared_ptr<common::OnCompletionCallbackMessageHandler> get(
        const multiAgentExperience::ipc::messaging::Message<models::common::OnCompletionCallbackFunctions, Payload>& message) {

        std::unique_lock<std::mutex> lock(m_mutex);

        auto reference = message.getReference();
        return m_onCompletionCallbackMessageHandlers[reference];
    }

    /// For @c Control
    template<typename Payload>
    std::shared_ptr<control::ControlMessageHandler> get(
        const multiAgentExperience::ipc::messaging::Message<models::control::ControlFunctions, Payload>& message) {

        std::unique_lock<std::mutex> lock(m_mutex);

        auto reference = message.getReference();
        return m_controlMessageHandlers[reference];
    }

    /// For @c ControlRegistryInterface
    template<typename Payload>
    std::shared_ptr<multiAgentExperience::ipc::proxy::control::ControlRegistryMessageHandler> get(
        const multiAgentExperience::ipc::messaging::Message<models::control::ControlRegistryFunctions, Payload>& message) {

        std::unique_lock<std::mutex> lock(m_mutex);

        auto reference = message.getReference();
        return m_controlRegistryMessageHandlers[reference];
    }

    /// For @c ControlReceiverInterface
    template<typename Payload>
    std::shared_ptr<dialog::ControlReceiverMessageHandler> get(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::ControlReceiverFunctions, Payload>& message) {

        std::unique_lock<std::mutex> lock(m_mutex);

        auto reference = message.getReference();
        return m_controlReceiverMessageHandlers[reference];
    }

    /// For @c DialogControllerInterface
    template<typename Payload>
    std::shared_ptr<dialog::DialogControllerMessageHandler> get(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogControllerFunctions, Payload>& message) {

        std::unique_lock<std::mutex> lock(m_mutex);

        auto reference = message.getReference();
        return m_dialogControllerMessageHandlers[reference];
    }

    /// For @c DialogManagerInterface
    template<typename Payload>
    std::shared_ptr<dialog::DialogManagerMessageHandler> get(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogManagerFunctions, Payload>& message) {

        std::unique_lock<std::mutex> lock(m_mutex);

        auto reference = message.getReference();
        return m_dialogManagerMessageHandlers[reference];
    }

    /// For @c DialogRequestInterface
    template<typename Payload>
    std::shared_ptr<dialog::DialogRequestMessageHandler> get(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctions, Payload>& message) {

        std::unique_lock<std::mutex> lock(m_mutex);

        auto reference = message.getReference();
        return m_dialogRequestMessageHandlers[reference];
    }

    /// For @c DialogRequestInterface's getDialogBargeInPriority
    template<typename Payload>
    std::shared_ptr<dialog::DialogRequestMessageHandler> get(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctionGetDialogBargeInPriority, Payload>& message) {

        std::unique_lock<std::mutex> lock(m_mutex);

        auto reference = message.getReference();
        return m_dialogRequestMessageHandlers[reference];
    }

    /// For @c ListeningHandlerInterface
    template<typename Payload>
    std::shared_ptr<dialog::ListeningHandlerMessageHandler> get(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::ListeningHandlerFunctions, Payload>& message) {

        std::unique_lock<std::mutex> lock(m_mutex);

        auto reference = message.getReference();
        return m_listeningHandlerMessageHandlers[reference];
    }

    /// For @c SpeakingHandlerInterface
    template<typename Payload>
    std::shared_ptr<dialog::SpeakingHandlerMessageHandler> get(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::SpeakingHandlerFunctions, Payload>& message) {

        std::unique_lock<std::mutex> lock(m_mutex);

        auto reference = message.getReference();
        return m_speakingHandlerMessageHandlers[reference];
    }

    /// For @c ThinkingHandlerInterface
    template<typename Payload>
    std::shared_ptr<dialog::ThinkingHandlerMessageHandler> get(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::ThinkingHandlerFunctions, Payload>& message) {

        std::unique_lock<std::mutex> lock(m_mutex);

        auto reference = message.getReference();
        return m_thinkingHandlerMessageHandlers[reference];
    }

    /// For @c StartListeningCallback
    template<typename Payload>
    std::shared_ptr<dialog::StartListeningCallbackMessageHandler> get(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::StartListeningCallbackFunctions, Payload>& message) {

        std::unique_lock<std::mutex> lock(m_mutex);

        auto reference = message.getReference();
        return m_startListeningCallbackMessageHandlers[reference];
    }

    /// For @c ExperienceControllerInterface
    template<typename Payload>
    std::shared_ptr<experience::ExperienceControllerMessageHandler> get(
        const multiAgentExperience::ipc::messaging::Message<models::experience::ExperienceControllerFunctions, Payload>& message) {

        std::unique_lock<std::mutex> lock(m_mutex);

        auto reference = message.getReference();
        return m_experienceControllerMessageHandlers[reference];
    }

    /// For @c StaticExperienceManagerInterface
    template<typename Payload>
    std::shared_ptr<experience::StaticExperienceManagerMessageHandler> get(
        const multiAgentExperience::ipc::messaging::Message<models::experience::StaticExperienceManagerFunctions, Payload>& message) {

        std::unique_lock<std::mutex> lock(m_mutex);

        auto reference = message.getReference();
        return m_staticExperienceManagerMessageHandlers[reference];
    }
    
    // TODO: obviously need to be able to remove things, and do so nicely. this results in issues when a function call is
    // coming in for something removed;

    template<typename T>
    void remove(std::shared_ptr<T> object) {

        std::unique_lock<std::mutex> lock(m_mutex);

        auto& messageHandlerMap = getMapForType(object);
        auto reference = multiAgentExperience::ipc::messaging::reference::createReference(object);
        removeFromMap(messageHandlerMap, reference);
    }

    template<typename FunctionEnum, typename Payload>
    void removeMessageHandler(const multiAgentExperience::ipc::messaging::Message<FunctionEnum, Payload>& message) {
        std::unique_lock<std::mutex> lock(m_mutex);

        auto reference = message.getReference();
        auto maxApiType = message.getFunction();
        switch(maxApiType) {
            // Activities
            case transport::MaxApiType::ACTIVITY_CONTROLLER:
                removeFromMap(m_activityControllerMessageHandlers, reference);
                break;
            case transport::MaxApiType::ACTIVITY_HANDLER:
                removeFromMap(m_activityHandlerMessageHandlers, reference);
                break;
            case transport::MaxApiType::ACTIVITY_MANAGER:
                removeFromMap(m_activityManagerMessageHandlers, reference);
                break;
            case transport::MaxApiType::ACTIVITY_REQUEST:
                removeFromMap(m_activityRequestMessageHandlers, reference);
                break;

            // Agent Registration
            case transport::MaxApiType::AGENT_REGISTRATION:
                removeFromMap(m_agentRegistrationMessageHandlers, reference);
                break;

            //On completion callback
            case transport::MaxApiType::ON_COMPLETION_CALLBACK:
                removeFromMap(m_onCompletionCallbackMessageHandlers, reference);
                break;

            // control
            case transport::MaxApiType::CONTROL:
                removeFromMap(m_controlMessageHandlers, reference);
                break;
            case transport::MaxApiType::CONTROL_REGISTRY:
                removeFromMap(m_controlRegistryMessageHandlers, reference);
                break;

            // Dialogs
            case transport::MaxApiType::CONTROL_RECEIVER:
                removeFromMap(m_controlReceiverMessageHandlers, reference);
                break;
            case transport::MaxApiType::DIALOG_CONTROLLER:
                removeFromMap(m_dialogControllerMessageHandlers, reference);
                break;
            case transport::MaxApiType::DIALOG_MANAGER:
                removeFromMap(m_dialogManagerMessageHandlers, reference);
                break;
            case transport::MaxApiType::DIALOG_REQUEST:
                removeFromMap(m_dialogRequestMessageHandlers, reference);
                break;
            case transport::MaxApiType::LISTENING_HANDLER:
                removeFromMap(m_listeningHandlerMessageHandlers, reference);
                break;
            case transport::MaxApiType::SPEAKING_HANDLER:
                removeFromMap(m_speakingHandlerMessageHandlers, reference);
                break;
            case transport::MaxApiType::START_LISTENING_CALLBACK:
                removeFromMap(m_startListeningCallbackMessageHandlers, reference);
                break;
            case transport::MaxApiType::THINKING_HANDLER:
                removeFromMap(m_thinkingHandlerMessageHandlers, reference);
                break;

            // Experiences
            case transport::MaxApiType::EXPERIENCE_CONTROLLER:
                removeFromMap(m_experienceControllerMessageHandlers, reference);
                break;
            case transport::MaxApiType::STATIC_EXPERIENCE_MANAGER:
                removeFromMap(m_staticExperienceManagerMessageHandlers, reference);
                break;
        }
    }

private:

    /// Mutex to serialize access to all the MessageHandler maps like m_activityManagerMessageHandlers, m_agentRegistrationMessageHandlers etc.
    std::mutex m_mutex;

    std::shared_ptr<transport::MessageSender> m_sender;

    /// Handlers for Activity APIs
    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<activity::ActivityManagerMessageHandler>> m_activityManagerMessageHandlers;
    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<activity::ActivityRequestMessageHandler>> m_activityRequestMessageHandlers;
    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<activity::ActivityHandlerMessageHandler>> m_activityHandlerMessageHandlers;
    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<activity::ActivityControllerMessageHandler>> m_activityControllerMessageHandlers;

    /// Handlers for AgentRegistration APIs
    std::map<multiAgentExperience::ipc::messaging::Reference,
    std::shared_ptr<multiAgentExperience::ipc::proxy::agent::AgentRegistrationMessageHandler>>
    m_agentRegistrationMessageHandlers;

    /// Handlers for Common APIs
    std::map<multiAgentExperience::ipc::messaging::Reference,
    std::shared_ptr<common::OnCompletionCallbackMessageHandler>>
    m_onCompletionCallbackMessageHandlers;

    /// Handlers for Control APIs
    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<control::ControlMessageHandler>> m_controlMessageHandlers;
    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<control::ControlRegistryMessageHandler>> m_controlRegistryMessageHandlers;

    /// Handlers for Dialog APIs
    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<dialog::ControlReceiverMessageHandler>> m_controlReceiverMessageHandlers;
    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<dialog::DialogControllerMessageHandler>> m_dialogControllerMessageHandlers;
    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<dialog::DialogManagerMessageHandler>> m_dialogManagerMessageHandlers;
    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<dialog::DialogRequestMessageHandler>> m_dialogRequestMessageHandlers;
    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<dialog::ListeningHandlerMessageHandler>> m_listeningHandlerMessageHandlers;
    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<dialog::SpeakingHandlerMessageHandler>> m_speakingHandlerMessageHandlers;
    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<dialog::ThinkingHandlerMessageHandler>> m_thinkingHandlerMessageHandlers;
    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<dialog::StartListeningCallbackMessageHandler>> m_startListeningCallbackMessageHandlers;

    /// Handlers for Experience APIs
    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<experience::ExperienceControllerMessageHandler>> m_experienceControllerMessageHandlers;
    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<experience::StaticExperienceManagerMessageHandler>>
    m_staticExperienceManagerMessageHandlers;

    /**
     * Utility methods to retrieve the corresponding handler map based on the API type
    */

    /// For Activity APIs
    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<activity::ActivityManagerMessageHandler>>& getMapForType(
        std::shared_ptr<::multiAgentExperience::activity::ActivityManagerInterface> activityManagerInterface) {
        return m_activityManagerMessageHandlers;
    }

    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<activity::ActivityRequestMessageHandler>>& getMapForType(
        std::shared_ptr<::multiAgentExperience::activity::ActivityRequestInterface> activityRequestInterface) {
        return m_activityRequestMessageHandlers;
    }

    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<activity::ActivityHandlerMessageHandler>>& getMapForType(
        std::shared_ptr<::multiAgentExperience::activity::ActivityHandlerInterface> activityHandlerInterface) {
        return m_activityHandlerMessageHandlers;
    }

    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<activity::ActivityControllerMessageHandler>>& getMapForType(
        std::shared_ptr<::multiAgentExperience::activity::ActivityControllerInterface> activityControllerInterface) {
        return m_activityControllerMessageHandlers;
    }

    /// For Agent APIs
    std::map<multiAgentExperience::ipc::messaging::Reference,
    std::shared_ptr<multiAgentExperience::ipc::proxy::agent::AgentRegistrationMessageHandler>>&
    getMapForType(
        std::shared_ptr<::multiAgentExperience::agent::AgentRegistrationInterface>
            agentRegistrationInterface) {
        return m_agentRegistrationMessageHandlers;
    }

    /// For Control APIs
    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<control::ControlMessageHandler>>& getMapForType(
        std::shared_ptr<::multiAgentExperience::control::Control> control) {
        return m_controlMessageHandlers;
    }

    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<control::ControlRegistryMessageHandler>>& getMapForType(
        std::shared_ptr<::multiAgentExperience::control::ControlRegistryInterface> controlRegistryInterface) {
        return m_controlRegistryMessageHandlers;
    }

    /// For Common APIs
    std::map<multiAgentExperience::ipc::messaging::Reference,
    std::shared_ptr<common::OnCompletionCallbackMessageHandler>>& getMapForType(
        std::shared_ptr<::multiAgentExperience::common::OnCompletionCallbackInterface>
        onCompletionCallbackInterface) {
        return m_onCompletionCallbackMessageHandlers;
    }

    /// For Dialog APIs
    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<dialog::ControlReceiverMessageHandler>>& getMapForType(
        std::shared_ptr<::multiAgentExperience::dialog::ControlReceiverInterface> controlReceiverInterface) {
        return m_controlReceiverMessageHandlers;
    }

    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<dialog::DialogControllerMessageHandler>>& getMapForType(
        std::shared_ptr<::multiAgentExperience::dialog::DialogControllerInterface> dialogControllerInterface) {
        return m_dialogControllerMessageHandlers;
    }

    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<dialog::DialogManagerMessageHandler>>& getMapForType(
        std::shared_ptr<::multiAgentExperience::dialog::DialogManagerInterface> dialogManagerInterface) {
        return m_dialogManagerMessageHandlers;
    }

    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<dialog::DialogRequestMessageHandler>>& getMapForType(
        std::shared_ptr<::multiAgentExperience::dialog::DialogRequestInterface> dialogRequestInterface) {
        return m_dialogRequestMessageHandlers;
    }

    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<dialog::ListeningHandlerMessageHandler>>& getMapForType(
        std::shared_ptr<::multiAgentExperience::dialog::ListeningHandlerInterface> listeningHandlerInterface) {
        return m_listeningHandlerMessageHandlers;
    }

    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<dialog::SpeakingHandlerMessageHandler>>& getMapForType(
        std::shared_ptr<::multiAgentExperience::dialog::SpeakingHandlerInterface> speakingHandlerInterface) {
        return m_speakingHandlerMessageHandlers;
    }

    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<dialog::ThinkingHandlerMessageHandler>>& getMapForType(
        std::shared_ptr<::multiAgentExperience::dialog::ThinkingHandlerInterface> thinkingHandlerInterface) {
        return m_thinkingHandlerMessageHandlers;
    }

    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<dialog::StartListeningCallbackMessageHandler>>& getMapForType(
        std::shared_ptr<::multiAgentExperience::dialog::StartListeningCallback> startListeningCallback) {
        return m_startListeningCallbackMessageHandlers;
    }

    /// For Experience APIs
    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<experience::ExperienceControllerMessageHandler>>& getMapForType(
        std::shared_ptr<::multiAgentExperience::experience::ExperienceControllerInterface> experienceControllerInterface) {
        return m_experienceControllerMessageHandlers;
    }

    std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<experience::StaticExperienceManagerMessageHandler>>& getMapForType(
        std::shared_ptr<::multiAgentExperience::experience::StaticExperienceManagerInterface>
            staticExperienceManagerInterface) {
        return m_staticExperienceManagerMessageHandlers;
    }

    /**
     * Utility methods to create respective handlers
     */

     /// For Activity APIs
    std::shared_ptr<activity::ActivityManagerMessageHandler> createHandler(
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<::multiAgentExperience::activity::ActivityManagerInterface> activityManagerInterface) {
        return std::make_shared<activity::ActivityManagerMessageHandler>(
            reference,
            m_sender,
            shared_from_this(),
            activityManagerInterface);
    }

    std::shared_ptr<activity::ActivityRequestMessageHandler> createHandler(
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<::multiAgentExperience::activity::ActivityRequestInterface> activityRequestInterface) {
        return std::make_shared<activity::ActivityRequestMessageHandler>(
            reference,
            shared_from_this(),
            activityRequestInterface);
    }

    std::shared_ptr<activity::ActivityHandlerMessageHandler> createHandler(
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<::multiAgentExperience::activity::ActivityHandlerInterface> activityHandlerInterface) {
        return std::make_shared<activity::ActivityHandlerMessageHandler>(
            reference,
            m_sender,
            shared_from_this(),
            activityHandlerInterface);
    }

    std::shared_ptr<activity::ActivityControllerMessageHandler> createHandler(
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<::multiAgentExperience::activity::ActivityControllerInterface> activityControllerInterface) {
        return std::make_shared<activity::ActivityControllerMessageHandler>(
            reference,
            activityControllerInterface);
    }

    /// For Agent APIs
    std::shared_ptr<agent::AgentRegistrationMessageHandler> createHandler(
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<::multiAgentExperience::agent::AgentRegistrationInterface> agentRegistrationInterface) {
        return std::make_shared<agent::AgentRegistrationMessageHandler>(
            reference,
            m_sender,
            shared_from_this(),
            agentRegistrationInterface);
    }

    /// For Common APIs
    std::shared_ptr<common::OnCompletionCallbackMessageHandler> createHandler(
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<::multiAgentExperience::common::OnCompletionCallbackInterface>
        onCompletionCallbackInterface) {
        return std::make_shared<common::OnCompletionCallbackMessageHandler>(
            reference,
            onCompletionCallbackInterface
        );
    }

    /// For Control APIs
    std::shared_ptr<control::ControlMessageHandler> createHandler(
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<::multiAgentExperience::control::Control> control) {
        return std::make_shared<control::ControlMessageHandler>(
            reference,
            control);
    }

    std::shared_ptr<control::ControlRegistryMessageHandler> createHandler(
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<::multiAgentExperience::control::ControlRegistryInterface> controlRegistryInterface) {
        return std::make_shared<control::ControlRegistryMessageHandler>(
            reference,
            m_sender,
            controlRegistryInterface);
    }

    /// For Dialog APIs
    std::shared_ptr<dialog::ControlReceiverMessageHandler> createHandler(
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<::multiAgentExperience::dialog::ControlReceiverInterface> controlReceiverInterface) {
        return std::make_shared<dialog::ControlReceiverMessageHandler>(
            reference,
            m_sender,
            controlReceiverInterface);
    }

    std::shared_ptr<dialog::DialogControllerMessageHandler> createHandler(
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<::multiAgentExperience::dialog::DialogControllerInterface> dialogControllerInterface) {
        return std::make_shared<dialog::DialogControllerMessageHandler>(
            reference,
            dialogControllerInterface);
    }

    std::shared_ptr<dialog::DialogManagerMessageHandler> createHandler(
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<::multiAgentExperience::dialog::DialogManagerInterface> dialogManagerInterface) {
        return std::make_shared<dialog::DialogManagerMessageHandler>(
            reference,
            m_sender,
            shared_from_this(),
            dialogManagerInterface);
    }

    std::shared_ptr<dialog::DialogRequestMessageHandler> createHandler(
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<::multiAgentExperience::dialog::DialogRequestInterface> dialogRequestInterface) {
        return std::make_shared<dialog::DialogRequestMessageHandler>(
            reference,
            m_sender,
            shared_from_this(),
            dialogRequestInterface);
    }

    std::shared_ptr<dialog::ListeningHandlerMessageHandler> createHandler(
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<::multiAgentExperience::dialog::ListeningHandlerInterface> listeningHandlerInterface) {
        return std::make_shared<dialog::ListeningHandlerMessageHandler>(
            reference,
            m_sender,
            listeningHandlerInterface);
    }

    std::shared_ptr<dialog::SpeakingHandlerMessageHandler> createHandler(
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<::multiAgentExperience::dialog::SpeakingHandlerInterface> speakingHandlerInterface) {
        return std::make_shared<dialog::SpeakingHandlerMessageHandler>(
            reference,
            m_sender,
            shared_from_this(),
            speakingHandlerInterface);
    }

    std::shared_ptr<dialog::ThinkingHandlerMessageHandler> createHandler(
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<::multiAgentExperience::dialog::ThinkingHandlerInterface> thinkingHandlerInterface) {
        return std::make_shared<dialog::ThinkingHandlerMessageHandler>(
            reference,
            m_sender,
            thinkingHandlerInterface);
    }

    std::shared_ptr<dialog::StartListeningCallbackMessageHandler> createHandler(
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<::multiAgentExperience::dialog::StartListeningCallback> startListeningCallback) {
        return std::make_shared<dialog::StartListeningCallbackMessageHandler>(
            reference,
            m_sender,
            startListeningCallback);
    }

    /// For Experience APIs
    std::shared_ptr<experience::ExperienceControllerMessageHandler> createHandler(
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<::multiAgentExperience::experience::ExperienceControllerInterface> experienceControllerInterface) {
        return std::make_shared<experience::ExperienceControllerMessageHandler>(
            reference,
            experienceControllerInterface);
    }

    std::shared_ptr<experience::StaticExperienceManagerMessageHandler> createHandler(
        multiAgentExperience::ipc::messaging::Reference reference,
        std::shared_ptr<::multiAgentExperience::experience::StaticExperienceManagerInterface>
            staticExperienceManagerInterface) {
        return std::make_shared<experience::StaticExperienceManagerMessageHandler>(
            reference,
            staticExperienceManagerInterface
            );
    }

    // This method isn't thread safe. So it should be called from methods that are thread safe
    template<typename T>
    void removeFromMap(std::map<multiAgentExperience::ipc::messaging::Reference, std::shared_ptr<T>>& messageHandlerMap,
                       multiAgentExperience::ipc::messaging::Reference& reference) {
        auto entry = messageHandlerMap.find(reference);
        if (entry != messageHandlerMap.end()) {
            messageHandlerMap.erase(entry);
        }
    }

};

} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_PROXY_MESSAGEHANDLERSTORE_H
