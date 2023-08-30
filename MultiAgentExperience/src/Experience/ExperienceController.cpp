/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Experience/ExperienceController.h"

#include <sstream>

#include "Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace library {
namespace experience {

static const std::string MODULE_TAG("ExperienceController");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

using namespace multiAgentExperience::experience;

std::shared_ptr<experience::ExperienceControllerInterface> ExperienceController::create(
    std::weak_ptr<ExperienceManager> manager,
    const multiAgentExperience::actor::ActorId& actor,
    const multiAgentExperience::experience::Experience::SessionId& session) {
    return std::shared_ptr<experience::ExperienceControllerInterface>(
        new ExperienceController(manager, actor, session));
}

ExperienceController::~ExperienceController() {
    invalidate();
}

void ExperienceController::startExperience(const ExperienceId& experience) {
    std::stringstream ss;
    ss << "details:"
       << " experienceId=" << multiAgentExperience::library::utils::getObfuscatedExperienceId(experience);
    LX(DEBUG0, ss.str());
    if (auto manager = m_manager.lock()) {
        manager->startExperience(m_actor, m_experienceControllerActivityId, m_session, experience);
        m_experienceIsActive = true;

    } else {
        LX(DEBUG3, "Manager is null");
    }
}

void ExperienceController::endExperience() {
    LX(DEBUG0, "");
    if (m_experienceIsActive) {
        if (auto manager = m_manager.lock()) {
            manager->endExperience(m_actor, m_session);
            m_experienceIsActive = false;
        } else {
            LX(DEBUG3, "Manager is null");
        }
    }
}

void ExperienceController::invalidate() {
    LX(DEBUG0, "");
    if (m_experienceIsActive) {
        endExperience();
    }
    m_manager.reset();
}

void ExperienceController::setExperienceControllerActivityId(const activity::ActivityID
                                                                 experienceControllerActivityId) {
    m_experienceControllerActivityId = experienceControllerActivityId;
}

ExperienceController::ExperienceController(
    std::weak_ptr<ExperienceManager> manager,
    const multiAgentExperience::actor::ActorId& actor,
    const multiAgentExperience::experience::Experience::SessionId& session) :
        m_manager(manager),
        m_experienceIsActive{false},
        m_actor(actor),
        m_experienceControllerActivityId{0},
        m_session(session) {
}

}  // namespace experience
}  // namespace library
}  // namespace multiAgentExperience
