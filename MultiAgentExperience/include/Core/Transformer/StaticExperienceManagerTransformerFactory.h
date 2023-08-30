/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/
#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_STATICEXPERIENCEMANAGERTRANSFORMERFACTORY_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_STATICEXPERIENCEMANAGERTRANSFORMERFACTORY_H_

#include "Experience/ExperienceManager.h"
#include "Core/Transformer/StaticExperienceManagerTransformer.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {
class StaticExperienceManagerTransformerFactory {
public:
    StaticExperienceManagerTransformerFactory(
        std::shared_ptr<library::experience::ExperienceManager> experienceManager);

    virtual ~StaticExperienceManagerTransformerFactory() = default;

    virtual std::shared_ptr<StaticExperienceManagerTransformer> create(
        const multiAgentExperience::actor::ActorId& actorId);

private:
    std::shared_ptr<library::experience::ExperienceManager> m_experienceManager;
};
}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_STATICEXPERIENCEMANAGERTRANSFORMERFACTORY_H_