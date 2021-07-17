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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AGENTMANAGER_AGENTFACTORY_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AGENTMANAGER_AGENTFACTORY_H_

#include <memory>

#include <MultiAgentExperience/Agent/Agent.h>
#include <MultiAgentExperience/Audio/AudioFormat.h>

#include "SampleApplication/AgentManager/AgentsConfig.h"
#include "SampleApplication/Utils/AudioDataDirectAccessInterface.h"
#include "SampleApplication/AudioManager/Wakeword/WakewordMetadataCache.h"
#include "SampleApplication/AudioManager/Wakeword/CrosswakeDetector/SimpleCrosswakeDetector.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace agentManager {

namespace MAX = multiAgentExperience;

/**
 * A class which should be used to instantiate agents.
 */
class AgentFactory {
public:
    /**
     * A method which creates an agent based upon input parameters.
     *
     * @param config The config to be used.
     * @param audioFormat The audio format.
     * @param audioDataAccessProvider The provider of the underlying audio data buffers.
     * @param crosswakeDetector The detector to prevent cross wakes.
     * @param metadataCache kwd metadata cache that shall be used upon wakeword detection.
     * @return An @c AgentFactory object if successful, otherwise nullptr.
     */
    static std::shared_ptr<MAX::agent::Agent> createAgent(
        const AgentsConfig::AgentConfig& config,
        const MAX::audio::AudioFormat& audioFormat,
        std::shared_ptr<utils::AudioDataDirectAccessInterface> audioDataAccessProvider,
        std::shared_ptr<audioManager::wakeword::crosswake::SimpleCrosswakeDetector> crosswakeDetector,
        std::shared_ptr<audioManager::wakeword::WakewordMetadataCache> metadataCache);
};

}  // namespace agentManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AGENTMANAGER_AGENTFACTORY_H_
