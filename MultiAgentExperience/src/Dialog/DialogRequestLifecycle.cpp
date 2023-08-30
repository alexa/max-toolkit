/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Dialog/DialogRequestLifecycle.h"

#include "Dialog/DialogRequest.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {

static const std::string MODULE_TAG("DialogRequestLifecycle");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

DialogRequestLifecycle::DialogRequestLifecycle(std::shared_ptr<DialogRequest> dialogRequest) :
        m_stateMutex(),
        m_state(RequestState::REQUESTED),
        m_dialogRequest(dialogRequest) {
}

const DialogRequestID DialogRequestLifecycle::getID() const {
    return m_dialogRequest->getID();
}

void DialogRequestLifecycle::grant() {
    LX(DEBUG3, "");

    std::unique_lock<std::mutex> lock(m_stateMutex);
    if (m_state == RequestState::REQUESTED) {
        m_state = RequestState::GRANTED;
        lock.unlock();
        m_dialogRequest->onGranted();
    }
}

void DialogRequestLifecycle::deny() {
    LX(DEBUG3, "");

    std::unique_lock<std::mutex> lock(m_stateMutex);
    if (m_state == RequestState::REQUESTED) {
        m_state = RequestState::DENIED;
        lock.unlock();
        m_dialogRequest->onDenied();
    }
}

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience
