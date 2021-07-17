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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_ACTIVITYREQUESTTRANSFORMERFACTORY_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_ACTIVITYREQUESTTRANSFORMERFACTORY_H_

#include <memory>
#include <string>

#include <MultiAgentExperience/Activity/ActivityRequestInterface.h>

#include "Activity/ActivityManager.h"
#include "Experience/ExperienceManager.h"
#include "ActivityRequestTransformer.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

class ActivityRequestTransformerFactory {
public:
    ActivityRequestTransformerFactory(
        std::shared_ptr<multiAgentExperience::library::activity::ActivityManager> activityManager,
        std::shared_ptr<library::experience::ExperienceManager> experienceManager);

    std::shared_ptr<ActivityRequestTransformer> create(
        multiAgentExperience::actor::ActorId actorId,
        std::shared_ptr<multiAgentExperience::activity::ActivityRequestInterface> request);

private:
    std::shared_ptr<multiAgentExperience::library::activity::ActivityManager> m_activityManager;
    std::shared_ptr<library::experience::ExperienceManager> m_experienceManager;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_ACTIVITYREQUESTTRANSFORMERFACTORY_H_
