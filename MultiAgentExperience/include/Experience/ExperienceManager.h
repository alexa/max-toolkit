/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_EXPERIENCE_EXPERIENCEMANAGER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_EXPERIENCE_EXPERIENCEMANAGER_H_

#include <array>
#include <list>
#include <map>
#include <mutex>
#include <vector>

#include <MultiAgentExperience/Experience/ExperienceControllerInterface.h>
#include <MultiAgentExperience/Experience/ExperienceManagerInterface.h>

#include <MultiAgentExperience/Actor/ActorId.h>

#include "Activity/ActivityID.h"
#include "Activity/ActivityManager.h"
#include "Utils/Threading/Executor.h"

namespace multiAgentExperience {
namespace library {
namespace experience {

class ExperienceManager
        : public std::enable_shared_from_this<ExperienceManager>
        , public multiAgentExperience::experience::ExperienceManagerInterface {
public:
    ExperienceManager(std::shared_ptr<multiAgentExperience::library::activity::ActivityManager> activityManager);

    ExperienceManager(std::shared_ptr<multiAgentExperience::library::activity::ActivityManager> activityManager,
                      std::shared_ptr<library::utils::threading::Executor> observerExecutor);

    void startExperience(
        const multiAgentExperience::actor::ActorId& actor,
        const multiAgentExperience::library::activity::ActivityID activityId,
        const multiAgentExperience::experience::Experience::SessionId& session,
        const multiAgentExperience::experience::ExperienceId& experience);

    void endExperience(
        const multiAgentExperience::actor::ActorId& actor,
        const multiAgentExperience::experience::Experience::SessionId& session);

    void clearExperiences();

    /// @name ExperienceManagerInterface method overrides.
    /// @{
    void addObserver(std::weak_ptr<multiAgentExperience::experience::ExperienceObserverInterface> observer) override;
    void removeObserver(std::weak_ptr<multiAgentExperience::experience::ExperienceObserverInterface> observer) override;
    void clearObservers() override;
    /// @}

    std::shared_ptr<multiAgentExperience::experience::ExperienceControllerInterface> getController(
        const multiAgentExperience::actor::ActorId& actor);

    void updateStaticExperiences(
        multiAgentExperience::actor::ActorId actorId,
        std::list<multiAgentExperience::experience::Experience> staticExperiences);

    void clearStaticExperiencesForActor(const actor::ActorId& actorId);

    /// Generate a unique SessionId
    /// Thread Safe
    static multiAgentExperience::experience::Experience::SessionId generateSessionId();

private:
    void notifyObservers();

    void notifyObserver(
        std::shared_ptr<multiAgentExperience::experience::ExperienceObserverInterface> observer,
        std::vector<multiAgentExperience::experience::Experience> experiences);

    std::vector<multiAgentExperience::experience::Experience> getCurrentExperiences();

    std::shared_ptr<library::utils::threading::Executor> m_executor;

    /// dependency on activity manager is required in order to fetch the list of current
    /// activities sorted by priority through activity channels encapsulated inside
    /// activity manager
    std::shared_ptr<activity::ActivityManager> m_activityManager;

    std::mutex m_mutex;
    std::list<std::weak_ptr<multiAgentExperience::experience::ExperienceObserverInterface>> m_observers;

    std::map<multiAgentExperience::library::activity::ActivityID, multiAgentExperience::experience::Experience>
        m_activityIdToExperiencesMap;
    std::map<std::string, std::list<multiAgentExperience::experience::Experience>> m_staticExperiencesMap;
};

}  // namespace experience
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_EXPERIENCE_EXPERIENCEMANAGER_H_
