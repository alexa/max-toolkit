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

#ifndef VII_MOCKDIALOG_H
#define VII_MOCKDIALOG_H

#include <gmock/gmock.h>

#include "Dialog/Dialog.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {
namespace test {

class MockDialog : public Dialog {
public:
    MOCK_METHOD1(onDialogStarted, void(std::shared_ptr<DialogController>));
    MOCK_METHOD1(onListening, void(std::unordered_set<control::ControlName>));
    MOCK_METHOD0(onThinking, void());
    MOCK_METHOD3(
        onOtherState,
        void(const DialogState, std::shared_ptr<control::ControlRegistry>, std::shared_ptr<control::ControlInvoker>));
    MOCK_METHOD0(onDialogFinished, void());
};

}  // namespace test
}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience

#endif  // VII_MOCKDIALOG_H
