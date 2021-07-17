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


#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_TEST_VERIFIERS_CONTROLNAMESETVERIFIER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_TEST_VERIFIERS_CONTROLNAMESETVERIFIER_H_

#include <gmock/gmock.h>

#include "Control/Control.h"

#include <unordered_set>

namespace multiAgentExperience {
namespace library {
namespace test {
namespace verifiers {

class ControlNameSetVerifier {
public:
    void setExpectedControlNames(std::unordered_set<control::ControlName> names) {
        m_expectedControlNames = std::move(names);
    }
    void captureControls(std::unordered_set<control::ControlName> availableControls) {
        for (auto controlName : m_expectedControlNames) {
            ASSERT_TRUE(availableControls.find(controlName) != availableControls.end());
        }
    }

private:
    std::unordered_set<control::ControlName> m_expectedControlNames;
};

}  // namespace verifiers
}  // namespace test
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_TEST_VERIFIERS_CONTROLNAMESETVERIFIER_H_
