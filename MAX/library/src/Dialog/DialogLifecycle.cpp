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

#include "Dialog/DialogLifecycle.h"

#include "Control/ControlInvoker.h"
#include "Control/ControlInvokerFactory.h"
#include "Control/ControlRegistry.h"
#include "Control/ControlRegistryFactory.h"
#include "Control/CurrentControls.h"
#include "Dialog/Dialog.h"
#include "Dialog/DialogController.h"
#include "Dialog/DialogState.h"
#include "Utils/Logger/Logger.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {

static const std::string MODULE_TAG("DialogLifecycle");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

DialogLifecycle::DialogLifecycle(
    std::shared_ptr<Dialog> dialog,
    std::shared_ptr<control::CurrentControls> currentControls,
    std::shared_ptr<control::ControlRegistryFactory> controlRegistryFactory,
    std::shared_ptr<control::ControlInvokerFactory> controlInvokerFactory) :
        m_stateMutex(),
        m_dialog(dialog),
        m_currentControls(currentControls),
        m_controlRegistryFactory(controlRegistryFactory),
        m_controlInvokerFactory(controlInvokerFactory),
        m_currentDialogState(DialogStateFactory::none()),
        m_lifecycleState(DialogLifecycleState::WAITING),
        m_uninterruptible(false) {
}

bool DialogLifecycle::isInterruptible() {
    LX(DEBUG3, "");
    std::unique_lock<std::mutex> lock(m_stateMutex);
    return !m_uninterruptible && (m_lifecycleState == DialogLifecycleState::FINISHED ||
                                  DialogStateFactory::isInterruptible(m_currentDialogState));
}

void DialogLifecycle::setOnFinishedCallback(std::function<void()> onFinished) {
    LX(DEBUG3, "");
    m_onFinishedCallback = std::move(onFinished);
}

void DialogLifecycle::startDialog() {
    LX(DEBUG3, "");
    std::unique_lock<std::mutex> lock(m_stateMutex);
    if (m_lifecycleState == DialogLifecycleState::WAITING) {
        m_lifecycleState = DialogLifecycleState::STARTED;
        lock.unlock();
        auto dialogController = std::make_shared<DialogController>(shared_from_this());
        cleanupLastState();
        m_dialog->onDialogStarted(dialogController);
    }
}

void DialogLifecycle::startListening() {
    LX(DEBUG3, "");
    std::unique_lock<std::mutex> lock(m_stateMutex);
    if (m_lifecycleState == DialogLifecycleState::STARTED) {
        m_currentDialogState = DialogStateFactory::listening();
        lock.unlock();
        cleanupLastState();
        auto currentControls = m_currentControls->getCurrentControls();
        m_dialog->onListening(currentControls);
    }
}

void DialogLifecycle::startThinking() {
    LX(DEBUG3, "");
    std::unique_lock<std::mutex> lock(m_stateMutex);
    if (m_lifecycleState == DialogLifecycleState::STARTED) {
        m_currentDialogState = DialogStateFactory::thinking();
        lock.unlock();
        cleanupLastState();
        m_dialog->onThinking();
    }
}

void DialogLifecycle::startOtherState(const DialogState& otherState) {
    LX(DEBUG3, "");
    std::unique_lock<std::mutex> lock(m_stateMutex);
    if (m_lifecycleState == DialogLifecycleState::STARTED) {
        m_currentDialogState = otherState;
        lock.unlock();
        cleanupLastState();
        m_currentRegistry = m_controlRegistryFactory->create(control::ControlPriority::DIALOG);
        m_currentInvoker = m_controlInvokerFactory->create();
        m_dialog->onOtherState(otherState, m_currentRegistry, m_currentInvoker);
    }
}

void DialogLifecycle::finishDialog() {
    LX(DEBUG3, "");
    std::unique_lock<std::mutex> lock(m_stateMutex);
    if (m_lifecycleState == DialogLifecycleState::STARTED) {
        m_lifecycleState = DialogLifecycleState::FINISHED;
        m_currentDialogState = DialogStateFactory::none();
        lock.unlock();
        cleanupLastState();
        m_dialog->onDialogFinished();
        if (m_onFinishedCallback) {
            m_onFinishedCallback();
        }
    }
}

void DialogLifecycle::markUninterruptible() {
    LX(DEBUG3, "");
    std::unique_lock<std::mutex> lock(m_stateMutex);
    m_uninterruptible = true;
}

void DialogLifecycle::cleanupLastState() {
    LX(DEBUG3, "");
    if (m_currentRegistry) {
        m_currentRegistry->cleanup();
        m_currentRegistry = nullptr;
    }
    if (m_currentInvoker) {
        m_currentInvoker->cleanup();
        m_currentInvoker = nullptr;
    }
}

DialogLifecycle::~DialogLifecycle() {
    cleanupLastState();
}

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience
