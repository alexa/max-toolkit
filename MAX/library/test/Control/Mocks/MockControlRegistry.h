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

#ifndef VII_CONTROL_TEST_MOCK_CONTROL_REGISTRY_H_
#define VII_CONTROL_TEST_MOCK_CONTROL_REGISTRY_H_

#include "Control/ControlRegistry.h"
#include "Control/Control.h"

#include "MockControlStore.h"

#include <gmock/gmock.h>
#include <memory>
#include <unordered_set>

namespace multiAgentExperience {
namespace library {
namespace control {
namespace test {

class MockControlRegistry : public ControlRegistry {
public:
    MockControlRegistry() : ControlRegistry(0, ControlPriority::DIALOG, std::make_shared<MockControlStore>()) {
    }

    MOCK_METHOD1(update, void(std::unordered_set<std::shared_ptr<Control>>));
    MOCK_METHOD0(cleanup, void());
};

}  // namespace test
}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience

#endif  // VII_CONTROL_TEST_MOCK_CONTROL_REGISTRY_H_
