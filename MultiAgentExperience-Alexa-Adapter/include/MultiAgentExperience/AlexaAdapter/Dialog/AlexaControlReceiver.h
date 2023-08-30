/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_DIALOG_ALEXACONTROLRECEIVER_H
#define MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_DIALOG_ALEXACONTROLRECEIVER_H

#include <MultiAgentExperience/Dialog/ControlReceiverInterface.h>

#include "MultiAgentExperience/AlexaAdapter/UniversalDeviceController/UniversalDeviceCommandsProvider.h"

#include <utility>

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace dialog {

// TODO: This is where we will integrate received controls from MAX and make them available in the UDC interfaces
// introduced by the UDC CA.

class AlexaControlReceiver : public ::multiAgentExperience::dialog::ControlReceiverInterface {
public:
    explicit AlexaControlReceiver(std::weak_ptr<
        alexaClientSDK::avsCommon::sdkInterfaces::UniversalDeviceCommandsProviderInterface> commandProvider);

    void onControlsReceived(
            std::shared_ptr<::multiAgentExperience::dialog::StartListeningCallback> startListeningCallback,
            std::set<::multiAgentExperience::control::ControlType> controls) final;

    void clearAvailableControls();

    void expectControls();

    void stopExpectingControls();

private:
    std::weak_ptr<alexaClientSDK::avsCommon::sdkInterfaces::UniversalDeviceCommandsProviderInterface> m_commandProvider;
};


} // namespace dialog
} // namespace multiAgentExperience
} // namespace alexaClientSDK

#endif //MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_DIALOG_ALEXACONTROLRECEIVER_H
