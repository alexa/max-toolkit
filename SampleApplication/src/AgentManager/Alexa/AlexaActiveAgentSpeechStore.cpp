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


#include "SampleApplication/AgentManager/Alexa/AlexaActiveAgentSpeechStore.h"

#include "SampleApplication/Utils/RadiantLogger.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace agentManager {
namespace alexa {

/// Metadata parameters that will be passed into our logging system.
static const std::string MODULE_TAG("AlexaActiveAgentSpeechStore");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, MODULE_TAG, __func__, message)

AlexaActiveAgentSpeechStore::AlexaActiveAgentSpeechStore() : m_speech{""} {
}

void AlexaActiveAgentSpeechStore::setActiveSpeech(const std::string& speech) {
    LX(DEBUG3, "setActiveSpeech: " + speech);
    m_speech = speech;
}

void AlexaActiveAgentSpeechStore::clear() {
    LX(DEBUG3, "clear");
    m_speech = "";
}

std::string AlexaActiveAgentSpeechStore::getActiveAgentSpeech() {
    return m_speech;
}

}  // namespace alexa
}  // namespace agentManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
