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

#ifndef VII_CORE_DIALOG_MOCKSPEAKINGHANDLERINTERFACE_H
#define VII_CORE_DIALOG_MOCKSPEAKINGHANDLERINTERFACE_H

#include "MultiAgentExperience/Dialog/SpeakingHandlerInterface.h"
#include "MultiAgentExperience/Dialog/DialogControllerInterface.h"

#include <gmock/gmock.h>
#include <memory>

namespace multiAgentExperience {
namespace experience {
class ExperienceControllerInterface;
}  // namespace experience

namespace control {
class ControlRegistryInterface;
}  // namespace control

namespace dialog {
class DialogControllerInterface;
namespace test {

class MockSpeakingHandlerInterface : public multiAgentExperience::dialog::SpeakingHandlerInterface {
public:
    MOCK_METHOD3(
        onStartSpeaking,
        void(
            std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface>,
            std::shared_ptr<multiAgentExperience::experience::ExperienceControllerInterface>,
            std::shared_ptr<multiAgentExperience::control::ControlRegistryInterface>));
    MOCK_METHOD0(onStopSpeaking, void());
};

}  // namespace test
}  // namespace dialog
}  // namespace multiAgentExperience

#endif  // VII_CORE_DIALOG_MOCKSPEAKINGHANDLERINTERFACE_H
