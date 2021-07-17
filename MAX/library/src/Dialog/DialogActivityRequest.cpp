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

#include "Dialog/DialogActivityRequest.h"

#include "Activity/ActivityType.h"
#include "Dialog/DialogActivity.h"
#include "Dialog/DialogRequestLifecycle.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {

DialogActivityRequest::DialogActivityRequest(
    std::shared_ptr<DialogRequestLifecycle> dialogRequest,
    std::shared_ptr<DialogActivity> dialogActivity) :
        activity::ActivityRequest(activity::ActivityType::DIALOG, dialogActivity),
        m_dialogRequest(dialogRequest) {
}

void DialogActivityRequest::onGranted() {
    m_dialogRequest->grant();
}

void DialogActivityRequest::onDenied() {
    m_dialogRequest->deny();
}

void DialogActivityRequest::onRemoved() {
}

void DialogActivityRequest::onFinished() {
}

void DialogActivityRequest::onWaiting() {
    // Activity on waiting is not the same as a dialog waiting. See the dialog scheduling rules.
}

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience
