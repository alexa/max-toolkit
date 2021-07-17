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

#ifndef VII_MOCKINTERNALDIALOGCONTROLLER_H
#define VII_MOCKINTERNALDIALOGCONTROLLER_H

#include "Dialog/DialogController.h"
#include "Dialog/DialogState.h"

#include "MockDialogLifecycle.h"

#include <gmock/gmock.h>
#include <memory>

namespace multiAgentExperience {
namespace library {
namespace dialog {
namespace test {

class MockInternalDialogController : public DialogController {
public:
    MockInternalDialogController() : DialogController(std::make_shared<MockDialogLifecycle>()) {
    }
    MOCK_METHOD0(startListening, void());
    MOCK_METHOD0(startThinking, void());
    MOCK_METHOD1(startOtherState, void(const DialogState otherState));
    MOCK_METHOD0(finishDialog, void());
    MOCK_METHOD0(markUninterruptible, void());
};

}  // namespace test
}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience

#endif  // VII_MOCKINTERNALDIALOGCONTROLLER_H
