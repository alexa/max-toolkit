/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <vector>

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Dialog/DialogManager.h"

#include "Activity/ActivityManager.h"
#include "Core/Transformer/DialogLifecycleTransformer.h"
#include "Dialog/DialogArbitrator.h"
#include "Dialog/DialogActivity.h"
#include "Dialog/DialogActivityRequest.h"
#include "Dialog/DialogRequest.h"
#include "Dialog/DialogRequestLifecycle.h"
#include "Dialog/DialogLifecycle.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {

static const std::string MODULE_TAG("DialogManager");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

DialogManager::DialogManager(
    std::shared_ptr<DialogArbitrator> dialogArbitrator,
    std::shared_ptr<activity::ActivityManager> activityManager,
    std::shared_ptr<device::DeviceRestrictRequestsHelper> deviceRestrictRequestsHelper) :
    m_dialogArbitrator{dialogArbitrator},
    m_activityManager{activityManager},
    m_dialogToActivityRequests{},
    m_deviceRestrictRequestsHelper{deviceRestrictRequestsHelper} {
}

control::ControlPriority getControlPriorityFromActivityType(activity::ActivityType activityType) {
    switch(activityType) {
        case activity::ActivityType::DIALOG:
            return control::ControlPriority::DIALOG;
        case activity::ActivityType::COMMUNICATIONS:
            return control::ControlPriority::COMMUNICATIONS;
        case activity::ActivityType::ALERTS:
            return control::ControlPriority::ALERTS;
        case activity::ActivityType::CONTENT:
            return control::ControlPriority::CONTENT;
        case activity::ActivityType::NONE:
        default:
            return control::ControlPriority::NONE;
    }
}

void DialogManager::request(std::shared_ptr<DialogRequest> dialogRequest) {
    LX(DEBUG3, "");

    if (m_deviceRestrictRequestsHelper->canRequestBeGrantedForActor(dialogRequest->getActorId())
        && m_dialogArbitrator->tryInterruptingWith(dialogRequest)) {
        /// extract the dialog lifecycle instance from the dialog request
        auto dialogLifecycle = dialogRequest->getDialog();

        std::shared_ptr<DialogActivityRequest> dialogActivityRequest;
        {
            std::unique_lock<std::mutex> lock(m_requestMutex);
            m_dialogToActivityRequests.clear();

            auto dialog = m_dialogArbitrator->getCurrentDialog();

            if(dialog) {
                auto foregroundActivitySnapshot = m_activityManager->getForegroundActivitySnapshotFromOtherActor(
                    dialogRequest->getActorId());
                if(foregroundActivitySnapshot) {
                    dialog->setActionableActivityId(foregroundActivitySnapshot->getActivityId());
                }
            }

            auto dialogActivity = std::make_shared<DialogActivity>(dialog);
            auto dialogRequestLifecycle = std::make_shared<DialogRequestLifecycle>(dialogRequest);
            dialogActivityRequest = std::make_shared<DialogActivityRequest>(dialogRequestLifecycle, dialogActivity);
            auto requestID = dialogRequestLifecycle->getID();
            m_dialogToActivityRequests.emplace(requestID, dialogActivityRequest->getID());

            /// set the ActivityId for the dialog using dialogActivityRequest which will be
            /// useful later for sorting experiences
            dialogLifecycle->setDialogActivityId(dialogActivityRequest->getID());

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
    } else {
        LX(WARN, "No activity to cleanup.");
    }
}

void DialogManager::clearDialogForActor(const actor::ActorId& actorId) {
    LX(DEBUG3, "");

    // Find if ongoing dialog belongs to this actor
    if(auto dialogIdToRemove = m_dialogArbitrator->getCurrentDialogIdForActor(actorId)) {
        // cleanup the dialog and related activity
        finish(*dialogIdToRemove);
    }
    else {
        LX(DEBUG3, "No dialog from actor to remove!");
    }
}

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience
