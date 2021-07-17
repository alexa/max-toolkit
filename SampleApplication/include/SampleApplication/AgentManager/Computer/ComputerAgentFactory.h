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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AGENTMANAGER_COMPUTERAGENTFACTORY_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AGENTMANAGER_COMPUTERAGENTFACTORY_H_

#include <memory>
#include <vector>

#include <MultiAgentExperience/Agent/Agent.h>
#include <MultiAgentExperience/Audio/AudioReaderInterface.h>

#include "SampleApplication/AgentManager/AgentsConfig.h"
#include "SampleApplication/AudioManager/Wakeword/CrosswakeDetector/SimpleCrosswakeDetector.h"
#include "SampleApplication/Utils/AudioDataDirectAccessInterface.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace agentManager {
namespace computer {

namespace MAX = multiAgentExperience;

/**
 * A class which should be used to instantiate the Computer Agent. Note that this class returns a singleton instance
 * upon repeated calls.
 */
class ComputerAgentFactory {
public:
    /**
     * Creates a Computer Agent.
     *
     * @param config The config to be used.
     * @param audioFormat The audio format to be used.
     * @param audioDataAccessProvider The provider of the underlying audio data buffers.
     * @param simpleCrosswakeDetector The detector to prevent cross wakes.
     * @return A Computer Agent if successful, otherwise nullptr.
     */
    static std::shared_ptr<MAX::agent::Agent> create(
        const AgentsConfig::AgentConfig& config,
        const MAX::audio::AudioFormat& audioFormat,
        std::shared_ptr<utils::AudioDataDirectAccessInterface> audioDataAccessProvider,
        std::shared_ptr<audioManager::wakeword::crosswake::SimpleCrosswakeDetector> simpleCrosswakeDetector);
};

}  // namespace computer
}  // namespace agentManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AGENTMANAGER_COMPUTERAGENTFACTORY_H_
