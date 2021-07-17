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


#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AGENTMANAGER_COMPUTERACTIVEAGENTSPEECHSTORE_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AGENTMANAGER_COMPUTERACTIVEAGENTSPEECHSTORE_H_

#include <string>

#include <MultiAgentExperience/Samples/Agents/Computer/ActiveAgentSpeechStore/ActiveAgentSpeechStoreInterface.h>

#include "SampleApplication/AudioManager/Wakeword/CrosswakeDetector/ActiveAgentSpeechStoreInterface.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace agentManager {
namespace computer {

/**
 * WARNING - This is part of a demo quality implementation of crosswake detection for use as a proof of concept.
 *
 * See SimpleCrosswakeDetector.h for more detail.
 */
class ComputerActiveAgentSpeechStore
        : public sampleApplication::audioManager::wakeword::crosswake::ActiveAgentSpeechStoreInterface
        , public multiAgentExperience::samples::agents::computer::speechStore::ActiveAgentSpeechStoreInterface {
public:
    ComputerActiveAgentSpeechStore();
    void setActiveSpeech(const std::string& speech) override;
    void clear() override;

    std::string getActiveAgentSpeech() override;

private:
    std::string m_activeSpeech;
};

}  // namespace computer
}  // namespace agentManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AGENTMANAGER_COMPUTERACTIVEAGENTSPEECHSTORE_H_
