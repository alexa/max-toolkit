/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_TRANSPORTSENDERINTERFACE_H
#define MULTIAGENTEXPERIENCE_IPC_TRANSPORTSENDERINTERFACE_H

#include <future>
#include <memory>
#include <utility>

#include <MultiAgentExperience/IPC/Messaging/StringPayload.h>
#include <MultiAgentExperience/IPC/Messaging/StringIntTuplePayload.h>
#include <MultiAgentExperience/IPC/Messaging/VoidMessageTypes.h>
#include <MultiAgentExperience/IPC/Messaging/EnumTuplePayload.h>
#include <MultiAgentExperience/IPC/Messaging/ReferenceListPayload.h>

#include "MultiAgentExperience/IPC/Messaging/Control/ControlRegistryPayload.h"
#include "MultiAgentExperience/IPC/Messaging/Dialog/ControlReceiverPayload.h"
#include "MaxApiTypes.h"
#include "MultiAgentExperience/IPC/Models/Activity/ActivityHandlerModel.h"
#include "MultiAgentExperience/IPC/Models/Activity/ActivityControllerModel.h"
#include "MultiAgentExperience/IPC/Models/Activity/ActivityManagerModel.h"
#include "MultiAgentExperience/IPC/Models/Agent/AgentRegistrationModel.h"
#include "MultiAgentExperience/IPC/Models/Common/OnCompletionCallbackModel.h"
#include "MultiAgentExperience/IPC/Models/Control/ControlModel.h"
#include "MultiAgentExperience/IPC/Models/Control/ControlRegistryModel.h"
#include "MultiAgentExperience/IPC/Models/Dialog/ControlReceiverModel.h"
#include "MultiAgentExperience/IPC/Models/Dialog/DialogControllerModel.h"
#include "MultiAgentExperience/IPC/Models/Dialog/DialogManagerModel.h"
#include "MultiAgentExperience/IPC/Models/Dialog/DialogRequestModel.h"
#include "MultiAgentExperience/IPC/Models/Dialog/ListeningHandlerModel.h"
#include "MultiAgentExperience/IPC/Models/Dialog/SpeakingHandlerModel.h"
#include "MultiAgentExperience/IPC/Models/Dialog/StartListeningCallbackModel.h"
#include "MultiAgentExperience/IPC/Models/Dialog/ThinkingHandlerModel.h"
#include "MultiAgentExperience/IPC/Models/Experience/ExperienceControllerModel.h"
#include "MultiAgentExperience/IPC/Models/Experience/StaticExperienceManagerModel.h"
#include "TransportFutureResponseStore.h"

namespace multiAgentExperience {
namespace ipc {
namespace transport {

class TransportSenderInterface {
public:
    explicit TransportSenderInterface(
            std::shared_ptr<transport::TransportFutureResponseStore> responderStore) :
            m_futureResponseStore{std::move(responderStore)} {
    }

    virtual ~TransportSenderInterface() = default;

    virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage> sendConnectedToMaxMessage() = 0;

    /// @c ActivityManagerInterface
    /// @{

    /// For @c request, @c stop methods
    virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(const multiAgentExperience::ipc::messaging::Message
            <models::activity::ActivityManagerFunctions,multiAgentExperience::ipc::messaging::ReferencePayload>& message) = 0;

    ///@}

    /// @c ActivityRequestInterface
    /// @{

    /// For @c getHandler (for Agent response)
    virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
            const multiAgentExperience::ipc::messaging::Message<
                    models::activity::ActivityRequestFunctionReturns,
                    multiAgentExperience::ipc::messaging::ReferencePayload>& message) = 0;

    /// For @c getType (for Agent response)
    virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
            const multiAgentExperience::ipc::messaging::Message<
                    models::activity::ActivityRequestFunctionReturns,
                    multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::activity::ActivityType>>& message) = 0;

    /// For @c GetMixabilityType (for Agent response)
    virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
            const multiAgentExperience::ipc::messaging::Message<
                    models::activity::ActivityRequestFunctionReturns,
                    multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::activity::MixabilityType>>& message) = 0;

    /// For @c getType (for MAX request)
    virtual std::future<multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestFunctionReturns,
            multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::activity::ActivityType>>> send(
            const multiAgentExperience::ipc::messaging::Message<
                    models::activity::ActivityRequestGetType,
                    multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;

    /// For @c getHandler (for MAX request)
    virtual std::future<multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestFunctionReturns, multiAgentExperience::ipc::messaging::ReferencePayload>> send(
            const multiAgentExperience::ipc::messaging::Message<
                    models::activity::ActivityRequestGetHandler,
                    multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;

    /// For @c GetMixabilityType (for MAX request)
    virtual std::future<multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestFunctionReturns, multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::activity::MixabilityType>>> send(
            const multiAgentExperience::ipc::messaging::Message<
                    models::activity::ActivityRequestGetMixabilityType,
                    multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;

    /// @}

    /// @c ActivityHandlerInterface
    /// @{

    /// For @c onFocusStateChange method
    virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
            const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityHandlerFunctions,
                    multiAgentExperience::ipc::messaging::EnumTuplePayload<::multiAgentExperience::activity::ActivityFocus,
                            multiAgentExperience::activity::MixingBehavior>>& message) = 0;

    /// For @c onGranted method
    virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
            const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityHandlerFunctions,
                    multiAgentExperience::ipc::messaging::ReferenceListPayload>& message) = 0;

    /// For @c onDenied @c onStop method
    virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage>
    send(const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityHandlerFunctions,
            multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;

    /// @}

    /// @c ActivityControllerInterface
    /// @{

    /// For @c stop method
    virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage>
    send(const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityControllerFunctions,
         multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;

    /// @}

    /// Control
    virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage>
    send(const multiAgentExperience::ipc::messaging::Message<models::control::ControlFunctions,
         multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;

    /// ControlRegistryInterface
    virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage>
    send(const multiAgentExperience::ipc::messaging::Message<models::control::ControlRegistryFunctions,
         multiAgentExperience::ipc::messaging::control::ControlRegistryPayload>& message) = 0;

    /// ControlReceiverInterface
    virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage>
    send(const multiAgentExperience::ipc::messaging::Message<models::dialog::ControlReceiverFunctions,
         multiAgentExperience::ipc::messaging::dialog::ControlReceiverPayload>& message) = 0;

    /// @c DialogControllerInterface
    /// @{
    virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogControllerFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;

    /// For @c invokeControlAndStartSpeaking, @c stopAndInvokeControl methods
    virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogControllerFunctions,
        multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::control::ControlType>>& message) = 0;
    /// @}

    /// @c DialogManagerInterface
    /// @{

    /// For @c request, @c stop, @c setControlReceiver, @c setListeningHandler, @c setThinkingHandler, @c setSpeakingHandler
    virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogManagerFunctions,
        multiAgentExperience::ipc::messaging::ReferencePayload>& message) = 0;

    /// For @c setAllHandlers method
    virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogManagerFunctions,
        multiAgentExperience::ipc::messaging::ReferenceListPayload>& message) = 0;

    /// For @c removeAllHandlers, @c removeControlReceiver, @c removeListeningHandler, @c removeThinkingHandler, @c removeSpeakingHandler
    virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogManagerFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;

    /// @}

    /// @c DialogRequestInterface
    /// @{

    /// For @c onDenied, @c onError
    virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctions,
        multiAgentExperience::ipc::messaging::StringPayload>& message) = 0;

