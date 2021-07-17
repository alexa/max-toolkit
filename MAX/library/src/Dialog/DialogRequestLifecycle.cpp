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

#include "Dialog/DialogRequestLifecycle.h"

#include "Dialog/DialogRequest.h"
#include "Utils/Logger/Logger.h"

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
