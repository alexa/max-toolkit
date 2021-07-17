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

#include "Core/Transformer/DialogStateHandlerLifecycle.h"

#include <gmock/gmock.h>
#include <memory>

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {
namespace test {

using testing::_;

static const transformer::DialogState m_dialogState = transformer::DialogState::create("test");

class DialogStateHandlerLifecycleTest : public ::testing::Test {};

TEST_F(DialogStateHandlerLifecycleTest, test_calling_get_dialog_state_returns_state) {
    auto start = []() { FAIL() << "should not start"; };

    auto stop = []() { FAIL() << "should not stop"; };

    auto dialogStateHandlerLifecycle = std::make_shared<DialogStateHandlerLifecycle>(m_dialogState, start, stop);
    ASSERT_EQ(transformer::DialogState::create("test"), dialogStateHandlerLifecycle->getDialogState());
}

TEST_F(DialogStateHandlerLifecycleTest, test_calling_start_uses_the_start_callback) {
    bool startCalled = false;

    auto start = [&startCalled]() { startCalled = true; };

    auto stop = []() { FAIL() << "should not stop"; };

    auto dialogStateHandlerLifecycle = std::make_shared<DialogStateHandlerLifecycle>(m_dialogState, start, stop);
    dialogStateHandlerLifecycle->start();
    ASSERT_TRUE(startCalled);
}

TEST_F(DialogStateHandlerLifecycleTest, test_calling_start_twice_does_nothing) {
    int startCalledTimes = 0;

    auto start = [&startCalledTimes]() {
        startCalledTimes++;
        if (startCalledTimes > 1) {
            FAIL() << "should not call start more than once";
        }
    };

    auto stop = []() { FAIL() << "should not stop"; };

    auto dialogStateHandlerLifecycle = std::make_shared<DialogStateHandlerLifecycle>(m_dialogState, start, stop);
    dialogStateHandlerLifecycle->start();
    dialogStateHandlerLifecycle->start();
    ASSERT_EQ(1, startCalledTimes);
}

TEST_F(DialogStateHandlerLifecycleTest, test_calling_stop_uses_the_stop_callback_does_nothing_if_not_started) {
    auto start = []() { FAIL() << "should not start"; };

    auto stop = []() { FAIL() << "should not stop"; };

    auto dialogStateHandlerLifecycle = std::make_shared<DialogStateHandlerLifecycle>(m_dialogState, start, stop);
    dialogStateHandlerLifecycle->stop();
}

TEST_F(DialogStateHandlerLifecycleTest, test_calling_stop_uses_the_stop_callback_when_started) {
    bool stopCalled = false;

    auto start = []() {};

    auto stop = [&stopCalled]() { stopCalled = true; };

    auto dialogStateHandlerLifecycle = std::make_shared<DialogStateHandlerLifecycle>(m_dialogState, start, stop);
    dialogStateHandlerLifecycle->start();
    dialogStateHandlerLifecycle->stop();
    ASSERT_TRUE(stopCalled);
}

TEST_F(DialogStateHandlerLifecycleTest, test_calling_start_is_not_called_after_stopped) {
    int startCalledTimes = 0;

    auto start = [&startCalledTimes]() {
        startCalledTimes++;
        if (startCalledTimes > 1) {
            FAIL() << "should not call start more than once";
        }
    };

    auto stop = []() {};

    auto dialogStateHandlerLifecycle = std::make_shared<DialogStateHandlerLifecycle>(m_dialogState, start, stop);
    dialogStateHandlerLifecycle->start();
    dialogStateHandlerLifecycle->stop();
    dialogStateHandlerLifecycle->start();
    ASSERT_EQ(1, startCalledTimes);
}

}  // namespace test
}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
