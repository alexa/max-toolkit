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

#ifndef VII_CORE_ACTIVITY_MOCKACTIVITYCONTROLLERINTERFACE_H
#define VII_CORE_ACTIVITY_MOCKACTIVITYCONTROLLERINTERFACE_H

#include "MultiAgentExperience/Activity/ActivityControllerInterface.h"

#include <gmock/gmock.h>
#include <memory>

namespace multiAgentExperience {
namespace library {
namespace core {
namespace activity {
namespace test {

class MockActivityControllerInterface : public ActivityControllerInterface {
public:
    MOCK_METHOD0(stop, void());
};

}  // namespace test
}  // namespace activity
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // VII_CORE_ACTIVITY_MOCKACTIVITYCONTROLLERINTERFACE_H
