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


#include "SampleApplication/AgentManager/Computer/ComputerActiveAgentSpeechStore.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace agentManager {
namespace computer {

ComputerActiveAgentSpeechStore::ComputerActiveAgentSpeechStore() : m_activeSpeech{""} {
}

void ComputerActiveAgentSpeechStore::setActiveSpeech(const std::string& speech) {
    m_activeSpeech = speech;
}

void ComputerActiveAgentSpeechStore::clear() {
    m_activeSpeech = "";
}

std::string ComputerActiveAgentSpeechStore::getActiveAgentSpeech() {
    return m_activeSpeech;
}

}  // namespace computer
}  // namespace agentManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
