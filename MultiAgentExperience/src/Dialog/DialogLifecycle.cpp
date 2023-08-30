/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Dialog/DialogLifecycle.h"

#include <sstream>

#include "Control/ControlInvoker.h"
#include "Control/ControlInvokerFactory.h"
#include "Control/ControlRegistry.h"
#include "Control/ControlRegistryFactory.h"
#include "Control/CurrentControls.h"
#include "Dialog/Dialog.h"
#include "Dialog/DialogController.h"
#include "Dialog/DialogState.h"
#include "Utils/Memory/Memory.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {

static const std::string MODULE_TAG("DialogLifecycle");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)



std::unordered_set<control::ControlName> reduceToControlNames(
    std::unordered_map<control::ControlName, std::weak_ptr<control::Control>> controls) {
    std::unordered_set<control::ControlName> currentControls;

    for(auto curControl : controls) {
        currentControls.insert(curControl.first);
    }

    return currentControls;
}

DialogLifecycle::DialogLifecycle(
    std::shared_ptr<Dialog> dialog,
    std::shared_ptr<control::CurrentControls> currentControls,
    std::shared_ptr<control::ControlRegistryFactory> controlRegistryFactory,
    std::shared_ptr<control::ControlInvokerFactory> controlInvokerFactory) :
        m_stateMutex{},
        m_dialog{dialog},
        m_currentControls{currentControls},
        m_controlRegistryFactory{controlRegistryFactory},
        m_controlInvokerFactory{controlInvokerFactory},
        m_currentDialogState{DialogStateFactory::idle()},
        m_lifecycleState{DialogLifecycleState::WAITING},
        m_uninterruptible{false},
        m_actionableActivityId{nullptr} {
}

bool DialogLifecycle::isInterruptible() {
    LX(DEBUG3, "");
    std::unique_lock<std::mutex> lock(m_stateMutex);
    return !m_uninterruptible && (m_lifecycleState == DialogLifecycleState::FINISHED ||
                                  DialogStateFactory::isNotIdle(m_currentDialogState));
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
        std::unordered_set<control::ControlName> controlNamesFromControlSnapshot;
        if(m_currentDialogState == DialogStateFactory::idle()
        && nullptr != m_actionableActivityId) {
            m_sharableControlSnapshot = m_currentControls->getControlsOfActivity(*m_actionableActivityId.get());
            controlNamesFromControlSnapshot = reduceToControlNames(m_sharableControlSnapshot);
        }

        m_currentDialogState = DialogStateFactory::listening();
        lock.unlock();
        cleanupLastState();

        m_dialog->onListening(controlNamesFromControlSnapshot);
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
        m_currentDialogState = DialogStateFactory::finished();
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

multiAgentExperience::actor::ActorId DialogLifecycle::getActorId() const {
    return m_dialog->getActorId();
}

std::weak_ptr<control::Control> DialogLifecycle::getHighestPriorityControlFromName(const control::ControlName& controlName) {
    LX(DEBUG3, "");
    std::unique_lock<std::mutex> lock(m_stateMutex);
    std::weak_ptr<control::Control> highestPriorityControl = m_sharableControlSnapshot[controlName];

    return highestPriorityControl;
}

void DialogLifecycle::setActionableActivityId(const activity::ActivityID &activityId) {
    std::stringstream ss;
    ss << "Activity details:"
       << "activityId=" << std::to_string(activityId);
    LX(DEBUG3, ss.str());
    m_actionableActivityId = utils::memory::make_unique<activity::ActivityID>(activityId);
}

bool DialogLifecycle::isNotListeningOrThinking() {
    LX(DEBUG3, "");
    std::unique_lock<std::mutex> lock(m_stateMutex);
    return DialogStateFactory::isNotListeningOrThinking(m_currentDialogState);
}

DialogLifecycle::~DialogLifecycle() {
    cleanupLastState();
}

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience
