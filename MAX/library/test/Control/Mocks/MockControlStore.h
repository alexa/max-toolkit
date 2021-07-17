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

#ifndef VII_CONTROL_TEST_MOCK_CONTROL_STORE_H_
#define VII_CONTROL_TEST_MOCK_CONTROL_STORE_H_

#include "Control/ControlStore.h"
#include "Control/ControlAccessKeys.h"
#include "Control/Control.h"

#include <gmock/gmock.h>
#include <memory>
#include <unordered_set>

namespace multiAgentExperience {
namespace library {
namespace control {
namespace test {

class MockControlStore : public ControlStore {
public:
    MockControlStore() : ControlStore(std::make_shared<ControlAccessKeys>()) {
    }

    MOCK_METHOD3(store, void(ControlAccessKey, const ControlPriority, std::unordered_set<std::shared_ptr<Control>>));
    MOCK_METHOD1(contains, bool(const ControlAccessKey&));
    MOCK_METHOD1(remove, void(const ControlAccessKey&));
    MOCK_METHOD1(revokeAccess, void(const ControlAccessKey&));
    MOCK_METHOD1(getUnionOfControlNames, std::unordered_set<ControlName>(const ControlAccessKey&));
    MOCK_METHOD2(
        getHighestPriorityControlByName,
        std::shared_ptr<Control>(const ControlAccessKey&, const ControlName&));
};

}  // namespace test
}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience

#endif  // VII_CONTROL_TEST_MOCK_CONTROL_STORE_H_
