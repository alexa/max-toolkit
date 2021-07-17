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

#include "Dialog/DialogController.h"

#include "Dialog/DialogLifecycle.h"
#include "Utils/Logger/Logger.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {

static const std::string MODULE_TAG("DialogController");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

DialogController::DialogController(std::shared_ptr<DialogLifecycle> dialogLifecycle) :
        m_dialogLifecycle(dialogLifecycle) {
}

void DialogController::startListening() {
    m_dialogLifecycle->startListening();
}

void DialogController::startThinking() {
    m_dialogLifecycle->startThinking();
}

void DialogController::startOtherState(const DialogState otherState) {
    m_dialogLifecycle->startOtherState(otherState);
}

void DialogController::finishDialog() {
    m_dialogLifecycle->finishDialog();
}

void DialogController::markUninterruptible() {
    m_dialogLifecycle->markUninterruptible();
}

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience
