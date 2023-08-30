/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_ACTIVITYREQUESTTRANSFORMER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_ACTIVITYREQUESTTRANSFORMER_H_

#include <memory>

#include <MultiAgentExperience/Activity/ActivityHandlerInterface.h>
#include <MultiAgentExperience/Activity/ActivityType.h>

#include "Activity/ActivityRequest.h"
#include "ActivityTransformer.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

class ActivityRequestTransformer : public multiAgentExperience::library::activity::ActivityRequest {
public:
    ActivityRequestTransformer(
        multiAgentExperience::library::activity::ActivityType activityType,
        std::shared_ptr<ActivityTransformer> activity,
        std::shared_ptr<multiAgentExperience::activity::ActivityHandlerInterface> activityHandlerInterface,
        multiAgentExperience::library::activity::MixabilityType mixabilityType
            = activity::MixabilityType::MIXABLE_RESTRICTED);

    /// @name ActivityRequest method overrides.
    /// @{
    void onGranted() override;
    void onDenied() override;
    void onRemoved() override;
    void onFinished() override;
    void onWaiting() override;
    /// @}

private:
    std::shared_ptr<multiAgentExperience::activity::ActivityHandlerInterface> m_activityHandlerInterface;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_ACTIVITYREQUESTTRANSFORMER_H_
