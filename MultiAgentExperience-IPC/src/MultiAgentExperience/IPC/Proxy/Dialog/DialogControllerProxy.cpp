/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#include "MultiAgentExperience/IPC/Proxy/Dialog/DialogControllerProxy.h"

#include <MultiAgentExperience/IPC/Utils/ConversionUtils.h>
#include <MultiAgentExperience/Utils/Logger/Logger.h>

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace dialog {

static const std::string MODULE_TAG("DialogControllerProxy");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

DialogControllerProxy::DialogControllerProxy(
        multiAgentExperience::ipc::messaging::Reference reference,std::shared_ptr<transport::MessageSender> sender):
        MaxIpcComponentsBaseProxy(std::move(reference), transport::MaxApiType::DIALOG_CONTROLLER, std::move(sender)) {}

void DialogControllerProxy::startListening() {
    LX(DEBUG0, "");

    auto message = multiAgentExperience::ipc::messaging::createMessage(
        m_reference,
        models::dialog::DialogControllerFunctions::START_LISTENING,
        multiAgentExperience::ipc::messaging::VoidPayload());

    m_sender->send(message);
}

void DialogControllerProxy::startThinking() {
    LX(DEBUG0, "");

    auto message = multiAgentExperience::ipc::messaging::createMessage(
        m_reference,
        models::dialog::DialogControllerFunctions::START_THINKING,
        multiAgentExperience::ipc::messaging::VoidPayload());

    m_sender->send(message);
}

void DialogControllerProxy::startSpeaking() {
    LX(DEBUG0, "");

    auto message = multiAgentExperience::ipc::messaging::createMessage(
        m_reference,
        models::dialog::DialogControllerFunctions::START_SPEAKING,
        multiAgentExperience::ipc::messaging::VoidPayload());

    m_sender->send(message);
}

void DialogControllerProxy::invokeControlAndStartSpeaking(const multiAgentExperience::control::ControlType& controlType) {
    LX(DEBUG0, "controlType:" + multiAgentExperience::ipc::utils::toString(controlType));

    auto message = multiAgentExperience::ipc::messaging::createMessage(
        m_reference,
        models::dialog::DialogControllerFunctions::INVOKE_CONTROL_AND_START_SPEAKING,
        multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::control::ControlType>(controlType));

    m_sender->send(message);
}

void DialogControllerProxy::stop() {
    LX(DEBUG0, "");

    auto message = multiAgentExperience::ipc::messaging::createMessage(
        m_reference,
        models::dialog::DialogControllerFunctions::STOP,
        multiAgentExperience::ipc::messaging::VoidPayload());

    m_sender->send(message);
}

void DialogControllerProxy::stopAndInvokeControl(const multiAgentExperience::control::ControlType& controlType) {
    LX(DEBUG0, "controlType:" + multiAgentExperience::ipc::utils::toString(controlType));

    auto message = multiAgentExperience::ipc::messaging::createMessage(
        m_reference,
        models::dialog::DialogControllerFunctions::STOP_AND_INVOKE_CONTROL,
        multiAgentExperience::ipc::messaging::EnumPayload<multiAgentExperience::control::ControlType>(controlType));

    m_sender->send(message);
}

} // namespace dialog
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience