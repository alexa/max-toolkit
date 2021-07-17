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

#ifndef MULTI_AGENT_EXPERIENCE_SAMPLES_AGENTS_COMPUTER_ACTIVEAGENTSPEECHSTORE_ACTIVEAGENTSPEECHSTOREINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_SAMPLES_AGENTS_COMPUTER_ACTIVEAGENTSPEECHSTORE_ACTIVEAGENTSPEECHSTOREINTERFACE_H_

namespace multiAgentExperience {
namespace samples {
namespace agents {
namespace computer {
namespace speechStore {

class ActiveAgentSpeechStoreInterface {
public:
    virtual ~ActiveAgentSpeechStoreInterface() = default;

    virtual void setActiveSpeech(const std::string& speech) = 0;

    virtual void clear() = 0;
};

}  // namespace speechStore
}  // namespace computer
}  // namespace agents
}  // namespace samples
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_SAMPLES_AGENTS_COMPUTER_ACTIVEAGENTSPEECHSTORE_ACTIVEAGENTSPEECHSTOREINTERFACE_H_
