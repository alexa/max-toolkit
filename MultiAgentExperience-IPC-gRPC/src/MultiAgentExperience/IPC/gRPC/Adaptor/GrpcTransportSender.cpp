/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <MultiAgentExperience/IPC/Messaging/VoidMessageTypes.h>
#include <MultiAgentExperience/IPC/Messaging/ReferencePayload.h>
#include <MultiAgentExperience/IPC/Messaging/MessageUtils.h>
#include <MultiAgentExperience/IPC/gRPC/Adaptor/GrpcTransportSender.h>
#include <MultiAgentExperience/Activity/ActivityType.h>
#include <MultiAgentExperience/Activity/ActivityFocus.h>
#include <future>

#include "MultiAgentExperience/IPC/gRPC/Utils/MessageUtils.h"
#include "MultiAgentExperience/IPC/gRPC/Utils/FunctionToMessageType.h"

namespace multiAgentExperience {
namespace ipc {
namespace grpc {
namespace adaptor {

std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::sendConnectedToMaxMessage() {
    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForVoidPayload(
        ::multiAgentExperience::ipc::messaging::reference::getNullReference());

    transportMessage.set_maxmessage(MultiAgentExperience::Rpc::MaxMessageType::CONNECTED_TO_MAX);

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(
        multiAgentExperience::ipc::messaging::reference::getNullReference()));
}

/// @c ActivityManagerInterface
/// @{

/// For @c request, @c stop methods
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
        const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityManagerFunctions,
        multiAgentExperience::ipc::messaging::ReferencePayload> &message) {
    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForReferencePayload(
            message.getReference(), message.getPayload());

    transportMessage.set_activitymanagermessagetype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}

///@}

/// @c ActivityRequestInterface
/// @{

/// For @c getHandler (for Agent response)
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
        const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestFunctionReturns,
        multiAgentExperience::ipc::messaging::ReferencePayload> &message) {
    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForReferencePayload(
            message.getReference(), message.getPayload());

    transportMessage.set_activityrequestreturnmessagetype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}

/// For @c getType (for Agent response)
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
        const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestFunctionReturns,
        multiAgentExperience::ipc::messaging::EnumPayload<::multiAgentExperience::activity::ActivityType>> &message) {
    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessage(message.getReference());
    transportMessage.mutable_replytoempty()->CopyFrom(MultiAgentExperience::Rpc::VoidPayload());

    transportMessage.set_activityrequestreturnmessagetype(utils::getMessageTypeForFunction(message.getFunction()));
    transportMessage.set_activitytype(utils::getMessageTypeForActivityType(message.getPayload().m_value));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}

/// For @c GetMixabilityType (for Agent response)
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
        const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestFunctionReturns,
        multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::activity::MixabilityType>> &message) {
    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessage(message.getReference());
    transportMessage.mutable_replytoempty()->CopyFrom(MultiAgentExperience::Rpc::VoidPayload());

    transportMessage.set_activityrequestreturnmessagetype(utils::getMessageTypeForFunction(message.getFunction()));
    transportMessage.set_mixabilitytype(utils::getMessageTypeForMixabilityType(message.getPayload().m_value));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}

/// For @c getType (for MAX request)
std::future<multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestFunctionReturns,
multiAgentExperience::ipc::messaging::EnumPayload<::multiAgentExperience::activity::ActivityType>>>
GrpcTransportSender::send(
        const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestGetType, multiAgentExperience::ipc::messaging::VoidPayload> &message) {

    auto futureResponse =
            this->m_futureResponseStore->createFutureResponse<
                    multiAgentExperience::ipc::messaging::Message<
                            models::activity::ActivityRequestFunctionReturns,
                            multiAgentExperience::ipc::messaging::EnumPayload<::multiAgentExperience::activity::ActivityType>>>();

    // Create the top-level protobuf Message with the replyTo parameter set to the Reference of the TransportFutureResponse object
    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForVoidPayloadWithReplyTo(
            message.getReference(), futureResponse->getReference());

    auto transportMessageType = MultiAgentExperience::Rpc::ActivityRequestGetTypeMessageType::ACTIVITY_REQUEST_GET_TYPE;
    transportMessage.set_activityrequestgettypemessagetype(transportMessageType);

    auto response = execute<
            models::activity::ActivityRequestFunctionReturns,
            multiAgentExperience::ipc::messaging::EnumPayload<::multiAgentExperience::activity::ActivityType>>(
            models::activity::ActivityRequestFunctionReturns::GET_TYPE,
            transportMessage,
            futureResponse);

    return response;
}

/// For @c getHandler (for MAX request)
std::future<multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestFunctionReturns, multiAgentExperience::ipc::messaging::ReferencePayload>>
GrpcTransportSender::send(
        const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestGetHandler, multiAgentExperience::ipc::messaging::VoidPayload> &message) {
    auto futureResponse =
            this->m_futureResponseStore->createFutureResponse<
                    multiAgentExperience::ipc::messaging::Message<
                            models::activity::ActivityRequestFunctionReturns,
                            multiAgentExperience::ipc::messaging::ReferencePayload>>();

    // Create the top-level protobuf Message with the replyTo parameter set to the Reference of the TransportFutureResponse object
    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForVoidPayloadWithReplyTo(
            message.getReference(), futureResponse->getReference());

    auto transportMessageType = MultiAgentExperience::Rpc::ActivityRequestGetHandlerMessageType::ACTIVITY_REQUEST_GET_HANDLER;
    transportMessage.set_activityrequestgethandlermessagetype(transportMessageType);

    auto response = execute<
            models::activity::ActivityRequestFunctionReturns,
            multiAgentExperience::ipc::messaging::ReferencePayload>(
            models::activity::ActivityRequestFunctionReturns::GET_HANDLER,
            transportMessage,
            futureResponse);

    return response;
}

/// For @c GetMixabilityType (for MAX request)
std::future<multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestFunctionReturns,
        multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::activity::MixabilityType>>>
GrpcTransportSender::send(
        const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityRequestGetMixabilityType, multiAgentExperience::ipc::messaging::VoidPayload> &message) {
    auto futureResponse =
            this->m_futureResponseStore->createFutureResponse<
                    multiAgentExperience::ipc::messaging::Message<
                            models::activity::ActivityRequestFunctionReturns,
                            multiAgentExperience::ipc::messaging::EnumPayload<::multiAgentExperience::activity::MixabilityType>>>();

    // Create the top-level protobuf Message with the replyTo parameter set to the Reference of the TransportFutureResponse object
    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForVoidPayloadWithReplyTo(
            message.getReference(), futureResponse->getReference());

    auto transportMessageType = MultiAgentExperience::Rpc::ActivityRequestGetMixabilityTypeMessageType::ACTIVITY_REQUEST_GET_MIXABILITY_TYPE;
    transportMessage.set_activityrequestgetmixabilitytypemessagetype(transportMessageType);

    auto response = execute<
            models::activity::ActivityRequestFunctionReturns,
            multiAgentExperience::ipc::messaging::EnumPayload<::multiAgentExperience::activity::MixabilityType>>(
            models::activity::ActivityRequestFunctionReturns::GET_MIXABILITY_TYPE,
            transportMessage,
            futureResponse);

    return response;
}

/// @}

/// @c ActivityHandlerInterface
/// @{

/// For @c onDenied @c onStop method
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
        const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityHandlerFunctions, multiAgentExperience::ipc::messaging::VoidPayload> &message) {
    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForVoidPayload(message.getReference());

    transportMessage.set_activityhandlermessagetype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}


/// For @c onGranted method
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
        const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityHandlerFunctions, multiAgentExperience::ipc::messaging::ReferenceListPayload> &message) {

    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForReferenceListPayload(
            message.getReference(), message.getPayload());

    transportMessage.set_activityhandlermessagetype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}

/// For @c onFocusStateChange method
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
    const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityHandlerFunctions,
            multiAgentExperience::ipc::messaging::EnumTuplePayload<
            ::multiAgentExperience::activity::ActivityFocus, multiAgentExperience::activity::MixingBehavior>>& message) {

    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessage(message.getReference());
    auto emptyReplyTo = MultiAgentExperience::Rpc::VoidPayload();
    transportMessage.mutable_replytoempty()->CopyFrom(emptyReplyTo);

    transportMessage.set_activityhandlermessagetype(utils::getMessageTypeForFunction(message.getFunction()));
    utils::createPayloadForActivityFocusChange(message.getPayload().m_value1, message.getPayload().m_value2, transportMessage);

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}

/// @}

/// @c ActivityControllerInterface
/// @{

/// For @c stop method
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
        const multiAgentExperience::ipc::messaging::Message<models::activity::ActivityControllerFunctions, multiAgentExperience::ipc::messaging::VoidPayload> &message) {

    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForVoidPayload(message.getReference());

    switch(message.getFunction()) {
        case models::activity::ActivityControllerFunctions::STOP: {
            transportMessage.set_activitycontrollermessagetype(MultiAgentExperience::Rpc::ActivityControllerMessageType::CONTROLLER_STOP);
            break;
        }
    }

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}

/// @}

/// @c DialogControllerInterface
/// @{

std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogControllerFunctions,
    multiAgentExperience::ipc::messaging::VoidPayload>& message) {

    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForVoidPayload(message.getReference());

    transportMessage.set_dialogcontrollermessagetype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}

/// For @c invokeControlAndStartSpeaking, @c stopAndInvokeControl methods
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogControllerFunctions,
    multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::control::ControlType>>& message) {

    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForControlTypePayload(
        message.getReference(), message.getPayload());

    transportMessage.set_dialogcontrollermessagetype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}

/// @}

/// @c DialogManagerInterface
/// @{

/// For @c request, @c stop, @c setControlReceiver, @c setListeningHandler, @c setThinkingHandler, @c setSpeakingHandler
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogManagerFunctions,
    multiAgentExperience::ipc::messaging::ReferencePayload>& message) {

    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForReferencePayload(
        message.getReference(), message.getPayload());

    transportMessage.set_dialogmanagermessagetype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}

/// For @c setAllHandlers method
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogManagerFunctions,
    multiAgentExperience::ipc::messaging::ReferenceListPayload>& message) {

    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForReferenceListPayload(
        message.getReference(), message.getPayload());

    transportMessage.set_dialogmanagermessagetype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}

/// For @c removeAllHandlers, @c removeControlReceiver, @c removeListeningHandler, @c removeThinkingHandler, @c removeSpeakingHandler
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogManagerFunctions,
    multiAgentExperience::ipc::messaging::VoidPayload>& message) {

    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForVoidPayload(
        message.getReference());

    transportMessage.set_dialogmanagermessagetype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}

/// @}

/// @c DialogRequestInterface
/// @{

/// For @c onDenied, @c onError
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctions,
    multiAgentExperience::ipc::messaging::StringPayload>& message) {

    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForStringPayload(
        message.getReference(), message.getPayload());

    transportMessage.set_dialogrequestmessagetype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}

/// For @c onDialogStarted method
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctions,
    multiAgentExperience::ipc::messaging::ReferencePayload>& message) {

    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForReferencePayload(
        message.getReference(), message.getPayload());

    transportMessage.set_dialogrequestmessagetype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}

/// For @c onDialogStopped
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctions,
    multiAgentExperience::ipc::messaging::VoidPayload>& message) {

    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForVoidPayload(
        message.getReference());

    transportMessage.set_dialogrequestmessagetype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}

/// For @c getDialogBargeInPriority (for MAX library request)
std::future<multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctionReturns,
    multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::dialog::DialogBargeInPriority>>> GrpcTransportSender::send(
        const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctionGetDialogBargeInPriority,
        multiAgentExperience::ipc::messaging::VoidPayload>& message) {

        /**
         * Create the TransportFutureResponse object for this API. Since getDialogBargeInPriority is a synchronous API,
         * we must wait until we receive a response from the other side. This response is sent as a separate gRPC request.
         *
         * We wait for this response using the TransportFutureResponse.waitForResponse() internally. When the response
         * is received the particular TransportFutureResponse stops waiting because the reply method is invoked.
         * Now the DialogBargeInPriority value can be retrieved and passed along.
         *
         * The FutureResponseStore stores the TransportFutureResponse object against its Reference (hash). This Reference is
         * sent across process in the replyTo parameter of the gRPC Message. The agent should take care to mention this
         * Reference when it sends back the response.
         */
        auto futureResponse = this->m_futureResponseStore->createFutureResponse<multiAgentExperience::ipc::messaging::Message<
            models::dialog::DialogRequestFunctionReturns,
            multiAgentExperience::ipc::messaging::EnumPayload<::multiAgentExperience::dialog::DialogBargeInPriority>>>();

        // Create the top-level protobuf Message with the replyTo parameter set to the Reference of the TransportFutureResponse object
        MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForVoidPayloadWithReplyTo(
            message.getReference(), futureResponse->getReference());

        transportMessage.set_dialogrequestgetdialogbargeinprioritymessagetype(
            MultiAgentExperience::Rpc::DialogRequestGetDialogBargeInPriorityMessageType::DIALOG_REQUEST_GET_DIALOG_BARGE_IN_PRIORITY);

        // In this version of the execute method, we specify the Message (ExpectedEnum and ExpectedPayload) that we expect to receive as a response.
        return execute<
            models::dialog::DialogRequestFunctionReturns,
            multiAgentExperience::ipc::messaging::EnumPayload<::multiAgentExperience::dialog::DialogBargeInPriority>>(
                models::dialog::DialogRequestFunctionReturns::GET_DIALOG_BARGE_IN_PRIORITY,
                transportMessage,
                futureResponse);
}

/// For @c getDialogBargeInPriority (for agent response)
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::DialogRequestFunctionReturns,
    multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::dialog::DialogBargeInPriority>>& message) {

    // The `message.getReference()` refers to the replyToReference that was stored in the TransportResponder object.
    // When MAX library handles this request, it extracts the reference and uses it to fetch the TransportFutureResponse
    // from the store.
    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessage(message.getReference());

    // Set the ReplyToReference parameter to VoidPayload
    transportMessage.mutable_replytoempty()->CopyFrom(MultiAgentExperience::Rpc::VoidPayload());

    // Retrieve the value of DialogBargePriority from the message object and set it in the protobuf Message
    transportMessage.set_dialogbargeinpriority(utils::getMessageTypeForDialogBargePriority(message.getPayload().m_value));

    transportMessage.set_dialogrequestreturnmessagetype(MultiAgentExperience::Rpc::DialogRequestReturnMessageType::GET_DIALOG_BARGE_IN_PRIORITY);

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}
/// @}

/// @c ListeningHandlerInterface
/// @{

/// For @c onStartListening
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::ListeningHandlerFunctions,
    multiAgentExperience::ipc::messaging::ReferencePayload>& message) {

    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForReferencePayload(
        message.getReference(), message.getPayload());

    transportMessage.set_listeninghandlermessagetype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}

/// For @c onStopListening
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::ListeningHandlerFunctions,
    multiAgentExperience::ipc::messaging::VoidPayload>& message) {

    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForVoidPayload(
        message.getReference());

    transportMessage.set_listeninghandlermessagetype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}

/// @}

/// @c ThinkingHandlerInterface
/// @{

/// For @c onStartThinking
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::ThinkingHandlerFunctions,
    multiAgentExperience::ipc::messaging::ReferencePayload>& message) {

    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForReferencePayload(
        message.getReference(), message.getPayload());

    transportMessage.set_thinkinghandlermessagetype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}

/// For @c onStopThinking
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::ThinkingHandlerFunctions,
    multiAgentExperience::ipc::messaging::VoidPayload>& message) {

    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForVoidPayload(
        message.getReference());

    transportMessage.set_thinkinghandlermessagetype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}

/// @}

/// @c SpeakingHandlerInterface
/// @{

/// For @c onStartSpeaking
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::SpeakingHandlerFunctions,
    multiAgentExperience::ipc::messaging::ReferenceListPayload>& message) {

    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForReferenceListPayload(
        message.getReference(), message.getPayload());

    transportMessage.set_speakinghandlermessagetype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}

/// For @c onStopSpeaking
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::SpeakingHandlerFunctions,
    multiAgentExperience::ipc::messaging::VoidPayload>& message) {

    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForVoidPayload(
        message.getReference());

    transportMessage.set_speakinghandlermessagetype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}
/// @}

/// @c StartListeningCallback
/// @{

/// For @c startListening
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::StartListeningCallbackFunctions,
    multiAgentExperience::ipc::messaging::VoidPayload>& message) {

    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForVoidPayload(
        message.getReference());

    transportMessage.set_startlisteningcallbackmessagetype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}

/// @}

/// @c Control
/// @{

/// For @c task
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
    const multiAgentExperience::ipc::messaging::Message<models::control::ControlFunctions,
    multiAgentExperience::ipc::messaging::VoidPayload>& message) {
    MultiAgentExperience::Rpc::Message transportMessage =
        utils::createMessageForVoidPayload(message.getReference());

    transportMessage.set_controlmessagetype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}
/// @}

/// @c ControlRegistryInterface
/// @{

/// For @c update
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
    const multiAgentExperience::ipc::messaging::Message<models::control::ControlRegistryFunctions,
    multiAgentExperience::ipc::messaging::control::ControlRegistryPayload>& message) {
    MultiAgentExperience::Rpc::Message transportMessage =
        utils::createMessageForControlRegistryPayload(
            message.getReference(),
            message.getPayload());

    transportMessage.set_controlregistrymessagetype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}
/// @}

/// @c ControlReceiverInterface
/// @{

/// For @c onControlsReceived
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
    const multiAgentExperience::ipc::messaging::Message<models::dialog::ControlReceiverFunctions,
    multiAgentExperience::ipc::messaging::dialog::ControlReceiverPayload>& message) {
    MultiAgentExperience::Rpc::Message transportMessage =
        utils::createMessageForControlReceiverPayload(
            message.getReference(),
            message.getPayload());

    transportMessage.set_controlreceivermessagetype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}
/// @}

/// ExperienceControllerInterface
/// @{

/// For @c startExperience
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
    const multiAgentExperience::ipc::messaging::Message<models::experience::ExperienceControllerFunctions,
    multiAgentExperience::ipc::messaging::StringPayload>& message) {

    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForStringPayload(
        message.getReference(), message.getPayload());

    transportMessage.set_experiencecontrollermessagetype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}

/// For @c endExperience and @c invalidate
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
    const multiAgentExperience::ipc::messaging::Message<models::experience::ExperienceControllerFunctions,
    multiAgentExperience::ipc::messaging::VoidPayload>& message) {

    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForVoidPayload(message.getReference());

    transportMessage.set_experiencecontrollermessagetype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}

/// @}

/// StaticExperienceManagerInterface
/// {@

/// For @c addStaticExperience
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
    const multiAgentExperience::ipc::messaging::Message<models::experience::StaticExperienceManagerFunctions,
    multiAgentExperience::ipc::messaging::StringIntTuplePayload>& message) {

    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForStringIntTuplePayload(
        message.getReference(), message.getPayload());

    transportMessage.set_staticexperiencemanagermessagetype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}

/// For @c removeStaticExperience
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
    const multiAgentExperience::ipc::messaging::Message<models::experience::StaticExperienceManagerFunctions,
    multiAgentExperience::ipc::messaging::StringPayload>& message) {

    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForStringPayload(
        message.getReference(), message.getPayload());

    transportMessage.set_staticexperiencemanagermessagetype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}

/// For @c removeAllStaticExperiences
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
    const multiAgentExperience::ipc::messaging::Message<models::experience::StaticExperienceManagerFunctions,
    multiAgentExperience::ipc::messaging::VoidPayload>& message) {

    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForVoidPayload(message.getReference());

    transportMessage.set_staticexperiencemanagermessagetype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}

/// @}


/// onCompletionCallbackInterface
/// @{
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
    const multiAgentExperience::ipc::messaging::Message<models::common::OnCompletionCallbackFunctions,
    multiAgentExperience::ipc::messaging::VoidPayload>& message) {

    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForVoidPayload(message.getReference());

    transportMessage.set_oncompletioncallbackmessagetype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}
/// @}

/// AgentRegistrationInterface
/// @{

/// @c onReady()
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
    const multiAgentExperience::ipc::messaging::Message<models::agent::AgentRegistrationFunctions,
    multiAgentExperience::ipc::messaging::ReferenceListPayload>& message) {

    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForReferenceListPayload(
        message.getReference(), message.getPayload());

    transportMessage.set_agentregistrationmessagetype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}

///// @c getId()
std::future<multiAgentExperience::ipc::messaging::Message<
    models::agent::AgentRegistrationFunctionReturns ,multiAgentExperience::ipc::messaging::StringPayload>> GrpcTransportSender::send(
        const multiAgentExperience::ipc::messaging::Message<models::agent::AgentRegistrationFunctionGetId,
        multiAgentExperience::ipc::messaging::VoidPayload>& message) {

    /**
     * Create the TransportFutureResponse object for this API. Since getId is a synchronous API,
     * we must wait until we receive a response from the other side. This response is sent as a separate gRPC request.
     *
     * We wait for this response using the TransportFutureResponse.waitForResponse() internally. When the response
     * is received the particular TransportFutureResponse stops waiting because the reply method is invoked.
     * Now the string value for the Id can be retrieved and passed along.
     *
     * The FutureResponseStore stores the TransportFutureResponse object against its Reference (hash). This Reference is
     * sent across process in the replyTo parameter of the gRPC Message. The agent should take care to mention this
     * Reference when it sends back the response.
     */
    auto futureResponse = this->m_futureResponseStore->createFutureResponse<multiAgentExperience::ipc::messaging::Message<
        models::agent::AgentRegistrationFunctionReturns, multiAgentExperience::ipc::messaging::StringPayload>>();

    // Create the top-level protobuf Message with the replyTo parameter set to the Reference of the TransportFutureResponse object
    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForVoidPayloadWithReplyTo(
        message.getReference(), futureResponse->getReference());

    transportMessage.set_agentregistrationgetidmessagetype(
        MultiAgentExperience::Rpc::AgentRegistrationGetIdMessageType::AGENT_REGISTRATION_GET_ID);

    // In this version of the execute method, we specify the Message (ExpectedEnum and ExpectedPayload) that we expect to receive as a response.
    return execute<models::agent::AgentRegistrationFunctionReturns, multiAgentExperience::ipc::messaging::StringPayload>(
        models::agent::AgentRegistrationFunctionReturns::GET_ID, transportMessage, futureResponse);
}

/// @c getName()
std::future<multiAgentExperience::ipc::messaging::Message<
    models::agent::AgentRegistrationFunctionReturns, multiAgentExperience::ipc::messaging::StringPayload>> GrpcTransportSender::send(
        const multiAgentExperience::ipc::messaging::Message<models::agent::AgentRegistrationFunctionGetName,
        multiAgentExperience::ipc::messaging::VoidPayload>& message) {

    /**
     * Create the TransportFutureResponse object for this API. Since getId is a synchronous API,
     * we must wait until we receive a response from the other side. This response is sent as a separate gRPC request.
     *
     * We wait for this response using the TransportFutureResponse.waitForResponse() internally. When the response
     * is received the particular TransportFutureResponse stops waiting because the reply method is invoked.
     * Now the string value for the Id can be retrieved and passed along.
     *
     * The FutureResponseStore stores the TransportFutureResponse object against its Reference (hash). This Reference is
     * sent across process in the replyTo parameter of the gRPC Message. The agent should take care to mention this
     * Reference when it sends back the response.
     */
    auto futureResponse = this->m_futureResponseStore->createFutureResponse<multiAgentExperience::ipc::messaging::Message<
        models::agent::AgentRegistrationFunctionReturns, multiAgentExperience::ipc::messaging::StringPayload>>();

    // Create the top-level protobuf Message with the replyTo parameter set to the Reference of the TransportFutureResponse object
    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForVoidPayloadWithReplyTo(
        message.getReference(), futureResponse->getReference());

    transportMessage.set_agentregistrationgetnamemessagetype(
        MultiAgentExperience::Rpc::AgentRegistrationGetNameMessageType::AGENT_REGISTRATION_GET_NAME);

    // In this version of the execute method, we specify the Message (ExpectedEnum and ExpectedPayload) that we expect to receive as a response.
    return execute<models::agent::AgentRegistrationFunctionReturns, multiAgentExperience::ipc::messaging::StringPayload>(
        models::agent::AgentRegistrationFunctionReturns::GET_NAME, transportMessage, futureResponse);
}

/// Used for the response for the above two methods (getId() and getName())
std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
    const multiAgentExperience::ipc::messaging::Message<models::agent::AgentRegistrationFunctionReturns,
    multiAgentExperience::ipc::messaging::StringPayload>& message) {

    // The `message.getReference()` refers to the replyToReference that was stored in the TransportResponder object.
    // When MAX library handles this request, it extracts the reference and uses it to fetch the TransportFutureResponse
    // from the store.
    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForStringPayload(
        message.getReference(), multiAgentExperience::ipc::messaging::StringPayload(message.getPayload().m_value));

    // Set the MessageType
    transportMessage.set_agentregistrationreturnmessagetype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}

/// @}

std::future<multiAgentExperience::ipc::messaging::VoidMessage> GrpcTransportSender::send(
        const multiAgentExperience::ipc::messaging::Message<multiAgentExperience::ipc::transport::MaxApiType,
                multiAgentExperience::ipc::messaging::VoidPayload>& message) {

    MultiAgentExperience::Rpc::Message transportMessage = utils::createMessageForVoidPayload(
            message.getReference());
    transportMessage.set_maxapitype(utils::getMessageTypeForFunction(message.getFunction()));

    return execute(transportMessage, multiAgentExperience::ipc::messaging::createVoidMessage(message.getReference()));
}

} // namespace adaptor
} // namespace grpc
} // namespace ipc
} // namespace multiAgentExperience