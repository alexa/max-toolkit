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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_EXPERIENCE_EXPERIENCEMANAGER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_EXPERIENCE_EXPERIENCEMANAGER_H_

#include <array>
#include <list>
#include <mutex>
#include <vector>

#include <MultiAgentExperience/Experience/ExperienceControllerInterface.h>
#include <MultiAgentExperience/Experience/ExperienceManagerInterface.h>

#include <MultiAgentExperience/Actor/ActorId.h>

#include "Utils/Threading/Executor.h"

namespace multiAgentExperience {
namespace library {
namespace experience {

class ExperienceManager
        : public std::enable_shared_from_this<ExperienceManager>
        , public multiAgentExperience::experience::ExperienceManagerInterface {
public:
    ExperienceManager();

    ExperienceManager(std::shared_ptr<library::utils::threading::Executor> observerExecutor);

    void startExperience(
        const multiAgentExperience::actor::ActorId& actor,
        const multiAgentExperience::experience::Experience::SessionId& session,
        const multiAgentExperience::experience::ExperienceId& experience);

    void endExperience(
        const multiAgentExperience::actor::ActorId& actor,
        const multiAgentExperience::experience::Experience::SessionId& session);

    void clearExperiences();

    /// @name ExperienceManagerInterface method overrides.
    /// @{
    void addObserver(std::weak_ptr<multiAgentExperience::experience::ExperienceObserverInterface> observer) override;
    void clearObservers() override;
    /// @}

    std::shared_ptr<multiAgentExperience::experience::ExperienceControllerInterface> getController(
        const multiAgentExperience::actor::ActorId& actor);

private:
    void notifyObservers();

    void notifyObserver(
        std::shared_ptr<multiAgentExperience::experience::ExperienceObserverInterface> observer,
        std::vector<multiAgentExperience::experience::Experience> experiences);

    std::vector<multiAgentExperience::experience::Experience> getCurrentExperiences();

    /// Generate a unique SessionId
    /// Thread Safe
    multiAgentExperience::experience::Experience::SessionId generateSessionId();

    std::shared_ptr<library::utils::threading::Executor> m_executor;

    std::mutex m_mutex;
    std::list<std::weak_ptr<multiAgentExperience::experience::ExperienceObserverInterface>> m_observers;
    std::list<multiAgentExperience::experience::Experience> m_activeExperiences;
};

}  // namespace experience
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_EXPERIENCE_EXPERIENCEMANAGER_H_
