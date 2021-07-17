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

#include "Core/Transformer/DialogRequestLifecycle.h"

#include "Mocks/MockDialogControllerInterface.h"
#include "Mocks/MockDialogRequestInterface.h"

#include <gmock/gmock.h>
#include <memory>

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {
namespace test {

using namespace multiAgentExperience::dialog::test;
using testing::Eq;
using testing::_;

class TransformerDialogRequestLifecycleTest : public ::testing::Test {
protected:
    std::shared_ptr<MockDialogRequestInterface> m_mockDialogRequestInterface;
    std::shared_ptr<DialogRequestLifecycle> m_dialogRequestLifecycle;

    virtual void SetUp() override {
        m_mockDialogRequestInterface = std::make_shared<testing::StrictMock<MockDialogRequestInterface>>();
        m_dialogRequestLifecycle = std::make_shared<DialogRequestLifecycle>(m_mockDialogRequestInterface);
    }
};

TEST_F(TransformerDialogRequestLifecycleTest, test_dialog_request_does_is_not_initially_started) {
    ASSERT_FALSE(m_dialogRequestLifecycle->isStarted());
}

TEST_F(TransformerDialogRequestLifecycleTest, test_start_starts_the_dialog) {
    auto mockDialogControl = std::make_shared<testing::StrictMock<MockDialogControllerInterface>>();
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStarted(Eq(mockDialogControl)));
    m_dialogRequestLifecycle->start(mockDialogControl);
}

TEST_F(TransformerDialogRequestLifecycleTest, test_start_puts_the_dialog_request_in_started) {
    auto mockDialogControl = std::make_shared<testing::StrictMock<MockDialogControllerInterface>>();
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStarted(_));
    m_dialogRequestLifecycle->start(mockDialogControl);

    ASSERT_TRUE(m_dialogRequestLifecycle->isStarted());
}

TEST_F(TransformerDialogRequestLifecycleTest, test_error_forwards_the_error_message_when_started) {
    auto mockDialogControl = std::make_shared<testing::StrictMock<MockDialogControllerInterface>>();
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStarted(_));
    m_dialogRequestLifecycle->start(mockDialogControl);

    auto errorMessage = std::string("test_error");
    EXPECT_CALL(*m_mockDialogRequestInterface, onError(Eq(errorMessage)));

    m_dialogRequestLifecycle->error(errorMessage);
}

TEST_F(TransformerDialogRequestLifecycleTest, test_error_does_not_change_state) {
    auto mockDialogControl = std::make_shared<testing::StrictMock<MockDialogControllerInterface>>();
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStarted(_));
    m_dialogRequestLifecycle->start(mockDialogControl);

    EXPECT_CALL(*m_mockDialogRequestInterface, onError(_));

    m_dialogRequestLifecycle->error("test_error");
    ASSERT_TRUE(m_dialogRequestLifecycle->isStarted());
}

TEST_F(TransformerDialogRequestLifecycleTest, test_error_does_nothing_if_not_started) {
    m_dialogRequestLifecycle->error("test_error");
    // fails if strict DialogRequestInterface mock is used unexpectedly.
}

TEST_F(TransformerDialogRequestLifecycleTest, test_deny_denies_the_request) {
    auto denialMessage = std::string("test_denial");
    EXPECT_CALL(*m_mockDialogRequestInterface, onDenied(Eq(denialMessage)));
    m_dialogRequestLifecycle->deny(denialMessage);
}

TEST_F(TransformerDialogRequestLifecycleTest, test_deny_does_not_state_the_dialog) {
    EXPECT_CALL(*m_mockDialogRequestInterface, onDenied(_));
    m_dialogRequestLifecycle->deny("test_denial");

    ASSERT_FALSE(m_dialogRequestLifecycle->isStarted());
}

TEST_F(TransformerDialogRequestLifecycleTest, test_deny_after_start_does_nothing) {
    auto mockDialogControl = std::make_shared<testing::StrictMock<MockDialogControllerInterface>>();
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStarted(Eq(mockDialogControl)));
    m_dialogRequestLifecycle->start(mockDialogControl);

    m_dialogRequestLifecycle->deny("test_denial");
    // fails if strict DialogRequestInterface mock is used unexpectedly.
}

TEST_F(TransformerDialogRequestLifecycleTest, test_deny_after_denial_does_nothing) {
    auto denialMessage = std::string("test_denial");
    EXPECT_CALL(*m_mockDialogRequestInterface, onDenied(_)).Times(1);
    m_dialogRequestLifecycle->deny(denialMessage);
    m_dialogRequestLifecycle->deny(denialMessage);
    // fails if strict DialogRequestInterface mock is used unexpectedly.
}

TEST_F(TransformerDialogRequestLifecycleTest, test_before_stop_denies_an_unstarted_request) {
    EXPECT_CALL(*m_mockDialogRequestInterface, onDenied(_));
    m_dialogRequestLifecycle->beforeStop();
}

TEST_F(TransformerDialogRequestLifecycleTest, test_before_stop_puts_a_started_request_in_a_non_started_state) {
    auto mockDialogControl = std::make_shared<testing::StrictMock<MockDialogControllerInterface>>();
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStarted(Eq(mockDialogControl)));
    m_dialogRequestLifecycle->start(mockDialogControl);

    m_dialogRequestLifecycle->beforeStop();

    ASSERT_FALSE(m_dialogRequestLifecycle->isStarted());
}

TEST_F(TransformerDialogRequestLifecycleTest, test_stop_stops_a_started_requst) {
    auto mockDialogControl = std::make_shared<testing::StrictMock<MockDialogControllerInterface>>();
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStarted(Eq(mockDialogControl)));
    m_dialogRequestLifecycle->start(mockDialogControl);

    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStopped());
    m_dialogRequestLifecycle->stop();
}

TEST_F(TransformerDialogRequestLifecycleTest, test_stop_does_not_stop_a_stopped_request_again) {
    auto mockDialogControl = std::make_shared<testing::StrictMock<MockDialogControllerInterface>>();
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStarted(Eq(mockDialogControl)));
    m_dialogRequestLifecycle->start(mockDialogControl);

    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStopped()).Times(1);
    m_dialogRequestLifecycle->stop();
    m_dialogRequestLifecycle->stop();
    // fails if strict DialogRequestInterface mock is used unexpectedly.
}

TEST_F(TransformerDialogRequestLifecycleTest, test_stop_puts_the_request_in_a_unstarted_state) {
    auto mockDialogControl = std::make_shared<testing::StrictMock<MockDialogControllerInterface>>();
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStarted(Eq(mockDialogControl)));
    m_dialogRequestLifecycle->start(mockDialogControl);

    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStopped());
    m_dialogRequestLifecycle->stop();

    ASSERT_FALSE(m_dialogRequestLifecycle->isStarted());
}

TEST_F(TransformerDialogRequestLifecycleTest, test_stop_denies_an_unstarted_request) {
    EXPECT_CALL(*m_mockDialogRequestInterface, onDenied(_));
    m_dialogRequestLifecycle->stop();
}

TEST_F(TransformerDialogRequestLifecycleTest, test_a_stopped_request_cannot_be_started) {
    EXPECT_CALL(*m_mockDialogRequestInterface, onDenied(_));
    m_dialogRequestLifecycle->stop();

    auto mockDialogControl = std::make_shared<testing::StrictMock<MockDialogControllerInterface>>();
    m_dialogRequestLifecycle->start(mockDialogControl);
    ASSERT_FALSE(m_dialogRequestLifecycle->isStarted());

    // fails if strict DialogRequestInterface mock is used unexpectedly.
}

}  // namespace test
}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
