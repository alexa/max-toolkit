/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGMANAGER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGMANAGER_H_

#include <memory>
#include <mutex>
#include <unordered_map>

#include "Activity/ActivityRequestID.h"
#include "Activity/ActivityManager.h"
#include "Device/DeviceRestrictRequestsHelper.h"
#include "DialogRequestID.h"
#include "DialogArbitrator.h"
#include "DialogRequest.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {

class DialogManager : public std::enable_shared_from_this<DialogManager> {
public:
    DialogManager(
        std::shared_ptr<DialogArbitrator> dialogArbitrator,
        std::shared_ptr<activity::ActivityManager> activityManager,
        std::shared_ptr<device::DeviceRestrictRequestsHelper> deviceRestrictRequestsHelper);

    void request(std::shared_ptr<DialogRequest> dialogRequest);

    void finish(const DialogRequestID& dialogRequestId);

    void clearDialogForActor(const actor::ActorId& actorId);

private:
    std::mutex m_requestMutex;
    std::shared_ptr<DialogArbitrator> m_dialogArbitrator;
    std::shared_ptr<activity::ActivityManager> m_activityManager;
    std::unordered_map<DialogRequestID, activity::ActivityRequestID> m_dialogToActivityRequests;
    std::shared_ptr<device::DeviceRestrictRequestsHelper> m_deviceRestrictRequestsHelper;
};

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGMANAGER_H_
