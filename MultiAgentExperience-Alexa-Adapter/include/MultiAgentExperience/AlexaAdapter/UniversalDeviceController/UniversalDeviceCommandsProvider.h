/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_MULTIASSISTANT_UNIVERSALDEVICECONTROLLERCOMMANDPROVIDERINTERFACE_H
#define MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_MULTIASSISTANT_UNIVERSALDEVICECONTROLLERCOMMANDPROVIDERINTERFACE_H

#include <condition_variable>
#include <set>
#include <string>

#include <AVSCommon/AVS/CapabilityState.h>
#include <AVSCommon/AVS/CapabilityTag.h>
#include <AVSCommon/SDKInterfaces/Endpoints/EndpointIdentifier.h>
#include <AVSCommon/SDKInterfaces/UniversalDeviceCommandsProviderInterface.h>

namespace alexaClientSDK {
namespace multiAssistant {
namespace universalDeviceController {

class UniversalDeviceCommandsProvider : public alexaClientSDK::avsCommon::sdkInterfaces::UniversalDeviceCommandsProviderInterface {
public:
    UniversalDeviceCommandsProvider(
        const avsCommon::sdkInterfaces::endpoints::EndpointIdentifier& endpointId);
    virtual ~UniversalDeviceCommandsProvider() = default;

    /// @name UniversalDeviceControllerInterface Functions
    /// @{
    virtual void onCommandsAvailable(std::set<std::string> commands) override;
    virtual void clearAvailableCommands() override;
    virtual avsCommon::avs::CapabilityTag getUniversalDeviceControllerTag() override;
    virtual avsCommon::avs::CapabilityState getUniversalDeviceControllerState(
        int waitTimeoutInMilliSeconds = 0) override;
    virtual void expectCommands() override;
    virtual void stopExpectingCommands() override;

    /// @}

private:
    enum class UDCProviderState {
        EXPECTING_COMMANDS,
        OBTAINED_COMMANDS,
        NO_COMMANDS_EXPECTED
    };

    std::string getPayload(int waitTimeoutInMilliSeconds);

    std::set<std::string> m_availableCommands;
    alexaClientSDK::avsCommon::utils::timing::TimePoint m_availableCommandsTimeObtained;
    UDCProviderState m_udcProviderState;
    std::condition_variable m_cv;
    std::mutex m_UDCProviderMutex;
    avsCommon::avs::CapabilityTag m_capabilityTag;
};

} // namespace universalDeviceController
} // namespace multiAssistant
} // namespace alexaClientSDK

#endif //MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_MULTIASSISTANT_UNIVERSALDEVICECONTROLLERCOMMANDPROVIDERINTERFACE_H
