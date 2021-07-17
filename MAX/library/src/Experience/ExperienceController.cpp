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

#include "Experience/ExperienceController.h"
#include "Utils/Logger/Logger.h"

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
    LX(DEBUG3, "");
    if (auto manager = m_manager.lock()) {
        manager->startExperience(m_actor, m_session, experience);
        m_experienceIsActive = true;

    } else {
        LX(ERROR, "Manager is null");
    }
}

void ExperienceController::endExperience() {
    LX(DEBUG3, "");
    if (m_experienceIsActive) {
        if (auto manager = m_manager.lock()) {
            manager->endExperience(m_actor, m_session);
            m_experienceIsActive = false;
        } else {
            LX(ERROR, "Manager is null");
        }
    }
}

void ExperienceController::invalidate() {
    if (m_experienceIsActive) {
        endExperience();
    }
    m_manager.reset();
}

ExperienceController::ExperienceController(
    std::weak_ptr<ExperienceManager> manager,
    const multiAgentExperience::actor::ActorId& actor,
    const multiAgentExperience::experience::Experience::SessionId& session) :
        m_manager(manager),
        m_experienceIsActive{false},
        m_actor(actor),
        m_session(session) {
}

}  // namespace experience
}  // namespace library
}  // namespace multiAgentExperience
