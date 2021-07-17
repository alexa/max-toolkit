/*
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include "Core/Transformer/DialogRequestLifecycle.h"

#include "MultiAgentExperience/Dialog/DialogControllerInterface.h"
#include "MultiAgentExperience/Dialog/DialogRequestInterface.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

static const std::string FINISHED_BEFORE_GRANTED_DENIAL_MESSAGE = "The dialog was stopped before it was granted.";

DialogRequestLifecycle::DialogRequestLifecycle(
    std::shared_ptr<multiAgentExperience::dialog::DialogRequestInterface> dialogRequest) :
        m_requestLifecycleState{RequestLifecycleState::REQUESTED},
        m_dialogRequest{dialogRequest} {
}

bool DialogRequestLifecycle::start(
    std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> dialogController) {
    if (trySwitchState(RequestLifecycleState::REQUESTED, RequestLifecycleState::STARTED)) {
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
        m_dialogRequest->onError(errorMessage);
    }
}

void DialogRequestLifecycle::deny(const std::string& denialMessage) {
    if (trySwitchState(RequestLifecycleState::REQUESTED, RequestLifecycleState::STOPPED)) {
        m_dialogRequest->onDenied(denialMessage);
    }
}

void DialogRequestLifecycle::beforeStop() {
    if (trySwitchState(RequestLifecycleState::REQUESTED, RequestLifecycleState::STOPPING)) {
        m_requestLifecycleState = RequestLifecycleState::STOPPED;
        m_dialogRequest->onDenied(FINISHED_BEFORE_GRANTED_DENIAL_MESSAGE);
    } else if (!isInState(RequestLifecycleState::STOPPED)) {
        m_requestLifecycleState = RequestLifecycleState::STOPPING;
    }
}

void DialogRequestLifecycle::stop() {
    if (trySwitchState(RequestLifecycleState::REQUESTED, RequestLifecycleState::STOPPING)) {
        m_requestLifecycleState = RequestLifecycleState::STOPPED;
        m_dialogRequest->onDenied(FINISHED_BEFORE_GRANTED_DENIAL_MESSAGE);
    } else if (!isInState(RequestLifecycleState::STOPPED)) {
        m_requestLifecycleState = RequestLifecycleState::STOPPED;
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
