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

#include "Experience/ExperienceManager.h"

#include <algorithm>
#include <atomic>
#include <sstream>

#include "Experience/ExperienceController.h"
#include "Utils/Logger/Logger.h"

namespace multiAgentExperience {
namespace library {
namespace experience {

static const std::string MODULE_TAG("ExperienceManager");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

using namespace multiAgentExperience::experience;
using namespace multiAgentExperience::actor;

ExperienceManager::ExperienceManager() : ExperienceManager(std::make_shared<library::utils::threading::Executor>()) {
}

ExperienceManager::ExperienceManager(std::shared_ptr<library::utils::threading::Executor> observerExecutor) :
        m_executor{observerExecutor},
        m_mutex{},
        m_observers{},
        m_activeExperiences{} {
}

void ExperienceManager::startExperience(
    const ActorId& actor,
    const Experience::SessionId& session,
    const ExperienceId& experience) {
    LX(DEBUG3,
       "actor:" + actor.get() + ", sessionId:" + std::to_string(session) + ", experienceID:" + experience.get());

    std::lock_guard<std::mutex> guard(m_mutex);
    auto it = m_activeExperiences.begin();
    while (it != m_activeExperiences.end()) {
        if (it->actorId == actor && it->sessionId == session) {
            it = m_activeExperiences.erase(it);
            LX(DEBUG3, "Found existing experience in session " + std::to_string(session) + " replacing.");
            break;
        } else {
            ++it;
        }
    }
    m_activeExperiences.push_front({actor, session, experience});
    notifyObservers();
}
void ExperienceManager::endExperience(const ActorId& actor, const Experience::SessionId& session) {
    LX(DEBUG3, "actor:" + actor.get() + ", sessionId:" + std::to_string(session));

    std::lock_guard<std::mutex> guard(m_mutex);
    auto it = m_activeExperiences.begin();
    while (it != m_activeExperiences.end()) {
        LX(DEBUG3, "Actor=" + it->actorId.get() + ", session=" + std::to_string(it->sessionId));
        if (it->actorId == actor && it->sessionId == session) {
            it = m_activeExperiences.erase(it);
            notifyObservers();
            return;
        } else {
            ++it;
        }
    }

    LX(ERROR, "actor:" + actor.get() + ", sessionId:" + std::to_string(session) + ", experience not found");
}

void ExperienceManager::clearExperiences() {
    LX(DEBUG3, "");

    std::lock_guard<std::mutex> guard(m_mutex);
    m_activeExperiences.clear();
    notifyObservers();
}

/// ExperienceManagerInterface functions
void ExperienceManager::addObserver(
    std::weak_ptr<multiAgentExperience::experience::ExperienceObserverInterface> observer) {
    LX(DEBUG3, "");

    std::lock_guard<std::mutex> guard(m_mutex);
    m_observers.push_back(observer);
    if (auto obs = observer.lock()) {
        auto experiences = getCurrentExperiences();
        notifyObserver(obs, experiences);
    }
}

void ExperienceManager::clearObservers() {
    LX(DEBUG3, "");

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
        dump << "SessionId: " + std::to_string(e.sessionId) + ", ActorId: " + e.actorId.get() +
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
    return std::vector<multiAgentExperience::experience::Experience>(
        m_activeExperiences.begin(), m_activeExperiences.end());
}

multiAgentExperience::experience::Experience::SessionId ExperienceManager::generateSessionId() {
    static std::atomic<multiAgentExperience::experience::Experience::SessionId> s_sessionCounter{0};
    auto session = s_sessionCounter.fetch_add(1);
    return session;
}

}  // namespace experience
}  // namespace library
}  // namespace multiAgentExperience
