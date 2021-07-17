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

#include "Core/Transformer/DialogLifecycleTransformer.h"

#include "Control/ControlInvoker.h"
#include "Core/Transformer/DialogStateHandlerRegistry.h"

#include "Dialog/DialogState.h"

#include "Mocks/MockCombinedDialogStateHandlersLifecycleFactory.h"
#include "Mocks/MockDialogControllerTransformerFactory.h"
#include "Mocks/MockDialogRequestInterface.h"
#include "Mocks/MockExperienceControlInterface.h"
#include "Mocks/MockListeningHandlerInterface.h"
#include "Mocks/MockSpeakingHandlerInterface.h"
#include "Mocks/MockThinkingHandlerInterface.h"

#include "Control/Mocks/MockControlInvokerFactory.h"
#include "Control/Mocks/MockControlRegistry.h"
#include "Control/Mocks/MockControlInvoker.h"
#include "Dialog/Mocks/MockInternalDialogController.h"

#include <gmock/gmock.h>
#include <memory>
#include <unordered_set>

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {
namespace test {

using namespace multiAgentExperience::library::dialog::test;
using namespace multiAgentExperience::experience::test;
using namespace multiAgentExperience::dialog::test;
using testing::Eq;
using testing::Return;
using testing::_;

static const multiAgentExperience::actor::ActorId AGENT_ID("test_agent");

class DialogLifecycleTransformerTest : public ::testing::Test {
protected:
    std::shared_ptr<MockListeningHandlerInterface> m_mockListeningHandlerInterface;
    std::shared_ptr<MockThinkingHandlerInterface> m_mockThinkingHandlerInterface;
    std::shared_ptr<MockSpeakingHandlerInterface> m_mockSpeakingHandlerInterface;
    std::shared_ptr<MockDialogRequestInterface> m_mockDialogRequestInterface;
    std::shared_ptr<MockInternalDialogController> m_mockDialogController;
    std::shared_ptr<MockCombinedDialogStateHandlersLifecycleFactory> m_mockCombinedDialogStateHandlersLifecycleFactory;
    std::shared_ptr<MockDialogControllerTransformerFactory> m_mockDialogControllerTransformerFactory;
    std::shared_ptr<DialogLifecycleTransformer> m_dialogLifecycleTransformer;

    virtual void SetUp() override {
        // Main verification mocks. The represent the complete lifecycle being transformed into.
        m_mockDialogRequestInterface = std::make_shared<testing::StrictMock<MockDialogRequestInterface>>();
        m_mockListeningHandlerInterface = std::make_shared<testing::StrictMock<MockListeningHandlerInterface>>();
        m_mockThinkingHandlerInterface = std::make_shared<testing::StrictMock<MockThinkingHandlerInterface>>();
        m_mockSpeakingHandlerInterface = std::make_shared<testing::StrictMock<MockSpeakingHandlerInterface>>();

        auto dialogStateHandlersRegistry = std::make_shared<DialogStateHandlerRegistry>();
        dialogStateHandlersRegistry->setListeningHandler(m_mockListeningHandlerInterface);
        dialogStateHandlersRegistry->setThinkingHandler(m_mockThinkingHandlerInterface);
        dialogStateHandlersRegistry->setSpeakingHandler(m_mockSpeakingHandlerInterface);
        auto controlFactory = std::make_shared<testing::NiceMock<control::test::MockControlInvokerFactory>>();
        m_mockDialogController = std::make_shared<testing::NiceMock<MockInternalDialogController>>();
        auto dialogControllerInterface =
            std::make_shared<DialogControllerTransformer>(controlFactory, m_mockDialogController);
        auto experienceControllerInterface = std::make_shared<testing::NiceMock<MockExperienceControlInterface>>();

        m_mockCombinedDialogStateHandlersLifecycleFactory =
            std::make_shared<testing::NiceMock<MockCombinedDialogStateHandlersLifecycleFactory>>();
        EXPECT_CALL(*m_mockCombinedDialogStateHandlersLifecycleFactory, create(_, _))
            .WillRepeatedly(Return(std::make_shared<CombinedDialogStateHandlersLifecycle>(
                dialogStateHandlersRegistry, dialogControllerInterface, experienceControllerInterface)));

        m_mockDialogControllerTransformerFactory =
            std::make_shared<testing::NiceMock<MockDialogControllerTransformerFactory>>();
        EXPECT_CALL(*m_mockDialogControllerTransformerFactory, create(Eq(m_mockDialogController)))
            .WillRepeatedly(Return(dialogControllerInterface));

        m_dialogLifecycleTransformer = std::make_shared<DialogLifecycleTransformer>(
            AGENT_ID,
            m_mockDialogRequestInterface,
            m_mockCombinedDialogStateHandlersLifecycleFactory,
            m_mockDialogControllerTransformerFactory);
    }
};

TEST_F(DialogLifecycleTransformerTest, test_on_granted_does_nothing) {
    m_dialogLifecycleTransformer->onGranted();

    // strict mock of DialogRequestInterface will fail if onGranted has impact on the request.
}

TEST_F(DialogLifecycleTransformerTest, test_on_denied_denies_the_request) {
    EXPECT_CALL(*m_mockDialogRequestInterface, onDenied(_));
    m_dialogLifecycleTransformer->onDenied();
}

TEST_F(DialogLifecycleTransformerTest, test_on_dialog_started_starts_the_request) {
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStarted(_));
    m_dialogLifecycleTransformer->onDialogStarted(m_mockDialogController);
}

TEST_F(DialogLifecycleTransformerTest, test_on_listening_does_nothing_if_not_started) {
    std::unordered_set<control::ControlName> availableControls;
    m_dialogLifecycleTransformer->onListening(availableControls);

    // strict mock of DialogController will fail if onListening has impact on the request.
}

TEST_F(DialogLifecycleTransformerTest, test_on_thinking_does_nothing_if_not_started) {
    m_dialogLifecycleTransformer->onThinking();

    // strict mock of DialogController will fail if onListening has impact on the request.
}

TEST_F(DialogLifecycleTransformerTest, test_on_other_state_does_nothing_if_not_started) {
    auto controlRegistery = std::make_shared<testing::NiceMock<control::test::MockControlRegistry>>();
    auto controlInvoker = std::make_shared<testing::NiceMock<control::test::MockControlInvoker>>();
    m_dialogLifecycleTransformer->onOtherState(
        dialog::DialogStateFactory::speaking(), controlRegistery, controlInvoker);

    // strict mock of DialogController will fail if onListening has impact on the request.
}

TEST_F(DialogLifecycleTransformerTest, test_on_dialog_stopped_denies_the_request_if_not_started) {
    EXPECT_CALL(*m_mockDialogRequestInterface, onDenied(_));
    m_dialogLifecycleTransformer->onDialogFinished();
}

TEST_F(DialogLifecycleTransformerTest, test_on_dialog_stopped_stops_a_started_dialog) {
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStarted(_));
    m_dialogLifecycleTransformer->onDialogStarted(m_mockDialogController);
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStopped());
    m_dialogLifecycleTransformer->onDialogFinished();
}

TEST_F(DialogLifecycleTransformerTest, test_on_listening_starts_listing_state_of_a_started_dialog) {
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStarted(_));
    m_dialogLifecycleTransformer->onDialogStarted(m_mockDialogController);

    EXPECT_CALL(*m_mockListeningHandlerInterface, onStartListening(_, _));

    std::unordered_set<control::ControlName> availableControls;
    m_dialogLifecycleTransformer->onListening(availableControls);
}

TEST_F(DialogLifecycleTransformerTest, test_on_thinking_starts_thinking_state_of_a_started_dialog) {
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStarted(_));
    m_dialogLifecycleTransformer->onDialogStarted(m_mockDialogController);

    EXPECT_CALL(*m_mockThinkingHandlerInterface, onStartThinking(_));

    m_dialogLifecycleTransformer->onThinking();
}

TEST_F(DialogLifecycleTransformerTest, test_on_other_state_of_speakingsstarts_speaking_state_of_a_started_dialog) {
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStarted(_));
    m_dialogLifecycleTransformer->onDialogStarted(m_mockDialogController);

    EXPECT_CALL(*m_mockSpeakingHandlerInterface, onStartSpeaking(_, _, _));

    auto controlRegistery = std::make_shared<testing::NiceMock<control::test::MockControlRegistry>>();
    auto controlInvoker = std::make_shared<testing::NiceMock<control::test::MockControlInvoker>>();

    m_dialogLifecycleTransformer->onOtherState(
        dialog::DialogStateFactory::speaking(), controlRegistery, controlInvoker);
}

TEST_F(DialogLifecycleTransformerTest, test_on_other_state_starts_speaking_state_of_a_started_dialog) {
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStarted(_));
    m_dialogLifecycleTransformer->onDialogStarted(m_mockDialogController);

    EXPECT_CALL(*m_mockSpeakingHandlerInterface, onStartSpeaking(_, _, _));

    auto controlRegistery = std::make_shared<testing::NiceMock<control::test::MockControlRegistry>>();
    auto controlInvoker = std::make_shared<testing::NiceMock<control::test::MockControlInvoker>>();

    m_dialogLifecycleTransformer->onOtherState(
        dialog::DialogStateFactory::speaking(), controlRegistery, controlInvoker);
}

TEST_F(DialogLifecycleTransformerTest, test_on_dialog_finished_stops_a_dialog_in_listing_state) {
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStarted(_));
    m_dialogLifecycleTransformer->onDialogStarted(m_mockDialogController);
    EXPECT_CALL(*m_mockListeningHandlerInterface, onStartListening(_, _));
    std::unordered_set<control::ControlName> availableControls;
    m_dialogLifecycleTransformer->onListening(availableControls);

    EXPECT_CALL(*m_mockListeningHandlerInterface, onStopListening());
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStopped());
    m_dialogLifecycleTransformer->onDialogFinished();
}

TEST_F(DialogLifecycleTransformerTest, test_on_dialog_finished_stops_a_dialog_in_thinking_state) {
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStarted(_));
    m_dialogLifecycleTransformer->onDialogStarted(m_mockDialogController);
    EXPECT_CALL(*m_mockThinkingHandlerInterface, onStartThinking(_));
    m_dialogLifecycleTransformer->onThinking();

    EXPECT_CALL(*m_mockThinkingHandlerInterface, onStopThinking());
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStopped());
    m_dialogLifecycleTransformer->onDialogFinished();
}

TEST_F(DialogLifecycleTransformerTest, test_on_dialog_finished_stops_a_dialog_in_speaking_state) {
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStarted(_));
    m_dialogLifecycleTransformer->onDialogStarted(m_mockDialogController);
    EXPECT_CALL(*m_mockSpeakingHandlerInterface, onStartSpeaking(_, _, _));
    auto controlRegistery = std::make_shared<testing::NiceMock<control::test::MockControlRegistry>>();
    auto controlInvoker = std::make_shared<testing::NiceMock<control::test::MockControlInvoker>>();
    m_dialogLifecycleTransformer->onOtherState(
        dialog::DialogStateFactory::speaking(), controlRegistery, controlInvoker);

    EXPECT_CALL(*m_mockSpeakingHandlerInterface, onStopSpeaking());
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStopped());
    m_dialogLifecycleTransformer->onDialogFinished();
}

TEST_F(DialogLifecycleTransformerTest, test_on_other_state_for_non_speaking_results_in_error_and_dialog_finished) {
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStarted(_));
    m_dialogLifecycleTransformer->onDialogStarted(m_mockDialogController);

    EXPECT_CALL(*m_mockDialogRequestInterface, onError(_));
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStopped());

    auto controlRegistery = std::make_shared<testing::NiceMock<control::test::MockControlRegistry>>();
    auto controlInvoker = std::make_shared<testing::NiceMock<control::test::MockControlInvoker>>();

    auto invalidState = dialog::DialogStateFactory::create("INVALID_STATE");
    m_dialogLifecycleTransformer->onOtherState(invalidState, controlRegistery, controlInvoker);
}

}  // namespace test
}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
