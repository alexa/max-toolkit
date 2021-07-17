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

#ifndef VII_CORE_EXPERIENCE_MOCKDIALOGCONTROLLERINTERFACE_H
#define VII_CORE_EXPERIENCE_MOCKDIALOGCONTROLLERINTERFACE_H

#include "MultiAgentExperience/Dialog/DialogControllerInterface.h"
#include "MultiAgentExperience/Control/Control.h"
#include "Core/Transformer/DialogState.h"

#include <gmock/gmock.h>
#include <memory>

namespace multiAgentExperience {
namespace dialog {
namespace test {

class MockDialogControllerInterface : public multiAgentExperience::dialog::DialogControllerInterface {
public:
    MOCK_METHOD0(startListening, void());
    MOCK_METHOD0(startThinking, void());
    MOCK_METHOD0(startSpeaking, void());
    MOCK_METHOD1(invokeControlAndStartSpeaking, void(const multiAgentExperience::control::ControlType&));
    MOCK_METHOD1(checkCrosswake, bool(const std::string&));
    MOCK_METHOD0(stop, void());
    MOCK_METHOD1(stopAndInvokeControl, void(const multiAgentExperience::control::ControlType&));
};

}  // namespace test
}  // namespace dialog
}  // namespace multiAgentExperience

#endif  // VII_CORE_EXPERIENCE_MOCKDIALOGCONTROLLERINTERFACE_H
