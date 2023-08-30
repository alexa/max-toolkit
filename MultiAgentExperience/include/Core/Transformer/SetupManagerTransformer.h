/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_SETUPMANAGERTRANSFORMER_H
#define MULTIAGENTEXPERIENCE_SETUPMANAGERTRANSFORMER_H

#include <MultiAgentExperience/Device/SetupManagerInterface.h>

#include <Activity/ActivityManager.h>

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

class SetupManagerTransformer : public multiAgentExperience::device::SetupManagerInterface {
public:
    SetupManagerTransformer(std::shared_ptr<device::DeviceRestrictRequestsHelper> deviceRestrictRequestsHelper,
                            std::shared_ptr<activity::ActivityManager> activityManager);

    /// @name SetupManagerInterface method overrides.
    /// @{
    void enterSetupMode(const multiAgentExperience::actor::ActorId& actorId) override;
    void exitSetupMode() override;
    /// @}

private:
    std::shared_ptr<device::DeviceRestrictRequestsHelper> m_deviceRestrictRequestsHelper;
    std::shared_ptr<activity::ActivityManager> m_activityManager;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience


#endif //MULTIAGENTEXPERIENCE_SETUPMANAGERTRANSFORMER_H
