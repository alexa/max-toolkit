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

#include <gmock/gmock.h>

#include "Control/Control.h"
#include "Control/ControlAccessKeys.h"
#include "Control/ControlInvoker.h"
#include "Control/ControlStore.h"

namespace multiAgentExperience {
namespace library {
namespace control {
namespace test {

using testing::_;

class ControlInvokerTest : public ::testing::Test {
protected:
    virtual void SetUp() override {
    }
};

TEST_F(ControlInvokerTest, test_invoke_with_a_name_which_is_not_available_does_nothing) {
    auto controlAccessKeys = std::make_shared<ControlAccessKeys>();
    auto controlStore = std::make_shared<ControlStore>(controlAccessKeys);
    auto key = controlAccessKeys->requestAccessKey();
    ControlInvoker invoker(key, controlStore);
    invoker.invoke(ControlName::STOP);
    // this should be a noop, the test fails if it crashes.
}

TEST_F(ControlInvokerTest, test_invoke_executes_the_correct_control) {
    auto controlAccessKeys = std::make_shared<ControlAccessKeys>();
    auto controlStore = std::make_shared<ControlStore>(controlAccessKeys);
    std::unordered_set<std::shared_ptr<Control>> controls;

    auto expectedName = ControlName::STOP;
    auto result = false;
    auto controlHigh = Control::create(expectedName, [&result]() { result = true; });
    controls.insert(controlHigh);

    auto storeKey = controlAccessKeys->requestAccessKey();
    controlStore->store(storeKey, ControlPriority::DIALOG, controls);

    auto invokeKey = controlAccessKeys->requestAccessKey();
    ControlInvoker invoker(invokeKey, controlStore);
    invoker.invoke(expectedName);
    ASSERT_TRUE(result);
}

TEST_F(ControlInvokerTest, test_invoke_after_cleanup_executes_nothing) {
    auto controlAccessKeys = std::make_shared<ControlAccessKeys>();
    auto controlStore = std::make_shared<ControlStore>(controlAccessKeys);
    std::unordered_set<std::shared_ptr<Control>> controls;

    auto expectedName = ControlName::STOP;
    auto result = false;
    auto control = Control::create(expectedName, [&result]() { result = true; });
    controls.insert(control);

    auto storeKey = controlAccessKeys->requestAccessKey();
    controlStore->store(storeKey, ControlPriority::DIALOG, controls);

    auto invokeKey = controlAccessKeys->requestAccessKey();
    ControlInvoker invoker(invokeKey, controlStore);
    invoker.cleanup();
    invoker.invoke(expectedName);
    ASSERT_FALSE(result);
}

}  // namespace test
}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience
