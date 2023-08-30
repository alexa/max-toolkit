/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Core/Transformer/ActivityRequestTransformerFactory.h"

#include "Core/Transformer/ActivityTransformer.h"
#include "Core/Transformer/TransformerUtils.h"
#include "Core/Transformer/ActivityRequestTransformer.h"
#include "Experience/ExperienceController.h"
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
        std::make_shared<ActivityTransformer>(actorId, m_activityManager, request->getHandler(), experienceController);

    /// we make sure to associate the activityId with the experience controller associated with the activity
    /// as this is going to prove useful later on when sorting experiences
    auto transformedActivityType =
        TransformerUtils::convertPublicActivityTypeToInternalActivityType(request->getType());
    auto transformedMixabilityType =
        TransformerUtils::convertPublicMixabilityTypeToInternalMixabilityType(request->getMixabilityType());

    auto transformedRequest = std::make_shared<ActivityRequestTransformer>(
            transformedActivityType, activityTransformer, request->getHandler(), transformedMixabilityType);

    activityTransformer->associateActivityIdWithExperienceController(transformedRequest->getID());

    return transformedRequest;
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
