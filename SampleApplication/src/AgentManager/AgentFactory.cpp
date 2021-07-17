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

#include "SampleApplication/AgentManager/AgentFactory.h"

#include "SampleApplication/AgentManager/Alexa/AlexaAgentFactory.h"
#include "SampleApplication/AgentManager/Computer/ComputerAgentFactory.h"
#include "SampleApplication/Utils/RadiantLogger.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace agentManager {

/// Metadata parameters that will be passed into our logging system.
static const std::string MODULE_TAG("AgentFactory");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, MODULE_TAG, __func__, message)

/// Local definition for the Alexa agent name.
static const std::string ALEXA_AGENT_NAME = "alexa";

/// Local definition for the Computer agent name.
static const std::string COMPUTER_AGENT_NAME = "computer";

/**
 * Utility function to create an Alexa agent.
 *
 * @param config The config file to be used.
 * @param audioFormat The audio format to use.
 * @param audioDataAccessProvider The provider of the underlying audio data buffers.
 * @param crosswakeDetector The detector to prevent cross wakes.
 * @param metadataCache kwd metadata cache that shall be used upon wakeword detection.
 * @return A new Alexa agent if successful, otherwise nullptr.
 */
static std::shared_ptr<MAX::agent::Agent> createAlexaAgent(
    const AgentsConfig::AgentConfig& config,
    const MAX::audio::AudioFormat& audioFormat,
    std::shared_ptr<utils::AudioDataDirectAccessInterface> audioDataAccessProvider,
    std::shared_ptr<audioManager::wakeword::crosswake::SimpleCrosswakeDetector> crosswakeDetector,
    std::shared_ptr<audioManager::wakeword::WakewordMetadataCache> metadataCache) {
    LX(DEBUG3, "");

    return alexa::AlexaAgentFactory::create(
        config, audioFormat, audioDataAccessProvider, crosswakeDetector, metadataCache);
}

/**
 * Utility function to create a Computer agent.
 *
 * @param config The config file to be used.
 * @param audioFormat The audio format to use.
 * @param audioDataAccessProvider The provider of the underlying audio data buffers.
 * @param crosswakeDetector The detector to prevent cross wakes.
 * @return A new Computer agent if successful, otherwise nullptr.
 */
static std::shared_ptr<MAX::agent::Agent> createComputerAgent(
    const AgentsConfig::AgentConfig& config,
    const MAX::audio::AudioFormat& audioFormat,
    std::shared_ptr<utils::AudioDataDirectAccessInterface> audioDataAccessProvider,
    std::shared_ptr<audioManager::wakeword::crosswake::SimpleCrosswakeDetector> crosswakeDetector) {
    LX(DEBUG3, "");

    return computer::ComputerAgentFactory::create(config, audioFormat, audioDataAccessProvider, crosswakeDetector);
}

std::shared_ptr<MAX::agent::Agent> AgentFactory::createAgent(
    const AgentsConfig::AgentConfig& config,
    const audio::AudioFormat& audioFormat,
    std::shared_ptr<utils::AudioDataDirectAccessInterface> audioDataAccessProvider,
    std::shared_ptr<audioManager::wakeword::crosswake::SimpleCrosswakeDetector> crosswakeDetector,
    std::shared_ptr<audioManager::wakeword::WakewordMetadataCache> metadataCache) {
    LX(DEBUG3, "");

    if (ALEXA_AGENT_NAME == config.name) {
        return createAlexaAgent(config, audioFormat, audioDataAccessProvider, crosswakeDetector, metadataCache);
    } else if (COMPUTER_AGENT_NAME == config.name) {
        return createComputerAgent(config, audioFormat, audioDataAccessProvider, crosswakeDetector);
    }

    LX(ERROR, "Unknown agent name : " + config.name);
    return nullptr;
}
}  // namespace agentManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
