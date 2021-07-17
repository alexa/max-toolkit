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


#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_TEST_VERIFIERS_CONTROLTYPESETVERIFIER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_TEST_VERIFIERS_CONTROLTYPESETVERIFIER_H_

#include <gmock/gmock.h>

#include <MultiAgentExperience/Control/Control.h>

#include <set>

namespace multiAgentExperience {
namespace library {
namespace test {
namespace verifiers {

class ControlTypeSetVerifier {
public:
    void setExpectedControlNames(std::set<multiAgentExperience::control::ControlType> names) {
        m_expectedControlNames = std::move(names);
    }
    void captureControls(std::set<multiAgentExperience::control::ControlType> availableControls) {
        for (auto controlName : m_expectedControlNames) {
            ASSERT_TRUE(availableControls.find(controlName) != availableControls.end());
        }
    }

private:
    std::set<multiAgentExperience::control::ControlType> m_expectedControlNames;
};

}  // namespace verifiers
}  // namespace test
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_TEST_VERIFIERS_CONTROLTYPESETVERIFIER_H_
