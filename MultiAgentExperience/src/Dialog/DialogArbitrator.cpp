/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Dialog/DialogArbitrator.h"

#include "Dialog/DialogLifecycle.h"
#include "Dialog/DialogLifecycleFactory.h"
#include "Dialog/DialogRequest.h"
#include "Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {

using namespace  multiAgentExperience::application;

static const std::string MODULE_TAG("DialogArbitrator");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

DialogArbitrator::DialogArbitrator(
    std::shared_ptr<DialogLifecycleFactory> dialogLifecycleFactory,
    const HighPriorityCrossAgentBargeInPolicy& highPriorityCrossAgentBargeInPolicy,
    const NormalPriorityCrossAgentBargeInPolicy& normalPriorityCrossAgentBargeInPolicy) :
        m_sessionMutex(),
        m_dialogLifecycleFactory(dialogLifecycleFactory),
        m_dialogLifecycle(nullptr),
        m_dialogRequestID(0),
        m_isHighPriorityCrossAgentBargeInAllowed(highPriorityCrossAgentBargeInPolicy == HighPriorityCrossAgentBargeInPolicy::SUPPORTED),
        m_isNormalPriorityCrossAgentBargeInAllowed(normalPriorityCrossAgentBargeInPolicy == NormalPriorityCrossAgentBargeInPolicy::SUPPORTED) {
}

bool DialogArbitrator::tryInterruptingWith(std::shared_ptr<DialogRequest> dialogRequest) {
    LX(DEBUG3, "");

    std::unique_lock<std::mutex> lock(m_sessionMutex);

    /**
     * m_dialogLifecycle keeps track of the current dialog's lifecycle
     *
     * There are 2 scenarios where an incoming dialog is allowed to interrupt:
     * 1. The current dialog lifecycle object does not exist, which means there is no ongoing dialog
     * 2. The current dialog lifecycle object does exist, and BOTH conditions below are true
     *      a. current dialog is interruptible
     *      b. the barge-in policies defined by the device integrator allow this type of dialog to barge-in
     *
     * The incoming dialog request is denied for all other scenarios.
     */
    if (!m_dialogLifecycle ||
        (m_dialogLifecycle && m_dialogLifecycle->isInterruptible() && isBargeInAllowed(dialogRequest))) {

        LX(DEBUG1, "Interrupt successful, creating a new dialog:requestID=" + std::to_string(dialogRequest->getID()) +
            ",dialogBargeInPriority=" + utils::toString(dialogRequest->getDialogBargeInPriority()));

        // Create and store the new dialog's lifecycle
        m_dialogLifecycle = m_dialogLifecycleFactory->create(dialogRequest->getDialog());
        m_dialogRequestID = dialogRequest->getID();
        return true;
    } else {
        LX(DEBUG1, "Interrupt failed:requestID=" + std::to_string(dialogRequest->getID()) +
            ",dialogBargeInPriority=" + utils::toString(dialogRequest->getDialogBargeInPriority()));
        return false;
    }
}

bool DialogArbitrator::isBargeInAllowed(std::shared_ptr<DialogRequest> dialogRequest) {
    LX(DEBUG3, "");

    switch (dialogRequest->getDialogBargeInPriority()) {

        case multiAgentExperience::dialog::DialogBargeInPriority::HIGH:
            if (m_dialogLifecycle->getActorId() == dialogRequest->getActorId()) {
                // If same-agent barge-in, allow.
                return true;
            } else {
                // If cross-agent barge-in, just check the corresponding cross-agent barge-in policy.
                return m_isHighPriorityCrossAgentBargeInAllowed;
            }

        case multiAgentExperience::dialog::DialogBargeInPriority::NORMAL:
            if (m_dialogLifecycle->getActorId() == dialogRequest->getActorId()) {
                // If same-agent barge-in, check if the dialog is not in listening or thinking states.
                return m_dialogLifecycle->isNotListeningOrThinking();
            } else {
                // If cross-agent barge-in, just check the corresponding cross-agent barge-in policy.
                return m_isNormalPriorityCrossAgentBargeInAllowed;
            }
    }

    return false;
}

std::shared_ptr<DialogLifecycle> DialogArbitrator::getCurrentDialog() {
    LX(DEBUG3, "");

    return m_dialogLifecycle;
}

std::shared_ptr<DialogRequestID> DialogArbitrator::getCurrentDialogIdForActor(
    const actor::ActorId& actorId) {
    LX(DEBUG3, "");
    std::shared_ptr<DialogRequestID> dialogRequestId = nullptr;

    std::unique_lock<std::mutex> lock(m_sessionMutex);
    if(nullptr != m_dialogLifecycle
        && actorId == m_dialogLifecycle->getActorId()) {
        dialogRequestId = std::make_shared<DialogRequestID>(m_dialogRequestID);
    }

    return dialogRequestId;
}

void DialogArbitrator::cleanup(const DialogRequestID dialogRequestId) {
    LX(DEBUG3, "");

    std::unique_lock<std::mutex> lock(m_sessionMutex);
    if (m_dialogRequestID == dialogRequestId) {
        m_dialogLifecycle = nullptr;
        m_dialogRequestID = DialogRequestID(-1);
    }
}

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience
