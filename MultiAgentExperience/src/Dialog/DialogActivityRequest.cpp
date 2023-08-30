/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
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
