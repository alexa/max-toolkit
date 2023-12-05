/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#include "MultiAgentExperience/IPC/gRPC/Adaptor/GrpcTransportReceiver.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "MultiAgentExperience/IPC/gRPC/Connection/GrpcConnectionConfiguration.h"
#include "MultiAgentExperience/IPC/gRPC/Utils/FunctionToMessageType.h"
#include "MultiAgentExperience/IPC/gRPC/Utils/MessageUtils.h"

namespace multiAgentExperience {
namespace ipc {
namespace grpc {
namespace adaptor {

static const std::string MODULE_TAG("GrpcTransportReceiver");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

bool GrpcTransportReceiver::waitForReady() {
    LX(DEBUG0, "Waiting for other process's client to connect to our server by sending the CONNECTED_TO_MAX message");
    auto status = m_connectionWaiter.get_future().wait_for(
        std::chrono::milliseconds(connection::CONNECTED_TO_MAX_TIMEOUT_MILLISECONDS));

    if (status != std::future_status::ready) {
        LX(ERROR, "Error occurred while waiting for CONNECTED_TO_MAX");
        return false;
    }

    LX(DEBUG0, "Received CONNECTED_TO_MAX message");

    return true;
}

void GrpcTransportReceiver::receiveAndHandle(const ::MultiAgentExperience::Rpc::Message* request) {
    LX(DEBUG3, "");

    auto reference = multiAgentExperience::ipc::messaging::Reference(
        request->reference().nspace(), request->reference().name(), request->reference().identifier());

    // Switch based on the type of the MessageType argument of the request. The MessageType parameter is a oneof type
    // and can be any one of the below types. For each type, we have a unique method to handle the request.
    switch (request->MessageType_case()) {

        case MultiAgentExperience::Rpc::Message::kMaxMessage:
            LX(DEBUG3, "Handling MaxMessageType for reference ");
            handleMaxMessage(request);
            break;

        case MultiAgentExperience::Rpc::Message::kActivityManagerMessageType:
            LX(DEBUG3, "Handling ActivityManagerMessageType");
            handleActivityManagerMessage(request, reference);
            break;

        case MultiAgentExperience::Rpc::Message::kActivityRequestGetTypeMessageType:
            LX(DEBUG3, "Handling ActivityRequestGetTypeMessageType");
            handleActivityRequestGetTypeMessage(request, reference);
            break;

        case MultiAgentExperience::Rpc::Message::kActivityRequestGetHandlerMessageType:
            LX(DEBUG3, "Handling ActivityRequestGetHandlerMessageType");
            handleActivityRequestGetHandlerMessage(request, reference);
            break;

        case MultiAgentExperience::Rpc::Message::kActivityRequestGetMixabilityTypeMessageType:
            LX(DEBUG3, "Handling ActivityRequestGetMixabilityTypeMessageType");
            handleActivityRequestGetMixabilityTypeMessage(request, reference);
            break;

        case MultiAgentExperience::Rpc::Message::kActivityRequestReturnMessageType:
            LX(DEBUG3, "Handling ActivityRequestReturnMessageType");
            handleActivityRequestReturnMessage(request, reference);
            break;

        case MultiAgentExperience::Rpc::Message::kActivityHandlerMessageType:
            LX(DEBUG3, "Handling ActivityHandlerMessageType");
            handleActivityHandlerMessage(request, reference);
            break;

        case MultiAgentExperience::Rpc::Message::kActivityControllerMessageType:
            LX(DEBUG3, "Handling ActivityControllerMessageType");
            handleActivityControllerMessage(reference);
            break;

        case MultiAgentExperience::Rpc::Message::kControlMessageType:
            LX(DEBUG3, "Handling ControlMessageType");
            handleControlMessage(request, reference);
            break;

        case MultiAgentExperience::Rpc::Message::kControlRegistryMessageType:
            LX(DEBUG3, "Handling ControlRegistryMessageType");
            handleControlRegistryMessage(request, reference);
            break;

        case MultiAgentExperience::Rpc::Message::kControlReceiverMessageType:
            LX(DEBUG3, "Handling ControlReceiverMessageType");
            handleControlReceiverMessage(request, reference);
            break;

        case MultiAgentExperience::Rpc::Message::kDialogControllerMessageType:
            LX(DEBUG3, "Handling DialogControllerMessageType");
            handleDialogControllerMessage(request, reference);
            break;

        case MultiAgentExperience::Rpc::Message::kDialogManagerMessageType:
            LX(DEBUG3, "Handling DialogManagerMessageType");
            handleDialogManagerMessage(request, reference);
            break;

        case MultiAgentExperience::Rpc::Message::kDialogRequestMessageType:
            LX(DEBUG3, "Handling DialogRequestMessageType");
            handleDialogRequestMessage(request, reference);
            break;

        case MultiAgentExperience::Rpc::Message::kDialogRequestGetDialogBargeInPriorityMessageType:
            LX(DEBUG3, "Handling DialogRequestGetDialogBargeInPriorityMessageType");
            handleDialogRequestGetDialogBargeInPriorityMessage(request, reference);
            break;

        case MultiAgentExperience::Rpc::Message::kDialogRequestReturnMessageType:
            LX(DEBUG3, "Handling DialogRequestReturnMessageType");
            handleDialogRequestReturnMessage(request, reference);
            break;

        case MultiAgentExperience::Rpc::Message::kListeningHandlerMessageType:
            LX(DEBUG3, "Handling ListeningHandlerMessageType");
            handleListeningHandlerMessage(request, reference);
            break;

        case MultiAgentExperience::Rpc::Message::kThinkingHandlerMessageType:
            LX(DEBUG3, "Handling ThinkingHandlerMessageType");
            handleThinkingHandlerMessage(request, reference);
            break;

        case MultiAgentExperience::Rpc::Message::kSpeakingHandlerMessageType:
            LX(DEBUG3, "Handling SpeakingHandlerMessageType");
            handleSpeakingHandlerMessage(request, reference);
            break;

        case MultiAgentExperience::Rpc::Message::kStartListeningCallbackMessageType:
            LX(DEBUG3, "Handling StartListeningCallbackMessageType");
            handleStartListeningCallbackMessage(request, reference);
            break;

        case MultiAgentExperience::Rpc::Message::kExperienceControllerMessageType:
            LX(DEBUG3, "Handling ExperienceControllerMessageType");
            handleExperienceControllerMessage(request, reference);
            break;

        case MultiAgentExperience::Rpc::Message::kStaticExperienceManagerMessageType:
            LX(DEBUG3, "Handling StaticExperienceManagerMessageType");
            handleStaticExperienceManagerMessage(request, reference);
            break;

        case MultiAgentExperience::Rpc::Message::kOnCompletionCallbackMessageType:
            LX(DEBUG3, "Handling OnCompletionCallbackMessageType");
            handleOnCompletionCallbackMessage(request, reference);
            break;

        case MultiAgentExperience::Rpc::Message::kAgentRegistrationMessageType:
            LX(DEBUG3, "Handling AgentRegistrationMessageType");
            handleAgentRegistrationMessage(request, reference);
            break;

        case MultiAgentExperience::Rpc::Message::kAgentRegistrationGetIdMessageType:
            LX(DEBUG3, "Handling AgentRegistrationGetIdMessageType");
            handleAgentRegistrationGetIdMessage(request, reference);
            break;

        case MultiAgentExperience::Rpc::Message::kAgentRegistrationGetNameMessageType:
            LX(DEBUG3, "Handling AgentRegistrationGetNameMessageType");
            handleAgentRegistrationGetNameMessage(request, reference);
            break;

        case MultiAgentExperience::Rpc::Message::kAgentRegistrationReturnMessageType:
            LX(DEBUG3, "Handling AgentRegistrationReturnMessageType");
            handleAgentRegistrationReturnMessage(request, reference);
            break;

        case MultiAgentExperience::Rpc::Message::kMaxApiType:
            LX(DEBUG3, "Handling MaxApiType for deleting message handlers");
            handleDeleteMessageHandlerMessage(request, reference);
            break;

        default:
            // TODO: add error handling here
            LX(WARN, "Incorrect MessageType received. Cannot process.");
    }
}

void GrpcTransportReceiver::handleMaxMessage(const ::MultiAgentExperience::Rpc::Message* request) {
    LX(DEBUG3, "")
    switch (request->maxmessage()) {
        case MultiAgentExperience::Rpc::MaxMessageType::CONNECTED_TO_MAX:
            LX(DEBUG3, "Received CONNECTED_TO_MAX from the other process");
            m_connectionWaiter.set_value();
            break;
        default:
            LX(WARN, "Incorrect MessageType received. Cannot process.");
    }
}

void GrpcTransportReceiver::handleActivityManagerMessage(
    const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference& reference) {
    LX(DEBUG3, "");

    auto payload = utils::convertPayload(request->referencepayload());
    switch (request->activitymanagermessagetype()) {
        case MultiAgentExperience::Rpc::ActivityManagerMessageType::ACTIVITY_MANAGER_REQUEST: {
            LX(DEBUG3, "Handling ACTIVITY_MANAGER_REQUEST");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(reference,
                                                                     models::activity::ActivityManagerFunctions::REQUEST, payload));
            break;
        }
        case MultiAgentExperience::Rpc::ActivityManagerMessageType::ACTIVITY_MANAGER_STOP: {
            LX(DEBUG3, "Handling ACTIVITY_MANAGER_STOP");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(reference,
                                                                     models::activity::ActivityManagerFunctions::STOP, payload));
            break;
        }
        default:
            break;
    }
}

void GrpcTransportReceiver::handleActivityRequestGetTypeMessage(
    const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference& reference) {
    LX(DEBUG3, "");
    if (request->has_replyto()) {
        auto replyToReference = multiAgentExperience::ipc::messaging::Reference(
                request->replyto().nspace(),
                request->replyto().name(),
                request->replyto().identifier());
        m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(reference,
                                                                 models::activity::ActivityRequestGetType::FUNCTION,
                                                                 multiAgentExperience::ipc::messaging::VoidPayload()),
                          std::make_shared<multiAgentExperience::ipc::transport::TransportResponder<
                                  models::activity::ActivityRequestFunctionReturns,
                                  multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::activity::ActivityType>>>(
                                  replyToReference,
                                  models::activity::ActivityRequestFunctionReturns::GET_TYPE,
                                  m_sender));
    } else{
        /// TODO: Error needs to be handled as replyto is absent
    }
}

void GrpcTransportReceiver::handleActivityRequestGetHandlerMessage(
    const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference& reference) {
    LX(DEBUG3, "");
    if (request->has_replyto()) {
        auto replyToReference = multiAgentExperience::ipc::messaging::Reference(
                request->replyto().nspace(),
                request->replyto().name(),
                request->replyto().identifier());
        m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(reference,
                                                                 models::activity::ActivityRequestGetHandler::FUNCTION,
                                                                 multiAgentExperience::ipc::messaging::VoidPayload()),
                          std::make_shared<multiAgentExperience::ipc::transport::TransportResponder<
                                  models::activity::ActivityRequestFunctionReturns,
                                  multiAgentExperience::ipc::messaging::ReferencePayload>>(replyToReference,
                                                                              models::activity::ActivityRequestFunctionReturns::GET_HANDLER,
                                                                              m_sender));
    } else{
        /// TODO: Error needs to be handled as replyto is absent
    }
}

void GrpcTransportReceiver::handleActivityRequestGetMixabilityTypeMessage(
        const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference& reference) {
    LX(DEBUG3, "");
    if (request->has_replyto()) {
        auto replyToReference = multiAgentExperience::ipc::messaging::Reference(
                request->replyto().nspace(),
                request->replyto().name(),
                request->replyto().identifier());
        m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(reference,
                                                                 models::activity::ActivityRequestGetMixabilityType::FUNCTION,
                                                                 multiAgentExperience::ipc::messaging::VoidPayload()),
                          std::make_shared<multiAgentExperience::ipc::transport::TransportResponder<
                                  models::activity::ActivityRequestFunctionReturns,
                                  multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::activity::MixabilityType>>>(
                                  replyToReference,
                                  models::activity::ActivityRequestFunctionReturns::GET_MIXABILITY_TYPE,
                                  m_sender));
    } else{
        /// TODO: Error needs to be handled as replyto is absent
    }
}

void GrpcTransportReceiver::handleActivityRequestReturnMessage(
    const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference& reference) {
    LX(DEBUG3, "");

    switch (request->activityrequestreturnmessagetype()) {
        case MultiAgentExperience::Rpc::ActivityRequestReturnMessageType::GET_HANDLER: {
            LX(DEBUG3, "Handling GET_HANDLER");
            auto payload = utils::convertPayload(request->referencepayload());
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                    reference,
                    models::activity::ActivityRequestFunctionReturns::GET_HANDLER,
                    payload));
            break;
        }
        case MultiAgentExperience::Rpc::ActivityRequestReturnMessageType::GET_TYPE: {
            LX(DEBUG3, "Handling GET_TYPE");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                    reference,
                    models::activity::ActivityRequestFunctionReturns::GET_TYPE,
                    multiAgentExperience::ipc::messaging::EnumPayload<activity::ActivityType>(
                            utils::getActivityTypeForMessageType(request->activitytype()))));
            break;
        }
        case MultiAgentExperience::Rpc::ActivityRequestReturnMessageType::GET_MIXABILITY_TYPE: {
            LX(DEBUG3, "Handling GET_MIXABILITY_TYPE");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                    reference,
                    models::activity::ActivityRequestFunctionReturns::GET_MIXABILITY_TYPE,
                    multiAgentExperience::ipc::messaging::EnumPayload<activity::MixabilityType>(
                            utils::getMixabilityTypeForMessageType(request->mixabilitytype()))));
            break;
        }
        default:
            break;
    }
}

void GrpcTransportReceiver::handleActivityHandlerMessage(
    const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference& reference) {
    LX(DEBUG3, "");

    switch (request->activityhandlermessagetype()) {
        case MultiAgentExperience::Rpc::ActivityHandlerMessageType::ON_DENIED: {
            LX(DEBUG3, "Handling ON_DENIED");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                    reference,
                    models::activity::ActivityHandlerFunctions::ON_DENIED,
                    multiAgentExperience::ipc::messaging::VoidPayload())
            );
            break;
        }
        case MultiAgentExperience::Rpc::ActivityHandlerMessageType::ON_STOP: {
            LX(DEBUG3, "Handling ON_STOP");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                    reference,
                    models::activity::ActivityHandlerFunctions::ON_STOP,
                    multiAgentExperience::ipc::messaging::VoidPayload())
            );
            break;
        }
        case MultiAgentExperience::Rpc::ActivityHandlerMessageType::ON_GRANTED: {
            LX(DEBUG3, "Handling ON_GRANTED");
            auto payload = utils::convertPayload(request->referencelistpayload());
                m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                        reference,
                        models::activity::ActivityHandlerFunctions::ON_GRANTED,
                        payload)
                );
            break;
        }
        case MultiAgentExperience::Rpc::ActivityHandlerMessageType::ON_FOCUS_CHANGED: {
            LX(DEBUG3, "Handling ON_FOCUS_CHANGED");
            if(request->has_activityfocusmixingbehaviortuple()){
                m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                        reference,
                models::activity::ActivityHandlerFunctions::ON_FOCUS_CHANGED,
                multiAgentExperience::ipc::messaging::EnumTuplePayload<multiAgentExperience::activity::ActivityFocus,
                        multiAgentExperience::activity::MixingBehavior>(
                            utils::convertActivityFocus(request->activityfocusmixingbehaviortuple().activityfocus()),
                            utils::convertMixingBehavior(request->activityfocusmixingbehaviortuple().mixingbehavior())
                        )));
            }
            break;
        }
        default:
            break;
    }
}

void GrpcTransportReceiver::handleActivityControllerMessage(multiAgentExperience::ipc::messaging::Reference &reference){
    LX(DEBUG3, "");
    m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
            reference,
            models::activity::ActivityControllerFunctions::STOP,
            multiAgentExperience::ipc::messaging::VoidPayload()));
}

void GrpcTransportReceiver::handleDialogControllerMessage(
    const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference& reference) {
    LX(DEBUG3, "");

    auto voidPayload = multiAgentExperience::ipc::messaging::VoidPayload();

    switch (request->dialogcontrollermessagetype()) {
        case MultiAgentExperience::Rpc::DialogControllerMessageType::DIALOG_CONTROLLER_START_LISTENING: {
            LX(DEBUG3, "Handling DIALOG_CONTROLLER_START_LISTENING");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(reference, models::dialog::DialogControllerFunctions::START_LISTENING, voidPayload));
            break;
        }

        case MultiAgentExperience::Rpc::DialogControllerMessageType::DIALOG_CONTROLLER_START_THINKING: {
            LX(DEBUG3, "Handling DIALOG_CONTROLLER_START_THINKING");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(reference, models::dialog::DialogControllerFunctions::START_THINKING, voidPayload));
            break;
        }

        case MultiAgentExperience::Rpc::DialogControllerMessageType::DIALOG_CONTROLLER_START_SPEAKING: {
            LX(DEBUG3, "Handling DIALOG_CONTROLLER_START_SPEAKING");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(reference, models::dialog::DialogControllerFunctions::START_SPEAKING, voidPayload));
            break;
        }

        case MultiAgentExperience::Rpc::DialogControllerMessageType::DIALOG_CONTROLLER_INVOKE_CONTROL_AND_START_SPEAKING: {
            LX(DEBUG3, "Handling DIALOG_CONTROLLER_INVOKE_CONTROL_AND_START_SPEAKING");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::dialog::DialogControllerFunctions::INVOKE_CONTROL_AND_START_SPEAKING,
                multiAgentExperience::ipc::messaging::EnumPayload<control::ControlType>(
                    utils::getControlTypeForMessageType(request->controltype()))));
            break;
        }

        case MultiAgentExperience::Rpc::DialogControllerMessageType::DIALOG_CONTROLLER_STOP: {
            LX(DEBUG3, "Handling DIALOG_CONTROLLER_STOP");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::dialog::DialogControllerFunctions::STOP, voidPayload));
            break;
        }

        case MultiAgentExperience::Rpc::DialogControllerMessageType::DIALOG_CONTROLLER_STOP_AND_INVOKE_CONTROL: {
            LX(DEBUG3, "Handling DIALOG_CONTROLLER_STOP_AND_INVOKE_CONTROL");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::dialog::DialogControllerFunctions::STOP_AND_INVOKE_CONTROL,
                multiAgentExperience::ipc::messaging::EnumPayload<control::ControlType>(
                    utils::getControlTypeForMessageType(request->controltype()))));
            break;
        }

        default:
            // TODO: Add error handling here
            LX(WARN, "Incorrect message type.");
            break;
    }
}

void GrpcTransportReceiver::handleDialogManagerMessage(
    const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference& reference) {
    LX(DEBUG3, "");

    switch (request->dialogmanagermessagetype()) {

        case MultiAgentExperience::Rpc::DialogManagerMessageType::DIALOG_MANAGER_REQUEST:
            LX(DEBUG3, "Handling DIALOG_MANAGER_REQUEST");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::dialog::DialogManagerFunctions::REQUEST,
                utils::convertPayload(request->referencepayload())));
            break;

        case MultiAgentExperience::Rpc::DialogManagerMessageType::DIALOG_MANAGER_STOP:
            LX(DEBUG3, "Handling DIALOG_MANAGER_STOP");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::dialog::DialogManagerFunctions::STOP,
                utils::convertPayload(request->referencepayload())));
            break;

        case MultiAgentExperience::Rpc::DialogManagerMessageType::DIALOG_MANAGER_SET_ALL_HANDLERS:
            LX(DEBUG3, "Handling DIALOG_MANAGER_SET_ALL_HANDLERS");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::dialog::DialogManagerFunctions::SET_ALL_HANDLERS,
                utils::convertPayload(request->referencelistpayload())));
            break;

        case MultiAgentExperience::Rpc::DialogManagerMessageType::DIALOG_MANAGER_REMOVE_ALL_HANDLERS:
            LX(DEBUG3, "Handling DIALOG_MANAGER_REMOVE_ALL_HANDLERS");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::dialog::DialogManagerFunctions::REMOVE_ALL_HANDLERS,
                multiAgentExperience::ipc::messaging::VoidPayload()));
            break;

        case MultiAgentExperience::Rpc::DialogManagerMessageType::DIALOG_MANAGER_SET_CONTROL_RECEIVER:
            LX(DEBUG3, "Handling DIALOG_MANAGER_SET_CONTROL_RECEIVER");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::dialog::DialogManagerFunctions::SET_CONTROL_RECEIVER,
                utils::convertPayload(request->referencepayload())));
            break;

        case MultiAgentExperience::Rpc::DialogManagerMessageType::DIALOG_MANAGER_REMOVE_CONTROL_RECEIVER:
            LX(DEBUG3, "Handling DIALOG_MANAGER_REMOVE_CONTROL_RECEIVER");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::dialog::DialogManagerFunctions::REMOVE_CONTROL_RECEIVER,
                multiAgentExperience::ipc::messaging::VoidPayload()));
            break;

        case MultiAgentExperience::Rpc::DialogManagerMessageType::DIALOG_MANAGER_SET_LISTENING_HANDLER:
            LX(DEBUG3, "Handling DIALOG_MANAGER_SET_LISTENING_HANDLER");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::dialog::DialogManagerFunctions::SET_LISTENING_HANDLER,
                utils::convertPayload(request->referencepayload())));
            break;

        case MultiAgentExperience::Rpc::DialogManagerMessageType::DIALOG_MANAGER_REMOVE_LISTENING_HANDLER:
            LX(DEBUG3, "Handling DIALOG_MANAGER_REMOVE_LISTENING_HANDLER");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::dialog::DialogManagerFunctions::REMOVE_LISTENING_HANDLER,
                multiAgentExperience::ipc::messaging::VoidPayload()));
            break;

        case MultiAgentExperience::Rpc::DialogManagerMessageType::DIALOG_MANAGER_SET_THINKING_HANDLER:
            LX(DEBUG3, "Handling DIALOG_MANAGER_SET_THINKING_HANDLER");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::dialog::DialogManagerFunctions::SET_THINKING_HANDLER,
                utils::convertPayload(request->referencepayload())));
            break;

        case MultiAgentExperience::Rpc::DialogManagerMessageType::DIALOG_MANAGER_REMOVE_THINKING_HANDLER:
            LX(DEBUG3, "Handling DIALOG_MANAGER_REMOVE_THINKING_HANDLER");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::dialog::DialogManagerFunctions::REMOVE_THINKING_HANDLER,
                multiAgentExperience::ipc::messaging::VoidPayload()));
            break;

        case MultiAgentExperience::Rpc::DialogManagerMessageType::DIALOG_MANAGER_SET_SPEAKING_HANDLER:
            LX(DEBUG3, "Handling DIALOG_MANAGER_SET_SPEAKING_HANDLER");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::dialog::DialogManagerFunctions::SET_SPEAKING_HANDLER,
                utils::convertPayload(request->referencepayload())));
            break;

        case MultiAgentExperience::Rpc::DialogManagerMessageType::DIALOG_MANAGER_REMOVE_SPEAKING_HANDLER:
            LX(DEBUG3, "Handling DIALOG_MANAGER_REMOVE_SPEAKING_HANDLER");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::dialog::DialogManagerFunctions::REMOVE_SPEAKING_HANDLER,
                multiAgentExperience::ipc::messaging::VoidPayload()));
            break;

        default:
            // TODO: Add error handling here
            LX(WARN, "Incorrect message type.");
            break;
    }
}

void GrpcTransportReceiver::handleDialogRequestMessage(
    const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference& reference) {
    LX(DEBUG3, "");

    switch (request->dialogrequestmessagetype()) {

        case MultiAgentExperience::Rpc::DialogRequestMessageType::DIALOG_REQUEST_ON_DENIED:
            LX(DEBUG3, "Handling DIALOG_REQUEST_ON_DENIED");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::dialog::DialogRequestFunctions::ON_DENIED,
                multiAgentExperience::ipc::messaging::StringPayload(request->stringpayload().value())));
            break;

        case MultiAgentExperience::Rpc::DialogRequestMessageType::DIALOG_REQUEST_ON_DIALOG_STARTED:
            LX(DEBUG3, "Handling DIALOG_REQUEST_ON_DIALOG_STARTED");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::dialog::DialogRequestFunctions::ON_DIALOG_STARTED,
                utils::convertPayload(request->referencepayload())));
            break;

        case MultiAgentExperience::Rpc::DialogRequestMessageType::DIALOG_REQUEST_ON_ERROR:
            LX(DEBUG3, "Handling DIALOG_REQUEST_ON_ERROR");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::dialog::DialogRequestFunctions::ON_ERROR,
                multiAgentExperience::ipc::messaging::StringPayload(request->stringpayload().value())));
            break;

        case MultiAgentExperience::Rpc::DialogRequestMessageType::DIALOG_REQUEST_ON_DIALOG_STOPPED:
            LX(DEBUG3, "Handling DIALOG_REQUEST_ON_DIALOG_STOPPED");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::dialog::DialogRequestFunctions::ON_DIALOG_STOPPED,
                multiAgentExperience::ipc::messaging::VoidPayload()));
            break;

        default:
            // TODO: Add error handling here
            LX(WARN, "Incorrect message type.");
            break;
    }
}

void GrpcTransportReceiver::handleDialogRequestGetDialogBargeInPriorityMessage(
    const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference& reference) {
    LX(DEBUG3, "");

    // MAX library expects a response when it invokes getDialogBargeInPriority(), so we check for a replyTo argument.
    if (request->has_dialogrequestgetdialogbargeinprioritymessagetype() && request->has_replyto()) {

        auto replyToReference = multiAgentExperience::ipc::messaging::Reference(
            request->replyto().nspace(), request->replyto().name(), request->replyto().identifier());

        /**
         * Create a TransportResponder object which will be used by the DialogRequestMessageHandler to send back the
         * DialogBargeInPriority value as a separate gRPC request.
         *
         * The TransportResponder is created with two template parameters:
         * 1. The ReturnEnum is specified as the DialogRequestFunctionReturns
         * 2. The Payload is specified as the EnumPayload of DialogBargeInPriority type
         */
        auto transportResponder = std::make_shared<multiAgentExperience::ipc::transport::TransportResponder<
            models::dialog::DialogRequestFunctionReturns, multiAgentExperience::ipc::messaging::EnumPayload<dialog::DialogBargeInPriority>>>(
                replyToReference,
                models::dialog::DialogRequestFunctionReturns::GET_DIALOG_BARGE_IN_PRIORITY,
                m_sender);

        m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
            reference,
            models::dialog::DialogRequestFunctionGetDialogBargeInPriority::FUNCTION,
            multiAgentExperience::ipc::messaging::VoidPayload()),
            transportResponder);

    } else {
        // TODO: Add error handling here
        LX(WARN, "Request message is of incorrect type, or replyTo argument is not a Reference.");
    }
}

void GrpcTransportReceiver::handleDialogRequestReturnMessage(
    const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference& reference) {
    LX(DEBUG3, "");

     switch (request->dialogrequestreturnmessagetype()) {

         case MultiAgentExperience::Rpc::DialogRequestReturnMessageType::GET_DIALOG_BARGE_IN_PRIORITY:
             LX(DEBUG3, "Handling GET_DIALOG_BARGE_IN_PRIORITY");
             m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                 reference,
                 models::dialog::DialogRequestFunctionReturns::GET_DIALOG_BARGE_IN_PRIORITY,
                 multiAgentExperience::ipc::messaging::EnumPayload<dialog::DialogBargeInPriority>(
                     utils::getDialogBargePriorityForMessageType(request->dialogbargeinpriority()))));
             break;

         default:
             // TODO: Add error handling here
             LX(WARN, "Incorrect message type.");
             break;
     }
}

void GrpcTransportReceiver::handleListeningHandlerMessage(
    const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference& reference) {
    LX(DEBUG3, "");

    switch (request->listeninghandlermessagetype()) {

        case MultiAgentExperience::Rpc::ListeningHandlerMessageType::ON_START_LISTENING:
            LX(DEBUG3, "Handling ON_START_LISTENING");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::dialog::ListeningHandlerFunctions::ON_START_LISTENING,
                utils::convertPayload(request->referencepayload())));
            break;

        case MultiAgentExperience::Rpc::ListeningHandlerMessageType::ON_STOP_LISTENING:
            LX(DEBUG3, "Handling ON_STOP_LISTENING");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::dialog::ListeningHandlerFunctions::ON_STOP_LISTENING,
                multiAgentExperience::ipc::messaging::VoidPayload()));
            break;

        default:
            // TODO: Add error handling here
            LX(WARN, "Incorrect message type.");
            break;
    }
}

void GrpcTransportReceiver::handleThinkingHandlerMessage(
    const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference& reference) {
    LX(DEBUG3, "");

    switch (request->thinkinghandlermessagetype()) {

        case MultiAgentExperience::Rpc::ThinkingHandlerMessageType::ON_START_THINKING:
            LX(DEBUG3, "Handling ON_START_THINKING");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::dialog::ThinkingHandlerFunctions::ON_START_THINKING,
                utils::convertPayload(request->referencepayload())));
            break;

        case MultiAgentExperience::Rpc::ThinkingHandlerMessageType::ON_STOP_THINKING:
            LX(DEBUG3, "Handling ON_STOP_THINKING");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::dialog::ThinkingHandlerFunctions::ON_STOP_THINKING,
                multiAgentExperience::ipc::messaging::VoidPayload()));
            break;

        default:
            // TODO: Add error handling here
            LX(WARN, "Incorrect message type.");
            break;
    }
}

void GrpcTransportReceiver::handleSpeakingHandlerMessage(
    const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference& reference) {
    LX(DEBUG3, "");

    switch (request->speakinghandlermessagetype()) {

        case MultiAgentExperience::Rpc::SpeakingHandlerMessageType::ON_START_SPEAKING:
            LX(DEBUG3, "Handling ON_START_SPEAKING");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::dialog::SpeakingHandlerFunctions::ON_START_SPEAKING,
                utils::convertPayload(request->referencelistpayload())));
            break;

        case MultiAgentExperience::Rpc::SpeakingHandlerMessageType::ON_STOP_SPEAKING:
            LX(DEBUG3, "Handling ON_STOP_SPEAKING");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::dialog::SpeakingHandlerFunctions::ON_STOP_SPEAKING,
                multiAgentExperience::ipc::messaging::VoidPayload()));
            break;

        default:
            // TODO: Add error handling here
            LX(WARN, "Incorrect message type.");
            break;
    }
}

void GrpcTransportReceiver::handleStartListeningCallbackMessage(
    const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference& reference) {
    LX(DEBUG3, "");

    switch (request->startlisteningcallbackmessagetype()) {

        case MultiAgentExperience::Rpc::StartListeningCallbackMessageType::START_LISTENING:
            LX(DEBUG3, "Handling START_LISTENING");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::dialog::StartListeningCallbackFunctions::START_LISTENING,
                multiAgentExperience::ipc::messaging::VoidPayload()));
            break;

        default:
            // TODO: Add error handling here
            LX(WARN, "Incorrect message type.");
            break;
    }
}

