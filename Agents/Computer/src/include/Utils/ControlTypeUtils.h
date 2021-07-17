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

#ifndef MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_UTILS_CONTROLTYPEUTILS_H_
#define MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_UTILS_CONTROLTYPEUTILS_H_

namespace multiAgentExperience {
namespace samples {
namespace agents {
namespace computer {
namespace utils {

class ControlTypeUtils {
public:
    static multiAgentExperience::control::ControlType getControlTypeForName(std::string& controlType) {
        return multiAgentExperience::control::ControlType::STOP;
    }

    static std::string getNameForControlType(multiAgentExperience::control::ControlType controlType) {
        switch (controlType) {
            case multiAgentExperience::control::ControlType::STOP:
                return std::string("STOP");
            default:
                return std::string("UNDEFINED");
        }
    }
};

}  // namespace utils
}  // namespace computer
}  // namespace agents
}  // namespace samples
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_UTILS_CONTROLTYPEUTILS_H_
