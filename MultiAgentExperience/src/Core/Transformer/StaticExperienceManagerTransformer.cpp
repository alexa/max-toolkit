/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/
#include <algorithm>
#include <sstream>
#include <thread>

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Experience/ExperienceManager.h"

#include "Core/Transformer/StaticExperienceManagerTransformer.h"

#include "Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

static const std::string MODULE_TAG("StaticExperienceManagerTransformer");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

static std::atomic_int id(0);

/// the tuple of static experiences <int, Experience> the index 0 stores the priority of the
/// static experience and index 1 in the tuple stores the actual experience object. Extracting this
/// priority index out explicitly helps with readability
static const int PRIORITY_INDEX = 0;
static const int EXPERIENCE_INDEX = 1;

StaticExperienceManagerTransformer::StaticExperienceManagerTransformer(
    const multiAgentExperience::actor::ActorId& actorId,
    std::shared_ptr<library::experience::ExperienceManager> experienceManager) :
        m_id{id++},
        m_mutex{},
        m_actorId{actorId},
        m_experienceManager{experienceManager},
        m_staticExperiences{} {
    std::stringstream ss;
    ss << "details:"
       << " actorId=" << multiAgentExperience::library::utils::getObfuscatedActorId(actorId)
       << " id=" << m_id;
    LX(DEBUG0, ss.str());
}

StaticExperienceManagerTransformer::~StaticExperienceManagerTransformer() {
    std::stringstream ss;
    ss << "details:"
       << " actorId=" << multiAgentExperience::library::utils::getObfuscatedActorId(m_actorId)
       << " id=" << m_id;
    LX(DEBUG0, ss.str());

    m_experienceManager->clearStaticExperiencesForActor(m_actorId);
}

std::list<multiAgentExperience::experience::Experience> StaticExperienceManagerTransformer::getSortedStaticExperienceList() {
    std::list<multiAgentExperience::experience::Experience> experiences;

    /// the experiences in the list of static experiences are already sorted by priority. This lambda
    /// is only responsible for extracting the static experience object out of the tuple and adding
    /// it to the list of experiences that needs to be sent to experience manager
    auto addExperienceToListLambda =
        [&](const std::tuple<StaticExperienceManagerTransformer::StaticExperiencePriority, multiAgentExperience::experience::Experience>
                staticExperienceTuple) {
            experiences.push_back(std::get<EXPERIENCE_INDEX>(staticExperienceTuple));
        };

    std::for_each(m_staticExperiences.begin(), m_staticExperiences.end(), addExperienceToListLambda);

    return experiences;
}

void StaticExperienceManagerTransformer ::addStaticExperience(
    const multiAgentExperience::experience::ExperienceId& experienceId,
    const StaticExperienceManagerTransformer::StaticExperiencePriority priority) {
    std::stringstream ss;
    ss << "details:"
       << " actorId=" << multiAgentExperience::library::utils::getObfuscatedActorId(m_actorId)
       << " id=" << m_id
       << " experienceId=" << multiAgentExperience::library::utils::getObfuscatedExperienceId(experienceId)
       << " staticExperiencePriority=" << priority;
    LX(DEBUG0, ss.str());

    std::lock_guard<std::mutex> guard(m_mutex);

    /// Create an experience object for the given experienceId
    multiAgentExperience::experience::Experience experience = {
        m_actorId, experience::ExperienceManager::generateSessionId(), experienceId
    };

    /// initially the static experience is just added to the end of the list and then sorted by
    /// priority
    m_staticExperiences.push_back(std::make_tuple(priority, experience));

    /// this comparator will be used to sort the list of static experiences in ascending order of
    /// priority such that the experience at the front of the list is the highest priority experience
    auto comparator =
        [](const std::tuple<int, multiAgentExperience::experience::Experience> staticExperience_1,
           const std::tuple<int, multiAgentExperience::experience::Experience> staticExperience_2) -> bool {
        return std::get<PRIORITY_INDEX>(staticExperience_1) < std::get<PRIORITY_INDEX>(staticExperience_2);
    };

    m_staticExperiences.sort(comparator);

    std::list<multiAgentExperience::experience::Experience> experiences = getSortedStaticExperienceList();

    /// post adding the static experience to the list invoke updateStaticExperiences on
    /// experience manager
    m_experienceManager->updateStaticExperiences(m_actorId, experiences);
}

void StaticExperienceManagerTransformer::removeStaticExperience(
    const multiAgentExperience::experience::ExperienceId& experienceId) {
    std::stringstream ss;
    ss << "details:"
       << " actorId=" << multiAgentExperience::library::utils::getObfuscatedActorId(m_actorId)
       << " id=" << m_id
       << " experienceId=" << multiAgentExperience::library::utils::getObfuscatedExperienceId(experienceId);
    LX(DEBUG0, ss.str());

    std::lock_guard<std::mutex> guard(m_mutex);

    if (m_staticExperiences.empty()) {
        // Don't notify observers if the static experience list is already empty
        LX(DEBUG3, "Static experience list is already empty.");
        return;
    }

    // Retrieve the size of the static experience list before any attempt at removal
    auto preRemovalSize = m_staticExperiences.size();

    auto removePredicate =
        [&](const std::tuple<int, multiAgentExperience::experience::Experience> staticExperienceTuple) -> bool {
        return (std::get<EXPERIENCE_INDEX>(staticExperienceTuple)).experienceId.get() == experienceId.get();
    };

    m_staticExperiences.remove_if(removePredicate);

    if (preRemovalSize == m_staticExperiences.size()) {
        LX(DEBUG3, "Static experience list was not updated.");
        return;
    }

    std::list<multiAgentExperience::experience::Experience> experiences = getSortedStaticExperienceList();

    /// post removing the static experience the update also needs to be communicated to
    /// experience manager
    m_experienceManager->updateStaticExperiences(m_actorId,experiences);
}

void StaticExperienceManagerTransformer::removeAllStaticExperiences() {
    std::stringstream ss;
    ss << "details:"
       << " actorId=" << multiAgentExperience::library::utils::getObfuscatedActorId(m_actorId)
       << " id=" << m_id;
    LX(DEBUG0, ss.str());

    std::lock_guard<std::mutex> guard(m_mutex);

    if (m_staticExperiences.empty()) {
        // Don't notify observers if the static experience list was already empty
        LX(DEBUG3, "Static experience list is already empty.");
        return;
    }

    m_staticExperiences.clear();

    /// post clearing the static experiences the changes need to also be communicated to
    /// experience manager
    m_experienceManager->updateStaticExperiences(m_actorId, std::list<multiAgentExperience::experience::Experience>{});
}

std::list<std::tuple<StaticExperienceManagerTransformer::StaticExperiencePriority, multiAgentExperience::experience::Experience>>
StaticExperienceManagerTransformer::
    getAllStaticExperiences() {
    std::lock_guard<std::mutex> guard(m_mutex);

    return m_staticExperiences;
}

int StaticExperienceManagerTransformer::getId() const {
    return m_id;
}

multiAgentExperience::actor::ActorId StaticExperienceManagerTransformer::getActorId() const {
    return m_actorId;
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience