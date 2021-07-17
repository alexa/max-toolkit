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

#ifndef VII_MOCKDIALOGREQUEST_H
#define VII_MOCKDIALOGREQUEST_H

#include <gmock/gmock.h>

#include "Dialog/DialogRequest.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {
namespace test {

using namespace multiAgentExperience::library::dialog;

class MockDialogRequest : public DialogRequest {
public:
    MockDialogRequest(std::shared_ptr<Dialog> dialog) : DialogRequest(dialog) {
    }

    MOCK_METHOD0(onGranted, void());
    MOCK_METHOD0(onDenied, void());
};

}  // namespace test
}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience

#endif  // VII_MOCKDIALOGREQUEST_H
