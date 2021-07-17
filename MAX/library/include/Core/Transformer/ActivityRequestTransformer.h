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

class ActivityRequestTransformer : public library::activity::ActivityRequest {
public:
    ActivityRequestTransformer(
        library::activity::ActivityType activityType,
        std::shared_ptr<ActivityTransformer> activity,
        std::shared_ptr<multiAgentExperience::activity::ActivityHandlerInterface> activityHandlerInterface);

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