void GrpcTransportReceiver::handleExperienceControllerMessage(
    const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference) {
    LX(DEBUG3, "");

    switch (request->experiencecontrollermessagetype()) {

        case MultiAgentExperience::Rpc::ExperienceControllerMessageType::START_EXPERIENCE:
            LX(DEBUG3, "Handling START_EXPERIENCE");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::experience::ExperienceControllerFunctions::START_EXPERIENCE,
                multiAgentExperience::ipc::messaging::StringPayload(request->stringpayload().value())));
            break;

        case MultiAgentExperience::Rpc::ExperienceControllerMessageType::END_EXPERIENCE:
            LX(DEBUG3, "Handling END_EXPERIENCE");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::experience::ExperienceControllerFunctions::END_EXPERIENCE,
                multiAgentExperience::ipc::messaging::VoidPayload()));
            break;

        case MultiAgentExperience::Rpc::ExperienceControllerMessageType::INVALIDATE:
            LX(DEBUG3, "Handling INVALIDATE");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::experience::ExperienceControllerFunctions::INVALIDATE,
                multiAgentExperience::ipc::messaging::VoidPayload()));
            break;

        default:
            // TODO: Add error handling here
            LX(WARN, "Incorrect message type.");
    }
}

void GrpcTransportReceiver::handleStaticExperienceManagerMessage(
    const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference) {
    LX(DEBUG3, "");

    switch (request->staticexperiencemanagermessagetype()) {

        case MultiAgentExperience::Rpc::StaticExperienceManagerMessageType::ADD_STATIC_EXPERIENCE:
            LX(DEBUG3, "Handling ADD_STATIC_EXPERIENCE");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::experience::StaticExperienceManagerFunctions::ADD_STATIC_EXPERIENCE,
                multiAgentExperience::ipc::messaging::StringIntTuplePayload(
                    request->stringinttuplepayload().stringvalue(),
                    request->stringinttuplepayload().intvalue())));
            break;

        case MultiAgentExperience::Rpc::StaticExperienceManagerMessageType::REMOVE_STATIC_EXPERIENCE:
            LX(DEBUG3, "Handling REMOVE_STATIC_EXPERIENCE");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::experience::StaticExperienceManagerFunctions::REMOVE_STATIC_EXPERIENCE,
                multiAgentExperience::ipc::messaging::StringPayload(request->stringpayload().value())));
            break;

        case MultiAgentExperience::Rpc::StaticExperienceManagerMessageType::REMOVE_ALL_STATIC_EXPERIENCES:
            LX(DEBUG3, "Handling REMOVE_ALL_STATIC_EXPERIENCES");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::experience::StaticExperienceManagerFunctions::REMOVE_ALL_STATIC_EXPERIENCES,
                multiAgentExperience::ipc::messaging::VoidPayload()));
                break;
        default:
            // TODO: Add error handling here
            LX(WARN, "Incorrect message type.");
    }
}

void GrpcTransportReceiver::handleControlMessage(
    const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference) {
    LX(DEBUG3, "");

    switch (request->controlmessagetype()) {

        case MultiAgentExperience::Rpc::ControlMessageType::CONTROL_TASK:
            LX(DEBUG3, "Handling CONTROL_TASK");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::control::ControlFunctions::CONTROL_TASK,
                multiAgentExperience::ipc::messaging::VoidPayload()));
            break;
        default:
            // TODO: Add error handling here
            LX(WARN, "Incorrect message type.");
    }
}

void GrpcTransportReceiver::handleControlRegistryMessage(
    const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference) {
    LX(DEBUG3, "");

    switch (request->controlregistrymessagetype()) {

        case MultiAgentExperience::Rpc::ControlRegistryMessageType::UPDATE:
            LX(DEBUG3, "Handling UPDATE");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::control::ControlRegistryFunctions::UPDATE,
                utils::convertPayload(request->controlregistrypayload())));
            break;

        default:
            // TODO: Add error handling here
            LX(WARN, "Incorrect message type.");
            break;
    }
}

void GrpcTransportReceiver::handleControlReceiverMessage(
    const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference) {
    LX(DEBUG3, "");

    switch (request->controlreceivermessagetype()) {

        case MultiAgentExperience::Rpc::ControlReceiverMessageType::ON_CONTROLS_RECEIVED:
            LX(DEBUG3, "Handling ON_CONTROLS_RECEIVED");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::dialog::ControlReceiverFunctions::ON_CONTROLS_RECEIVED,
                utils::convertPayload(request->controlreceiverpayload())));
            break;

        default:
            // TODO: Add error handling here
            LX(WARN, "Incorrect message type.");
            break;
    }
}

void GrpcTransportReceiver::handleOnCompletionCallbackMessage(
    const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference& reference) {
    LX(DEBUG3, "");

    switch (request->oncompletioncallbackmessagetype()) {
        case MultiAgentExperience::Rpc::OnCompletionCallbackMessageType::COMPLETED:
            LX(DEBUG3, "Handling COMPLETED");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::common::OnCompletionCallbackFunctions::COMPLETED,
                multiAgentExperience::ipc::messaging::VoidPayload()));
            break;

        default:
            // TODO: Add error handling here
            LX(WARN, "Incorrect message type.");
    }
}

void GrpcTransportReceiver::handleAgentRegistrationMessage(
    const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference& reference) {
    LX(DEBUG3, "");

    switch (request->agentregistrationmessagetype()) {
        case MultiAgentExperience::Rpc::AgentRegistrationMessageType::AGENT_REGISTRATION_ON_READY:
            LX(DEBUG3, "Handling AGENT_REGISTRATION_ON_READY");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::agent::AgentRegistrationFunctions::ON_READY,
                utils::convertPayload(request->referencelistpayload())));
            break;

        default:
            // TODO: Add error handling here
            LX(WARN, "Incorrect message type.");
    }
}

void GrpcTransportReceiver::handleAgentRegistrationGetIdMessage(
    const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference) {
    LX(DEBUG3, "");

    // MAX library expects a response when it invokes getId(), so we check for a replyTo argument.
    if (request->has_agentregistrationgetidmessagetype() && request->has_replyto()) {

        auto replyToReference = multiAgentExperience::ipc::messaging::Reference(
            request->replyto().nspace(), request->replyto().name(), request->replyto().identifier());

        /**
         * Create a TransportResponder object which will be used by the AgentRegistrationMessageHandler to send back the
         * Id value as a separate gRPC request.
         *
         * The TransportResponder is created with two template parameters:
         * 1. The ReturnEnum is specified as the AgentRegistrationFunctionReturns
         * 2. The Payload is specified as StringPayload because Id is a string
         */
        auto transportResponder = std::make_shared<multiAgentExperience::ipc::transport::TransportResponder<
            models::agent::AgentRegistrationFunctionReturns, multiAgentExperience::ipc::messaging::StringPayload>>(
                replyToReference,
                models::agent::AgentRegistrationFunctionReturns::GET_ID,
                m_sender);

        m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
            reference,
            models::agent::AgentRegistrationFunctionGetId::FUNCTION,
            multiAgentExperience::ipc::messaging::VoidPayload()),
            transportResponder);

    } else {
        // TODO: Add error handling here
        LX(WARN, "Request message is of incorrect type, or replyTo argument is not a Reference.");
    }
}

void GrpcTransportReceiver::handleAgentRegistrationGetNameMessage(
    const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference) {
    LX(DEBUG3, "");

    // MAX library expects a response when it invokes getName(), so we check for a replyTo argument.
    if (request->has_agentregistrationgetnamemessagetype() && request->has_replyto()) {

        auto replyToReference = multiAgentExperience::ipc::messaging::Reference(
            request->replyto().nspace(), request->replyto().name(), request->replyto().identifier());

        /**
         * Create a TransportResponder object which will be used by the AgentRegistrationMessageHandler to send back the
         * Id value as a separate gRPC request.
         *
         * The TransportResponder is created with two template parameters:
         * 1. The ReturnEnum is specified as the AgentRegistrationFunctionReturns
         * 2. The Payload is specified as StringPayload because Name is a string
         */
        auto transportResponder = std::make_shared<multiAgentExperience::ipc::transport::TransportResponder<
            models::agent::AgentRegistrationFunctionReturns, multiAgentExperience::ipc::messaging::StringPayload>>(
            replyToReference,
            models::agent::AgentRegistrationFunctionReturns::GET_NAME,
            m_sender);

        m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
            reference,
            models::agent::AgentRegistrationFunctionGetName::FUNCTION,
            multiAgentExperience::ipc::messaging::VoidPayload()),
            transportResponder);

    } else {
        // TODO: Add error handling here
        LX(WARN, "Request message is of incorrect type, or replyTo argument is not a Reference.");
    }
}

void GrpcTransportReceiver::handleAgentRegistrationReturnMessage(
    const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference) {
    LX(DEBUG3, "");

    switch (request->agentregistrationreturnmessagetype()) {

        case MultiAgentExperience::Rpc::AgentRegistrationReturnMessageType::GET_ID:
            LX(DEBUG3, "Handling GET_ID");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::agent::AgentRegistrationFunctionReturns::GET_ID,
                multiAgentExperience::ipc::messaging::StringPayload(request->stringpayload().value())));
            break;

        case MultiAgentExperience::Rpc::AgentRegistrationReturnMessageType::GET_NAME:
            LX(DEBUG3, "Handling GET_NAME");
            m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
                reference,
                models::agent::AgentRegistrationFunctionReturns::GET_NAME,
                multiAgentExperience::ipc::messaging::StringPayload(request->stringpayload().value())));
            break;

        default:
            // TODO: Add error handling here
            LX(WARN, "Incorrect message type.");
            break;
    }
}

void GrpcTransportReceiver::handleDeleteMessageHandlerMessage(
        const ::MultiAgentExperience::Rpc::Message* request, multiAgentExperience::ipc::messaging::Reference &reference) {
    LX(DEBUG3, "");

    m_handler->handle(multiAgentExperience::ipc::messaging::createMessage(
            reference,
            utils::convertPayload(request->maxapitype()),
            multiAgentExperience::ipc::messaging::VoidPayload()));
}

} // namespace adaptor
} // namespace grpc
} // namespace ipc
} // namespace multiAgentExperience