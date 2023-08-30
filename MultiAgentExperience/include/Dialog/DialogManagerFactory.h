/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGMANAGERFACTORY_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGMANAGERFACTORY_H_

#include <memory>

#include <MultiAgentExperience/Application/MAXPolicies.h>

#include "Activity/ActivityManager.h"
#include "Control/CurrentControls.h"
#include "Control/ControlInvokerFactory.h"
#include "Control/ControlRegistryFactory.h"
#include "DialogManager.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {

struct DialogManagerFactory {
    static std::shared_ptr<DialogManager> create(
        std::shared_ptr<activity::ActivityManager> activityManager,
        std::shared_ptr<control::CurrentControls> currentControls,
        std::shared_ptr<control::ControlInvokerFactory> controlInvokerFactory,
        std::shared_ptr<control::ControlRegistryFactory> controlRegistryFactory,
        std::shared_ptr<device::DeviceRestrictRequestsHelper> deviceRestrictRequestsHelper,
        const multiAgentExperience::application::HighPriorityCrossAgentBargeInPolicy& highPriorityCrossAgentBargeInPolicy,
        const multiAgentExperience::application::NormalPriorityCrossAgentBargeInPolicy& normalPriorityCrossAgentBargeInPolicy);
};

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGMANAGERFACTORY_H_
