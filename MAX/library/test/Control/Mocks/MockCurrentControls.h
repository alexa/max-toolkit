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

#ifndef VII_CONTROL_TEST_MOCK_CURRENT_CONTROLS_H_
#define VII_CONTROL_TEST_MOCK_CURRENT_CONTROLS_H_

#include "Control/CurrentControls.h"
#include "Control/Control.h"

#include "MockControlStore.h"

#include <gmock/gmock.h>
#include <memory>

namespace multiAgentExperience {
namespace library {
namespace control {
namespace test {

class MockCurrentControls : public CurrentControls {
public:
    MockCurrentControls() : CurrentControls(0, std::make_shared<MockControlStore>()) {
    }

    MOCK_METHOD0(getCurrentControls, std::unordered_set<ControlName>());
};

}  // namespace test
}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience

#endif  // VII_CONTROL_TEST_MOCK_CURRENT_CONTROLS_H_
