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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AGENTMANAGER_AGENTMANAGER_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AGENTMANAGER_AGENTMANAGER_H_

#include <memory>
#include <set>

#include <MultiAgentExperience/Agent/AgentManagerInterface.h>
#include <MultiAgentExperience/Audio/AudioFormat.h>

#include <rapidjson/document.h>
#include <SampleApplication/AudioManager/Wakeword/CrosswakeDetector/SimpleCrosswakeDetector.h>

#include "SampleApplication/AgentManager/AgentsConfig.h"
#include "SampleApplication/AgentManager/GestureHandlerInterface.h"
#include "SampleApplication/AudioManager/Wakeword/WakewordMetadataCache.h"
#include "SampleApplication/Utils/AudioDataDirectAccessInterface.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace agentManager {

namespace MAX = multiAgentExperience;

/**
 * This class takes care of Agent management, from instantiation from config data, registering with the MAX library,
 * and providing access to summarized data without exposing direct Agent APIs.
 */
class AgentManager : public GestureHandlerInterface {
public:
    /**
     * A utility structure reflecting metadata of a managed Agent.
     */
    struct AgentSummary {
        /**
         * Constructor.
         */
        AgentSummary() : id{""}, enabled{false} {
        }

        /// The Id of the agent.
        MAX::actor::ActorId id;
        /// The wakewords which this agent responds to.
        std::set<std::string> wakewords;
        /// Whether the agent is enabled.
        bool enabled;

        /**
         * Comparator function.
         *
         * @param rhs Element to be compared.
         * @return Whether this object is less than @c rhs.
         */
        bool operator<(const AgentSummary& rhs) const;
    };

    /**
     * Create an @c AgentManager object.
     *
     * @param maxAgentManager The MAX AgentManager.
     * @param parsedJsonDocumentRoot The JSON document to parse for configuration.
     * @param audioFormat The audio format to use.
     * @param audioDataAccessProvider The provider of the underlying audio data buffers.
     * @param crosswakeDetector The detector to prevent cross wakes.
     * @param metadataCache kwd metadata cache that shall be used upon wakeword detection.
     * @return An @c AgentManager object if successful, otherwise nullptr.
     */
    static std::unique_ptr<AgentManager> create(
        std::shared_ptr<MAX::agent::AgentManagerInterface> maxAgentManager,
        const rapidjson::Document& parsedJsonDocumentRoot,
        const MAX::audio::AudioFormat& audioFormat,
        std::shared_ptr<utils::AudioDataDirectAccessInterface> audioDataAccessProvider,
        std::shared_ptr<audioManager::wakeword::crosswake::SimpleCrosswakeDetector> crosswakeDetector,
        std::shared_ptr<audioManager::wakeword::WakewordMetadataCache> metadataCache);

    /// @name GestureHandlerInterface method overrides.
    /// @{
    void invokeGesture(GestureType gesture, const std::string& wakeword) override;
    /// @}

    /**
     * Returns a collection of @c AgentSummary objects, reflecting all currently managet Agents.
     * @return A collection of @c AgentSummary objects, reflecting all currently managet Agents.
     */
    std::set<AgentSummary> getAgentSummaries();

    /**
     * Enables an Agent.
     *
     * @param agentName The agent name to enable.
     * @return Whether the agent was successfully enabled.
     */
    bool enableAgent(const MAX::actor::ActorId& agentName);

    /**
     * Disables an Agent.
     *
     * @param agentName The agent name to disable.
     * @return Whether the agent was successfully disabled.
     */
    bool disableAgent(const MAX::actor::ActorId& agentName);

    // TODO: This is a short-term solution to handle user input for Tap-To-Talk. Remove under VII-350.
    void invokeTapToTalk(std::size_t agentIndex);

private:
    /**
     * A utility structure for internal management of Agents, ensuring a single source of truth for all data elements.
     * TODO: Migrate this into the MAX Library, since it is somewhat redundant, under VII-351.
     */
    struct AgentDetail {
        /// The Agent summary.
        AgentSummary summary;
        /// The actual Agent.
        std::shared_ptr<MAX::agent::Agent> agent;

        /**
         * Comparator function.
         *
         * @param rhs Element to be compared.
         * @return Whether this object is less than @c rhs.
         */
        bool operator<(const AgentDetail& rhs) const;
    };

    /**
     * Constructor.
     *
     * @param maxAgentManager The MAX Agent Manager.
     */
    AgentManager(std::shared_ptr<MAX::agent::AgentManagerInterface> maxAgentManager);

    /**
     * Initializes this object.
     *
     * @param configs The agent configurations to use.
     * @param audioFormat The audio format to use.
     * @param audioDataAccessProvider The provider of the underlying audio data buffers.
     * @param crosswakeDetector The detector to prevent cross wakes.
     * @param metadataCache kwd metadata cache that shall be used upon wakeword detection.
     * @return whether initialization was successful.
     */
    bool initialize(
        const AgentsConfig& configs,
        const MAX::audio::AudioFormat& audioFormat,
        std::shared_ptr<utils::AudioDataDirectAccessInterface> audioDataAccessProvider,
        std::shared_ptr<audioManager::wakeword::crosswake::SimpleCrosswakeDetector> crosswakeDetector,
        std::shared_ptr<audioManager::wakeword::WakewordMetadataCache> metadataCache);

    /**
     * Utility method to acquire an agent detail given its name.
     * @param id The id of the agent.
     * @return The Agent detail if successful, otherwise nullptr.
     */
    std::shared_ptr<AgentDetail> getAgentDetail(const MAX::actor::ActorId& id);

    /**
     * Utility method to acquire an agent detail given its wakeword.
     * @param agentName The wakeword of the agent.
     * @return The Agent detail if successful, otherwise nullptr.
     */
    std::shared_ptr<AgentDetail> getAgentDetailByWakeword(const std::string& wakeword);

    /// Our collection of Agent details.
    std::vector<std::shared_ptr<AgentDetail>> m_agentDetails;
    /// The MAX Agent Manager.
    std::shared_ptr<MAX::agent::AgentManagerInterface> m_agentManager;
};

/**
 * Returns whether or not the agent summary describes an agent with one or more configured wakewords.
 *
 * @param summary The summary to check for wakewords.
 * @return  Whether or not the agent summary describes an agent with one or more configured wakewords.
 */
bool hasWakeword(const AgentManager::AgentSummary& summary);

}  // namespace agentManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AGENTMANAGER_AGENTMANAGER_H_
