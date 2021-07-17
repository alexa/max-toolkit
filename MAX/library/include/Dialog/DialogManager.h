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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGMANAGER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGMANAGER_H_

#include <memory>
#include <mutex>
#include <unordered_map>

#include "Activity/ActivityRequestID.h"
#include "Activity/ActivityManager.h"
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
        std::shared_ptr<activity::ActivityManager> activityManager);

    void request(std::shared_ptr<DialogRequest> dialogRequest);

    void finish(const DialogRequestID& dialogRequestId);

private:
    std::mutex m_requestMutex;
    std::shared_ptr<DialogArbitrator> m_dialogArbitrator;
    std::shared_ptr<activity::ActivityManager> m_activityManager;
    std::unordered_map<DialogRequestID, activity::ActivityRequestID> m_dialogToActivityRequests;
};

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGMANAGER_H_
