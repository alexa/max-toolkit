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

#include "SampleApplication/AgentManager/AgentManager.h"

#include "SampleApplication/AgentManager/AgentFactory.h"
#include "SampleApplication/Utils/RadiantLogger.h"
#include "SampleApplication/Utils/StringUtils.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace agentManager {

/// Metadata parameters that will be passed into our logging system.
static const std::string MODULE_TAG("AgentManager");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, MODULE_TAG, __func__, message)

std::shared_ptr<AgentManager::AgentDetail> AgentManager::getAgentDetail(const MAX::actor::ActorId& id) {
    for (auto agentDetail : m_agentDetails) {
        if (agentDetail->summary.id == id) {
            return agentDetail;
        }
    }

    return nullptr;
}

std::shared_ptr<AgentManager::AgentDetail> AgentManager::getAgentDetailByWakeword(const std::string& wakeword) {
    std::string wakewordLower = utils::stringToLowerCase(wakeword);
    for (auto agentDetail : m_agentDetails) {
        for (auto ww : agentDetail->summary.wakewords) {
            if (ww == wakewordLower) {
                return agentDetail;
            }
        }
    }

    return nullptr;
}

bool AgentManager::AgentSummary::operator<(const AgentManager::AgentSummary& rhs) const {
    return static_cast<std::string>(id) < static_cast<std::string>(rhs.id);
}

bool AgentManager::AgentDetail::operator<(const AgentManager::AgentDetail& rhs) const {
    return static_cast<std::string>(summary.id) < static_cast<std::string>(rhs.summary.id);
}

std::unique_ptr<AgentManager> AgentManager::create(
    std::shared_ptr<MAX::agent::AgentManagerInterface> maxAgentManager,
    const rapidjson::Document& parsedJsonDocumentRoot,
    const MAX::audio::AudioFormat& audioFormat,
    std::shared_ptr<utils::AudioDataDirectAccessInterface> audioDataAccessProvider,
    std::shared_ptr<audioManager::wakeword::crosswake::SimpleCrosswakeDetector> crosswakeDetector,
    std::shared_ptr<audioManager::wakeword::WakewordMetadataCache> metadataCache) {
    LX(DEBUG3, "");

    if (!maxAgentManager) {
        LX(ERROR, "maxAgentManager is nullptr.");
        return nullptr;
    }

    if (!audioDataAccessProvider) {
        LX(ERROR, "audioDataAccessProvider is nullptr.");
        return nullptr;
    }

    if (!metadataCache) {
        LX(ERROR, "metadataCache is nullptr.");
        return nullptr;
    }

    AgentsConfig configs;
    if (!parseJSONConfig(parsedJsonDocumentRoot, &configs)) {
        LX(ERROR, "Unable to parse JSON config.");
        return nullptr;
    }

    auto agentManager = std::unique_ptr<AgentManager>(new AgentManager(maxAgentManager));
    if (!agentManager->initialize(configs, audioFormat, audioDataAccessProvider, crosswakeDetector, metadataCache)) {
        LX(ERROR, "Unable to initialize.");
        return nullptr;
    }

    return agentManager;
}

AgentManager::AgentManager(std::shared_ptr<MAX::agent::AgentManagerInterface> maxAgentManager) :
        m_agentManager{maxAgentManager} {
}

bool AgentManager::initialize(
    const AgentsConfig& configs,
    const MAX::audio::AudioFormat& audioFormat,
    std::shared_ptr<utils::AudioDataDirectAccessInterface> audioDataAccessProvider,
    std::shared_ptr<audioManager::wakeword::crosswake::SimpleCrosswakeDetector> crosswakeDetector,
    std::shared_ptr<audioManager::wakeword::WakewordMetadataCache> metadataCache) {
    LX(DEBUG3, "");

    for (auto& config : configs.agentConfigs) {
        std::shared_ptr<MAX::agent::Agent> agent =
            AgentFactory::createAgent(config, audioFormat, audioDataAccessProvider, crosswakeDetector, metadataCache);
        if (!agent) {
            LX(ERROR, "Failed to create Agent : " + config.name);
            continue;
        }

        if (!m_agentManager->registerAgent(agent)) {
            LX(ERROR, "Unable to register Agent with MAX : " + config.name);
            return false;
        }

        AgentSummary summary;
        summary.id = agent->getId();
        summary.wakewords.insert(agent->getWakeword());
        summary.enabled = true;

        auto detail = std::make_shared<AgentDetail>();
        detail->summary = summary;
        detail->agent = agent;

        m_agentDetails.push_back(detail);
    }

    std::sort(
        m_agentDetails.begin(),
        m_agentDetails.end(),
        [](std::shared_ptr<AgentDetail> const& a, std::shared_ptr<AgentDetail> const& b) {
            return a->summary.id.get() < b->summary.id.get();
        });

    return true;
}

std::set<AgentManager::AgentSummary> AgentManager::getAgentSummaries() {
    std::set<AgentManager::AgentSummary> summaries;
    for (auto& detail : m_agentDetails) {
        summaries.insert(detail->summary);
    }

    return summaries;
}

bool AgentManager::enableAgent(const MAX::actor::ActorId& id) {
    LX(DEBUG3, "");

    auto agentDetail = getAgentDetail(id);
    if (!agentDetail) {
        LX(ERROR, "Could not find agent with id : " + static_cast<std::string>(id));
        return false;
    }

    if (agentDetail->summary.enabled) {
        LX(ERROR, "Agent already enabled : " + static_cast<std::string>(id));
        return false;
    }

    if (!m_agentManager->registerAgent(agentDetail->agent)) {
        LX(ERROR, "Unable to register agent with MAX : " + static_cast<std::string>(id));
        return false;
    }

    agentDetail->summary.enabled = true;
    return true;
}

bool AgentManager::disableAgent(const MAX::actor::ActorId& id) {
    LX(DEBUG3, "");

    auto agentDetail = getAgentDetail(id);
    if (!agentDetail) {
        LX(ERROR, "Could not find agent with name : " + static_cast<std::string>(id));
        return false;
    }

    if (!agentDetail->summary.enabled) {
        LX(ERROR, "Agent already disabled : " + static_cast<std::string>(id));
        return false;
    }

    m_agentManager->deregisterAgent(agentDetail->agent);
    agentDetail->summary.enabled = false;
    return true;
}

void AgentManager::invokeTapToTalk(std::size_t agentIndex) {
    if (agentIndex >= 0 && agentIndex < m_agentDetails.size()) {
        LX(DEBUG3, "Invoking tap to talk for Agent #" + std::to_string(agentIndex + 1));
        m_agentDetails[agentIndex]->agent->onTapDetected();
    } else {
        LX(ERROR, "No agent assigned for the specified index: " + std::to_string(agentIndex));
    }
}

void AgentManager::invokeGesture(GestureType gesture, const std::string& wakeword) {
    LX(DEBUG3, "");

    if (GestureType::TAP != gesture) {
        LX(ERROR, "Gesture not currently handled.");
        return;
    }

    auto agentDetail = getAgentDetailByWakeword(wakeword);

    if (!agentDetail) {
        LX(ERROR, "Could not find agent with wakeword:" + wakeword);
        return;
    }

    agentDetail->agent->onTapDetected();
}

bool hasWakeword(const AgentManager::AgentSummary& summary) {
    for (const auto& wakeword : summary.wakewords) {
        if (!wakeword.empty()) {
            return true;
        }
    }
    return false;
}

}  // namespace agentManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
