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

#ifndef VII_MOCKACTIVITY_H
#define VII_MOCKACTIVITY_H

#include <gmock/gmock.h>

#include "Activity/Activity.h"

namespace multiAgentExperience {
namespace library {
namespace activity {
namespace test {

class MockActivity : public activity::Activity {
public:
    MOCK_METHOD1(onControlRegistryAvailable, void(std::shared_ptr<control::ControlRegistry>));
    MOCK_METHOD0(onForeground, void());
    MOCK_METHOD0(onBackground, void());
    MOCK_METHOD0(onStop, void());
};

}  // namespace test
}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // VII_MOCKACTIVITY_H
