/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Core/Transformer/DialogStateHandlerLifecycle.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

DialogStateHandlerLifecycle::DialogStateHandlerLifecycle(
    const library::core::transformer::DialogState& dialogState,
    std::function<void()> startCallback,
    std::function<void()> stopCallback) :
        m_lifecycleState{LifecycleState::NONE},
        m_dialogState{dialogState},
        m_startCallback{startCallback},
        m_stopCallback{stopCallback} {
}

library::core::transformer::DialogState DialogStateHandlerLifecycle::getDialogState() {
    return m_dialogState;
}

void DialogStateHandlerLifecycle::start() {
    if (trySwitchState(LifecycleState::NONE, LifecycleState::STARTED)) {
        m_startCallback();
    }
}

void DialogStateHandlerLifecycle::stop() {
    if (trySwitchState(LifecycleState::STARTED, LifecycleState::STOPPED)) {
        m_stopCallback();
    }
}

bool DialogStateHandlerLifecycle::trySwitchState(
    DialogStateHandlerLifecycle::LifecycleState from,
    const DialogStateHandlerLifecycle::LifecycleState& to) {
    return m_lifecycleState.compare_exchange_strong(from, to);
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
