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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_APPLICATION_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_APPLICATION_H_

#include <memory>
#include <string>

#include <MultiAgentExperience/Application/MAXInterface.h>

#include "SampleApplication/AgentManager/AgentManager.h"
#include "SampleApplication/AudioManager/AudioManager.h"
#include "SampleApplication/AudioManager/Wakeword/CrosswakeDetector/SimpleCrosswakeDetector.h"
#include "SampleApplication/ExperienceManager/ExperienceManager.h"
#include "SampleApplication/UIManager/UIManager.h"
#include "SampleApplication/UniversalDeviceCommandManager/Console/ConsoleCommandRenderer.h"
#include "SampleApplication/UniversalDeviceCommandManager/UniversalDeviceCommandManager.h"

namespace multiAgentExperience {
namespace sampleApplication {

/**
 * This class encapsulates all logic which may vary across partner implementations. Each major aspect of a
 * multi-agent application is decoupled here, in similar spirit to the MAX Library interfaces. In particular:
 *
 *  * Agent management
 *  * Audio management
 *  * Experience management
 *  * UI management
 *
 * This separation of concerns is intended to benefit developers who may wish to add a new Agent or other element
 * without needing to modify, or be concerned with, other parts of the application.
 */
class Application {
public:
    /**
     * Creates an instance of our Application.
     *
     * @param maxConfigPath Path to the JSON file providing runtime configuration.
     * @return A pointer to an application if successful, otherwise nullptr.
     */
    static std::unique_ptr<Application> create(const std::string& maxConfigPath);

    /**
     * Begins the UI menu system, allowing user interaction with the application. This method will continue until the
     * user chooses to exit the application.
     */
    void run();

private:
    /**
     * Constructor.
     *
     * @param maxInterface A handle to the @c MAXInterface this application is using.
     */
    Application(
        std::shared_ptr<audioManager::wakeword::crosswake::SimpleCrosswakeDetector> crosswakeDetector,
        std::shared_ptr<application::MAXInterface> maxInterface);

    /**
     * A helper method to initialize our subsystems.
     *
     * @param parsedJsonDocumentRoot A rapidjson document which has been successfully parsed.
     * @return whether initialization was successful.
     */
    bool initialize(const rapidjson::Document& parsedJsonDocumentRoot);

    /// Our crosswake detector component.
    std::shared_ptr<audioManager::wakeword::crosswake::SimpleCrosswakeDetector> m_crosswakeDetector;

    /// A handle to the @c MAXInterface.
    std::shared_ptr<application::MAXInterface> m_maxInterface;

    /// Our agent manager component.
    std::shared_ptr<agentManager::AgentManager> m_agentManager;

    /// Our audio manager component.
    std::shared_ptr<audioManager::AudioManager> m_audioManager;

    /// Our experience manager component.
    std::shared_ptr<experienceManager::ExperienceManager> m_experienceManager;

    /// Our UDC manager component.
    std::shared_ptr<universalDeviceCommandManager::UniversalDeviceCommandManager> m_udcManager;

    std::shared_ptr<universalDeviceCommandManager::console::ConsoleCommandRenderer> m_commandRenderer;

    /// Our UI manager component.
    std::shared_ptr<uiManager::UIManager> m_uiManager;
};

}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_APPLICATION_H_
