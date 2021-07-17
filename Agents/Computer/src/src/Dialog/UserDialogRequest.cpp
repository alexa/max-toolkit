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

#include "Computer/Dialog/UserDialogRequest.h"

#include <iostream>

#include <MultiAgentExperience/Dialog/DialogControllerInterface.h>

#include "Utils/Logger.h"

namespace multiAgentExperience {
namespace samples {
namespace agents {
namespace computer {
namespace dialog {

static const std::string MODULE_TAG("UserDialogRequest");
#define LX(logCommand, message) COMPUTER_AGENT_LOG_##logCommand("", MODULE_TAG, __func__, message)

void UserDialogRequest::onDenied(const std::string& denialMessage) {
    LX(DEBUG3, "");
}

void UserDialogRequest::onDialogStarted(
    std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> controller) {
    LX(DEBUG3, "");
    controller->startListening();
}

void UserDialogRequest::onError(const std::string& errorMessage) {
    LX(DEBUG3, "");
}

void UserDialogRequest::onDialogStopped() {
    LX(DEBUG3, "");
}

}  // namespace dialog
}  // namespace computer
}  // namespace agents
}  // namespace samples
}  // namespace multiAgentExperience
