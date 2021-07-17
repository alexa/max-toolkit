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

#include "Core/Transformer/CombinedDialogStateHandlersLifecycle.h"

#include "Core/Transformer/DialogStateHandlerRegistry.h"

#include <Mocks/MockControlRegistryInterface.h>
#include <Mocks/MockDialogControllerInterface.h>
#include <Mocks/MockExperienceControlInterface.h>
#include <Mocks/MockListeningHandlerInterface.h>
#include <Mocks/MockSpeakingHandlerInterface.h>
#include <Mocks/MockThinkingHandlerInterface.h>

#include <gmock/gmock.h>
#include <memory>

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {
namespace test {

using namespace multiAgentExperience::experience::test;
using namespace multiAgentExperience::dialog;
using namespace multiAgentExperience::control::test;
using namespace multiAgentExperience::dialog::test;
using testing::Eq;
using testing::_;

class CombinedDialogStateHandlersLifecycleTest : public ::testing::Test {
protected:
    std::shared_ptr<DialogStateHandlerRegistry> m_registry;

    std::shared_ptr<testing::NiceMock<MockDialogControllerInterface>> m_dialogControl;
    std::shared_ptr<testing::NiceMock<MockExperienceControlInterface>> m_experienceControl;
    std::shared_ptr<CombinedDialogStateHandlersLifecycle> m_lifecycle;

    virtual void SetUp() override {
        m_registry = std::make_shared<DialogStateHandlerRegistry>();
        m_dialogControl = std::make_shared<testing::NiceMock<MockDialogControllerInterface>>();
        m_experienceControl = std::make_shared<testing::NiceMock<MockExperienceControlInterface>>();
        m_lifecycle =
            std::make_shared<CombinedDialogStateHandlersLifecycle>(m_registry, m_dialogControl, m_experienceControl);
    }
};

TEST_F(CombinedDialogStateHandlersLifecycleTest, test_start_listening_returns_false_when_not_registerd) {
    std::set<multiAgentExperience::control::ControlType> controls;
    ASSERT_FALSE(m_lifecycle->startListening(controls));
}

TEST_F(CombinedDialogStateHandlersLifecycleTest, test_start_listening_starts_listening_when_registerd) {
    auto mockListeningHandler = std::make_shared<testing::StrictMock<MockListeningHandlerInterface>>();
    m_registry->setListeningHandler(mockListeningHandler);

    std::set<multiAgentExperience::control::ControlType> controls;
    EXPECT_CALL(*mockListeningHandler, onStartListening(Eq(m_dialogControl), Eq(controls)));

    ASSERT_TRUE(m_lifecycle->startListening(controls));
}

TEST_F(CombinedDialogStateHandlersLifecycleTest, test_start_thinking_returns_false_when_not_registerd) {
    ASSERT_FALSE(m_lifecycle->startThinking());
}

TEST_F(CombinedDialogStateHandlersLifecycleTest, test_start_thinking_starts_thinking_when_registered) {
    auto mockThinkingHandler = std::make_shared<testing::StrictMock<MockThinkingHandlerInterface>>();
    m_registry->setThinkingHandler(mockThinkingHandler);

    EXPECT_CALL(*mockThinkingHandler, onStartThinking(Eq(m_dialogControl)));

    ASSERT_TRUE(m_lifecycle->startThinking());
}

TEST_F(CombinedDialogStateHandlersLifecycleTest, test_start_speaking_returns_false_when_not_registerd) {
    auto mockRegistry = std::make_shared<testing::NiceMock<MockControlRegistryInterface>>();
    ASSERT_FALSE(m_lifecycle->startSpeaking(mockRegistry));
}

TEST_F(CombinedDialogStateHandlersLifecycleTest, test_start_speaking_starts_speaking_when_registered) {
    auto mockRegistry = std::make_shared<testing::NiceMock<MockControlRegistryInterface>>();
    auto mockSpeakingHandler = std::make_shared<testing::StrictMock<MockSpeakingHandlerInterface>>();
    m_registry->setSpeakingHandler(mockSpeakingHandler);

    EXPECT_CALL(*mockSpeakingHandler, onStartSpeaking(Eq(m_dialogControl), _, Eq(mockRegistry)));

    ASSERT_TRUE(m_lifecycle->startSpeaking(mockRegistry));
}

TEST_F(CombinedDialogStateHandlersLifecycleTest, test_stop_current_dialog_state_stops_listening_when_in_listening) {
    auto mockListeningHandler = std::make_shared<testing::StrictMock<MockListeningHandlerInterface>>();
    m_registry->setListeningHandler(mockListeningHandler);

    std::set<multiAgentExperience::control::ControlType> controls;
    EXPECT_CALL(*mockListeningHandler, onStartListening(_, _));
    m_lifecycle->startListening(controls);

    EXPECT_CALL(*mockListeningHandler, onStopListening());

    m_lifecycle->stopCurrentDialogState();
}

TEST_F(
    CombinedDialogStateHandlersLifecycleTest,
    test_stop_current_dialog_state_does_not_stop_listening_when_not_in_listening) {
    auto mockListeningHandler = std::make_shared<testing::StrictMock<MockListeningHandlerInterface>>();
    m_registry->setListeningHandler(mockListeningHandler);

    std::set<multiAgentExperience::control::ControlType> controls;
    EXPECT_CALL(*mockListeningHandler, onStartListening(_, _));
    m_lifecycle->startListening(controls);

    EXPECT_CALL(*mockListeningHandler, onStopListening()).Times(1);

    m_lifecycle->stopCurrentDialogState();
    m_lifecycle->stopCurrentDialogState();
}

TEST_F(CombinedDialogStateHandlersLifecycleTest, test_stop_current_dialog_state_stops_thinking_when_in_thinking) {
    auto mockThinkingHandler = std::make_shared<testing::StrictMock<MockThinkingHandlerInterface>>();
    m_registry->setThinkingHandler(mockThinkingHandler);

    EXPECT_CALL(*mockThinkingHandler, onStartThinking(_));
    m_lifecycle->startThinking();

    EXPECT_CALL(*mockThinkingHandler, onStopThinking());

    m_lifecycle->stopCurrentDialogState();
}

TEST_F(
    CombinedDialogStateHandlersLifecycleTest,
    test_stop_current_dialog_state_does_not_stop_thinking_when_not_in_thinking) {
    auto mockThinkingHandler = std::make_shared<testing::StrictMock<MockThinkingHandlerInterface>>();
    m_registry->setThinkingHandler(mockThinkingHandler);

    EXPECT_CALL(*mockThinkingHandler, onStartThinking(_));
    m_lifecycle->startThinking();

    EXPECT_CALL(*mockThinkingHandler, onStopThinking()).Times(1);

    m_lifecycle->stopCurrentDialogState();
    m_lifecycle->stopCurrentDialogState();
}

TEST_F(CombinedDialogStateHandlersLifecycleTest, test_stop_current_dialog_state_stops_speaking_when_in_speaking) {
    auto mockSpeakingHandler = std::make_shared<testing::StrictMock<MockSpeakingHandlerInterface>>();
    m_registry->setSpeakingHandler(mockSpeakingHandler);

    EXPECT_CALL(*mockSpeakingHandler, onStartSpeaking(_, _, _));
    auto mockRegistry = std::make_shared<testing::NiceMock<MockControlRegistryInterface>>();
    m_lifecycle->startSpeaking(mockRegistry);

    EXPECT_CALL(*mockSpeakingHandler, onStopSpeaking());

    m_lifecycle->stopCurrentDialogState();
}

TEST_F(
    CombinedDialogStateHandlersLifecycleTest,
    test_stop_current_dialog_state_does_not_stop_speaking_when_not_in_speaking) {
    auto mockSpeakingHandler = std::make_shared<testing::StrictMock<MockSpeakingHandlerInterface>>();
    m_registry->setSpeakingHandler(mockSpeakingHandler);

    EXPECT_CALL(*mockSpeakingHandler, onStartSpeaking(_, _, _));
    auto mockRegistry = std::make_shared<testing::NiceMock<MockControlRegistryInterface>>();
    m_lifecycle->startSpeaking(mockRegistry);

    EXPECT_CALL(*mockSpeakingHandler, onStopSpeaking()).Times(1);

    m_lifecycle->stopCurrentDialogState();
    m_lifecycle->stopCurrentDialogState();
}

TEST_F(CombinedDialogStateHandlersLifecycleTest, test_stop_stops_listening_when_in_listening) {
    auto mockListeningHandler = std::make_shared<testing::StrictMock<MockListeningHandlerInterface>>();
    m_registry->setListeningHandler(mockListeningHandler);

    std::set<multiAgentExperience::control::ControlType> controls;
    EXPECT_CALL(*mockListeningHandler, onStartListening(_, _));
    m_lifecycle->startListening(controls);

    EXPECT_CALL(*mockListeningHandler, onStopListening());

    m_lifecycle->stop();
}

TEST_F(CombinedDialogStateHandlersLifecycleTest, test_stop_stops_thinking_when_in_thinking) {
    auto mockThinkingHandler = std::make_shared<testing::StrictMock<MockThinkingHandlerInterface>>();
    m_registry->setThinkingHandler(mockThinkingHandler);

    EXPECT_CALL(*mockThinkingHandler, onStartThinking(_));
    m_lifecycle->startThinking();

    EXPECT_CALL(*mockThinkingHandler, onStopThinking());

    m_lifecycle->stop();
}

TEST_F(CombinedDialogStateHandlersLifecycleTest, test_stop_stops_speaking_when_in_speaking) {
    auto mockSpeakingHandler = std::make_shared<testing::StrictMock<MockSpeakingHandlerInterface>>();
    m_registry->setSpeakingHandler(mockSpeakingHandler);

    EXPECT_CALL(*mockSpeakingHandler, onStartSpeaking(_, _, _));
    auto mockRegistry = std::make_shared<testing::NiceMock<MockControlRegistryInterface>>();
    m_lifecycle->startSpeaking(mockRegistry);

    EXPECT_CALL(*mockSpeakingHandler, onStopSpeaking());

    m_lifecycle->stop();
}

TEST_F(CombinedDialogStateHandlersLifecycleTest, test_stop_current_dialog_state_does_not_stop_entire_dialog) {
    auto mockDialogControl = std::make_shared<testing::StrictMock<MockDialogControllerInterface>>();
    m_lifecycle =
        std::make_shared<CombinedDialogStateHandlersLifecycle>(m_registry, mockDialogControl, m_experienceControl);
    m_lifecycle->stopCurrentDialogState();
    // fails if strict mock is used unexpectedly.
}

TEST_F(CombinedDialogStateHandlersLifecycleTest, test_stop_stops_entire_dialog) {
    auto mockDialogControl = std::make_shared<testing::StrictMock<MockDialogControllerInterface>>();
    m_lifecycle =
        std::make_shared<CombinedDialogStateHandlersLifecycle>(m_registry, mockDialogControl, m_experienceControl);

    EXPECT_CALL(*mockDialogControl, stop());
    m_lifecycle->stop();
}

TEST_F(CombinedDialogStateHandlersLifecycleTest, test_stop_stops_entire_dialog_when_in_listening) {
    auto mockListeningHandler = std::make_shared<testing::NiceMock<MockListeningHandlerInterface>>();
    m_registry->setListeningHandler(mockListeningHandler);

    auto mockDialogControl = std::make_shared<testing::StrictMock<MockDialogControllerInterface>>();
    m_lifecycle =
        std::make_shared<CombinedDialogStateHandlersLifecycle>(m_registry, mockDialogControl, m_experienceControl);
    std::set<multiAgentExperience::control::ControlType> controls;
    m_lifecycle->startListening(controls);
    EXPECT_CALL(*mockDialogControl, stop());

    m_lifecycle->stop();
}

TEST_F(CombinedDialogStateHandlersLifecycleTest, test_stop_stops_entire_dialog_when_in_thinking) {
    auto mockThinkingHandler = std::make_shared<testing::NiceMock<MockThinkingHandlerInterface>>();
    m_registry->setThinkingHandler(mockThinkingHandler);

    auto mockDialogControl = std::make_shared<testing::StrictMock<MockDialogControllerInterface>>();
    m_lifecycle =
        std::make_shared<CombinedDialogStateHandlersLifecycle>(m_registry, mockDialogControl, m_experienceControl);
    m_lifecycle->startThinking();
    EXPECT_CALL(*mockDialogControl, stop());

    m_lifecycle->stop();
}

TEST_F(CombinedDialogStateHandlersLifecycleTest, test_stop_stops_entire_dialog_when_in_speaking) {
    auto mockSpeakingHandler = std::make_shared<testing::NiceMock<MockSpeakingHandlerInterface>>();
    m_registry->setSpeakingHandler(mockSpeakingHandler);

    auto mockDialogControl = std::make_shared<testing::StrictMock<MockDialogControllerInterface>>();
    m_lifecycle =
        std::make_shared<CombinedDialogStateHandlersLifecycle>(m_registry, mockDialogControl, m_experienceControl);
    auto mockRegistry = std::make_shared<testing::NiceMock<MockControlRegistryInterface>>();
    m_lifecycle->startSpeaking(mockRegistry);
    EXPECT_CALL(*mockDialogControl, stop());

    m_lifecycle->stop();
}

TEST_F(CombinedDialogStateHandlersLifecycleTest, test_listening_is_stopped_when_starting_another_state) {
    auto mockListeningHandler = std::make_shared<testing::StrictMock<MockListeningHandlerInterface>>();
    m_registry->setListeningHandler(mockListeningHandler);
    auto mockThinkingHandler = std::make_shared<testing::NiceMock<MockThinkingHandlerInterface>>();
    m_registry->setThinkingHandler(mockThinkingHandler);

    EXPECT_CALL(*mockListeningHandler, onStartListening(_, _));

    std::set<multiAgentExperience::control::ControlType> controls;
    m_lifecycle->startListening(controls);

    EXPECT_CALL(*mockListeningHandler, onStopListening());

    m_lifecycle->startThinking();
}

TEST_F(CombinedDialogStateHandlersLifecycleTest, test_thinking_is_stopped_when_starting_another_state) {
    auto mockThinkingHandler = std::make_shared<testing::StrictMock<MockThinkingHandlerInterface>>();
    m_registry->setThinkingHandler(mockThinkingHandler);
    auto mockSpeakingHandler = std::make_shared<testing::NiceMock<MockSpeakingHandlerInterface>>();
    m_registry->setSpeakingHandler(mockSpeakingHandler);

    EXPECT_CALL(*mockThinkingHandler, onStartThinking(_));

    m_lifecycle->startThinking();

    EXPECT_CALL(*mockThinkingHandler, onStopThinking());

    auto mockRegistry = std::make_shared<testing::NiceMock<MockControlRegistryInterface>>();
    m_lifecycle->startSpeaking(mockRegistry);
}

TEST_F(CombinedDialogStateHandlersLifecycleTest, test_speaking_is_stopped_when_starting_another_state) {
    auto mockSpeakingHandler = std::make_shared<testing::StrictMock<MockSpeakingHandlerInterface>>();
    m_registry->setSpeakingHandler(mockSpeakingHandler);
    auto mockListeningHandler = std::make_shared<testing::NiceMock<MockListeningHandlerInterface>>();
    m_registry->setListeningHandler(mockListeningHandler);

    EXPECT_CALL(*mockSpeakingHandler, onStartSpeaking(_, _, _));

    auto mockRegistry = std::make_shared<testing::NiceMock<MockControlRegistryInterface>>();
    m_lifecycle->startSpeaking(mockRegistry);

    EXPECT_CALL(*mockSpeakingHandler, onStopSpeaking());

    std::set<multiAgentExperience::control::ControlType> controls;
    m_lifecycle->startListening(controls);
}

TEST_F(CombinedDialogStateHandlersLifecycleTest, test_starting_the_same_state_restarts_the_lifecycle) {
    auto mockListeningHandler = std::make_shared<testing::StrictMock<MockListeningHandlerInterface>>();
    m_registry->setListeningHandler(mockListeningHandler);

    EXPECT_CALL(*mockListeningHandler, onStartListening(_, _)).Times(2);

    std::set<multiAgentExperience::control::ControlType> controls;
    m_lifecycle->startListening(controls);

    EXPECT_CALL(*mockListeningHandler, onStopListening());

    m_lifecycle->startListening(controls);
}

}  // namespace test
}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
