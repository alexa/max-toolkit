/*
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Amazon Software License (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *     https://aws.amazon.com/asl/
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include "SampleApplication/AudioManager/Wakeword/CrosswakeDetector/SimpleCrosswakeDetector.h"

#include "SampleApplication/Utils/RadiantLogger.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace audioManager {
namespace wakeword {
namespace crosswake {

const std::string REGEX_WHOLE_WORD = "\\b";

/// Metadata parameters that will be passed into our logging system.
static const std::string MODULE_TAG("SimpleCrosswakeDetector");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, MODULE_TAG, __func__, message)

SimpleCrosswakeDetector::SimpleCrosswakeDetector() : m_agentSpeechStores{} {
}

void SimpleCrosswakeDetector::addAgentSpeechStore(std::shared_ptr<ActiveAgentSpeechStoreInterface> agentSpeechStore) {
    std::unique_lock<std::mutex> lock(m_storeMutex);
    m_agentSpeechStores.push_back(agentSpeechStore);
}

void SimpleCrosswakeDetector::removeAgentSpeechStore(
    std::shared_ptr<ActiveAgentSpeechStoreInterface> agentSpeechStore) {
    std::unique_lock<std::mutex> lock(m_storeMutex);
    m_agentSpeechStores.erase(
        std::remove(m_agentSpeechStores.begin(), m_agentSpeechStores.end(), agentSpeechStore),
        m_agentSpeechStores.end());
}

bool SimpleCrosswakeDetector::canWake(const std::string& wakeword) {
#ifdef ENABLE_DEMO_ONLY_SOFTWARE_CROSSWAKE_DETECTION
    LX(WARN,
       "ENABLE_DEMO_ONLY_SOFTWARE_CROSSWAKE_DETECTION is enabled. For a non-demo application a real "
       "cross wake solution must be developed.");
    std::unique_lock<std::mutex> lock(m_storeMutex);
    auto regex = createRegex(wakeword);
    for (auto speechStore : m_agentSpeechStores) {
        auto speech = speechStore->getActiveAgentSpeech();
        if (std::regex_search(speech, regex)) {
            LX(DEBUG3, "Wake rejected.");
            return false;
        }
    }
#endif
    return true;
}

std::regex SimpleCrosswakeDetector::createRegex(const std::string& wakeword) {
    std::string pattern = REGEX_WHOLE_WORD + wakeword + REGEX_WHOLE_WORD;
    auto regex = std::regex(pattern, std::regex_constants::icase);
    return regex;
}

}  // namespace crosswake
}  // namespace wakeword
}  // namespace audioManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience