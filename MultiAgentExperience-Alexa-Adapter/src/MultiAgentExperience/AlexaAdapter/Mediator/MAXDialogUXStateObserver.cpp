/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/AlexaAdapter/Mediator/MAXDialogUXStateObserver.h"

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace mediator {

MAXDialogUXStateObserver::MAXDialogUXStateObserver(std::shared_ptr<MAXFocusMediator>
    maxFocusMediator) : m_maxFocusMediator{maxFocusMediator} {}

void MAXDialogUXStateObserver::onDialogUXStateChanged
(alexaClientSDK::avsCommon::sdkInterfaces::DialogUXStateObserverInterface::DialogUXState newState) {
  /// invoke the onThinkingReceived() API exposed in MAXFocusMediator if the new state received
  /// by the observer is "THINKING"
  if (newState == DialogUXState::THINKING) {
    m_maxFocusMediator->onThinkingReceived();
  }
}

}
}
}