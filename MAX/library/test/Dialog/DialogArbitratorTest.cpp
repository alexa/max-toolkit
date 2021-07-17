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

#include "Control/ControlAccessKeys.h"
#include "Control/ControlRegistryFactory.h"
#include "Control/ControlInvokerFactory.h"
#include "Control/ControlStore.h"
#include "Control/CurrentControls.h"
#include "Dialog/DialogArbitrator.h"
#include "Dialog/DialogLifecycle.h"
#include "Dialog/DialogLifecycleFactory.h"
#include "Dialog/DialogRequestLifecycle.h"

#include "Mocks/MockDialog.h"
#include "Mocks/MockDialogRequest.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {
namespace test {

using testing::_;

class DialogArbitratorTest : public ::testing::Test {
protected:
    std::shared_ptr<DialogArbitrator> m_dialogArbitrator;

    void SetUp() override {
        auto controlAccessKeys = std::make_shared<control::ControlAccessKeys>();
        auto controlStore = std::make_shared<control::ControlStore>(controlAccessKeys);
        auto currentControlsKey = controlAccessKeys->requestAccessKey();
        auto currentControls = std::make_shared<control::CurrentControls>(currentControlsKey, controlStore);
        auto controlRegistryFactory =
            std::make_shared<control::ControlRegistryFactory>(controlAccessKeys, controlStore);
        auto controlInvokerFactory = std::make_shared<control::ControlInvokerFactory>(controlAccessKeys, controlStore);
        auto dialogLifecycleFactory =
            std::make_shared<DialogLifecycleFactory>(currentControls, controlRegistryFactory, controlInvokerFactory);
        m_dialogArbitrator = std::make_shared<DialogArbitrator>(dialogLifecycleFactory);
    }

    static std::shared_ptr<MockDialogRequest> createAndSetupMockDialogRequest(bool isStrict = false) {
        auto mockDialog = std::make_shared<MockDialog>();
        if (isStrict) {
            return std::make_shared<testing::StrictMock<MockDialogRequest>>(mockDialog);
        } else {
            return std::make_shared<testing::NiceMock<MockDialogRequest>>(mockDialog);
        }
    }
};

TEST_F(DialogArbitratorTest, test_interrupting_succeeds_when_no_other_dialog_is_registered) {
    auto mockRequest = createAndSetupMockDialogRequest();
    ASSERT_TRUE(m_dialogArbitrator->tryInterruptingWith(mockRequest));
}

TEST_F(DialogArbitratorTest, test_interrupting_fails_when_a_non_interruptible_other_dialog_is_registered) {
    auto mockRequestFirst = createAndSetupMockDialogRequest();
    auto mockRequestSecond = createAndSetupMockDialogRequest();
    m_dialogArbitrator->tryInterruptingWith(mockRequestFirst);
    auto currentDialogLifecycle = m_dialogArbitrator->getCurrentDialog();
    currentDialogLifecycle->startDialog();
    currentDialogLifecycle->startListening();
    ASSERT_FALSE(m_dialogArbitrator->tryInterruptingWith(mockRequestSecond));
}

TEST_F(DialogArbitratorTest, test_interrupting_succeds_when_an_interruptible_other_dialog_is_registered) {
    auto mockRequestFirst = createAndSetupMockDialogRequest();
    auto mockRequestSecond = createAndSetupMockDialogRequest();
    m_dialogArbitrator->tryInterruptingWith(mockRequestFirst);
    auto currentDialogLifecycle = m_dialogArbitrator->getCurrentDialog();
    currentDialogLifecycle->startDialog();
    currentDialogLifecycle->startOtherState(DialogStateFactory::create("otherState"));
    ASSERT_TRUE(m_dialogArbitrator->tryInterruptingWith(mockRequestSecond));
}

TEST_F(DialogArbitratorTest, test_cleanup_with_the_current_id_resets_the_arbitrator) {
    auto mockRequestFirst = createAndSetupMockDialogRequest();
    auto mockRequestSecond = createAndSetupMockDialogRequest();
    m_dialogArbitrator->tryInterruptingWith(mockRequestFirst);
    auto currentDialogLifecycle = m_dialogArbitrator->getCurrentDialog();
    currentDialogLifecycle->startDialog();
    currentDialogLifecycle->startListening();
    m_dialogArbitrator->cleanup(mockRequestFirst->getID());
    ASSERT_TRUE(m_dialogArbitrator->tryInterruptingWith(mockRequestSecond));
}

TEST_F(DialogArbitratorTest, test_cleanup_with_a_noncurrent_id_does_nothing) {
    auto mockRequestFirst = createAndSetupMockDialogRequest();
    auto mockRequestSecond = createAndSetupMockDialogRequest();
    m_dialogArbitrator->tryInterruptingWith(mockRequestFirst);
    auto currentDialogLifecycle = m_dialogArbitrator->getCurrentDialog();
    currentDialogLifecycle->startDialog();
    currentDialogLifecycle->startListening();
    m_dialogArbitrator->cleanup(DialogRequestID(-1));
    ASSERT_FALSE(m_dialogArbitrator->tryInterruptingWith(mockRequestSecond));
}

TEST_F(DialogArbitratorTest, test_interrupting_fails_when_an_dialog_is_marked_uninterruptible) {
    auto mockRequestFirst = createAndSetupMockDialogRequest();
    auto mockRequestSecond = createAndSetupMockDialogRequest();
    m_dialogArbitrator->tryInterruptingWith(mockRequestFirst);
    auto currentDialogLifecycle = m_dialogArbitrator->getCurrentDialog();
    currentDialogLifecycle->startDialog();
    currentDialogLifecycle->startOtherState(DialogStateFactory::create("otherState"));
    currentDialogLifecycle->markUninterruptible();
    ASSERT_FALSE(m_dialogArbitrator->tryInterruptingWith(mockRequestSecond));
}

}  // namespace test
}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience
