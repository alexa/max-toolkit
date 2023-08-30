/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Core/Transformer/SetupManagerTransformer.h"

#include <sstream>

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

static const std::string MODULE_TAG("SetupManagerTransformer");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

SetupManagerTransformer::SetupManagerTransformer(
    std::shared_ptr<device::DeviceRestrictRequestsHelper> deviceRestrictRequestsHelper,
    std::shared_ptr<activity::ActivityManager> activityManager)
:m_deviceRestrictRequestsHelper(deviceRestrictRequestsHelper),
m_activityManager(activityManager) {
    LX(DEBUG0, "");
}

void SetupManagerTransformer::enterSetupMode(const multiAgentExperience::actor::ActorId& actorId) {
    std::stringstream ss;
    ss << "details:"
       << " actorId=" << multiAgentExperience::library::utils::getObfuscatedActorId(actorId);
    LX(DEBUG0, ss.str());

    m_deviceRestrictRequestsHelper->restrictRequestsToActor(actorId);
    m_activityManager->stopAllActivities();
}

void SetupManagerTransformer::exitSetupMode() {
    LX(DEBUG0, "");
    m_deviceRestrictRequestsHelper->stopRestrictingRequests();
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience