/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_IPC_GRPC_UTILS_MESSAGEUTILS_H
#define MULTIAGENTEXPERIENCE_IPC_GRPC_UTILS_MESSAGEUTILS_H

#include <MultiAgentExperience/Activity/ActivityFocus.h>
#include <MultiAgentExperience/Activity/MixingBehavior.h>
#include <MultiAgentExperience/IPC/Messaging/Control/ControlRegistryPayload.h>
#include <MultiAgentExperience/IPC/Messaging/Dialog/ControlReceiverPayload.h>
#include <MultiAgentExperience/IPC/Messaging/EnumPayload.h>
#include <MultiAgentExperience/IPC/Messaging/EnumTuplePayload.h>
#include <MultiAgentExperience/IPC/Messaging/IntPayload.h>
#include <MultiAgentExperience/IPC/Messaging/ListPayload.h>
#include <MultiAgentExperience/IPC/Messaging/Reference.h>
#include <MultiAgentExperience/IPC/Messaging/ReferencePayload.h>
#include <MultiAgentExperience/IPC/Messaging/ReferenceListPayload.h>
#include <MultiAgentExperience/IPC/Messaging/StringPayload.h>
#include <MultiAgentExperience/IPC/Messaging/StringIntTuplePayload.h>
#include <MultiAgentExperience/IPC/Messaging/StringListPayload.h>
#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include <maxrpc.grpc.pb.h>

#include "FunctionToMessageType.h"

namespace multiAgentExperience {
namespace ipc {
namespace grpc {
namespace utils {

static const std::string MODULE_TAG("MessageUtils");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

static MultiAgentExperience::Rpc::Reference createReference(const multiAgentExperience::ipc::messaging::Reference& reference) {
    MultiAgentExperience::Rpc::Reference transportReference;

    transportReference.set_name(reference.getTypeName().m_name);
    transportReference.set_nspace(reference.getTypeName().m_nspace);
    transportReference.set_identifier(reference.getInstance().m_identifier);

    return transportReference;
}

static MultiAgentExperience::Rpc::Message createMessage(const multiAgentExperience::ipc::messaging::Reference& reference) {
    MultiAgentExperience::Rpc::Message transportMessage;
    transportMessage.mutable_reference()->CopyFrom(createReference(reference));
    return transportMessage;
}

static MultiAgentExperience::Rpc::ReferencePayload createReferencePayload(
    const multiAgentExperience::ipc::messaging::ReferencePayload& referencePayload) {

    // Create a protobuf message of ReferencePayload type
    auto transportReferencePayload = MultiAgentExperience::Rpc::ReferencePayload();

    // Create a Reference protobuf message for the m_reference stored in the referencePayload
    auto transportReference = createReference(referencePayload.m_reference);

    // Set the reference parameter of the ReferencePayload protobuf message
    transportReferencePayload.mutable_reference()->CopyFrom(transportReference);

    return transportReferencePayload;
}

static MultiAgentExperience::Rpc::ReferenceListPayload createReferenceListPayload(
    const multiAgentExperience::ipc::messaging::ReferenceListPayload& referenceListPayload) {

    // Create a protobuf message of ReferenceListPayload type
    auto transportReferenceListPayload = MultiAgentExperience::Rpc::ReferenceListPayload();

    // Create a Reference message for each entry in m_references, and add to the list
    for (const auto& reference: referenceListPayload.m_references) {
        /*
         * The method - add_referenceList() adds a new element to the end of the list and returns a pointer to it.
         * The returned Reference is mutable and will have none of its fields set.
         */
        MultiAgentExperience::Rpc::Reference* transportReference = transportReferenceListPayload.add_referencelist();

        // Set the fields for the Reference message
        transportReference->set_name(reference.getTypeName().m_name);
        transportReference->set_nspace(reference.getTypeName().m_nspace);
        transportReference->set_identifier(reference.getInstance().m_identifier);
    }

    return transportReferenceListPayload;
}

/**
 * Creates a gRPC Message which has VoidPayloads for the replyToReference parameter and the payload parameter.
 * Multiple APIs use this kind of Message.
 *
 * @param reference The Reference object for which the gRPC Message is created
 * @return The gRPC Message
 */
static MultiAgentExperience::Rpc::Message createMessageForVoidPayload(const multiAgentExperience::ipc::messaging::Reference& reference) {

    auto transportMessage = createMessage(reference);
    auto transportVoidPayload = MultiAgentExperience::Rpc::VoidPayload();

    // Set the ReplyToReference parameter to VoidPayload
    transportMessage.mutable_replytoempty()->CopyFrom(transportVoidPayload);

    // Set the Payload parameter to VoidPayload
    transportMessage.mutable_voidpayload()->CopyFrom(transportVoidPayload);

    return transportMessage;
}

/**
 * Creates a gRPC Message which has a VoidPayload for the replyToReference parameter and a ReferencePayload for the payload parameter.
 *
 * @param reference The Reference object for which the gRPC Message is created. This is the top-level reference
 * @param referencePayload The ReferencePayload object
 * @return The gRPC Message
 */
static MultiAgentExperience::Rpc::Message createMessageForReferencePayload(
    const multiAgentExperience::ipc::messaging::Reference& reference,
    const multiAgentExperience::ipc::messaging::ReferencePayload& referencePayload) {

    auto transportMessage = createMessage(reference);

    // Set the ReplyToReference parameter to VoidPayload
    transportMessage.mutable_replytoempty()->CopyFrom(MultiAgentExperience::Rpc::VoidPayload());

    // Set the Payload parameter to ReferencePayload
    transportMessage.mutable_referencepayload()->CopyFrom(createReferencePayload(referencePayload));

    return transportMessage;
}

/**
 * Creates a gRPC Message which has a VoidPayload for the replyToReference parameter and a ReferenceListPayload for the payload parameter.
 *
 * @param reference The Reference object for which the gRPC Message is created. This is the top-level reference
 * @param referenceListPayload The ReferenceListPayload object which needs to be converted into its corresponding Protobuf message
 * @return The gRPC Message
 */
static MultiAgentExperience::Rpc::Message createMessageForReferenceListPayload(
    const multiAgentExperience::ipc::messaging::Reference& reference,
    const multiAgentExperience::ipc::messaging::ReferenceListPayload& referenceListPayload) {

    auto transportMessage = createMessage(reference);

    // Set the ReplyToReference parameter to VoidPayload
    transportMessage.mutable_replytoempty()->CopyFrom(MultiAgentExperience::Rpc::VoidPayload());

    // Set the Payload parameter to ReferenceListPayload
    transportMessage.mutable_referencelistpayload()->CopyFrom(createReferenceListPayload(referenceListPayload));

    return transportMessage;
}

/**
 * Creates a gRPC Message which has a VoidPayload for the replyToReference parameter and a StringPayload for the payload parameter.
 *
 * @param reference The Reference object for which the gRPC Message is created
 * @param stringPayload The StringPayload object
 * @return The gRPC Message
 */
static MultiAgentExperience::Rpc::Message createMessageForStringPayload(
    const multiAgentExperience::ipc::messaging::Reference& reference,
    const multiAgentExperience::ipc::messaging::StringPayload& stringPayload) {

    auto transportMessage = createMessage(reference);

    // Set the ReplyToReference parameter to VoidPayload
    transportMessage.mutable_replytoempty()->CopyFrom(MultiAgentExperience::Rpc::VoidPayload());

    // Create a protobuf message of StringPayload type, with the string value retrieved from stringPayload argument
    auto transportStringPayload = MultiAgentExperience::Rpc::StringPayload();
    transportStringPayload.set_value(stringPayload.m_value);

    // Set the Payload parameter to StringPayload
    transportMessage.mutable_stringpayload()->CopyFrom(transportStringPayload);

    return transportMessage;
}

/**
 * Creates a gRPC payload of type ActivityFocusMixingBehaviorTuple and inserts it into a transport message
 *
 * @param focus The Activity focus we want to set
 * @param behavior The Mixing behavior we want to set
*/
static void createPayloadForActivityFocusChange(
        multiAgentExperience::activity::ActivityFocus focus,
        multiAgentExperience::activity::MixingBehavior behavior,
        MultiAgentExperience::Rpc::Message& transportMessage){
    auto transportPayload = MultiAgentExperience::Rpc::ActivityFocusMixingBehaviorTuple();
    transportPayload.set_activityfocus(convertActivityFocus(focus));
    transportPayload.set_mixingbehavior(convertMixingBehavior(behavior));
    transportMessage.mutable_activityfocusmixingbehaviortuple()->CopyFrom(transportPayload);
}

/**
 * Creates a gRPC Message which has a VoidPayload for the replyToReference parameter and a ControlType for the payload parameter.
 *
 * @param reference The Reference object for which the gRPC Message is created
 * @param payload The EnumPayload<ControlType> object
 * @return The gRPC Message
 */
static MultiAgentExperience::Rpc::Message createMessageForControlTypePayload(
    const multiAgentExperience::ipc::messaging::Reference& reference,
    const multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::control::ControlType>& payload) {

    auto transportMessage = createMessage(reference);

    // Set the ReplyToReference parameter to VoidPayload
    transportMessage.mutable_replytoempty()->CopyFrom(MultiAgentExperience::Rpc::VoidPayload());

    // Set the Payload parameter to ControlType
    transportMessage.set_controltype(utils::getMessageTypeForControlType(payload.m_value));

    return transportMessage;
}

/**
 * Creates a gRPC Message which has VoidPayloads for the replyToReference parameter and the ControlRegistryPayload parameter.
 *
 * @param reference The Reference object for which the gRPC Message is created
 * @return The gRPC Message
 */
static MultiAgentExperience::Rpc::Message createMessageForControlRegistryPayload(
    const multiAgentExperience::ipc::messaging::Reference& reference,
    const multiAgentExperience::ipc::messaging::control::ControlRegistryPayload& payload) {

    auto transportMessage = createMessage(reference);

    // Set the ReplyToReference parameter to VoidPayload
    transportMessage.mutable_replytoempty()->CopyFrom(MultiAgentExperience::Rpc::VoidPayload());

    auto referenceControlTypesList = payload.m_referenceControlTypesList;

    MultiAgentExperience::Rpc::ControlRegistryPayload rpcControlRegistryPayload;

    for (const auto& referenceControlTypeTuple : referenceControlTypesList) {
        auto curReference = std::get<0>(referenceControlTypeTuple);
        auto curRpcReference = MultiAgentExperience::Rpc::Reference();
        auto curTypeName = curReference.getTypeName();
        curRpcReference.set_name(curTypeName.m_name);
        curRpcReference.set_nspace(curTypeName.m_nspace);
        curRpcReference.set_identifier(curReference.getInstance().m_identifier);
        MultiAgentExperience::Rpc::ReferenceControlTypeTuple curReferenceControlTypeTuple;
        curReferenceControlTypeTuple.mutable_reference()->CopyFrom(curRpcReference);

        auto curControlType = std::get<1>(referenceControlTypeTuple);
        switch (curControlType) {
            case::multiAgentExperience::control::ControlType::STOP:
            curReferenceControlTypeTuple.set_controltype(MultiAgentExperience::Rpc::ControlType::STOP);
            break;
        }

        rpcControlRegistryPayload.add_referencecontroltypetuple()->CopyFrom(curReferenceControlTypeTuple);
    }

    transportMessage.mutable_controlregistrypayload()->CopyFrom(rpcControlRegistryPayload);

    return transportMessage;
}

/**
 * Creates a gRPC Message which has VoidPayloads for the replyToReference parameter and the ControlReceiverPayload parameter.
 *
 * @param reference The Reference object for which the gRPC Message is created
 * @return The gRPC Message
 */
static MultiAgentExperience::Rpc::Message createMessageForControlReceiverPayload(
    const multiAgentExperience::ipc::messaging::Reference& reference,
    const multiAgentExperience::ipc::messaging::dialog::ControlReceiverPayload& payload) {

    auto transportMessage = createMessage(reference);

    // Set the ReplyToReference parameter to VoidPayload
    transportMessage.mutable_replytoempty()->CopyFrom(MultiAgentExperience::Rpc::VoidPayload());

    MultiAgentExperience::Rpc::ControlReceiverPayload rpcControlReceiverPayload;

    auto startListeningCallbackReference = payload.m_reference;
    auto rpcstartListeningCallbackReference = MultiAgentExperience::Rpc::Reference();
    auto curTypeName = startListeningCallbackReference.getTypeName();
    rpcstartListeningCallbackReference.set_name(curTypeName.m_name);
    rpcstartListeningCallbackReference.set_nspace(curTypeName.m_nspace);
    rpcstartListeningCallbackReference.set_identifier(startListeningCallbackReference.getInstance().m_identifier);
    rpcControlReceiverPayload.mutable_reference()->CopyFrom(rpcstartListeningCallbackReference);

    auto controlTypes = payload.m_controlTypes;

    for (const auto &curControlType: controlTypes) {
        switch (curControlType) {
            case ::multiAgentExperience::control::ControlType::STOP:
                rpcControlReceiverPayload.add_controltype(MultiAgentExperience::Rpc::ControlType::STOP);
            break;
        }
    }

    transportMessage.mutable_controlreceiverpayload()->CopyFrom(rpcControlReceiverPayload);

    return transportMessage;
}

/**
 * Creates a gRPC Message which has a VoidPayload for the replyToReference parameter and a StringIntTuplePayload
 * for the payload parameter.
 *
 * @param reference The Reference object for which the gRPC Message is created
 * @param stringPayload The StringIntTuplePayload object
 * @return The gRPC Message
 */
static MultiAgentExperience::Rpc::Message createMessageForStringIntTuplePayload(
    const multiAgentExperience::ipc::messaging::Reference& reference,
    const multiAgentExperience::ipc::messaging::StringIntTuplePayload& payload) {

    auto transportMessage = createMessage(reference);

    // Set the ReplyToReference parameter to VoidPayload
    transportMessage.mutable_replytoempty()->CopyFrom(MultiAgentExperience::Rpc::VoidPayload());

    // Create a protobuf message of StringIntTuplePayload type, with the string value retrieved from payload argument
    auto transportPayload = MultiAgentExperience::Rpc::StringIntTuplePayload();
    transportPayload.set_stringvalue(payload.m_value1);
    transportPayload.set_intvalue(payload.m_value2);

    // Set the Payload parameter to StringIntTuplePayload
    transportMessage.mutable_stringinttuplepayload()->CopyFrom(transportPayload);

    return transportMessage;
}

/**
 * Creates a gRPC Message which has a Reference for the replyToReference parameter and a VoidPayload for the Payload parameter.
 *
 * @param reference The Reference object for which the gRPC Message is created. This is the top-level reference
 * @param replyToReference The Reference object for the replyTo parameter
 * @return The gRPC Message
 */
static MultiAgentExperience::Rpc::Message createMessageForVoidPayloadWithReplyTo(
    const multiAgentExperience::ipc::messaging::Reference& reference,
    const multiAgentExperience::ipc::messaging::Reference& replyToReference) {

    auto transportMessage = createMessage(reference);

    // Set the ReplyToReference parameter to the Reference received in replyToReference
    transportMessage.mutable_replyto()->CopyFrom(utils::createReference(replyToReference));

    // Set the Payload parameter to VoidPayload
    transportMessage.mutable_voidpayload()->CopyFrom(MultiAgentExperience::Rpc::VoidPayload());

    return transportMessage;
}

/**
 * Creates a multiAgentExperience IPC Message which has a ReferencePayload for the payload parameter.
 *
 * @param referencePayload The gRPC ReferencePayload object
 * @return The multiAgentExperience IPC Message
 */
static multiAgentExperience::ipc::messaging::ReferencePayload convertPayload(
        const MultiAgentExperience::Rpc::ReferencePayload& referencePayload) {
    auto reference =
            multiAgentExperience::ipc::messaging::Reference(
                    referencePayload.reference().nspace(),
                    referencePayload.reference().name(),
                    referencePayload.reference().identifier());
    return {reference};
}


/**
 * Creates a multiAgentExperience IPC Message which has a ReferenceListPayload for the payload parameter.
 *
 * @param referenceListPayload The gRPC ReferenceListPayload object
 * @return The multiAgentExperience IPC Message
 */
static multiAgentExperience::ipc::messaging::ReferenceListPayload convertPayload(
        const MultiAgentExperience::Rpc::ReferenceListPayload& referenceListPayload) {
    std::vector<multiAgentExperience::ipc::messaging::Reference> references;
    for(const auto& rpcReference: referenceListPayload.referencelist()){
        auto reference =
                multiAgentExperience::ipc::messaging::Reference(
                        rpcReference.nspace(),
                        rpcReference.name(),
                        rpcReference.identifier());
        references.push_back(reference);
    }
    return {references};
}


static messaging::control::ControlRegistryPayload convertPayload(
        const MultiAgentExperience::Rpc::ControlRegistryPayload& controlRegistryPayload) {
    std::list<
            std::tuple<
                    multiAgentExperience::ipc::messaging::Reference,
                    multiAgentExperience::control::ControlType>> referenceControlTypesList;

    for (int i = 0; i < controlRegistryPayload.referencecontroltypetuple_size(); i++) {
        auto curMessageReferencecontroltypetuple = controlRegistryPayload.referencecontroltypetuple(i);

        auto curReference = multiAgentExperience::ipc::messaging::Reference(
                curMessageReferencecontroltypetuple.reference().nspace(),
                curMessageReferencecontroltypetuple.reference().name(),
                curMessageReferencecontroltypetuple.reference().identifier());

        auto curControlType = getControlTypeForMessageType(curMessageReferencecontroltypetuple.controltype());

        auto curReferencecontroltypetuple = std::make_tuple(
                curReference,
                curControlType);

        referenceControlTypesList.push_back(curReferencecontroltypetuple);
    }

    return {referenceControlTypesList};
}

static messaging::dialog::ControlReceiverPayload convertPayload(
        const MultiAgentExperience::Rpc::ControlReceiverPayload& controlReceiverPayload) {
    std::set<multiAgentExperience::control::ControlType> controlTypes;

    auto reference =
            multiAgentExperience::ipc::messaging::Reference(
                    controlReceiverPayload.reference().nspace(),
                    controlReceiverPayload.reference().name(),
                    controlReceiverPayload.reference().identifier());

    for (int i = 0; i < controlReceiverPayload.controltype_size(); i++) {
        auto curControlType = getControlTypeForMessageType(controlReceiverPayload.controltype(i));
        controlTypes.insert(curControlType);
    }

    return {reference, controlTypes};
}

static multiAgentExperience::ipc::transport::MaxApiType convertPayload(
        const MultiAgentExperience::Rpc::MaxApiType& rpcMaxApiType) {
    switch (rpcMaxApiType) {
        case MultiAgentExperience::Rpc::MaxApiType::ACTIVITY_CONTROLLER:
            return multiAgentExperience::ipc::transport::MaxApiType::ACTIVITY_CONTROLLER;
        case MultiAgentExperience::Rpc::MaxApiType::ACTIVITY_HANDLER:
            return multiAgentExperience::ipc::transport::MaxApiType::ACTIVITY_HANDLER;
        case MultiAgentExperience::Rpc::MaxApiType::ACTIVITY_MANAGER:
            return multiAgentExperience::ipc::transport::MaxApiType::ACTIVITY_MANAGER;
        case MultiAgentExperience::Rpc::MaxApiType::ACTIVITY_REQUEST:
            return multiAgentExperience::ipc::transport::MaxApiType::ACTIVITY_REQUEST;
        case MultiAgentExperience::Rpc::MaxApiType::AGENT_REGISTRATION:
            return multiAgentExperience::ipc::transport::MaxApiType::AGENT_REGISTRATION;
        case MultiAgentExperience::Rpc::MaxApiType::ON_COMPLETION_CALLBACK:
            return multiAgentExperience::ipc::transport::MaxApiType::ON_COMPLETION_CALLBACK;
        case MultiAgentExperience::Rpc::MaxApiType::CONTROL:
            return multiAgentExperience::ipc::transport::MaxApiType::CONTROL;
        case MultiAgentExperience::Rpc::MaxApiType::CONTROL_REGISTRY:
            return multiAgentExperience::ipc::transport::MaxApiType::CONTROL_REGISTRY;
        case MultiAgentExperience::Rpc::MaxApiType::EXPERIENCE_CONTROLLER:
            return multiAgentExperience::ipc::transport::MaxApiType::EXPERIENCE_CONTROLLER;
        case MultiAgentExperience::Rpc::MaxApiType::STATIC_EXPERIENCE_MANAGER:
            return multiAgentExperience::ipc::transport::MaxApiType::STATIC_EXPERIENCE_MANAGER;
        default:
            LX(ERROR, "Incorrect MaxApiType provided.");
            return multiAgentExperience::ipc::transport::MaxApiType();
    }
}

} // namespace utils
} // namespace grpc
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_GRPC_UTILS_MESSAGEUTILS_H
