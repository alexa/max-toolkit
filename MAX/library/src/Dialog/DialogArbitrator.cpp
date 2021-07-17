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

#include "Dialog/DialogArbitrator.h"

#include "Dialog/DialogLifecycle.h"
#include "Dialog/DialogLifecycleFactory.h"
#include "Dialog/DialogRequest.h"
#include "Utils/Logger/Logger.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {

static const std::string MODULE_TAG("DialogArbitrator");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

DialogArbitrator::DialogArbitrator(std::shared_ptr<DialogLifecycleFactory> dialogLifecycleFactory) :
        m_sessionMutex(),
        m_dialogLifecycleFactory(dialogLifecycleFactory),
        m_dialogLifecycle(nullptr),
        m_dialogRequestID(0) {
}

bool DialogArbitrator::tryInterruptingWith(std::shared_ptr<DialogRequest> dialogRequest) {
    LX(DEBUG3, "");

    std::unique_lock<std::mutex> lock(m_sessionMutex);
    if (m_dialogLifecycle && !m_dialogLifecycle->isInterruptible()) {
        return false;
    } else {
        m_dialogLifecycle = m_dialogLifecycleFactory->create(dialogRequest->getDialog());
        m_dialogRequestID = dialogRequest->getID();
        return true;
    }
}

std::shared_ptr<DialogLifecycle> DialogArbitrator::getCurrentDialog() {
    LX(DEBUG3, "");

    return m_dialogLifecycle;
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
