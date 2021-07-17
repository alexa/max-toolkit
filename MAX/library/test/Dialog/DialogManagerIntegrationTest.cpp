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

#include "Activity/ActivityManager.h"
#include "Activity/ActivityManagerFactory.h"
#include "Activity/ActivityRequest.h"
#include "Activity/ActivityType.h"
#include "Control/Control.h"
#include "Control/ControlAccessKeys.h"
#include "Control/ControlRegistryFactory.h"
#include "Control/ControlInvokerFactory.h"
#include "Control/ControlStore.h"
#include "Control/CurrentControls.h"
#include "Dialog/DialogArbitrator.h"
#include "Dialog/DialogController.h"
#include "Dialog/DialogLifecycleFactory.h"
#include "Dialog/DialogManager.h"
#include "Dialog/DialogRequest.h"

#include "Activity/Mocks/MockActivity.h"

#include "Mocks/MockDialog.h"
#include "Mocks/MockDialogRequest.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {
namespace test {

using testing::_;

class DialogManagerIntegrationTest : public ::testing::Test {
protected:
    std::shared_ptr<DialogManager> m_dialogManager;

    virtual void SetUp() override {
        m_dialogManager = createAndSetupAll();
    }

    static std::shared_ptr<activity::ActivityManager> createActivityManager(
        std::shared_ptr<control::ControlRegistryFactory> controlRegistryFactory) {
        return activity::ActivityManagerFactory::create(controlRegistryFactory, false);
    }

    static std::shared_ptr<DialogManager> createAndSetupMockDialogManager(
        std::shared_ptr<control::ControlAccessKeys> controlAccessKeys,
        std::shared_ptr<control::ControlStore> controlStore,
        std::shared_ptr<control::ControlRegistryFactory> controlRegistryFactory,
        std::shared_ptr<activity::ActivityManager> activityManager) {
        auto currentControls =
            std::make_shared<control::CurrentControls>(controlAccessKeys->requestAccessKey(), controlStore);
        auto controlInvokerFactory = std::make_shared<control::ControlInvokerFactory>(controlAccessKeys, controlStore);
        auto dialogLifecycleFactory =
            std::make_shared<DialogLifecycleFactory>(currentControls, controlRegistryFactory, controlInvokerFactory);
        auto dialogArbitrator = std::make_shared<DialogArbitrator>(dialogLifecycleFactory);

        return std::make_shared<DialogManager>(dialogArbitrator, activityManager);
    }

    static std::shared_ptr<DialogManager> createAndSetupAll() {
        auto controlAccessKeys = std::make_shared<control::ControlAccessKeys>();
        auto controlStore = std::make_shared<control::ControlStore>(controlAccessKeys);
        auto controlRegistryFactory =
            std::make_shared<control::ControlRegistryFactory>(controlAccessKeys, controlStore);
        auto activityManager = createActivityManager(controlRegistryFactory);
        return createAndSetupMockDialogManager(
            controlAccessKeys, controlStore, controlRegistryFactory, activityManager);
    }

    static std::shared_ptr<MockDialog> createAndSetupMockDialog() {
        return std::make_shared<testing::NiceMock<MockDialog>>();
    }

    static std::shared_ptr<MockDialogRequest> createAndSetupMockDialogRequest(
        const std::shared_ptr<Dialog> dialog = createAndSetupMockDialog()) {
        return std::make_shared<testing::NiceMock<MockDialogRequest>>(dialog);
    }

    class DialogAdapter : public Dialog {
    public:
        void onDialogStarted(std::shared_ptr<DialogController> dialogController) override {
        }

        void onListening(std::unordered_set<control::ControlName> availableControls) override {
        }

        void onThinking() override {
        }

        void onOtherState(
            DialogState otherState,
            std::shared_ptr<control::ControlRegistry> controlRegistry,
            std::shared_ptr<control::ControlInvoker> controlInvoker) override {
        }

        void onDialogFinished() override {
        }
    };

    class InterruptibleDialog : public DialogAdapter {
    public:
        void onDialogStarted(std::shared_ptr<DialogController> dialogController) override {
            dialogController->startOtherState(DialogState("interruptible"));
        }

        void onDialogFinished() override {
            m_wasFinished = true;
        }

        bool wasFinished() {
            return m_wasFinished;
        }

    private:
        bool m_wasFinished = false;
    };
};

class TestActivityRequest : public activity::ActivityRequest {
public:
    TestActivityRequest(activity::ActivityType activityType, std::shared_ptr<activity::Activity> activity) :
            ActivityRequest(activityType, activity) {
    }

    void onGranted() override {
    }

    void onDenied() override {
    }

    void onRemoved() override {
    }

    void onFinished() override {
    }

    void onWaiting() override {
    }

    ~TestActivityRequest() override {
    }
};

struct DialogControllerValue {
    std::shared_ptr<DialogController> value;
};

TEST_F(DialogManagerIntegrationTest, test_a_valid_dialog_request_is_granted) {
    auto mockDialogRequest = createAndSetupMockDialogRequest();

    EXPECT_CALL(*mockDialogRequest, onGranted());

    m_dialogManager->request(mockDialogRequest);
}

TEST_F(DialogManagerIntegrationTest, test_a_valid_dialog_request_starts_the_dialog) {
    auto mockDialog = createAndSetupMockDialog();
    auto mockDialogRequest = createAndSetupMockDialogRequest(mockDialog);

    EXPECT_CALL(*mockDialog, onDialogStarted(_));

    m_dialogManager->request(mockDialogRequest);
}

TEST_F(DialogManagerIntegrationTest, test_a_dialog_controller_finsih_dialog_removes_the_request) {
    auto mockDialog = createAndSetupMockDialog();
    auto mockDialogRequest = createAndSetupMockDialogRequest(mockDialog);

    DialogControllerValue capturedDialogController;
    auto captor = [&capturedDialogController](std::shared_ptr<DialogController> dialogController) {
        capturedDialogController.value = dialogController;
    };
    EXPECT_CALL(*mockDialog, onDialogStarted(_)).WillRepeatedly(testing::Invoke(captor));

    auto controlAccessKeys = std::make_shared<control::ControlAccessKeys>();
    auto controlStore = std::make_shared<control::ControlStore>(controlAccessKeys);
    auto controlRegistryFactory = std::make_shared<control::ControlRegistryFactory>(controlAccessKeys, controlStore);
    auto activityManager = createActivityManager(controlRegistryFactory);
    auto dialogManager =
        createAndSetupMockDialogManager(controlAccessKeys, controlStore, controlRegistryFactory, activityManager);

    auto mockActivity = std::make_shared<testing::StrictMock<activity::test::MockActivity>>();
    auto activityRequest = std::make_shared<TestActivityRequest>(activity::ActivityType::CONTENT, mockActivity);

    EXPECT_CALL(*mockActivity, onControlRegistryAvailable(_));
    EXPECT_CALL(*mockActivity, onForeground());
    activityManager->request(activityRequest);
    EXPECT_CALL(*mockActivity, onBackground());
    dialogManager->request(mockDialogRequest);

    testing::Mock::VerifyAndClearExpectations(mockActivity.get());

    EXPECT_CALL(*mockActivity, onForeground());
    capturedDialogController.value->finishDialog();
    testing::Mock::VerifyAndClearExpectations(mockActivity.get());

    // destructor side effects
    EXPECT_CALL(*mockActivity, onStop());
}

TEST_F(DialogManagerIntegrationTest, test_finishing_the_current_dialog_request_finishes_the_dialog) {
    auto mockDialog = createAndSetupMockDialog();
    auto mockDialogRequest = createAndSetupMockDialogRequest(mockDialog);
    m_dialogManager->request(mockDialogRequest);

    EXPECT_CALL(*mockDialog, onDialogFinished());

    m_dialogManager->finish(mockDialogRequest->getID());
}

TEST_F(DialogManagerIntegrationTest, test_if_a_dialog_is_active_during_destruction_it_is_finished) {
    {
        auto mockDialog = createAndSetupMockDialog();
        auto mockDialogRequest = createAndSetupMockDialogRequest(mockDialog);
        auto dialogManager = createAndSetupAll();
        dialogManager->request(mockDialogRequest);

        EXPECT_CALL(*mockDialog, onDialogFinished());
    }
}

TEST_F(DialogManagerIntegrationTest, test_finishing_an_irrelavant_id_does_not_finish_the_active_dialog) {
    auto mockDialog = createAndSetupMockDialog();
    auto mockDialogRequest = createAndSetupMockDialogRequest(mockDialog);
    m_dialogManager->request(mockDialogRequest);

    EXPECT_CALL(*mockDialog, onDialogFinished()).Times(0);

    m_dialogManager->finish(DialogRequestID(-1));
    // clear expectations for destructor side effects here
    testing::Mock::VerifyAndClearExpectations(mockDialog.get());
}

TEST_F(DialogManagerIntegrationTest, test_a_valid_request_is_denied_if_a_dialog_is_active_and_uninterruptible) {
    auto mockDialogRequestFirst = createAndSetupMockDialogRequest();
    auto mockDialogRequestSecond = createAndSetupMockDialogRequest();

    m_dialogManager->request(mockDialogRequestFirst);

    EXPECT_CALL(*mockDialogRequestSecond, onDenied());

    m_dialogManager->request(mockDialogRequestSecond);
}

TEST_F(DialogManagerIntegrationTest, test_a_valid_request_is_granted_if_a_dialog_is_active_and_interruptible) {
    auto interruptibleDialog = std::make_shared<InterruptibleDialog>();
    auto mockDialogRequestFirst = createAndSetupMockDialogRequest(interruptibleDialog);
    auto mockDialogRequestSecond = createAndSetupMockDialogRequest();

    m_dialogManager->request(mockDialogRequestFirst);

    EXPECT_CALL(*mockDialogRequestSecond, onGranted());

    m_dialogManager->request(mockDialogRequestSecond);
}

TEST_F(DialogManagerIntegrationTest, test_an_interrupted_dialog_is_finished) {
    auto interruptibleDialog = std::make_shared<InterruptibleDialog>();
    auto mockDialogRequestFirst = createAndSetupMockDialogRequest(interruptibleDialog);
    auto mockDialogRequestSecond = createAndSetupMockDialogRequest();

    m_dialogManager->request(mockDialogRequestFirst);

    m_dialogManager->request(mockDialogRequestSecond);

    ASSERT_TRUE(interruptibleDialog->wasFinished());
}

}  // namespace test
}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience
