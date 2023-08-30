/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_UNIVERSALDEVICECOMMANDSINVOKER_H
#define MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_UNIVERSALDEVICECOMMANDSINVOKER_H

#include <AVSCommon/SDKInterfaces/UniversalDeviceCommandsInvokerInterface.h>

#include <MultiAgentExperience/AlexaAdapter/Mediator/MAXDialogFocusRequester.h>

namespace alexaClientSDK {
namespace multiAssistant {
namespace universalDeviceController {

class UniversalDeviceCommandsInvoker : public avsCommon::sdkInterfaces::UniversalDeviceCommandsInvokerInterface {
public:
    UniversalDeviceCommandsInvoker();

    /// @name UniversalDeviceControllerInterface Functions
    /// @{
    bool invokeCommand(std::string universalDeviceCommand) override;
    /// @}

    void onReady(
        std::shared_ptr<multiAgentExperience::mediator::MAXDialogFocusRequesterInterface> maxDialogFocusRequester);

private:
    bool getControlTypeFromUDCString(
        const std::string& universalDeviceCommand,
        ::multiAgentExperience::control::ControlType& controlType);

    std::shared_ptr<multiAgentExperience::mediator::MAXDialogFocusRequesterInterface> m_maxDialogFocusRequester;
};

} // namespace universalDeviceController
} // namespace multiAssistant
} // namespace alexaClientSDK

#endif //MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_UNIVERSALDEVICECOMMANDSINVOKER_H
