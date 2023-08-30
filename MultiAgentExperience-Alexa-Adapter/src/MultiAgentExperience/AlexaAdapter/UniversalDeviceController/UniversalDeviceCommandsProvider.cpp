/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/AlexaAdapter/UniversalDeviceController/UniversalDeviceCommandsProvider.h"
#include <AVSCommon/Utils/Logger/Logger.h>
#include <sstream>

namespace alexaClientSDK {
namespace multiAssistant {
namespace universalDeviceController {

static const std::string TAG("UniversalDeviceCommandsProvider");
#define LX(event) alexaClientSDK::avsCommon::utils::logger::LogEntry(TAG, event)

const std::string AVAILABLE_COMMANDS_PAYLOAD_TEMPLATE = R"({"availableCommands" : [{{Enum}}]})";
const std::string AVAILABLE_COMMANDS_PAYLOAD_TEMPLATE_TO_REPLACE = "{{Enum}}";
const std::string NAMESPACE = "MultiAssistant.UniversalDeviceController";
const std::string UNIVERSALDEVICECONTROLLER_CAPABILITY_NAME = "UniversalDeviceControllerState";

UniversalDeviceCommandsProvider::UniversalDeviceCommandsProvider(
    const avsCommon::sdkInterfaces::endpoints::EndpointIdentifier& endpointId)
: m_udcProviderState{UDCProviderState::NO_COMMANDS_EXPECTED},
  m_capabilityTag{NAMESPACE, UNIVERSALDEVICECONTROLLER_CAPABILITY_NAME, endpointId} {}

void UniversalDeviceCommandsProvider::onCommandsAvailable(std::set<std::string> commands) {
    ACSDK_DEBUG3(LX(""));
    if (UniversalDeviceCommandsProvider::UDCProviderState::EXPECTING_COMMANDS == m_udcProviderState) {
        {
            if(!commands.empty()) {
              ACSDK_DEBUG3(LX("Commands are expected and commands are now available!"));
            }
            else {
              ACSDK_DEBUG3(LX("Commands are expected, but NO commands avilable!"));
            }
            std::unique_lock<std::mutex> lock(m_UDCProviderMutex);
            m_availableCommands = commands;
            m_availableCommandsTimeObtained = avsCommon::utils::timing::TimePoint::now();
            m_udcProviderState = UniversalDeviceCommandsProvider::UDCProviderState::OBTAINED_COMMANDS;
        }
        m_cv.notify_all();
    }
}

void UniversalDeviceCommandsProvider::clearAvailableCommands() {
    ACSDK_DEBUG3(LX(""));
    std::unique_lock<std::mutex> lock(m_UDCProviderMutex);
    m_availableCommands.clear();
    m_udcProviderState = UniversalDeviceCommandsProvider::UDCProviderState::NO_COMMANDS_EXPECTED;
    m_cv.notify_all();
}

avsCommon::avs::CapabilityTag UniversalDeviceCommandsProvider::getUniversalDeviceControllerTag() {
    return m_capabilityTag;
}

avsCommon::avs::CapabilityState
    UniversalDeviceCommandsProvider::getUniversalDeviceControllerState(int waitTimeoutInMilliSeconds) {
    ACSDK_DEBUG3(LX(""));
    auto capabilityState = avsCommon::avs::CapabilityState();

    auto payload = getPayload(waitTimeoutInMilliSeconds);
    ACSDK_DEBUG3(LX("Payload got!").d("payload", payload));

    if (!payload.empty()) {
        capabilityState.valuePayload = payload;
        {
            std::unique_lock<std::mutex> lockAvailableCommands(m_UDCProviderMutex);
            capabilityState.timeOfSample = m_availableCommandsTimeObtained;
        }
    }

    return capabilityState;
}

void UniversalDeviceCommandsProvider::expectCommands() {
    std::unique_lock<std::mutex> lock(m_UDCProviderMutex);
    m_udcProviderState = UniversalDeviceCommandsProvider::UDCProviderState::EXPECTING_COMMANDS;
}

void UniversalDeviceCommandsProvider::stopExpectingCommands() {
    std::unique_lock<std::mutex> lock(m_UDCProviderMutex);
    if(UniversalDeviceCommandsProvider::UDCProviderState::EXPECTING_COMMANDS == m_udcProviderState) {
        m_udcProviderState = UniversalDeviceCommandsProvider::UDCProviderState::NO_COMMANDS_EXPECTED;
        m_cv.notify_all();
    }
}

std::string getPayloadWithValues(std::string values) {
    std::string output = AVAILABLE_COMMANDS_PAYLOAD_TEMPLATE;

    size_t pos = output.find(AVAILABLE_COMMANDS_PAYLOAD_TEMPLATE_TO_REPLACE);
    output.replace(pos, AVAILABLE_COMMANDS_PAYLOAD_TEMPLATE_TO_REPLACE.length(), values);

    return output;
}

std::string UniversalDeviceCommandsProvider::getPayload(int waitTimeoutInMilliSeconds) {
    std::set<std::string> curAvailableCommands;
    {
        std::unique_lock<std::mutex> lockUDCProviderState(m_UDCProviderMutex);
        if (UDCProviderState::NO_COMMANDS_EXPECTED == m_udcProviderState
            || (UDCProviderState::OBTAINED_COMMANDS == m_udcProviderState && m_availableCommands.empty())) {
            ACSDK_DEBUG3(LX("No commands expected or no commands avilable!"));
            return getPayloadWithValues("");
        }

        auto updateReceived = m_cv.wait_for(lockUDCProviderState,
                                              std::chrono::milliseconds(waitTimeoutInMilliSeconds),
                                              [this]{return UDCProviderState::OBTAINED_COMMANDS == m_udcProviderState
                                              || UDCProviderState::NO_COMMANDS_EXPECTED == m_udcProviderState;});

        if (updateReceived) {
            if (m_availableCommands.empty()) {
                ACSDK_DEBUG3(LX("No commands available!"));
                return getPayloadWithValues("");
            } else {
                curAvailableCommands = m_availableCommands;
            }
        } else {
            ACSDK_ERROR(LX("Timeout waiting for expected available commands."));
            return getPayloadWithValues("");
        }
    }

    // Concatenate all commands
    std::stringstream ss;
    std::string delim = "\",\"";
    std::copy(curAvailableCommands.begin(),
              curAvailableCommands.end(),
              std::ostream_iterator<std::string>(ss, delim.c_str()));

    // Removes the last comma from previous concatenation
    auto curConcatenatedAvailableCommands = ss.str(); // curConcatenatedAvailableCommands = GLOBAL_STOP","VOLUME_UP","VOLUME_DOWN","
    if (!curConcatenatedAvailableCommands.empty()) {
        curConcatenatedAvailableCommands = "\"" + curConcatenatedAvailableCommands; // curConcatenatedAvailableCommands = "GLOBAL_STOP","VOLUME_UP","VOLUME_DOWN","
        curConcatenatedAvailableCommands.pop_back(); // curConcatenatedAvailableCommands = "GLOBAL_STOP","VOLUME_UP","VOLUME_DOWN",
        curConcatenatedAvailableCommands.pop_back(); // curConcatenatedAvailableCommands = "GLOBAL_STOP","VOLUME_UP","VOLUME_DOWN"
    }

    return getPayloadWithValues(curConcatenatedAvailableCommands);
}

} // namespace universalDeviceController
} // namespace multiAssistant
} // namespace alexaClientSDK
