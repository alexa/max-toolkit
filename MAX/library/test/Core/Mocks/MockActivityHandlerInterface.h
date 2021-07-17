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

#ifndef VII_CORE_ACTIVITY_MOCKACTIVITYHANDLERINTERFACE_H
#define VII_CORE_ACTIVITY_MOCKACTIVITYHANDLERINTERFACE_H

#include "MultiAgentExperience/Activity/ActivityHandlerInterface.h"
#include "MultiAgentExperience/Activity/ActivityControllerInterface.h"
#include "MultiAgentExperience/Activity/ActivityFocus.h"
#include "MultiAgentExperience/Control/ControlRegistryInterface.h"
#include "MultiAgentExperience/Experience/ExperienceControllerInterface.h"

#include <gmock/gmock.h>
#include <memory>
#include <set>

namespace multiAgentExperience {
namespace library {
namespace activity {
namespace test {

class MockActivityHandlerInterface : public multiAgentExperience::activity::ActivityHandlerInterface {
public:
    MOCK_METHOD0(onDenied, void());

    MOCK_METHOD4(
        onReady,
        void(
            std::shared_ptr<multiAgentExperience::activity::ActivityControllerInterface>,
            multiAgentExperience::activity::ActivityFocus,
            std::shared_ptr<multiAgentExperience::control::ControlRegistryInterface>,
            std::shared_ptr<multiAgentExperience::experience::ExperienceControllerInterface>));

    MOCK_METHOD1(onFocusStateChange, void(multiAgentExperience::activity::ActivityFocus));

    MOCK_METHOD0(onStop, void());
};

}  // namespace test
}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // VII_CORE_ACTIVITY_MOCKACTIVITYHANDLERINTERFACE_H
