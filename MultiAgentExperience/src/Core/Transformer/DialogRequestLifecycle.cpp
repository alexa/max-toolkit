/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <sstream>

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Core/Transformer/DialogRequestLifecycle.h"

#include "MultiAgentExperience/Dialog/DialogControllerInterface.h"
#include "MultiAgentExperience/Dialog/DialogRequestInterface.h"


namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

static const std::string MODULE_TAG("DialogRequestLifecycle");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

static const std::string FINISHED_BEFORE_GRANTED_DENIAL_MESSAGE = "The dialog was stopped before it was granted.";

DialogRequestLifecycle::DialogRequestLifecycle(
    std::shared_ptr<multiAgentExperience::dialog::DialogRequestInterface> dialogRequest) :
        m_requestLifecycleState{RequestLifecycleState::REQUESTED},
        m_dialogRequest{dialogRequest} {
    LX(DEBUG0, "");
}

bool DialogRequestLifecycle::start(
    std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> dialogController) {
    if (trySwitchState(RequestLifecycleState::REQUESTED, RequestLifecycleState::STARTED)) {
        LX(DEBUG0, "DialogRequestInterface::onDialogStarted called");
        m_dialogRequest->onDialogStarted(dialogController);
        return true;
    }
    return false;
}

bool DialogRequestLifecycle::isStarted() {
    return isInState(RequestLifecycleState::STARTED);
}

void DialogRequestLifecycle::error(const std::string& errorMessage) {
    if (isStarted()) {
        LX(DEBUG0, "DialogRequestInterface::onError called");
        m_dialogRequest->onError(errorMessage);
    }
}

void DialogRequestLifecycle::deny(const std::string& denialMessage) {
    if (trySwitchState(RequestLifecycleState::REQUESTED, RequestLifecycleState::STOPPED)) {
        LX(DEBUG0, "DialogRequestInterface::onDenied called");
        m_dialogRequest->onDenied(denialMessage);
    }
}

void DialogRequestLifecycle::beforeStop() {
    if (trySwitchState(RequestLifecycleState::REQUESTED, RequestLifecycleState::STOPPING)) {
        m_requestLifecycleState = RequestLifecycleState::STOPPED;
        LX(DEBUG0, "DialogRequestInterface::onDenied called");
        m_dialogRequest->onDenied(FINISHED_BEFORE_GRANTED_DENIAL_MESSAGE);
    } else if (!isInState(RequestLifecycleState::STOPPED)) {
        m_requestLifecycleState = RequestLifecycleState::STOPPING;
    }
}

void DialogRequestLifecycle::stop() {
    if (trySwitchState(RequestLifecycleState::REQUESTED, RequestLifecycleState::STOPPING)) {
        m_requestLifecycleState = RequestLifecycleState::STOPPED;
        LX(DEBUG0, "DialogRequestInterface::onDenied called");
        m_dialogRequest->onDenied(FINISHED_BEFORE_GRANTED_DENIAL_MESSAGE);
    } else if (!isInState(RequestLifecycleState::STOPPED)) {
        m_requestLifecycleState = RequestLifecycleState::STOPPED;
        LX(DEBUG0, "DialogRequestInterface::onDialogStopped called");
        m_dialogRequest->onDialogStopped();
    }
}

bool DialogRequestLifecycle::trySwitchState(RequestLifecycleState from, const RequestLifecycleState& to) {
    return m_requestLifecycleState.compare_exchange_strong(from, to);
}

bool DialogRequestLifecycle::isInState(const DialogRequestLifecycle::RequestLifecycleState& state) {
    return m_requestLifecycleState == state;
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
