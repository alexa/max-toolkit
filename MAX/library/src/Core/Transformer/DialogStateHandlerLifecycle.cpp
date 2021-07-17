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
