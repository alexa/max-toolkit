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

#include "SampleApplication/AgentManager/Alexa/AlexaAgentFactory.h"
#include "SampleApplication/AgentManager/Alexa/AlexaActiveAgentSpeechStore.h"

#include "SampleApplication/Utils/RadiantLogger.h"
#include "SampleApplication/AgentManager/Alexa/DefaultClientFactory.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace agentManager {
namespace alexa {

/// Metadata parameters that will be passed into our logging system.
static const std::string MODULE_TAG("AlexaAgentFactory");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, MODULE_TAG, __func__, message)

std::shared_ptr<MAX::agent::Agent> AlexaAgentFactory::create(
    const AgentsConfig::AgentConfig& config,
    const audio::AudioFormat& audioFormat,
    std::shared_ptr<utils::AudioDataDirectAccessInterface> audioDataAccessProvider,
    std::shared_ptr<audioManager::wakeword::crosswake::SimpleCrosswakeDetector> crosswakeDetector,
    std::shared_ptr<audioManager::wakeword::WakewordMetadataCache> metadataCache) {
    LX(DEBUG3, "");

    static std::shared_ptr<alexaClientSDK::defaultClient::DefaultClient> defaultClient;

    if (!defaultClient) {
        LX(DEBUG3, "creating.");
        auto agentSpeechStore = std::make_shared<AlexaActiveAgentSpeechStore>();
        crosswakeDetector->addAgentSpeechStore(agentSpeechStore);
        defaultClient = DefaultClientFactory::create(config, audioDataAccessProvider, agentSpeechStore, metadataCache);
        if (!defaultClient) {
            LX(ERROR, "Failed to create DefaultClient.");
            return nullptr;
        }
    }

    return defaultClient;
}
}  // namespace alexa
}  // namespace agentManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
