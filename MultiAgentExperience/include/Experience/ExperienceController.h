/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_EXPERIENCE_EXPERIENCECONTROLLER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_EXPERIENCE_EXPERIENCECONTROLLER_H_

#include <memory>

#include <MultiAgentExperience/Experience/ExperienceControllerInterface.h>

#include "Activity/ActivityID.h"
#include "Experience/ExperienceManager.h"

namespace multiAgentExperience {
namespace library {
namespace experience {

class ExperienceController : public multiAgentExperience::experience::ExperienceControllerInterface {
public:
    static std::shared_ptr<multiAgentExperience::experience::ExperienceControllerInterface> create(
        std::weak_ptr<library::experience::ExperienceManager> manager,
        const multiAgentExperience::actor::ActorId& actor,
        const multiAgentExperience::experience::Experience::SessionId& session);

    ~ExperienceController();

    /// @name ExperienceControllerInterface method overrides.
    /// @{
    void startExperience(const multiAgentExperience::experience::ExperienceId& experience) override;
    void endExperience() override;
    void invalidate() override;
    /// @}

    void setExperienceControllerActivityId(const activity::ActivityID experienceControllerActivityId);

private:
    ExperienceController(
        std::weak_ptr<ExperienceManager> manager,
        const multiAgentExperience::actor::ActorId& actor,
        const multiAgentExperience::experience::Experience::SessionId& session);

    std::weak_ptr<library::experience::ExperienceManager> m_manager;
    bool m_experienceIsActive;
    activity::ActivityID m_experienceControllerActivityId;
    const multiAgentExperience::actor::ActorId m_actor;
    const multiAgentExperience::experience::Experience::SessionId m_session;
};

}  // namespace experience
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_EXPERIENCE_EXPERIENCECONTROLLER_H_
