/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_STATICEXPERIENCEMANAGERTRANSFORMER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_STATICEXPERIENCEMANAGERTRANSFORMER_H_

#include <MultiAgentExperience/Actor/ActorId.h>
#include <MultiAgentExperience/Experience/StaticExperienceManagerInterface.h>

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

class StaticExperienceManagerTransformer : public multiAgentExperience::experience::StaticExperienceManagerInterface {
public:
    using StaticExperiencePriority = unsigned int;

    StaticExperienceManagerTransformer(
        const multiAgentExperience::actor::ActorId& id,
        std::shared_ptr<library::experience::ExperienceManager> experienceManager);

    ~StaticExperienceManagerTransformer();

    /// @name StaticExperienceManagerInterface method overrides.
    /// @{
    void addStaticExperience(
        const multiAgentExperience::experience::ExperienceId& experienceId,
        const StaticExperiencePriority priority) override;
    void removeStaticExperience(const multiAgentExperience::experience::ExperienceId& experienceId) override;
    void removeAllStaticExperiences() override;
    /// @}

    std::list<std::tuple<StaticExperiencePriority, multiAgentExperience::experience::Experience>> getAllStaticExperiences();
    int getId() const;
    multiAgentExperience::actor::ActorId getActorId() const;

private:
    std::list<multiAgentExperience::experience::Experience> getSortedStaticExperienceList();

    const std::atomic_int m_id;
    std::mutex m_mutex;
    const multiAgentExperience::actor::ActorId m_actorId;
    std::shared_ptr<library::experience::ExperienceManager> m_experienceManager;

    /// the list of static experiences stores tuples of the form <Experience_Priority, Experience>
    /// priorities of these experiences will be used in sorting these experiences as explained in
    /// StaticExperienceManagerInterface API. Each agent can maintain its own list of supported
    /// static experiences using their respective transformer objects
    std::list<std::tuple<StaticExperiencePriority, multiAgentExperience::experience::Experience>> m_staticExperiences;
};
}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

template <>
struct std::hash<multiAgentExperience::library::core::transformer::StaticExperienceManagerTransformer> {
    std::size_t operator()(const multiAgentExperience::library::core::transformer::StaticExperienceManagerTransformer&
                               staticExperienceManagerTransformer) const noexcept {
        return staticExperienceManagerTransformer.getId();
    }
};

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_STATICEXPERIENCEMANAGERTRANSFORMER_H_