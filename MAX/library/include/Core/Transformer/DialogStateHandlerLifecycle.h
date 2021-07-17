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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGSTATEHANDLERLIFECYCLE_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGSTATEHANDLERLIFECYCLE_H_

#include <atomic>
#include <functional>

#include "DialogState.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

/**
 * The DialogStateHandlerLifecycle helps manage the lifecycle of any DialogStateHandler. The callbacks are given to take
 * action as the lifecycle changes. Callbacks are used in favor of wrapping the DialogStateHandler itself as there is no
 * interface shared between all state handlers. The lifecycle will prevent the callbacks from being used in the wrong
 * order or the wrong number of times.
 */
class DialogStateHandlerLifecycle {
public:
    DialogStateHandlerLifecycle(
        const multiAgentExperience::library::core::transformer::DialogState& dialogState,
        std::function<void()> startCallback,
        std::function<void()> stopCallback);

    multiAgentExperience::library::core::transformer::DialogState getDialogState();

    void start();

    void stop();

private:
    enum class LifecycleState { NONE, STARTED, STOPPED };

    // TODO: move to a LifecycleUtils set of free functions.
    bool trySwitchState(LifecycleState from, const LifecycleState& to);

    std::atomic<LifecycleState> m_lifecycleState;
    const multiAgentExperience::library::core::transformer::DialogState m_dialogState;
    const std::function<void()> m_startCallback;
    const std::function<void()> m_stopCallback;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGSTATEHANDLERLIFECYCLE_H_
