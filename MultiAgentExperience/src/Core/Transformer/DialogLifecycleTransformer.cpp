/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <thread>

#include "Core/Transformer/DialogLifecycleTransformer.h"

#include "Core/Transformer/CombinedDialogStateHandlersLifecycleFactory.h"
#include "Core/Transformer/ControlRegistryTransformer.h"
#include "Core/Transformer/DialogControllerTransformerFactory.h"
#include "Core/Transformer/DialogRequestLifecycle.h"
#include "Core/Transformer/DialogState.h"
#include "Core/Transformer/TransformerUtils.h"
#include "Control/ControlInvoker.h"
#include "Control/ControlName.h"
#include "Control/ControlRegistry.h"
#include "Dialog/DialogController.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

static const std::string STANDARD_DENIAL_MESSAGE = "Denied because of Dialog arbitration.";
static const std::string ERROR_MESSAGE_FAILED_TO_ENTER_UNREGISTERED_STATE =
    "Failed attempting to enter unregistered responding state: ";

static std::atomic_int id(0);

DialogLifecycleTransformer::DialogLifecycleTransformer(
    const multiAgentExperience::actor::ActorId& actorId,
    std::shared_ptr<multiAgentExperience::dialog::DialogRequestInterface> dialogRequest,
    std::shared_ptr<CombinedDialogStateHandlersLifecycleFactory> dialogStateLifecycleFactory,
    std::shared_ptr<DialogControllerTransformerFactory> dialogControllerTransformerFactory) :
        m_id{id++},
        m_actorId{actorId},
        m_dialogActivityId{0},
        m_dialogRequestLifecycle{std::make_shared<DialogRequestLifecycle>(dialogRequest)},
        m_dialogStateLifecycleFactory{dialogStateLifecycleFactory},
        m_dialogControllerTransformerFactory{dialogControllerTransformerFactory},
        m_dialogStatesLifecycle{nullptr} {
}

void DialogLifecycleTransformer::onGranted() {
}

void DialogLifecycleTransformer::onDenied() {
    m_dialogRequestLifecycle->deny(STANDARD_DENIAL_MESSAGE);
}

void DialogLifecycleTransformer::onDialogStarted(std::shared_ptr<library::dialog::DialogController> dialogController) {
    auto dialogControllerTransformer = m_dialogControllerTransformerFactory->create(dialogController);
    m_dialogStatesLifecycle = m_dialogStateLifecycleFactory->create(m_actorId, m_dialogActivityId,
                                                                    dialogControllerTransformer);
    if (!m_dialogRequestLifecycle->start(dialogControllerTransformer)) {
        m_dialogStatesLifecycle = nullptr;
    }
}

void DialogLifecycleTransformer::onListening(std::unordered_set<library::control::ControlName> availableControls) {
    if (m_dialogRequestLifecycle->isStarted()) {
        auto controlTypes = TransformerUtils::convertSetOfControlNamesToControlTypes(availableControls);
        auto lifecycle = m_dialogStatesLifecycle;

        if (lifecycle && !lifecycle->startListening(controlTypes)) {
            sendErrorMessageForMissingState(
                multiAgentExperience::library::core::transformer::DialogState::createListening());
        }
    }
}

void DialogLifecycleTransformer::onThinking() {
    if (m_dialogRequestLifecycle->isStarted()) {
        if (!m_dialogStatesLifecycle->startThinking()) {
            sendErrorMessageForMissingState(
                multiAgentExperience::library::core::transformer::DialogState::createThinking());
        }
    }
}

void DialogLifecycleTransformer::onOtherState(
    const library::dialog::DialogState otherState,
    std::shared_ptr<library::control::ControlRegistry> controlRegistry,
    std::shared_ptr<library::control::ControlInvoker> controlInvoker) {
    if (m_dialogRequestLifecycle->isStarted()) {
        auto dialogStateKey = TransformerUtils::convertDialogStatesToDialogState(otherState);
        auto controlRegistryTransformer = std::make_shared<transformer::ControlRegistryTransformer>(m_dialogActivityId, controlRegistry);

        auto lifecycle = m_dialogStatesLifecycle;

        if (!dialogStateKey.isSpeaking() || !(lifecycle && lifecycle->startSpeaking(controlRegistryTransformer))) {
            sendErrorMessageForMissingState(dialogStateKey);
        }
    }
}

void DialogLifecycleTransformer::onDialogFinished() {
    m_dialogRequestLifecycle->beforeStop();
    auto lifecycle = m_dialogStatesLifecycle;
    if (lifecycle) {
        {
            // onDialogFinished may be called on multiple threads and this causes at least tests to fail.
            std::unique_lock<std::mutex> lock(m_lifecycleMutex);
            m_dialogStatesLifecycle = nullptr;
        }
        lifecycle->stop();
        lifecycle = nullptr;
    }
    m_dialogRequestLifecycle->stop();
}

int DialogLifecycleTransformer::getId() const {
    return m_id;
}

void DialogLifecycleTransformer::setDialogActivityId(const activity::ActivityID dialogActivityId) {
    m_dialogActivityId = dialogActivityId;
}

multiAgentExperience::actor::ActorId DialogLifecycleTransformer::getActorId() const {
    return m_actorId;
}

void DialogLifecycleTransformer::sendErrorMessageForMissingState(
    const multiAgentExperience::library::core::transformer::DialogState& dialogState) {
    auto errorMessage = std::string(ERROR_MESSAGE_FAILED_TO_ENTER_UNREGISTERED_STATE) + dialogState.getStateName();
    m_dialogRequestLifecycle->error(errorMessage);
    onDialogFinished();
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
