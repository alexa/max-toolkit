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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGLIFECYCLE_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGLIFECYCLE_H_

#include <memory>
#include <mutex>
#include <functional>
#include <unordered_set>

#include "Control/CurrentControls.h"
#include "Control/ControlInvoker.h"
#include "Control/ControlInvokerFactory.h"
#include "Control/ControlRegistry.h"
#include "Control/ControlRegistryFactory.h"
#include "Dialog.h"
#include "DialogState.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {

// TODO: Forward declare to address a circular dependency. To be addressed under VII-248.
class Dialog;

class DialogLifecycle : public std::enable_shared_from_this<DialogLifecycle> {
public:
    DialogLifecycle(
        std::shared_ptr<Dialog> dialog,
        std::shared_ptr<control::CurrentControls> currentControls,
        std::shared_ptr<control::ControlRegistryFactory> controlRegistryFactory,
        std::shared_ptr<control::ControlInvokerFactory> controlInvokerFactory);

    ~DialogLifecycle();

    bool isInterruptible();

    void setOnFinishedCallback(std::function<void()> onFinished);

    void startDialog();

    void startListening();

    void startThinking();

    void startOtherState(const DialogState& otherState);

    void finishDialog();

    void markUninterruptible();

private:
    enum class DialogLifecycleState { WAITING, STARTED, FINISHED };

    void cleanupLastState();

    std::mutex m_stateMutex;
    std::shared_ptr<Dialog> m_dialog;
    std::shared_ptr<control::CurrentControls> m_currentControls;
    std::shared_ptr<control::ControlRegistryFactory> m_controlRegistryFactory;
    std::shared_ptr<control::ControlInvokerFactory> m_controlInvokerFactory;
    std::shared_ptr<control::ControlRegistry> m_currentRegistry;
    std::shared_ptr<control::ControlInvoker> m_currentInvoker;
    std::function<void()> m_onFinishedCallback;
    DialogState m_currentDialogState;
    DialogLifecycleState m_lifecycleState;

    bool m_uninterruptible;
};

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGLIFECYCLE_H_
