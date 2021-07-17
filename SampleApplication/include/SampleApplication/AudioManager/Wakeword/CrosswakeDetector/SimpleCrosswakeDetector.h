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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_WAKEWORD_CROSSWAKEDETECTORINTERFACE_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_WAKEWORD_CROSSWAKEDETECTORINTERFACE_H_

#include "ActiveAgentSpeechStoreInterface.h"

#include <memory>
#include <mutex>
#include <regex>
#include <string>
#include <vector>

namespace multiAgentExperience {
namespace sampleApplication {
namespace audioManager {
namespace wakeword {
namespace crosswake {

/**
 * WARNING - This is part of a demo quality implementation of crosswake detection for use as a proof of concept.
 *
 * This functionality emulates Audio Front End (AFE) hardware, and tests if an Agent's speech contains the
 * wakeword of another Agent that may be registered with the MAX Library. Without an AFE, this will result
 * in an active wakeword engine detecting the wakeword, and appear to the application as if the user had
 * said the wakeword. The original Agent will then be interrupted in favor of the Agent whose wakeword it
 * just spoke.
 *
 * This trivial implementation disallows user barge-in on an Agent's speech when another Agent's wakeword
 * is present. This should be used ONLY for demonstration purposes on devices without sufficient hardware,
 * and for the purposes of testing cases where an Agent speaking another Agent's name causes that Agent to
 * interrupt and begin listening.
 */
class SimpleCrosswakeDetector {
public:
    SimpleCrosswakeDetector();
    void addAgentSpeechStore(std::shared_ptr<ActiveAgentSpeechStoreInterface> agentSpeechStore);
    void removeAgentSpeechStore(std::shared_ptr<ActiveAgentSpeechStoreInterface> agentSpeechStore);
    bool canWake(const std::string& wakeword);

private:
    std::vector<std::shared_ptr<ActiveAgentSpeechStoreInterface>> m_agentSpeechStores;
    std::mutex m_storeMutex;

    std::regex createRegex(const std::string& wakeword);
};

}  // namespace crosswake
}  // namespace wakeword
}  // namespace audioManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_WAKEWORD_CROSSWAKEDETECTORINTERFACE_H_
