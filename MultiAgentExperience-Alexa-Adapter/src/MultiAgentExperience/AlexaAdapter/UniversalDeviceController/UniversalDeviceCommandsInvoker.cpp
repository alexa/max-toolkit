/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <string>

#include <AVSCommon/Utils/Logger/Logger.h>

#include "MultiAgentExperience/AlexaAdapter/UniversalDeviceController/UniversalDeviceCommandsInvoker.h"

namespace alexaClientSDK {
namespace multiAssistant {
namespace universalDeviceController {

static const std::string TAG("UniversalDeviceCommandsInvoker");
#define LX(event) alexaClientSDK::avsCommon::utils::logger::LogEntry(TAG, event)


UniversalDeviceCommandsInvoker::UniversalDeviceCommandsInvoker() {
}

bool UniversalDeviceCommandsInvoker::getControlTypeFromUDCString(
    const std::string& universalDeviceCommand,
    ::multiAgentExperience::control::ControlType& controlType) {
    if ("GLOBAL_FOREGROUND_STOP" == universalDeviceCommand) {
        controlType = ::multiAgentExperience::control::ControlType::STOP;
        return true;
    }

    return false;
}

bool UniversalDeviceCommandsInvoker::invokeCommand(std::string universalDeviceCommand) {
    if (m_maxDialogFocusRequester) {
        auto activeDialogRequest = m_maxDialogFocusRequester->getCurrentDialog();
        if (auto activeDialogRequestPtr = activeDialogRequest.lock()) {
            ::multiAgentExperience::control::ControlType controlType;
            auto isValidControlType = getControlTypeFromUDCString(universalDeviceCommand, controlType);
            if (isValidControlType) {
                activeDialogRequestPtr->stopAndInvokeControl(controlType);
                return true;
            } else {
                ACSDK_ERROR(LX("Invalid ControlType").d("UDC", universalDeviceCommand));
                activeDialogRequestPtr->stop();
            }
        } else {
            ACSDK_ERROR(LX("No Active dialog present!"));
        }
    }
    else {
        ACSDK_ERROR(LX("NULL MAXDialogFocusRequester"));
    }
    return false;
}

void UniversalDeviceCommandsInvoker::onReady(
    std::shared_ptr<multiAgentExperience::mediator::MAXDialogFocusRequesterInterface> maxDialogFocusRequester) {
    m_maxDialogFocusRequester = maxDialogFocusRequester;
}

} // namespace universalDeviceController
} // namespace multiAssistant
} // namespace alexaClientSDK
