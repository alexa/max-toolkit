/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <AVSCommon/Utils/Logger/Logger.h>

#include "MultiAgentExperience/AlexaAdapter/Dialog/AlexaControlReceiver.h"

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace dialog {

static const std::string TAG("AlexaControlReceiver");
#define LX(event) alexaClientSDK::avsCommon::utils::logger::LogEntry(TAG, event)

AlexaControlReceiver::AlexaControlReceiver(std::weak_ptr<
    alexaClientSDK::avsCommon::sdkInterfaces::UniversalDeviceCommandsProviderInterface> commandProvider)
    : m_commandProvider{std::move(commandProvider)} {
}

bool getUDCCommandFromControlType(::multiAgentExperience::control::ControlType control, std::string& universalDeviceCommand) {
    switch(control) {
        case ::multiAgentExperience::control::ControlType::STOP:
            universalDeviceCommand = "GLOBAL_FOREGROUND_STOP";
            return true;
        default:
            return false;
    }
}

void AlexaControlReceiver::onControlsReceived(
    std::shared_ptr<::multiAgentExperience::dialog::StartListeningCallback> startListeningCallback,
    std::set<::multiAgentExperience::control::ControlType> controls) {
    ACSDK_DEBUG3(LX(""));
    std::set<std::string> universalDeviceCommands;
    for (auto control : controls) {
        std::string universalDeviceCommand;
        if (getUDCCommandFromControlType(control, universalDeviceCommand)) {
            universalDeviceCommands.insert(universalDeviceCommand);
        }
        else {
            ACSDK_ERROR(LX("Invalid ControlType"));
        }
    }

    if (auto commandProvider = m_commandProvider.lock()) {
        commandProvider->onCommandsAvailable(universalDeviceCommands);
    }

    if (startListeningCallback) {
        startListeningCallback->startListening();
    }
}

void AlexaControlReceiver::clearAvailableControls() {
    if (auto commandProvider = m_commandProvider.lock()) {
        commandProvider->clearAvailableCommands();
    }
}

void AlexaControlReceiver::expectControls() {
    if (auto commandProvider = m_commandProvider.lock()) {
        commandProvider->expectCommands();
    }
}

void AlexaControlReceiver::stopExpectingControls() {
    if (auto commandProvider = m_commandProvider.lock()) {
        commandProvider->stopExpectingCommands();
    }
}

} // namespace dialog
} // namespace multiAgentExperience
} // namespace alexaClientSDK