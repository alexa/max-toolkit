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

#include "Core/Transformer/ActivityRequestTransformerFactory.h"

#include "Core/Transformer/ActivityTransformer.h"
#include "Core/Transformer/TransformerUtils.h"
#include "Core/Transformer/ActivityRequestTransformer.h"
#include "Experience/ExperienceManager.h"

#include "MultiAgentExperience/Activity/ActivityRequestInterface.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

ActivityRequestTransformerFactory::ActivityRequestTransformerFactory(
    std::shared_ptr<multiAgentExperience::library::activity::ActivityManager> activityManager,
    std::shared_ptr<library::experience::ExperienceManager> experienceManager) :
        m_activityManager{activityManager},
        m_experienceManager{experienceManager} {
}

std::shared_ptr<ActivityRequestTransformer> ActivityRequestTransformerFactory::create(
    multiAgentExperience::actor::ActorId actorId,
    std::shared_ptr<multiAgentExperience::activity::ActivityRequestInterface> request) {
    auto experienceController = m_experienceManager->getController(actorId);
    auto activityTransformer =
        std::make_shared<ActivityTransformer>(m_activityManager, request->getHandler(), experienceController);
    auto transformedActivityType =
        TransformerUtils::convertPublicActivityTypeToInternalActivityType(request->getType());
    return std::make_shared<ActivityRequestTransformer>(
        transformedActivityType, activityTransformer, request->getHandler());
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
