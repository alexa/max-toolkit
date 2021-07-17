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

#include "Control/ControlRegistry.h"
#include "Control/ControlInvoker.h"
#include "Control/ControlName.h"
#include "Dialog/DialogRequestLifecycle.h"

#include "Mocks/MockDialog.h"
#include "Mocks/MockDialogRequest.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {
namespace test {

using testing::_;

class DialogRequestLifecycleTest : public ::testing::Test {
protected:
    static std::shared_ptr<MockDialogRequest> createAndSetupMockDialogRequest(bool isStrict = false) {
        auto mockDialog = std::make_shared<MockDialog>();
        if (isStrict) {
            return std::make_shared<testing::StrictMock<MockDialogRequest>>(mockDialog);
        } else {
            return std::make_shared<testing::NiceMock<MockDialogRequest>>(mockDialog);
        }
    }

    static std::shared_ptr<DialogRequestLifecycle> createAndSetupDialogLifecycle(
        std::shared_ptr<DialogRequest> dialogRequest = createAndSetupMockDialogRequest()) {
        return std::make_shared<DialogRequestLifecycle>(dialogRequest);
    }
};

TEST_F(DialogRequestLifecycleTest, test_get_id_returns_the_expected_wrapped_value) {
    auto mockRequest = createAndSetupMockDialogRequest();
    auto lifecycle = createAndSetupDialogLifecycle(mockRequest);
    ASSERT_EQ(mockRequest->getID(), lifecycle->getID());
}

TEST_F(DialogRequestLifecycleTest, test_grant_grants_the_wrapped_request) {
    auto mockRequest = createAndSetupMockDialogRequest();
    auto lifecycle = createAndSetupDialogLifecycle(mockRequest);

    EXPECT_CALL(*mockRequest, onGranted());

    lifecycle->grant();
}

TEST_F(DialogRequestLifecycleTest, test_deny_denies_the_wrapped_request) {
    auto mockRequest = createAndSetupMockDialogRequest();
    auto lifecycle = createAndSetupDialogLifecycle(mockRequest);

    EXPECT_CALL(*mockRequest, onDenied());

    lifecycle->deny();
}

TEST_F(DialogRequestLifecycleTest, test_multiple_calls_to_grant_only_grants_the_wrapped_request_once) {
    auto mockRequest = createAndSetupMockDialogRequest(true);
    auto lifecycle = createAndSetupDialogLifecycle(mockRequest);

    EXPECT_CALL(*mockRequest, onGranted());

    lifecycle->grant();
    lifecycle->grant();
}

TEST_F(DialogRequestLifecycleTest, test_multiple_calls_to_deny_only_denies_the_wrapped_request_once) {
    auto mockRequest = createAndSetupMockDialogRequest(true);
    auto lifecycle = createAndSetupDialogLifecycle(mockRequest);

    EXPECT_CALL(*mockRequest, onDenied());

    lifecycle->deny();
    lifecycle->deny();
}

TEST_F(DialogRequestLifecycleTest, test_a_granted_request_cannot_be_denied) {
    auto mockRequest = createAndSetupMockDialogRequest(true);
    auto lifecycle = createAndSetupDialogLifecycle(mockRequest);

    EXPECT_CALL(*mockRequest, onGranted());

    lifecycle->grant();
    lifecycle->deny();
}

TEST_F(DialogRequestLifecycleTest, test_a_denied_request_cannot_be_granted) {
    auto mockRequest = createAndSetupMockDialogRequest(true);
    auto lifecycle = createAndSetupDialogLifecycle(mockRequest);

    EXPECT_CALL(*mockRequest, onDenied());

    lifecycle->deny();
    lifecycle->grant();
}

}  // namespace test
}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience
