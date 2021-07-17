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

#include "Core/Transformer/DialogControllerTransformer.h"

#include "Control/ControlInvoker.h"
#include "Control/ControlInvokerFactory.h"
#include "Core/Transformer/TransformerUtils.h"
#include "Dialog/DialogController.h"
#include "Dialog/DialogState.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

DialogControllerTransformer::DialogControllerTransformer(
    std::shared_ptr<multiAgentExperience::library::control::ControlInvokerFactory> controlInvokerFactory,
    std::shared_ptr<multiAgentExperience::library::dialog::DialogController> dialogController) :
        m_controllerLifecycleState{ControllerLifecycleState::STARTED},
        m_controlInvokerFactory{controlInvokerFactory},
        m_dialogController{dialogController} {
}

void DialogControllerTransformer::startListening() {
    if (isStarted()) {
        m_dialogController->startListening();
    }
}

void DialogControllerTransformer::startThinking() {
    if (isStarted()) {
        m_dialogController->startThinking();
    }
}

void DialogControllerTransformer::startSpeaking() {
    if (isStarted()) {
        m_dialogController->startOtherState(library::dialog::DialogStateFactory::speaking());
    }
}

void DialogControllerTransformer::invokeControlAndStartSpeaking(
    const multiAgentExperience::control::ControlType& controlType) {
    if (isStarted()) {
        invokeControl(controlType);
        startSpeaking();
    }
}

void DialogControllerTransformer::stop() {
    stopInternal();
}

void DialogControllerTransformer::stopAndInvokeControl(const multiAgentExperience::control::ControlType& controlType) {
    if (stopInternal()) {
        invokeControl(controlType);
    }
}

void DialogControllerTransformer::markUninterruptible() {
    if (m_dialogController) {
        m_dialogController->markUninterruptible();
    }
}

void DialogControllerTransformer::invokeControl(const multiAgentExperience::control::ControlType& controlType) {
    // TODO: Capture the set of controls given to this Agent and validate only controls from the last set are used.
    // do this under VII-291.
    auto invoker = m_controlInvokerFactory->create();
    auto controlName = TransformerUtils::convertControlTypeToControlName(controlType);
    invoker->invoke(controlName);
}

bool DialogControllerTransformer::stopInternal() {
    if (trySwitchState(ControllerLifecycleState::STARTED, ControllerLifecycleState::STOPPED)) {
        m_dialogController->finishDialog();
        return true;
    }
    return false;
}

bool DialogControllerTransformer::trySwitchState(ControllerLifecycleState from, const ControllerLifecycleState& to) {
    return m_controllerLifecycleState.compare_exchange_strong(from, to);
}

bool DialogControllerTransformer::isStarted() {
    return m_controllerLifecycleState == ControllerLifecycleState::STARTED;
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
