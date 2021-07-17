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

#ifndef VII_MOCKACTIVITYCHANNELS_H
#define VII_MOCKACTIVITYCHANNELS_H

#include <gmock/gmock.h>

#include "Activity/ActivityChannels.h"

namespace multiAgentExperience {
namespace library {
namespace activity {
namespace test {

class MockActivityChannels : public ActivityChannels {
public:
    MOCK_METHOD1(add, bool(std::shared_ptr<ActivityRequestLifecycle>));
    MOCK_METHOD1(remove, void(const ActivityRequestID));
};

}  // namespace test
}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // VII_MOCKACTIVITYCHANNELS_H
