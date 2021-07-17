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

#include <gmock/gmock.h>

#include "Activity/ActivityType.h"
#include "Activity/ActivityManager.h"
#include "Activity/ChannelToActivityObserver.h"
#include "Activity/CurrentActivities.h"
#include "Activity/CurrentActivityRequests.h"
#include "Activity/FocusManagerActivityChannels.h"
#include "Activity/FocusManager/FocusManager.h"
#include "Control/Control.h"
#include "Control/ControlAccessKeys.h"
#include "Control/ControlRegistryFactory.h"
#include "Control/ControlStore.h"

#include "Mocks/MockActivity.h"
#include "Mocks/MockActivityRequest.h"

namespace multiAgentExperience {
namespace library {
namespace activity {
namespace test {

using testing::_;

class ActivityManagerTest : public ::testing::Test {
protected:
    std::shared_ptr<ActivityManager> m_activityManager;

    virtual void SetUp() override {
        auto unthreadedExecutor = std::make_shared<multiAgentExperience::library::utils::threading::Executor>(false);
        auto focusManager = std::make_shared<FocusManager>(
            FocusManagerActivityChannels::getChannelConfigurations(), unthreadedExecutor);
        auto currentActivityRequests = std::make_shared<CurrentActivityRequests>();
        auto currentActivities = std::make_shared<CurrentActivities>();
        auto controlAccessKeys = std::make_shared<control::ControlAccessKeys>();
        auto controlStore = std::make_shared<control::ControlStore>(controlAccessKeys);
        auto controlRegistryFactory =
            std::make_shared<control::ControlRegistryFactory>(controlAccessKeys, controlStore);
        auto activityChannels = std::make_shared<FocusManagerActivityChannels>(
            focusManager, currentActivityRequests, currentActivities, controlRegistryFactory);

        m_activityManager = std::make_shared<ActivityManager>(activityChannels, currentActivityRequests);
    }

    static std::shared_ptr<MockActivity> createAndSetupMockActivity() {
        return std::make_shared<testing::NiceMock<MockActivity>>();
    }

    static std::shared_ptr<MockActivityRequest> createAndSetupMockActivityRequest(
        const ActivityType activityType,
        const std::shared_ptr<Activity> activity = createAndSetupMockActivity(),
        const bool isWillingToWait = false) {
        auto mockActivityRequest =
            std::make_shared<testing::NiceMock<MockActivityRequest>>(activityType, activity, isWillingToWait);
        return mockActivityRequest;
    }
};

TEST_F(ActivityManagerTest, test_a_valid_activity_request_is_granted) {
    auto mockActivityRequest = createAndSetupMockActivityRequest(ActivityType::CONTENT);

    EXPECT_CALL(*mockActivityRequest, onGranted());

    m_activityManager->request(mockActivityRequest);
}

TEST_F(ActivityManagerTest, test_a_valid_activity_request_is_finished_when_the_requester_finishes_it) {
    auto mockActivityRequest = createAndSetupMockActivityRequest(ActivityType::CONTENT);

    m_activityManager->request(mockActivityRequest);

    EXPECT_CALL(*mockActivityRequest, onFinished());

    m_activityManager->finish(mockActivityRequest->getID());
}

TEST_F(ActivityManagerTest, test_a_granted_activity_is_given_an_id) {
    auto mockActivity = createAndSetupMockActivity();
    auto mockActivityRequest = createAndSetupMockActivityRequest(ActivityType::CONTENT, mockActivity);

    m_activityManager->request(mockActivityRequest);

    ActivityID notExpected = -1;
    ASSERT_NE(notExpected, mockActivity->getID());
}

TEST_F(ActivityManagerTest, test_an_activity_is_in_the_foreground_when_it_is_the_highest_priority) {
    auto mockActivity = createAndSetupMockActivity();
    auto mockActivityRequest = createAndSetupMockActivityRequest(ActivityType::CONTENT, mockActivity);

    EXPECT_CALL(*mockActivity, onForeground());

    m_activityManager->request(mockActivityRequest);
}

TEST_F(ActivityManagerTest, test_an_activity_is_in_the_background_when_it_is_not_the_highest_priority) {
    auto mockActivityRequestHigh = createAndSetupMockActivityRequest(ActivityType::DIALOG);

    m_activityManager->request(mockActivityRequestHigh);

    auto mockActivityLow = createAndSetupMockActivity();
    auto mockActivityRequestLow = createAndSetupMockActivityRequest(ActivityType::CONTENT, mockActivityLow);

    EXPECT_CALL(*mockActivityLow, onBackground());

    m_activityManager->request(mockActivityRequestLow);
}

TEST_F(ActivityManagerTest, test_an_activity_replaces_an_activity_of_the_same_type) {
    auto mockActivityRequestFirst = createAndSetupMockActivityRequest(ActivityType::CONTENT);

    m_activityManager->request(mockActivityRequestFirst);

    auto mockActivitySecond = createAndSetupMockActivity();
    auto mockActivityRequestSecond = createAndSetupMockActivityRequest(ActivityType::CONTENT, mockActivitySecond);

    EXPECT_CALL(*mockActivitySecond, onForeground());

    m_activityManager->request(mockActivityRequestSecond);
}

TEST_F(ActivityManagerTest, test_a_replaced_activities_request_is_removed) {
    auto mockActivityRequestFirst = createAndSetupMockActivityRequest(ActivityType::CONTENT);

    m_activityManager->request(mockActivityRequestFirst);

    auto mockActivityRequestSecond = createAndSetupMockActivityRequest(ActivityType::CONTENT);

    EXPECT_CALL(*mockActivityRequestFirst, onRemoved());

    m_activityManager->request(mockActivityRequestSecond);
}

TEST_F(ActivityManagerTest, test_a_replaced_activity_is_stopped) {
    auto mockActivityFirst = createAndSetupMockActivity();
    auto mockActivityRequestFirst = createAndSetupMockActivityRequest(ActivityType::CONTENT, mockActivityFirst);

    m_activityManager->request(mockActivityRequestFirst);

    auto mockActivityRequestSecond = createAndSetupMockActivityRequest(ActivityType::CONTENT);

    EXPECT_CALL(*mockActivityFirst, onStop());

    m_activityManager->request(mockActivityRequestSecond);
}

}  // namespace test
}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience
