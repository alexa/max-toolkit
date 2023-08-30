/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/
#ifndef MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_MEDIATOR_MAXDIALOGUXSTATEOBSERVER_H
#define MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_MEDIATOR_MAXDIALOGUXSTATEOBSERVER_H

#include <AVSCommon/SDKInterfaces/DialogUXStateObserverInterface.h>

#include "MultiAgentExperience/AlexaAdapter/Mediator/MAXFocusMediator.h"

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace mediator {

class MAXDialogUXStateObserver : public avsCommon::sdkInterfaces::DialogUXStateObserverInterface {
 public:

  MAXDialogUXStateObserver(std::shared_ptr<MAXFocusMediator> maxFocusMediator);

  ~MAXDialogUXStateObserver() = default;

  /// @name DialogUXStateObserverInterface overrides
  /// @{
  void onDialogUXStateChanged(DialogUXState newState) override;
  /// @}

 private:
  std::shared_ptr<MAXFocusMediator> m_maxFocusMediator;
};

}
}
}

#endif // MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_MEDIATOR_MAXDIALOGUXSTATEOBSERVER_H