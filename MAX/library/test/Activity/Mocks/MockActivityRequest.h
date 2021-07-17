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

#ifndef VII_MOCKACTIVITYREQUEST_H
#define VII_MOCKACTIVITYREQUEST_H

#include <gmock/gmock.h>

#include "Activity/ActivityRequest.h"

namespace multiAgentExperience {
namespace library {
namespace activity {
namespace test {

using ::testing::Return;

class MockActivityRequest : public ActivityRequest {
public:
    MockActivityRequest(
        const ActivityType activityType,
        std::shared_ptr<Activity> activity,
        bool isWillingToWait = false) :
            ActivityRequest(activityType, activity, isWillingToWait) {
    }

    MOCK_METHOD0(onGranted, void());
    MOCK_METHOD0(onDenied, void());
    MOCK_METHOD0(onRemoved, void());
    MOCK_METHOD0(onFinished, void());
    MOCK_METHOD0(onWaiting, void());
};

}  // namespace test
}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // VII_MOCKACTIVITYREQUEST_H
