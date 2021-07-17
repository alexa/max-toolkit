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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_EXPERIENCEMANAGER_EXPERIENCEMANAGER_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_EXPERIENCEMANAGER_EXPERIENCEMANAGER_H_

#include <MultiAgentExperience/Experience/ExperienceManagerInterface.h>

#include "SampleApplication/ExperienceManager/ExperienceRendererInterface.h"

#include <memory>
#include <set>

namespace multiAgentExperience {
namespace sampleApplication {
namespace experienceManager {

namespace MAX = multiAgentExperience;

/**
 * This class handles management of MAX Experiences and their rendering, whether to console or other hardware.
 */
class ExperienceManager {
public:
    /**
     * Creates an @c ExperienceManager.
     *
     * @param maxExperienceManager The MAX ExperienceManager to be used.
     * @return A handle to a @c ExperienceManager if successful, otherwise nullptr.
     */
    static std::unique_ptr<ExperienceManager> create(
        std::shared_ptr<MAX::experience::ExperienceManagerInterface> maxExperienceManager);

    /**
     * Add an Experience renderer.
     *
     * @param renderer The renderere to add.
     */
    void addRenderer(std::shared_ptr<ExperienceRendererInterface> renderer);

    /**
     * Remove an Experience renderer.
     *
     * @param renderer The renderer to remove.
     */
    void removeRenderer(std::shared_ptr<ExperienceRendererInterface> renderer);

private:
    /**
     * Constructor.
     *
     * @param maxExperienceManager A handle to the MAX ExperienceManager.
     */
    ExperienceManager(std::shared_ptr<MAX::experience::ExperienceManagerInterface> maxExperienceManager);

    /**
     * Utility function to update our renderers with the MAX Library.
     */
    void updateActiveRenderers();

    /// A handle to the MAX ExperienceManager.
    std::shared_ptr<MAX::experience::ExperienceManagerInterface> m_maxExperienceManager;
    /// Our renderers.
    std::set<std::shared_ptr<ExperienceRendererInterface>> m_renderers;
};

}  // namespace experienceManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_EXPERIENCEMANAGER_EXPERIENCEMANAGER_H_