    /// For @c onDialogStarted method
    virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctions,
        multiAgentExperience::ipc::messaging::ReferencePayload>& message) = 0;

    /// For @c onDialogStopped
    virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;

    /// For @c getDialogBargeInPriority (for MAX library request)
    virtual std::future<multiAgentExperience::ipc::messaging::Message<
        models::dialog::DialogRequestFunctionReturns,
        multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::dialog::DialogBargeInPriority>>> send(
            const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctionGetDialogBargeInPriority,
            multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;

    /// For @c getDialogBargeInPriority (for agent response)
    virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctionReturns,
        multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::dialog::DialogBargeInPriority>>& message) = 0;
    /// @}

    /// @c ListeningHandlerInterface
    /// @{

    /// For @c onStartListening
    virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::ListeningHandlerFunctions,
        multiAgentExperience::ipc::messaging::ReferencePayload>& message) = 0;

    /// For @c onStopListening
    virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::ListeningHandlerFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;
    /// @}

    /// @c ThinkingHandlerInterface
    /// @{

    /// For @c onStartThinking
    virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::ThinkingHandlerFunctions,
        multiAgentExperience::ipc::messaging::ReferencePayload>& message) = 0;

    /// For @c onStopThinking
    virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::ThinkingHandlerFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;
    /// @}

    /// @c SpeakingHandlerInterface
    /// @{

    /// For @c onStartSpeaking
    virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::SpeakingHandlerFunctions,
        multiAgentExperience::ipc::messaging::ReferenceListPayload>& message) = 0;

    /// For @c onStopSpeaking
    virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::SpeakingHandlerFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;
    /// @}

    /// @c StartListeningCallback
    /// @{

    /// For @c startListening
    virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::StartListeningCallbackFunctions,
        multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;
    /// @}


    /// ExperienceControllerInterface
    /// @{

    /// For @c startExperience
    virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage>
    send(const multiAgentExperience::ipc::messaging::Message<models::experience
    ::ExperienceControllerFunctions, multiAgentExperience::ipc::messaging::StringPayload>& message) = 0;

    /// For @c endExperience
    /// ToDo : discuss if we can re-use the same function for sending invalidate() message as well
    virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage>
    send(const multiAgentExperience::ipc::messaging::Message<models::experience
    ::ExperienceControllerFunctions, multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;

    /// @}

  /// StaticExperienceManagerInterface
  /// {@

  /// For @c addStaticExperience
  virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage>
  send(const multiAgentExperience::ipc::messaging::Message<models::experience
  ::StaticExperienceManagerFunctions, multiAgentExperience::ipc::messaging::StringIntTuplePayload>& message) = 0;

  /// For @c removeStaticExperience
  virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage>
  send(const multiAgentExperience::ipc::messaging::Message<models::experience::StaticExperienceManagerFunctions, multiAgentExperience::ipc::messaging::StringPayload>& message) = 0;

  /// For @c removeAllStaticExperiences
  virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage>
  send(const multiAgentExperience::ipc::messaging::Message<models::experience::StaticExperienceManagerFunctions, multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;

  /// @}

  /// onCompletionCallbackInterface
  /// @{
  virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage>
  send(const multiAgentExperience::ipc::messaging::Message<models::common::OnCompletionCallbackFunctions,
       multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;
  /// @}

  /// AgentRegistrationInterface
  /// @{
  virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
      const multiAgentExperience::ipc::messaging::Message<models::agent::AgentRegistrationFunctions,
      multiAgentExperience::ipc::messaging::ReferenceListPayload>& message) = 0;

  virtual std::future<multiAgentExperience::ipc::messaging::Message<
    models::agent::AgentRegistrationFunctionReturns,
    multiAgentExperience::ipc::messaging::StringPayload>> send(
        const multiAgentExperience::ipc::messaging::Message<models::agent::AgentRegistrationFunctionGetId,
        multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;

  virtual std::future<multiAgentExperience::ipc::messaging::Message<
        models::agent::AgentRegistrationFunctionReturns,
        multiAgentExperience::ipc::messaging::StringPayload>> send(
        const multiAgentExperience::ipc::messaging::Message<models::agent::AgentRegistrationFunctionGetName,
        multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;

  virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
        const multiAgentExperience::ipc::messaging::Message<models::agent::AgentRegistrationFunctionReturns,
        multiAgentExperience::ipc::messaging::StringPayload>& message) = 0;
  /// @}

  /// MessageHandlerDeletion
  /// @{
  virtual std::future<multiAgentExperience::ipc::messaging::VoidMessage> send(
          const multiAgentExperience::ipc::messaging::Message<transport::MaxApiType,
                  multiAgentExperience::ipc::messaging::VoidPayload>& message) = 0;
  /// @}

protected:
    std::shared_ptr<transport::TransportFutureResponseStore> m_futureResponseStore;

};

} // namespace transport
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_TRANSPORTSENDERINTERFACE_H
