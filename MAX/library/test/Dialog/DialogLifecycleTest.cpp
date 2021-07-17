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

#include <utility>

#include "Control/Control.h"
#include "Control/ControlAccessKeys.h"
#include "Control/ControlRegistry.h"
#include "Control/ControlRegistryFactory.h"
#include "Control/ControlInvoker.h"
#include "Control/ControlInvokerFactory.h"
#include "Control/ControlStore.h"
#include "Control/CurrentControls.h"
#include "Dialog/DialogController.h"
#include "Dialog/DialogLifecycle.h"

#include "Mocks/MockDialog.h"
#include "Verifiers/ControlNameSetVerifier.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {
namespace test {

using testing::_;

class DialogLifecycleTest : public ::testing::Test {
protected:
    std::shared_ptr<control::ControlAccessKeys> m_controlAccessKeys;
    std::shared_ptr<control::ControlStore> m_controlStore;

    void SetUp() override {
        m_controlAccessKeys = std::make_shared<control::ControlAccessKeys>();
        m_controlStore = std::make_shared<control::ControlStore>(m_controlAccessKeys);
    }

    static std::shared_ptr<MockDialog> createAndSetupMockDialog(bool isStrict = false) {
        if (isStrict) {
            return std::make_shared<testing::StrictMock<MockDialog>>();
        } else {
            return std::make_shared<testing::NiceMock<MockDialog>>();
        }
    }

    std::shared_ptr<DialogLifecycle> createAndSetupDialogLifecycle(
        std::shared_ptr<Dialog> dialog = createAndSetupMockDialog()) {
        auto controlRegistryFactory =
            std::make_shared<control::ControlRegistryFactory>(m_controlAccessKeys, m_controlStore);
        auto currentControls =
            std::make_shared<control::CurrentControls>(m_controlAccessKeys->requestAccessKey(), m_controlStore);
        auto controlInvokerFactory =
            std::make_shared<control::ControlInvokerFactory>(m_controlAccessKeys, m_controlStore);
        return std::make_shared<DialogLifecycle>(
            dialog, currentControls, controlRegistryFactory, controlInvokerFactory);
    }
};

class DialogControllerVerifier {
public:
    explicit DialogControllerVerifier(std::shared_ptr<MockDialog> dialog) : m_mockDialog(std::move(dialog)) {
    }

    void captureDialogController(std::shared_ptr<DialogController> dialogController) {
        EXPECT_CALL(*m_mockDialog, onListening(_));
        dialogController->startListening();

        EXPECT_CALL(*m_mockDialog, onThinking());
        dialogController->startThinking();

        EXPECT_CALL(*m_mockDialog, onOtherState(_, _, _));
        dialogController->startOtherState(DialogStateFactory::create("otherState"));

        EXPECT_CALL(*m_mockDialog, onDialogFinished());
        dialogController->finishDialog();
    }

private:
    std::shared_ptr<MockDialog> m_mockDialog;
};

class OtherStateVerifier {
public:
    void captureControlTypes(
        const DialogState dialogState,
        std::shared_ptr<control::ControlRegistry> controlRegistry,
        std::shared_ptr<control::ControlInvoker> controlInvoker) {
        m_controlRegistry = controlRegistry;
        m_controlInvoker = controlInvoker;
    }

    std::shared_ptr<control::ControlRegistry> getRegistry() {
        return m_controlRegistry;
    }
    std::shared_ptr<control::ControlInvoker> getInvoker() {
        return m_controlInvoker;
    }

private:
    std::shared_ptr<control::ControlRegistry> m_controlRegistry;
    std::shared_ptr<control::ControlInvoker> m_controlInvoker;
};

TEST_F(DialogLifecycleTest, test_starting_a_dialog_lifecycle_starts_the_dialog) {
    auto mockDialog = createAndSetupMockDialog();
    auto dialogLifecycle = createAndSetupDialogLifecycle(mockDialog);

    EXPECT_CALL(*mockDialog, onDialogStarted(_));

    dialogLifecycle->startDialog();
}

TEST_F(DialogLifecycleTest, test_starting_a_dialog_lifecycle_more_than_once_starts_the_dialog_once) {
    auto mockDialog = createAndSetupMockDialog();
    auto dialogLifecycle = createAndSetupDialogLifecycle(mockDialog);

    EXPECT_CALL(*mockDialog, onDialogStarted(_));

    dialogLifecycle->startDialog();
    dialogLifecycle->startDialog();
}

TEST_F(DialogLifecycleTest, test_finishing_an_unstarted_dialog_lifecycle_does_nothing) {
    auto mockDialog = createAndSetupMockDialog(true);
    auto dialogLifecycle = createAndSetupDialogLifecycle(mockDialog);
    dialogLifecycle->finishDialog();
}

TEST_F(DialogLifecycleTest, test_finishing_a_started_dialog_lifecycle_finished_the_dialog) {
    auto mockDialog = createAndSetupMockDialog();
    auto dialogLifecycle = createAndSetupDialogLifecycle(mockDialog);
    dialogLifecycle->startDialog();

    EXPECT_CALL(*mockDialog, onDialogFinished());

    dialogLifecycle->finishDialog();
}

TEST_F(DialogLifecycleTest, test_finishing_a_started_dialog_lifecycle_more_than_once_finished_the_dialog_once) {
    auto mockDialog = createAndSetupMockDialog();
    auto dialogLifecycle = createAndSetupDialogLifecycle(mockDialog);
    dialogLifecycle->startDialog();

    EXPECT_CALL(*mockDialog, onDialogFinished());

    dialogLifecycle->finishDialog();
    dialogLifecycle->finishDialog();
}

TEST_F(DialogLifecycleTest, test_an_unstarted_dialog_lifecycle_cannot_start_listening) {
    auto mockDialog = createAndSetupMockDialog(true);
    auto dialogLifecycle = createAndSetupDialogLifecycle(mockDialog);
    dialogLifecycle->startListening();
}

TEST_F(DialogLifecycleTest, test_an_unstarted_dialog_lifecycle_cannot_start_thinking) {
    auto mockDialog = createAndSetupMockDialog(true);
    auto dialogLifecycle = createAndSetupDialogLifecycle(mockDialog);
    dialogLifecycle->startThinking();
}

TEST_F(DialogLifecycleTest, test_an_unstarted_dialog_lifecycle_cannot_start_another_state) {
    auto mockDialog = createAndSetupMockDialog(true);
    auto dialogLifecycle = createAndSetupDialogLifecycle(mockDialog);
    dialogLifecycle->startOtherState(DialogState("otherState"));
}

TEST_F(DialogLifecycleTest, test_a_finished_dialog_lifecycle_cannot_start_listening) {
    auto mockDialog = createAndSetupMockDialog(true);
    auto dialogLifecycle = createAndSetupDialogLifecycle(mockDialog);

    EXPECT_CALL(*mockDialog, onDialogStarted(_));
    EXPECT_CALL(*mockDialog, onDialogFinished());

    dialogLifecycle->startDialog();
    dialogLifecycle->finishDialog();

    dialogLifecycle->startListening();
}

TEST_F(DialogLifecycleTest, test_a_finished_dialog_lifecycle_cannot_start_thinking) {
    auto mockDialog = createAndSetupMockDialog(true);
    auto dialogLifecycle = createAndSetupDialogLifecycle(mockDialog);

    EXPECT_CALL(*mockDialog, onDialogStarted(_));
    EXPECT_CALL(*mockDialog, onDialogFinished());

    dialogLifecycle->startDialog();
    dialogLifecycle->finishDialog();

    dialogLifecycle->startThinking();
}

TEST_F(DialogLifecycleTest, test_a_finished_dialog_lifecycle_cannot_start_another_state) {
    auto mockDialog = createAndSetupMockDialog(true);
    auto dialogLifecycle = createAndSetupDialogLifecycle(mockDialog);

    EXPECT_CALL(*mockDialog, onDialogStarted(_));
    EXPECT_CALL(*mockDialog, onDialogFinished());
    dialogLifecycle->startDialog();
    dialogLifecycle->finishDialog();

    dialogLifecycle->startOtherState(DialogState("otherState"));
}

TEST_F(DialogLifecycleTest, test_a_started_dialog_lifecycle_can_start_listening) {
    auto mockDialog = createAndSetupMockDialog();
    auto dialogLifecycle = createAndSetupDialogLifecycle(mockDialog);
    dialogLifecycle->startDialog();

    EXPECT_CALL(*mockDialog, onListening(_));

    dialogLifecycle->startListening();
}

TEST_F(DialogLifecycleTest, test_a_started_dialog_lifecycle_can_start_thinking) {
    auto mockDialog = createAndSetupMockDialog();
    auto dialogLifecycle = createAndSetupDialogLifecycle(mockDialog);
    dialogLifecycle->startDialog();

    EXPECT_CALL(*mockDialog, onThinking());

    dialogLifecycle->startThinking();
}

TEST_F(DialogLifecycleTest, test_a_started_dialog_lifecycle_can_start_another_state) {
    auto mockDialog = createAndSetupMockDialog();
    auto dialogLifecycle = createAndSetupDialogLifecycle(mockDialog);
    dialogLifecycle->startDialog();

    EXPECT_CALL(*mockDialog, onOtherState(_, _, _));

    dialogLifecycle->startOtherState(DialogState("otherState"));
}

TEST_F(DialogLifecycleTest, test_a_started_dialog_lifecycle_can_finish_after_start_listening) {
    auto mockDialog = createAndSetupMockDialog();
    auto dialogLifecycle = createAndSetupDialogLifecycle(mockDialog);
    dialogLifecycle->startDialog();
    dialogLifecycle->startListening();

    EXPECT_CALL(*mockDialog, onDialogFinished());
    dialogLifecycle->finishDialog();
}

TEST_F(DialogLifecycleTest, test_a_started_dialog_lifecycle_can_finish_after_start_thinking) {
    auto mockDialog = createAndSetupMockDialog();
    auto dialogLifecycle = createAndSetupDialogLifecycle(mockDialog);
    dialogLifecycle->startDialog();
    dialogLifecycle->startThinking();

    EXPECT_CALL(*mockDialog, onDialogFinished());
    dialogLifecycle->finishDialog();
}

TEST_F(DialogLifecycleTest, test_a_started_dialog_lifecycle_can_finish_after_start_another_state) {
    auto mockDialog = createAndSetupMockDialog();
    auto dialogLifecycle = createAndSetupDialogLifecycle(mockDialog);
    dialogLifecycle->startDialog();
    dialogLifecycle->startOtherState(DialogState("otherState"));

    EXPECT_CALL(*mockDialog, onDialogFinished());
    dialogLifecycle->finishDialog();
}

TEST_F(DialogLifecycleTest, test_a_initially_created_dialog_lifecycle_is_not_interruptible) {
    auto dialogLifecycle = createAndSetupDialogLifecycle();

    ASSERT_FALSE(dialogLifecycle->isInterruptible());
}

TEST_F(DialogLifecycleTest, test_a_started_dialog_lifecycle_without_a_new_state_is_not_interruptible) {
    auto dialogLifecycle = createAndSetupDialogLifecycle();
    dialogLifecycle->startDialog();

    ASSERT_FALSE(dialogLifecycle->isInterruptible());
}

TEST_F(DialogLifecycleTest, test_a_finished_dialog_lifecycle_is_interruptible) {
    auto dialogLifecycle = createAndSetupDialogLifecycle();
    dialogLifecycle->startDialog();
    dialogLifecycle->finishDialog();

    ASSERT_TRUE(dialogLifecycle->isInterruptible());
}

TEST_F(DialogLifecycleTest, test_dialog_lifecycle_in_listening_is_not_interruptible) {
    auto mockDialog = createAndSetupMockDialog();
    auto dialogLifecycle = createAndSetupDialogLifecycle(mockDialog);
    dialogLifecycle->startDialog();
    dialogLifecycle->startListening();

    ASSERT_FALSE(dialogLifecycle->isInterruptible());
}

TEST_F(DialogLifecycleTest, test_dialog_lifecycle_in_thinking_is_not_interruptible) {
    auto mockDialog = createAndSetupMockDialog();
    auto dialogLifecycle = createAndSetupDialogLifecycle(mockDialog);
    dialogLifecycle->startDialog();
    dialogLifecycle->startThinking();

    ASSERT_FALSE(dialogLifecycle->isInterruptible());
}

TEST_F(DialogLifecycleTest, test_dialog_lifecycle_in_some_other_state_is_interruptible) {
    auto mockDialog = createAndSetupMockDialog();
    auto dialogLifecycle = createAndSetupDialogLifecycle(mockDialog);
    dialogLifecycle->startDialog();
    dialogLifecycle->startOtherState(DialogState("otherState"));

    ASSERT_TRUE(dialogLifecycle->isInterruptible());
}

TEST_F(DialogLifecycleTest, test_start_dialog_passes_the_a_dialog_controller_for_this_dialog) {
    auto mockDialog = createAndSetupMockDialog();
    DialogControllerVerifier dialogControllerVerifier(mockDialog);
    auto dialogLifecycle = createAndSetupDialogLifecycle(mockDialog);

    EXPECT_CALL(*mockDialog, onDialogStarted(_))
        .WillOnce(testing::Invoke([&dialogControllerVerifier](std::shared_ptr<DialogController> dialogController) {
            dialogControllerVerifier.captureDialogController(dialogController);
        }));

    dialogLifecycle->startDialog();
}

TEST_F(DialogLifecycleTest, test_start_listening_passes_the_current_controls_none) {
    library::test::verifiers::ControlNameSetVerifier controlsVerifier;
    auto mockDialog = createAndSetupMockDialog();
    auto dialogLifecycle = createAndSetupDialogLifecycle(mockDialog);
    dialogLifecycle->startDialog();

    EXPECT_CALL(*mockDialog, onListening(_))
        .WillOnce(testing::Invoke([&controlsVerifier](std::unordered_set<control::ControlName> availableControls) {
            controlsVerifier.captureControls(availableControls);
        }));

    std::unordered_set<control::ControlName> controlNames;
    controlsVerifier.setExpectedControlNames(controlNames);
    dialogLifecycle->startListening();
}

TEST_F(DialogLifecycleTest, test_start_listening_passes_the_current_controls) {
    library::test::verifiers::ControlNameSetVerifier controlsVerifier;
    auto mockDialog = createAndSetupMockDialog();
    auto dialogLifecycle = createAndSetupDialogLifecycle(mockDialog);
    dialogLifecycle->startDialog();

    EXPECT_CALL(*mockDialog, onListening(_))
        .WillOnce(testing::Invoke([&controlsVerifier](std::unordered_set<control::ControlName> availableControls) {
            controlsVerifier.captureControls(availableControls);
        }));

    std::unordered_set<std::shared_ptr<control::Control>> controls;
    controls.insert(control::Control::create(control::ControlName::STOP, []() {}));
    m_controlStore->store(m_controlAccessKeys->requestAccessKey(), control::ControlPriority::CONTENT, controls);

    std::unordered_set<control::ControlName> controlNames;
    controlNames.insert(control::ControlName::STOP);
    controlsVerifier.setExpectedControlNames(controlNames);
    dialogLifecycle->startListening();
}

TEST_F(DialogLifecycleTest, test_starting_an_other_state_gives_access_to_an_active_control_registry) {
    OtherStateVerifier otherStateVerifier;
    auto mockDialog = createAndSetupMockDialog();
    auto dialogLifecycle = createAndSetupDialogLifecycle(mockDialog);
    dialogLifecycle->startDialog();

    EXPECT_CALL(*mockDialog, onOtherState(_, _, _))
        .WillOnce(testing::Invoke([&otherStateVerifier](
                                      const DialogState dialogState,
                                      std::shared_ptr<control::ControlRegistry> controlRegistry,
                                      std::shared_ptr<control::ControlInvoker> controlInvoker) {
            otherStateVerifier.captureControlTypes(dialogState, controlRegistry, controlInvoker);
        }));

    dialogLifecycle->startOtherState(DialogStateFactory::create("otherState"));

    std::unordered_set<std::shared_ptr<control::Control>> controls;
    controls.insert(control::Control::create(control::ControlName::STOP, []() {}));
    auto registry = otherStateVerifier.getRegistry();

    // verify the registry actually puts controls in the store.
    registry->update(controls);
    std::unordered_set<control::ControlName> expectedControlNames;
    expectedControlNames.insert(control::ControlName::STOP);

    auto testKey = m_controlAccessKeys->requestAccessKey();
    for (auto controlName : m_controlStore->getUnionOfControlNames(testKey)) {
        ASSERT_TRUE(expectedControlNames.find(controlName) != expectedControlNames.end());
    }
}

TEST_F(DialogLifecycleTest, test_starting_an_other_state_gives_access_to_an_active_control_invoker) {
    OtherStateVerifier otherStateVerifier;
    auto mockDialog = createAndSetupMockDialog();
    auto dialogLifecycle = createAndSetupDialogLifecycle(mockDialog);
    dialogLifecycle->startDialog();

    EXPECT_CALL(*mockDialog, onOtherState(_, _, _))
        .WillOnce(testing::Invoke([&otherStateVerifier](
                                      const DialogState dialogState,
                                      std::shared_ptr<control::ControlRegistry> controlRegistry,
                                      std::shared_ptr<control::ControlInvoker> controlInvoker) {
            otherStateVerifier.captureControlTypes(dialogState, controlRegistry, controlInvoker);
        }));

    dialogLifecycle->startOtherState(DialogStateFactory::create("otherState"));

    auto result = false;
    std::unordered_set<std::shared_ptr<control::Control>> controls;
    controls.insert(control::Control::create(control::ControlName::STOP, [&result]() { result = true; }));
    auto testKey = m_controlAccessKeys->requestAccessKey();
    m_controlStore->store(testKey, control::ControlPriority::COMMUNICATIONS, controls);

    // verify the invoker actually calls controls in the store.
    auto invoker = otherStateVerifier.getInvoker();
    invoker->invoke(control::ControlName::STOP);

    ASSERT_TRUE(result);
}

TEST_F(DialogLifecycleTest, test_starting_an_other_state_revokes_access_to_old_control_registry) {
    OtherStateVerifier otherStateVerifier;
    auto mockDialog = createAndSetupMockDialog();
    auto dialogLifecycle = createAndSetupDialogLifecycle(mockDialog);
    dialogLifecycle->startDialog();

    EXPECT_CALL(*mockDialog, onOtherState(_, _, _))
        .WillOnce(testing::Invoke([&otherStateVerifier](
                                      const DialogState dialogState,
                                      std::shared_ptr<control::ControlRegistry> controlRegistry,
                                      std::shared_ptr<control::ControlInvoker> controlInvoker) {
            otherStateVerifier.captureControlTypes(dialogState, controlRegistry, controlInvoker);
        }));

    dialogLifecycle->startOtherState(DialogStateFactory::create("otherState"));
    dialogLifecycle->startListening();

    std::unordered_set<std::shared_ptr<control::Control>> controls;
    controls.insert(control::Control::create(control::ControlName::STOP, []() {}));
    auto registry = otherStateVerifier.getRegistry();

    // verify the registry actually puts controls in the store.
    registry->update(controls);

    auto testKey = m_controlAccessKeys->requestAccessKey();
    ASSERT_TRUE(m_controlStore->getUnionOfControlNames(testKey).empty());
}

TEST_F(DialogLifecycleTest, test_starting_an_other_state_revokes_access_to_old_control_invoker) {
    OtherStateVerifier otherStateVerifier;
    auto mockDialog = createAndSetupMockDialog();
    auto dialogLifecycle = createAndSetupDialogLifecycle(mockDialog);
    dialogLifecycle->startDialog();

    EXPECT_CALL(*mockDialog, onOtherState(_, _, _))
        .WillOnce(testing::Invoke([&otherStateVerifier](
                                      const DialogState dialogState,
                                      std::shared_ptr<control::ControlRegistry> controlRegistry,
                                      std::shared_ptr<control::ControlInvoker> controlInvoker) {
            otherStateVerifier.captureControlTypes(dialogState, controlRegistry, controlInvoker);
        }));

    dialogLifecycle->startOtherState(DialogStateFactory::create("otherState"));
    dialogLifecycle->startListening();

    std::unordered_set<std::shared_ptr<control::Control>> controls;
    controls.insert(control::Control::create(control::ControlName::STOP, []() { FAIL(); }));
    auto testKey = m_controlAccessKeys->requestAccessKey();
    m_controlStore->store(testKey, control::ControlPriority::CONTENT, controls);

    // verify the invoker actually calls controls in the store.
    auto invoker = otherStateVerifier.getInvoker();
    invoker->invoke(control::ControlName::STOP);
    // fails if the control body if it is actually invoked.
}

TEST_F(DialogLifecycleTest, test_destructor_cleans_up_access_to_controls) {
    OtherStateVerifier otherStateVerifier;
    {
        auto mockDialog = createAndSetupMockDialog();
        auto dialogLifecycle = createAndSetupDialogLifecycle(mockDialog);
        dialogLifecycle->startDialog();

        EXPECT_CALL(*mockDialog, onOtherState(_, _, _))
            .WillOnce(testing::Invoke([&otherStateVerifier](
                                          const DialogState dialogState,
                                          std::shared_ptr<control::ControlRegistry> controlRegistry,
                                          std::shared_ptr<control::ControlInvoker> controlInvoker) {
                otherStateVerifier.captureControlTypes(dialogState, controlRegistry, controlInvoker);
            }));

        dialogLifecycle->startOtherState(DialogStateFactory::create("otherState"));
    }

    // verify registry doesnt work first
    std::unordered_set<std::shared_ptr<control::Control>> controls;
    controls.insert(control::Control::create(control::ControlName::STOP, []() { FAIL(); }));
    auto registry = otherStateVerifier.getRegistry();

    // verify the registry actually puts controls in the store.
    registry->update(controls);

    auto testKey = m_controlAccessKeys->requestAccessKey();
    ASSERT_TRUE(m_controlStore->getUnionOfControlNames(testKey).empty());

    // verify invoker does not work
    m_controlStore->store(testKey, control::ControlPriority::CONTENT, controls);

    // verify the invoker actually calls controls in the store.
    auto invoker = otherStateVerifier.getInvoker();
    invoker->invoke(control::ControlName::STOP);
    // fails if the control body if it is actually invoked.
}

}  // namespace test
}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience
