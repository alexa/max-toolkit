/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Experience/ExperienceManager.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include <algorithm>
#include <atomic>
#include <sstream>

#include "Experience/ExperienceController.h"
#include "Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace library {
namespace experience {

static const std::string MODULE_TAG("ExperienceManager");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

using namespace multiAgentExperience::experience;
using namespace multiAgentExperience::actor;

ExperienceManager::ExperienceManager(std::shared_ptr<multiAgentExperience::library::activity::ActivityManager> activityManager) :
        ExperienceManager(activityManager, std::make_shared<library::utils::threading::Executor>()) {
}

ExperienceManager::ExperienceManager(std::shared_ptr<multiAgentExperience::library::activity::ActivityManager>
    activityManager,std::shared_ptr<library::utils::threading::Executor> observerExecutor) :
        m_executor{observerExecutor}, m_activityManager{activityManager}, m_mutex{}, m_observers{}, m_activityIdToExperiencesMap{},
        m_staticExperiencesMap{} {
}

void ExperienceManager::startExperience(
    const ActorId& actor,
    const activity::ActivityID activityId,
    const Experience::SessionId& session,
    const ExperienceId& experience) {
    LX(DEBUG3, "actorId=" + multiAgentExperience::library::utils::getObfuscatedActorId(actor) +
               ", sessionId=" + std::to_string(session) +
               ", experienceID=" + experience.get());

    std::lock_guard<std::mutex> guard(m_mutex);
    auto it = m_activityIdToExperiencesMap.begin();
    while (it != m_activityIdToExperiencesMap.end()) {
        if (it->second.actorId == actor && it->second.sessionId == session) {
            it = m_activityIdToExperiencesMap.erase(it);
            LX(DEBUG3, "Found existing experience in session " + std::to_string(session) + " replacing.");
            break;
        } else {
            ++it;
        }
    }

    /// add the (activityId, Experience) pair to the map, this assumes 1:1 correspondence of activity to experience
    m_activityIdToExperiencesMap[activityId] = Experience{actor, session, experience};

    notifyObservers();
}


void ExperienceManager::endExperience(const ActorId& actor, const Experience::SessionId& session) {
    LX(DEBUG3, "actorId=" + multiAgentExperience::library::utils::getObfuscatedActorId(actor) +
               ", sessionId=" + std::to_string(session));

    std::lock_guard<std::mutex> guard(m_mutex);
    auto it = m_activityIdToExperiencesMap.begin();
    while (it != m_activityIdToExperiencesMap.end()) {
        LX(DEBUG3, "actorId=" + multiAgentExperience::library::utils::getObfuscatedActorId(it->second.actorId) +
                   ", sessionId=" + std::to_string(it->second.sessionId));

        if (it->second.actorId == actor && it->second.sessionId == session) {
            it = m_activityIdToExperiencesMap.erase(it);
            notifyObservers();
            return;
        } else {
            ++it;
        }
    }

    LX(ERROR, "Experience not found! actorId=" + multiAgentExperience::library::utils::getObfuscatedActorId(actor) +
              ", sessionId=" + std::to_string(session));
}

void ExperienceManager::clearExperiences() {
    LX(DEBUG3, "");

    std::lock_guard<std::mutex> guard(m_mutex);
    m_activityIdToExperiencesMap.clear();
    m_staticExperiencesMap.clear();
    notifyObservers();
}

/// ExperienceManagerInterface functions
void ExperienceManager::addObserver(
    std::weak_ptr<multiAgentExperience::experience::ExperienceObserverInterface> observer) {
    LX(DEBUG0, "");
    std::lock_guard<std::mutex> guard(m_mutex);
    m_observers.push_back(observer);

    if (auto obs = observer.lock()) {
        auto experiences = getCurrentExperiences();
        notifyObserver(obs, experiences);
    }
}

void ExperienceManager::removeObserver(
    std::weak_ptr<multiAgentExperience::experience::ExperienceObserverInterface> observer) {
    LX(DEBUG0, "");

    std::lock_guard<std::mutex> guard(m_mutex);

    // the following sequence of steps are put in because weak_ptr<T>'s don't support equality
    // operator and hence there is no easy way to remove the weak_ptr<T> from the std::list
    std::shared_ptr<multiAgentExperience::experience::ExperienceObserverInterface> observerToRemove = observer.lock();
    if (observerToRemove) {
        std::list<std::weak_ptr<multiAgentExperience::experience::ExperienceObserverInterface>>::iterator it;
        for (it = m_observers.begin(); it != m_observers.end(); it++) {
            std::shared_ptr<multiAgentExperience::experience::ExperienceObserverInterface> observerToCheck = it->lock();

            // equality operator on shared_ptr<T> doesn't offer a strong guarantee on the equivalence
            // of shared_ptr's and hence owning relationships need to be used in order to compare
            // shared_ptr's
            if (!observerToCheck.owner_before(observerToRemove) && !observerToRemove.owner_before(observerToCheck)) {
                break;
            }
        }

        m_observers.erase(it);
    }
}

void ExperienceManager::clearObservers() {
    LX(DEBUG0, "");

    std::lock_guard<std::mutex> guard(m_mutex);
    m_observers.clear();
}

std::shared_ptr<multiAgentExperience::experience::ExperienceControllerInterface> ExperienceManager::getController(
    const ActorId& actor) {
    LX(DEBUG3, "");

    return ExperienceController::create(shared_from_this(), actor, generateSessionId());
}

void ExperienceManager::notifyObservers() {
    LX(DEBUG3, "");

    auto experiences = getCurrentExperiences();

#ifndef NDEBUG
    std::stringstream dump;
    dump << "\n";
    for (auto& e : experiences) {
        dump << "SessionId: " + std::to_string(e.sessionId) +
                ", ActorId: " + multiAgentExperience::library::utils::getObfuscatedActorId(e.actorId) +
                ", ExperienceId: " + e.experienceId.get() + "\n";
    }
    LX(DEBUG3, dump.str());
#endif

    auto it = m_observers.begin();
    while (it != m_observers.end()) {
        auto observer = it->lock();
        if (observer) {
            notifyObserver(observer, experiences);
            it++;
        } else {
            it = m_observers.erase(it);
        }
    }
}

void ExperienceManager::notifyObserver(
    std::shared_ptr<multiAgentExperience::experience::ExperienceObserverInterface> observer,
    std::vector<multiAgentExperience::experience::Experience> experiences) {
    m_executor->submit([observer, experiences]() { observer->onExperienceChange(experiences); });
}

std::vector<multiAgentExperience::experience::Experience> ExperienceManager::getCurrentExperiences() {
    auto allActivitiesSortedByPriority =
        m_activityManager->getAllActivitiesSortedByPriorityAndActivityId();

    std::vector<multiAgentExperience::experience::Experience> activeExperiences;

    /// iterate through the activity lifecycles in order of their priority and add corresponding
    /// experience if available in the map of active experiences
    auto itr = allActivitiesSortedByPriority.begin();
    while (itr != allActivitiesSortedByPriority.end()) {
        std::shared_ptr<activity::ActivityLifecycle> activityLifecycle = (*itr).lock();
        if (activityLifecycle) {
            if (m_activityIdToExperiencesMap.find(activityLifecycle->getID()) !=
                m_activityIdToExperiencesMap.end()) {
                activeExperiences.push_back(m_activityIdToExperiencesMap[activityLifecycle->getID()]);
            }
        }

        itr++;
    }

    /// currently this logic adds static experiences supported by each agent to the back of
    /// the active experiences list as static experiences are lower priority compared to active
    /// experiences. The relative priority of these static experiences and relative priority of
    /// which agent's static experiences needs to be delivered first is still something that needs
    /// be figured out
    std::map<std::string, std::list<multiAgentExperience::experience::Experience>>::iterator it;
    for (it = m_staticExperiencesMap.begin(); it != m_staticExperiencesMap.end(); it++) {
        std::list<multiAgentExperience::experience::Experience>::iterator experienceIterator;
        for (experienceIterator = it->second.begin(); experienceIterator != it->second.end(); experienceIterator++) {
            activeExperiences.emplace_back(*experienceIterator);
        }
    }

    return activeExperiences;
}

multiAgentExperience::experience::Experience::SessionId ExperienceManager::generateSessionId() {
    static std::atomic<multiAgentExperience::experience::Experience::SessionId> s_sessionCounter{0};
    auto session = s_sessionCounter.fetch_add(1);
    return session;
}

void ExperienceManager::updateStaticExperiences(
    multiAgentExperience::actor::ActorId actorId,
    std::list<multiAgentExperience::experience::Experience> staticExperiences) {
    LX(DEBUG3, "");

    std::lock_guard<std::mutex> guard(m_mutex);

    if (m_staticExperiencesMap.find(actorId.get()) == m_staticExperiencesMap.end()) {
        m_staticExperiencesMap.emplace(actorId.get(), staticExperiences);
    } else {
        m_staticExperiencesMap[actorId.get()] = staticExperiences;
    }

    notifyObservers();
}

}  // namespace experience
}  // namespace library
}  // namespace multiAgentExperience
