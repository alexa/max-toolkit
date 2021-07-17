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

#include "Activity/FocusManagerActivityChannels.h"

#include "Activity/ActivityLifecycle.h"
#include "Activity/ActivityRequestLifecycle.h"
#include "Activity/ActivityTypeToChannelUtils.h"
#include "Activity/CurrentActivities.h"
#include "Activity/FocusManager/FocusManager.h"
#include "Control/ControlAccessKeys.h"
#include "Control/ControlStore.h"
#include "Control/ControlRegistryFactory.h"

#include "Mocks/MockActivity.h"
#include "Mocks/MockActivityRequest.h"
#include "Mocks/MockCurrentActivityRequests.h"

namespace multiAgentExperience {
namespace library {
namespace activity {
namespace test {

using namespace testing;

using testing::_;

class FocusManagerActivityChannelsTest : public ::testing::Test {
protected:
    std::shared_ptr<MockCurrentActivityRequests> m_mockCurrentActivityRequests;
    std::shared_ptr<ActivityChannels> m_activityChannels;

    virtual void SetUp() override {
        m_mockCurrentActivityRequests = std::make_shared<NiceMock<MockCurrentActivityRequests>>();
        m_activityChannels = setupActivityChannels();
    }

    std::shared_ptr<ActivityChannels> setupActivityChannels() {
        auto unthreadedExecutor = std::make_shared<multiAgentExperience::library::utils::threading::Executor>(false);
        auto focusManager = std::make_shared<FocusManager>(
            FocusManagerActivityChannels::getChannelConfigurations(), unthreadedExecutor);
        auto currentActivities = std::make_shared<CurrentActivities>();
        auto controlAccessKeys = std::make_shared<control::ControlAccessKeys>();
        auto controlStore = std::make_shared<control::ControlStore>(controlAccessKeys);
        auto controlRegistryFactory =
            std::make_shared<control::ControlRegistryFactory>(controlAccessKeys, controlStore);
        return std::make_shared<FocusManagerActivityChannels>(
            focusManager, m_mockCurrentActivityRequests, currentActivities, controlRegistryFactory);
    }

    std::shared_ptr<ActivityRequestLifecycle> setupRequestLifecycleFor(
        const ActivityType activityType,
        std::shared_ptr<NiceMock<MockActivity>> mockActivity) {
        auto mockActivityRequest = std::make_shared<NiceMock<MockActivityRequest>>(activityType, mockActivity);
        auto requestLifecycle = std::make_shared<ActivityRequestLifecycle>(mockActivityRequest);
        auto activityLifecycle = std::make_shared<ActivityLifecycle>(mockActivity);

        ON_CALL(*m_mockCurrentActivityRequests, grant(mockActivityRequest->getID()))
            .WillByDefault(Return(activityLifecycle));
        return requestLifecycle;
    }
};

TEST_F(FocusManagerActivityChannelsTest, test_add_grants_the_request_and_puts_the_activity_in_the_foreground) {
    auto mockActivity = std::make_shared<NiceMock<MockActivity>>();
    auto requestLifecycle = setupRequestLifecycleFor(ActivityType::CONTENT, mockActivity);
    EXPECT_CALL(*mockActivity, onForeground());

    m_activityChannels->add(requestLifecycle);
}

TEST_F(FocusManagerActivityChannelsTest, test_remove_finishes_the_request) {
    auto mockActivity = std::make_shared<NiceMock<MockActivity>>();
    auto requestLifecycle = setupRequestLifecycleFor(ActivityType::CONTENT, mockActivity);
    m_activityChannels->add(requestLifecycle);

    EXPECT_CALL(*m_mockCurrentActivityRequests, finish(requestLifecycle->getID()));

    m_activityChannels->remove(requestLifecycle->getID());
}

TEST_F(FocusManagerActivityChannelsTest, test_remove_stops_the_requests_activity) {
    auto mockActivity = std::make_shared<NiceMock<MockActivity>>();
    auto requestLifecycle = setupRequestLifecycleFor(ActivityType::CONTENT, mockActivity);
    m_activityChannels->add(requestLifecycle);

    EXPECT_CALL(*mockActivity, onStop());

    m_activityChannels->remove(requestLifecycle->getID());
}

TEST_F(FocusManagerActivityChannelsTest, test_destructor_removes_the_request) {
    {
        auto activityChannels = setupActivityChannels();
        auto mockActivity = std::make_shared<NiceMock<MockActivity>>();
        auto requestLifecycle = setupRequestLifecycleFor(ActivityType::CONTENT, mockActivity);
        activityChannels->add(requestLifecycle);

        EXPECT_CALL(*m_mockCurrentActivityRequests, remove(requestLifecycle->getID())).Times(2);
    }
}

TEST_F(FocusManagerActivityChannelsTest, test_destructor_stops_the_requests_activity) {
    {
        auto activityChannels = setupActivityChannels();
        auto mockActivity = std::make_shared<NiceMock<MockActivity>>();
        auto requestLifecycle = setupRequestLifecycleFor(ActivityType::CONTENT, mockActivity);
        activityChannels->add(requestLifecycle);

        EXPECT_CALL(*mockActivity, onStop());
    }
}

TEST_F(FocusManagerActivityChannelsTest, test_destructor_removes_and_stops_everything) {
    {
        auto mockActivityLow = std::make_shared<NiceMock<MockActivity>>();
        auto requestLifecycleLow = setupRequestLifecycleFor(ActivityType::CONTENT, mockActivityLow);
        m_activityChannels->add(requestLifecycleLow);

        auto mockActivityHigh = std::make_shared<NiceMock<MockActivity>>();
        auto requestLifecycleHigh = setupRequestLifecycleFor(ActivityType::DIALOG, mockActivityHigh);
        m_activityChannels->add(requestLifecycleHigh);

        EXPECT_CALL(*m_mockCurrentActivityRequests, remove(requestLifecycleLow->getID())).Times(2);
        EXPECT_CALL(*m_mockCurrentActivityRequests, remove(requestLifecycleHigh->getID())).Times(2);
        EXPECT_CALL(*mockActivityLow, onStop());
        EXPECT_CALL(*mockActivityHigh, onStop());
    }
}

TEST_F(FocusManagerActivityChannelsTest, test_adding_a_higher_priority_request_puts_both_activities_in_correct_state) {
    auto mockActivityLow = std::make_shared<NiceMock<MockActivity>>();
    auto requestLifecycleLow = setupRequestLifecycleFor(ActivityType::CONTENT, mockActivityLow);

    EXPECT_CALL(*mockActivityLow, onForeground());
    m_activityChannels->add(requestLifecycleLow);

    auto mockActivityHigh = std::make_shared<NiceMock<MockActivity>>();
    auto requestLifecycleHigh = setupRequestLifecycleFor(ActivityType::DIALOG, mockActivityHigh);

    EXPECT_CALL(*mockActivityLow, onBackground());
    EXPECT_CALL(*mockActivityHigh, onForeground());

    m_activityChannels->add(requestLifecycleHigh);

    // clear expectations for destructor side effects here
    Mock::VerifyAndClearExpectations(mockActivityLow.get());
    Mock::VerifyAndClearExpectations(mockActivityHigh.get());
}

TEST_F(FocusManagerActivityChannelsTest, test_adding_a_lower_priority_request_puts_both_activities_in_correct_state) {
    auto mockActivityHigh = std::make_shared<NiceMock<MockActivity>>();
    auto requestLifecycleHigh = setupRequestLifecycleFor(ActivityType::DIALOG, mockActivityHigh);
    EXPECT_CALL(*mockActivityHigh, onForeground());

    m_activityChannels->add(requestLifecycleHigh);

    auto mockActivityLow = std::make_shared<NiceMock<MockActivity>>();
    auto requestLifecycleLow = setupRequestLifecycleFor(ActivityType::CONTENT, mockActivityLow);
    EXPECT_CALL(*mockActivityLow, onBackground());
    m_activityChannels->add(requestLifecycleLow);

    // clear expectations for destructor side effects here
    Mock::VerifyAndClearExpectations(mockActivityLow.get());
    Mock::VerifyAndClearExpectations(mockActivityHigh.get());
}

TEST_F(FocusManagerActivityChannelsTest, test_adding_more_than_one_activity_at_the_same_priority_stops_the_earliest) {
    auto mockActivityOne = std::make_shared<NiceMock<MockActivity>>();
    auto requestLifecycleOne = setupRequestLifecycleFor(ActivityType::CONTENT, mockActivityOne);
    m_activityChannels->add(requestLifecycleOne);

    auto mockActivityTwo = std::make_shared<NiceMock<MockActivity>>();
    auto requestLifecycleTwo = setupRequestLifecycleFor(ActivityType::CONTENT, mockActivityTwo);
    EXPECT_CALL(*mockActivityOne, onStop());
    EXPECT_CALL(*mockActivityTwo, onForeground());
    m_activityChannels->add(requestLifecycleTwo);

    // clear expectations for destructor side effects here
    Mock::VerifyAndClearExpectations(mockActivityOne.get());
    Mock::VerifyAndClearExpectations(mockActivityTwo.get());
}

TEST_F(FocusManagerActivityChannelsTest, test_removing_a_higher_priority_request_puts_the_lower_in_foreground) {
    auto mockActivityHigh = std::make_shared<NiceMock<MockActivity>>();
    auto requestLifecycleHigh = setupRequestLifecycleFor(ActivityType::DIALOG, mockActivityHigh);
    m_activityChannels->add(requestLifecycleHigh);

    auto mockActivityLow = std::make_shared<NiceMock<MockActivity>>();
    auto requestLifecycleLow = setupRequestLifecycleFor(ActivityType::CONTENT, mockActivityLow);
    m_activityChannels->add(requestLifecycleLow);

    EXPECT_CALL(*mockActivityLow, onForeground());
    m_activityChannels->remove(requestLifecycleHigh->getID());

    // clear expectations for destructor side effects here
    Mock::VerifyAndClearExpectations(mockActivityLow.get());
    Mock::VerifyAndClearExpectations(mockActivityHigh.get());
}

}  // namespace test
}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience
