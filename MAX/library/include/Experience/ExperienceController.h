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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_EXPERIENCE_EXPERIENCECONTROLLER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_EXPERIENCE_EXPERIENCECONTROLLER_H_

#include <memory>

#include <MultiAgentExperience/Experience/ExperienceControllerInterface.h>

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

private:
    ExperienceController(
        std::weak_ptr<ExperienceManager> manager,
        const multiAgentExperience::actor::ActorId& actor,
        const multiAgentExperience::experience::Experience::SessionId& session);

    std::weak_ptr<library::experience::ExperienceManager> m_manager;
    bool m_experienceIsActive;
    const multiAgentExperience::actor::ActorId m_actor;
    const multiAgentExperience::experience::Experience::SessionId m_session;
};

}  // namespace experience
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_EXPERIENCE_EXPERIENCECONTROLLER_H_
