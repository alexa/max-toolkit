/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Dialog/DialogManagerFactory.h"

#include "Activity/ActivityManager.h"
#include "Control/CurrentControls.h"
#include "Control/ControlInvokerFactory.h"
#include "Control/ControlRegistryFactory.h"
#include "Dialog/DialogArbitrator.h"
#include "Dialog/DialogLifecycleFactory.h"
#include "Dialog/DialogManager.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {

std::shared_ptr<DialogManager> DialogManagerFactory::create(
    std::shared_ptr<activity::ActivityManager> activityManager,
    std::shared_ptr<control::CurrentControls> currentControls,
    std::shared_ptr<control::ControlInvokerFactory> controlInvokerFactory,
    std::shared_ptr<control::ControlRegistryFactory> controlRegistryFactory,
    std::shared_ptr<device::DeviceRestrictRequestsHelper> deviceRestrictRequestsHelper,
    const multiAgentExperience::application::HighPriorityCrossAgentBargeInPolicy& highPriorityCrossAgentBargeInPolicy,
    const multiAgentExperience::application::NormalPriorityCrossAgentBargeInPolicy& normalPriorityCrossAgentBargeInPolicy) {
    auto dialogLifecycleFactory =
        std::make_shared<DialogLifecycleFactory>(currentControls, controlRegistryFactory, controlInvokerFactory);
    auto dialogArbitrator = std::make_shared<DialogArbitrator>(
        dialogLifecycleFactory,
        highPriorityCrossAgentBargeInPolicy,
        normalPriorityCrossAgentBargeInPolicy);
    return std::make_shared<DialogManager>(dialogArbitrator, activityManager, deviceRestrictRequestsHelper);
}

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience
