/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGACTIVITYREQUEST_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGACTIVITYREQUEST_H_

#include <memory>

#include "Activity/ActivityRequest.h"
#include "DialogActivity.h"
#include "DialogRequestLifecycle.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {

class DialogActivityRequest : public activity::ActivityRequest {
public:
    DialogActivityRequest(
        std::shared_ptr<DialogRequestLifecycle> dialogRequest,
        std::shared_ptr<DialogActivity> dialogActivity);

    /// @name ActivityRequest method overrides.
    /// @{
    void onGranted() override;
    void onDenied() override;
    void onRemoved() override;
    void onFinished() override;
    void onWaiting() override;
    /// @}

private:
    std::shared_ptr<DialogRequestLifecycle> m_dialogRequest;
};

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGACTIVITYREQUEST_H_
