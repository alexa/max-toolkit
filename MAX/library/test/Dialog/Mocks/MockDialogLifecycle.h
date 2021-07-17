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

#ifndef VII_MOCKDIALOGLIFECYCLE_H
#define VII_MOCKDIALOGLIFECYCLE_H

#include "Dialog/DialogLifecycle.h"
#include "Dialog/DialogState.h"

#include "MockDialog.h"
#include "Control/Mocks/MockControlInvokerFactory.h"
#include "Control/Mocks/MockControlRegistryFactory.h"
#include "Control/Mocks/MockCurrentControls.h"

#include <functional>
#include <gmock/gmock.h>
#include <memory>

namespace multiAgentExperience {
namespace library {
namespace dialog {
namespace test {

class MockDialogLifecycle : public DialogLifecycle {
public:
    MockDialogLifecycle() :
            DialogLifecycle(
                std::make_shared<MockDialog>(),
                std::make_shared<library::control::test::MockCurrentControls>(),
                std::make_shared<library::control::test::MockControlRegistryFactory>(),
                std::make_shared<library::control::test::MockControlInvokerFactory>()) {
    }

    MOCK_METHOD0(isInterruptible, bool());
    MOCK_METHOD1(setOnFinishedCallback, void(std::function<void()>));
    MOCK_METHOD0(startDialog, void());
    MOCK_METHOD0(startListening, void());
    MOCK_METHOD0(startThinking, void());
    MOCK_METHOD1(startOtherState, void(const DialogState&));
    MOCK_METHOD0(finishDialog, void());
    MOCK_METHOD0(markUninterruptible, void());
};

}  // namespace test
}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience

#endif  // VII_MOCKDIALOGLIFECYCLE_H
