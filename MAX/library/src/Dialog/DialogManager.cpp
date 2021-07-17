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

#include <vector>

#include "Dialog/DialogManager.h"

#include "Activity/ActivityManager.h"
#include "Dialog/DialogArbitrator.h"
#include "Dialog/Dialog.h"
#include "Dialog/DialogActivity.h"
#include "Dialog/DialogActivityRequest.h"
#include "Dialog/DialogController.h"
#include "Dialog/DialogRequest.h"
#include "Dialog/DialogRequestLifecycle.h"
#include "Dialog/DialogLifecycle.h"
#include "Utils/Logger/Logger.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {

static const std::string MODULE_TAG("DialogManager");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

DialogManager::DialogManager(
    std::shared_ptr<DialogArbitrator> dialogArbitrator,
    std::shared_ptr<activity::ActivityManager> activityManager) :
        m_dialogArbitrator(dialogArbitrator),
        m_activityManager(activityManager),
        m_dialogToActivityRequests() {
}

void DialogManager::request(std::shared_ptr<DialogRequest> dialogRequest) {
    LX(DEBUG3, "");

    if (m_dialogArbitrator->tryInterruptingWith(dialogRequest)) {
        std::shared_ptr<DialogActivityRequest> dialogActivityRequest;
        std::vector<activity::ActivityRequestID> requestIdsToCleanup;
        {
            std::unique_lock<std::mutex> lock(m_requestMutex);
            for (auto activeRequestEntry : m_dialogToActivityRequests) {
                requestIdsToCleanup.emplace_back(activeRequestEntry.second);
            }
            m_dialogToActivityRequests.clear();

            auto dialog = m_dialogArbitrator->getCurrentDialog();
            auto dialogActivity = std::make_shared<DialogActivity>(dialog);
            auto dialogRequestLifecycle = std::make_shared<DialogRequestLifecycle>(dialogRequest);
            dialogActivityRequest = std::make_shared<DialogActivityRequest>(dialogRequestLifecycle, dialogActivity);
            auto requestID = dialogRequestLifecycle->getID();
            m_dialogToActivityRequests.emplace(requestID, dialogActivityRequest->getID());

            // create an on finished callback to call finish for this request
            auto sharedThis = shared_from_this();
            auto weakSharedThis = std::weak_ptr<DialogManager>(sharedThis);
            auto onFinishedCallback = [weakSharedThis, requestID]() {
                if (auto sharedThis = weakSharedThis.lock()) {
                    sharedThis->finish(requestID);
                }
            };

            dialog->setOnFinishedCallback(onFinishedCallback);
        }
        for (auto requestIdToCleanup : requestIdsToCleanup) {
            m_activityManager->finish(requestIdToCleanup);
        }
        m_activityManager->request(dialogActivityRequest);
    } else {
        dialogRequest->onDenied();
    }
}

void DialogManager::finish(const DialogRequestID& dialogRequestId) {
    LX(DEBUG3, "");

    activity::ActivityRequestID activityRequestId(-1);
    bool hasActivityToCleanup = false;
    {
        std::unique_lock<std::mutex> lock(m_requestMutex);
        auto requestEntry = m_dialogToActivityRequests.find(dialogRequestId);
        if (requestEntry != m_dialogToActivityRequests.end()) {
            activityRequestId = requestEntry->second;
            hasActivityToCleanup = true;
            m_dialogToActivityRequests.erase(dialogRequestId);
            m_dialogArbitrator->cleanup(dialogRequestId);
        }
    }
    if (hasActivityToCleanup) {
        m_activityManager->finish(activityRequestId);
    }
}

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience
