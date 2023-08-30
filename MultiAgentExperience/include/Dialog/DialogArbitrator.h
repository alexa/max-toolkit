/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGARBITRATOR_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGARBITRATOR_H_

#include <memory>
#include <mutex>

#include <MultiAgentExperience/Application/MAXPolicies.h>
#include <MultiAgentExperience/Dialog/DialogBargeInPriority.h>

#include "DialogRequestID.h"
#include "DialogLifecycle.h"
#include "DialogLifecycleFactory.h"
#include "DialogRequest.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {

class DialogArbitrator {
public:
    DialogArbitrator(
        std::shared_ptr<DialogLifecycleFactory> dialogLifecycleFactory,
        const multiAgentExperience::application::HighPriorityCrossAgentBargeInPolicy& highPriorityCrossAgentBargeInPolicy,
        const multiAgentExperience::application::NormalPriorityCrossAgentBargeInPolicy& normalPriorityCrossAgentBargeInPolicy);

    bool tryInterruptingWith(std::shared_ptr<DialogRequest> dialogRequest);

    std::shared_ptr<DialogLifecycle> getCurrentDialog();

    void cleanup(const DialogRequestID dialogRequestId);

private:
    bool isBargeInAllowed(std::shared_ptr<DialogRequest> dialogRequest);

    std::mutex m_sessionMutex;
    std::shared_ptr<DialogLifecycleFactory> m_dialogLifecycleFactory;
    std::shared_ptr<DialogLifecycle> m_dialogLifecycle;
    DialogRequestID m_dialogRequestID;
    const bool m_isHighPriorityCrossAgentBargeInAllowed;
    const bool m_isNormalPriorityCrossAgentBargeInAllowed;
};

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGARBITRATOR_H_
