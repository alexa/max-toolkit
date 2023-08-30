/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Core/Transformer/StaticExperienceManagerTransformerFactory.h"
#include "Core/Transformer/StaticExperienceManagerTransformer.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

StaticExperienceManagerTransformerFactory::StaticExperienceManagerTransformerFactory(
    std::shared_ptr<library::experience::ExperienceManager> experienceManager) :
        m_experienceManager{experienceManager} {
}

std::shared_ptr<StaticExperienceManagerTransformer> StaticExperienceManagerTransformerFactory::create(
    const multiAgentExperience::actor::ActorId& actorId) {
    return std::make_shared<StaticExperienceManagerTransformer>(actorId, m_experienceManager);
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience