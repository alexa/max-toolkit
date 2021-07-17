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

#ifndef VII_CORE_DIALOG_MOCKLISTENINGHANDLERINTERFACE_H
#define VII_CORE_DIALOG_MOCKLISTENINGHANDLERINTERFACE_H

#include "MultiAgentExperience/Dialog/ListeningHandlerInterface.h"
#include "MultiAgentExperience/Dialog/DialogControllerInterface.h"
#include "MultiAgentExperience/Control/Control.h"

#include <gmock/gmock.h>
#include <memory>
#include <set>

namespace multiAgentExperience {
namespace dialog {
namespace test {

class MockListeningHandlerInterface : public multiAgentExperience::dialog::ListeningHandlerInterface {
public:
    MOCK_METHOD2(
        onStartListening,
        void(
            std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface>,
            std::set<multiAgentExperience::control::ControlType>));
    MOCK_METHOD0(onStopListening, void());
};

}  // namespace test
}  // namespace dialog
}  // namespace multiAgentExperience

#endif  // VII_CORE_DIALOG_MOCKLISTENINGHANDLERINTERFACE_H
