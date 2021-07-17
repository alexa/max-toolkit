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

#include "SampleApplication/ExperienceManager/ExperienceManager.h"
#include "SampleApplication/Utils/RadiantLogger.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace experienceManager {

/// Metadata parameters that will be passed into our logging system.
static const std::string MODULE_TAG("ExperienceManager");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, MODULE_TAG, __func__, message)

std::unique_ptr<ExperienceManager> ExperienceManager::create(
    std::shared_ptr<MAX::experience::ExperienceManagerInterface> maxExperienceManager) {
    LX(DEBUG3, "");

    if (!maxExperienceManager) {
        LX(ERROR, "maxExperienceManager is nullptr.");
        return nullptr;
    }

    auto experienceManager = std::unique_ptr<ExperienceManager>(new ExperienceManager(maxExperienceManager));

    return experienceManager;
}

ExperienceManager::ExperienceManager(
    std::shared_ptr<MAX::experience::ExperienceManagerInterface> maxExperienceManager) {
    m_maxExperienceManager = maxExperienceManager;
}

void ExperienceManager::addRenderer(std::shared_ptr<ExperienceRendererInterface> renderer) {
    LX(DEBUG3, "");

    if (!renderer) {
        LX(ERROR, "renderer is nullptr.");
        return;
    }

    if (m_renderers.find(renderer) != m_renderers.end()) {
        LX(ERROR, "Unable to add renderer, renderer already present.");
        return;
    }

    LX(DEBUG3, "Adding renderer");

    m_renderers.insert(renderer);
    updateActiveRenderers();
}

void ExperienceManager::removeRenderer(std::shared_ptr<ExperienceRendererInterface> renderer) {
    LX(DEBUG3, "");

    if (!renderer) {
        LX(ERROR, "renderer is nullptr.");
        return;
    }

    if (m_renderers.find(renderer) == m_renderers.end()) {
        LX(ERROR, "Unable to remove renderer, renderer not present.");
        return;
    }

    LX(DEBUG3, "Removing renderer.");

    m_renderers.erase(renderer);
    updateActiveRenderers();
}

void ExperienceManager::updateActiveRenderers() {
    LX(DEBUG3, "");

    if (m_renderers.empty()) {
        LX(DEBUG3, "No renderers.");
        return;
    }

    m_maxExperienceManager->clearObservers();
    for (auto& renderer : m_renderers) {
        LX(DEBUG3, "Registering observer with MAX.");
        m_maxExperienceManager->addObserver(renderer);
    }
}

}  // namespace experienceManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
