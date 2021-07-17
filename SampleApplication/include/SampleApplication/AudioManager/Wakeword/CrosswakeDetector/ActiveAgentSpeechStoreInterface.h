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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_WAKEWORD_ACTIVEAGENTSPEECHSTOREINTERFACE_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_WAKEWORD_ACTIVEAGENTSPEECHSTOREINTERFACE_H_

#include <string>

namespace multiAgentExperience {
namespace sampleApplication {
namespace audioManager {
namespace wakeword {
namespace crosswake {

class ActiveAgentSpeechStoreInterface {
public:
    virtual ~ActiveAgentSpeechStoreInterface() = default;
    virtual std::string getActiveAgentSpeech() = 0;
};

}  // namespace crosswake
}  // namespace wakeword
}  // namespace audioManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_WAKEWORD_ACTIVEAGENTSPEECHSTOREINTERFACE_H_
