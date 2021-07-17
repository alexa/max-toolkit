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

#include "Core/Transformer/DialogManagerTransformer.h"
#include "Core/Transformer/DialogControllerTransformerFactory.h"
#include "Core/Transformer/CombinedDialogStateHandlersLifecycleFactory.h"

#include "Activity/ActivityManager.h"
#include "Activity/ActivityManagerFactory.h"
#include "Activity/ActivityRequestLifecycle.h"
#include "Activity/CurrentActivityRequests.h"

#include "Control/ControlAccessKeys.h"
#include "Control/ControlRegistryFactory.h"
#include "Control/ControlInvokerFactory.h"
#include "Control/ControlStore.h"
#include "Control/CurrentControls.h"

#include "Core/Transformer/DialogStateHandlerRegistry.h"

#include "Dialog/DialogArbitrator.h"
#include "Dialog/DialogLifecycleFactory.h"
#include "Dialog/DialogManager.h"
#include "Dialog/DialogManagerFactory.h"

#include "Experience/ExperienceManager.h"

#include "Utils/Threading/Executor.h"

#include "Activity/Mocks/MockActivityChannels.h"
#include "Control/Mocks/MockControlInvokerFactory.h"
#include "Dialog/Mocks/MockInternalDialogController.h"

#include "Mocks/MockCombinedDialogStateHandlersLifecycleFactory.h"
#include "Mocks/MockDialogControllerTransformerFactory.h"
#include "Mocks/MockDialogRequestInterface.h"
#include "Mocks/MockExperienceControlInterface.h"
#include "Mocks/MockListeningHandlerInterface.h"
#include "Mocks/MockSpeakingHandlerInterface.h"
#include "Mocks/MockThinkingHandlerInterface.h"

#include <gmock/gmock.h>
#include <memory>

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {
namespace test {

using namespace multiAgentExperience::library::dialog::test;
using namespace multiAgentExperience::dialog::test;
using namespace multiAgentExperience::experience::test;
using testing::Eq;
using testing::Invoke;
using testing::Return;
using testing::_;

static const multiAgentExperience::actor::ActorId AGENT_ID("test_agent");

class DialogManagerTransformerTest : public ::testing::Test {
protected:
    std::shared_ptr<MockListeningHandlerInterface> m_mockListeningHandlerInterface;
    std::shared_ptr<MockThinkingHandlerInterface> m_mockThinkingHandlerInterface;
    std::shared_ptr<MockSpeakingHandlerInterface> m_mockSpeakingHandlerInterface;
    std::shared_ptr<MockDialogRequestInterface> m_mockDialogRequestInterface;
    std::shared_ptr<DialogManagerTransformer> m_dialogManagerTransformer;

    virtual void SetUp() override {
        // Main verification mocks. The represent the complete lifecycle being transformed into.
        m_mockDialogRequestInterface = std::make_shared<testing::StrictMock<MockDialogRequestInterface>>();
        m_mockListeningHandlerInterface = std::make_shared<testing::StrictMock<MockListeningHandlerInterface>>();
        m_mockThinkingHandlerInterface = std::make_shared<testing::StrictMock<MockThinkingHandlerInterface>>();
        m_mockSpeakingHandlerInterface = std::make_shared<testing::StrictMock<MockSpeakingHandlerInterface>>();

        auto dialogStateHandlersRegistry = std::make_shared<DialogStateHandlerRegistry>();
        auto experienceControllerInterface = std::make_shared<testing::NiceMock<MockExperienceControlInterface>>();
        auto experienceManager =
            std::make_shared<experience::ExperienceManager>(std::make_shared<utils::threading::Executor>(false));
        auto combinedFactory = std::make_shared<transformer::CombinedDialogStateHandlersLifecycleFactory>(
            dialogStateHandlersRegistry, experienceManager);

        auto controlFactory = std::make_shared<testing::NiceMock<control::test::MockControlInvokerFactory>>();
        auto dialogControlTransformerFactory =
            std::make_shared<transformer::DialogControllerTransformerFactory>(controlFactory);

        auto controlAccessKeys = std::make_shared<control::ControlAccessKeys>();
        auto controlStore = std::make_shared<control::ControlStore>(controlAccessKeys);
        auto currentControls =
            std::make_shared<control::CurrentControls>(controlAccessKeys->requestAccessKey(), controlStore);
        auto controlRegistryFactory =
            std::make_shared<control::ControlRegistryFactory>(controlAccessKeys, controlStore);
        auto controlInvokerFactory = std::make_shared<control::ControlInvokerFactory>(controlAccessKeys, controlStore);

        auto currentActivityRequests = std::make_shared<activity::CurrentActivityRequests>();

        auto activityManager = activity::ActivityManagerFactory::create(controlRegistryFactory, false);
        auto dialogManager = dialog::DialogManagerFactory::create(
            activityManager, currentControls, controlInvokerFactory, controlRegistryFactory);

        m_dialogManagerTransformer = std::make_shared<DialogManagerTransformer>(
            AGENT_ID, dialogManager, dialogStateHandlersRegistry, dialogControlTransformerFactory, combinedFactory);
    }
};

struct DialogControllerValue {
    std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> value;
};

TEST_F(DialogManagerTransformerTest, test_requests_are_not_denied_if_no_handlers_are_registered) {
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStarted(_));
    m_dialogManagerTransformer->request(m_mockDialogRequestInterface);
    testing::Mock::VerifyAndClearExpectations(m_mockDialogRequestInterface.get());

    // destructor side effects
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStopped());
}

TEST_F(DialogManagerTransformerTest, test_requests_are_granted_if_the_right_handlers_are_registered) {
    m_dialogManagerTransformer->setListeningHandler(m_mockListeningHandlerInterface);
    m_dialogManagerTransformer->setThinkingHandler(m_mockThinkingHandlerInterface);
    m_dialogManagerTransformer->setSpeakingHandler(m_mockSpeakingHandlerInterface);

    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStarted(_));
    m_dialogManagerTransformer->request(m_mockDialogRequestInterface);
    testing::Mock::VerifyAndClearExpectations(m_mockDialogRequestInterface.get());

    // destructor side effects
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStopped());
}

TEST_F(DialogManagerTransformerTest, test_stop_stops_the_requested_dialog) {
    m_dialogManagerTransformer->setListeningHandler(m_mockListeningHandlerInterface);
    m_dialogManagerTransformer->setThinkingHandler(m_mockThinkingHandlerInterface);
    m_dialogManagerTransformer->setSpeakingHandler(m_mockSpeakingHandlerInterface);

    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStarted(_));
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStopped());
    m_dialogManagerTransformer->request(m_mockDialogRequestInterface);
    m_dialogManagerTransformer->stop(m_mockDialogRequestInterface);
    testing::Mock::VerifyAndClearExpectations(m_mockDialogRequestInterface.get());
}

TEST_F(DialogManagerTransformerTest, test_current_listening_handler_is_used_for_listening_state) {
    m_dialogManagerTransformer->setListeningHandler(m_mockListeningHandlerInterface);
    m_dialogManagerTransformer->setThinkingHandler(m_mockThinkingHandlerInterface);
    m_dialogManagerTransformer->setSpeakingHandler(m_mockSpeakingHandlerInterface);

    DialogControllerValue dialogControllerValue;
    auto captor = [&dialogControllerValue](
                      std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> dialogController) {
        dialogControllerValue.value = dialogController;
    };

    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStarted(_)).WillRepeatedly(testing::Invoke(captor));
    m_dialogManagerTransformer->request(m_mockDialogRequestInterface);

    ASSERT_NE(dialogControllerValue.value, nullptr);
    EXPECT_CALL(*m_mockListeningHandlerInterface, onStartListening(_, _));
    dialogControllerValue.value->startListening();

    // destructor side effects
    EXPECT_CALL(*m_mockListeningHandlerInterface, onStopListening());
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStopped());
}

TEST_F(DialogManagerTransformerTest, test_current_thinking_handler_is_used_for_thinking_state) {
    m_dialogManagerTransformer->setListeningHandler(m_mockListeningHandlerInterface);
    m_dialogManagerTransformer->setThinkingHandler(m_mockThinkingHandlerInterface);
    m_dialogManagerTransformer->setSpeakingHandler(m_mockSpeakingHandlerInterface);

    DialogControllerValue dialogControllerValue;
    auto captor = [&dialogControllerValue](
                      std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> dialogController) {
        dialogControllerValue.value = dialogController;
    };
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStarted(_)).WillRepeatedly(testing::Invoke(captor));
    m_dialogManagerTransformer->request(m_mockDialogRequestInterface);

    ASSERT_NE(dialogControllerValue.value, nullptr);
    EXPECT_CALL(*m_mockThinkingHandlerInterface, onStartThinking(_));
    dialogControllerValue.value->startThinking();

    // destructor side effects
    EXPECT_CALL(*m_mockThinkingHandlerInterface, onStopThinking());
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStopped());
}

TEST_F(DialogManagerTransformerTest, test_current_speaking_handler_is_used_for_speaking_state) {
    m_dialogManagerTransformer->setListeningHandler(m_mockListeningHandlerInterface);
    m_dialogManagerTransformer->setThinkingHandler(m_mockThinkingHandlerInterface);
    m_dialogManagerTransformer->setSpeakingHandler(m_mockSpeakingHandlerInterface);

    DialogControllerValue dialogControllerValue;
    auto captor = [&dialogControllerValue](
                      std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> dialogController) {
        dialogControllerValue.value = dialogController;
    };
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStarted(_)).WillRepeatedly(testing::Invoke(captor));
    m_dialogManagerTransformer->request(m_mockDialogRequestInterface);

    ASSERT_NE(dialogControllerValue.value, nullptr);
    EXPECT_CALL(*m_mockSpeakingHandlerInterface, onStartSpeaking(_, _, _));
    dialogControllerValue.value->startSpeaking();

    // destructor side effects
    EXPECT_CALL(*m_mockSpeakingHandlerInterface, onStopSpeaking());
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStopped());
}

TEST_F(
    DialogManagerTransformerTest,
    test_removing_the_listening_handler_and_trasitioning_to_listening_results_in_error_and_stopped_dialog) {
    m_dialogManagerTransformer->setListeningHandler(m_mockListeningHandlerInterface);
    m_dialogManagerTransformer->setThinkingHandler(m_mockThinkingHandlerInterface);
    m_dialogManagerTransformer->setSpeakingHandler(m_mockSpeakingHandlerInterface);
    m_dialogManagerTransformer->removeListeningHandler();

    DialogControllerValue dialogControllerValue;
    auto captor = [&dialogControllerValue](
                      std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> dialogController) {
        dialogControllerValue.value = dialogController;
    };
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStarted(_)).WillRepeatedly(testing::Invoke(captor));
    m_dialogManagerTransformer->request(m_mockDialogRequestInterface);

    ASSERT_NE(dialogControllerValue.value, nullptr);
    EXPECT_CALL(*m_mockDialogRequestInterface, onError(_));
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStopped());
    dialogControllerValue.value->startListening();
}

TEST_F(
    DialogManagerTransformerTest,
    test_removing_the_thinking_handler_and_trasitioning_to_thinking_results_in_error_and_stopped_dialog) {
    m_dialogManagerTransformer->setListeningHandler(m_mockListeningHandlerInterface);
    m_dialogManagerTransformer->setThinkingHandler(m_mockThinkingHandlerInterface);
    m_dialogManagerTransformer->setSpeakingHandler(m_mockSpeakingHandlerInterface);
    m_dialogManagerTransformer->removeThinkingHandler();

    DialogControllerValue dialogControllerValue;
    auto captor = [&dialogControllerValue](
                      std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> dialogController) {
        dialogControllerValue.value = dialogController;
    };
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStarted(_)).WillRepeatedly(testing::Invoke(captor));
    m_dialogManagerTransformer->request(m_mockDialogRequestInterface);

    ASSERT_NE(dialogControllerValue.value, nullptr);
    EXPECT_CALL(*m_mockDialogRequestInterface, onError(_));
    EXPECT_CALL(*m_mockDialogRequestInterface, onDialogStopped());
    dialogControllerValue.value->startThinking();
}

}  // namespace test
}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
