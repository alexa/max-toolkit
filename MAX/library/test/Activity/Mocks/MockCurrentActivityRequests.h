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

#ifndef VII_MOCKCURRENTACTIVITYREQUESTS_H
#define VII_MOCKCURRENTACTIVITYREQUESTS_H

#include <gmock/gmock.h>

#include "Activity/CurrentActivityRequests.h"

namespace multiAgentExperience {
namespace library {
namespace activity {
namespace test {

class MockCurrentActivityRequests : public CurrentActivityRequests {
public:
    MOCK_METHOD1(add, void(std::shared_ptr<ActivityRequestLifecycle> activityRequest));
    MOCK_METHOD1(grant, std::shared_ptr<ActivityLifecycle>(const ActivityRequestID));
    MOCK_METHOD1(wait, bool(const ActivityRequestID));
    MOCK_METHOD1(deny, void(const ActivityRequestID));
    MOCK_METHOD1(remove, const ActivityID(const ActivityRequestID));
    MOCK_METHOD1(finish, const ActivityID(const ActivityRequestID));
};

}  // namespace test
}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // VII_MOCKCURRENTACTIVITYREQUESTS_H
