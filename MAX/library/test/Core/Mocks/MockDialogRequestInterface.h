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

#ifndef VII_CORE_DIALOG_MOCKDIALOGREQUESTINTERFACE_H
#define VII_CORE_DIALOG_MOCKDIALOGREQUESTINTERFACE_H

#include <gmock/gmock.h>

#include "MultiAgentExperience/Dialog/DialogRequestInterface.h"

namespace multiAgentExperience {
namespace dialog {
namespace test {

class MockDialogRequestInterface : public multiAgentExperience::dialog::DialogRequestInterface {
public:
    MOCK_METHOD1(onDenied, void(const std::string&));

    MOCK_METHOD1(
        onDialogStarted,
        void(std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> controller));

    MOCK_METHOD1(onError, void(const std::string&));

    MOCK_METHOD0(onDialogStopped, void());
};

}  // namespace test
}  // namespace dialog
}  // namespace multiAgentExperience

#endif  // VII_CORE_DIALOG_MOCKDIALOGREQUESTINTERFACE_H
