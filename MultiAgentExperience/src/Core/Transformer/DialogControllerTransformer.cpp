/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Core/Transformer/DialogControllerTransformer.h"

#include <sstream>

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Control/ControlInvoker.h"
#include "Control/ControlInvokerFactory.h"
#include "Core/Transformer/TransformerUtils.h"
#include "Dialog/DialogController.h"
#include "Dialog/DialogState.h"

#include "Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

static const std::string MODULE_TAG("DialogControllerTransformer");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

DialogControllerTransformer::DialogControllerTransformer(
    std::shared_ptr<multiAgentExperience::library::control::ControlInvokerFactory> controlInvokerFactory,
    std::shared_ptr<multiAgentExperience::library::dialog::DialogController> dialogController) :
        m_controllerLifecycleState{ControllerLifecycleState::STARTED},
        m_controlInvokerFactory{controlInvokerFactory},
        m_dialogController{dialogController} {
    LX(DEBUG0, "");
}

void DialogControllerTransformer::startListening() {
    LX(DEBUG0, "");
    if (isStarted()) {
        m_dialogController->startListening();
    }
}

void DialogControllerTransformer::startThinking() {
    LX(DEBUG0, "");
    if (isStarted()) {
        m_dialogController->startThinking();
    }
}

void DialogControllerTransformer::startSpeaking() {
    LX(DEBUG0, "");
    if (isStarted()) {
        m_dialogController->startOtherState(library::dialog::DialogStateFactory::speaking());
    }
}

void DialogControllerTransformer::invokeControlAndStartSpeaking(
    const multiAgentExperience::control::ControlType& controlType) {
    std::stringstream ss;
    ss << "details:"
       << " controlType=" << multiAgentExperience::library::utils::toString(controlType);
    LX(DEBUG0, ss.str());

    if (isStarted()) {
        invokeControl(controlType);
        startSpeaking();
    }
}

void DialogControllerTransformer::stop() {
    LX(DEBUG0, "");
    stopInternal();
}

void DialogControllerTransformer::stopAndInvokeControl(const multiAgentExperience::control::ControlType& controlType) {
    std::stringstream ss;
    ss << "details:"
       << " controlType=" << multiAgentExperience::library::utils::toString(controlType);
    LX(DEBUG0, ss.str());

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
    auto invoker = m_controlInvokerFactory->create();
    auto controlName = TransformerUtils::convertControlTypeToControlName(controlType);
    std::weak_ptr<multiAgentExperience::library::control::Control> control = m_dialogController->getHighestPriorityControlFromName(controlName);
    invoker->invoke(control);
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
