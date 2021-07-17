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

#include "Activity/ActivityLifecycle.h"
#include "Activity/ChannelToActivityObserver.h"
#include "Activity/CurrentActivities.h"
#include "Control/ControlAccessKeys.h"
#include "Control/ControlRegistryFactory.h"
#include "Control/ControlStore.h"

#include "Mocks/MockActivity.h"
#include "Mocks/MockCurrentActivityRequests.h"

namespace multiAgentExperience {
namespace library {
namespace activity {
namespace test {

using namespace testing;

using testing::_;

class ChannelToActivityObserverTest : public ::testing::Test {
protected:
    const MixingBehavior noopMixingBehavior = MixingBehavior::PRIMARY;
    const ActivityRequestID currentActivityRequestID = ActivityRequestID(123);
    std::shared_ptr<MockActivity> m_mockActivity;
    std::shared_ptr<CurrentActivities> m_currentActivities;
    std::shared_ptr<MockCurrentActivityRequests> m_mockCurrentActivityRequests;
    std::shared_ptr<ChannelToActivityObserver> m_observer;

    virtual void SetUp() override {
        setupObserver();
    }

    void setupObserver(const bool isStrict = false) {
        if (isStrict) {
            m_mockActivity = std::make_shared<StrictMock<MockActivity>>();
            m_mockCurrentActivityRequests = std::make_shared<StrictMock<MockCurrentActivityRequests>>();
        } else {
            m_mockActivity = std::make_shared<NiceMock<MockActivity>>();
            m_mockCurrentActivityRequests = std::make_shared<NiceMock<MockCurrentActivityRequests>>();
        }

        auto activityLifecycle = std::make_shared<ActivityLifecycle>(m_mockActivity);

        ON_CALL(*m_mockCurrentActivityRequests, grant(_)).WillByDefault(Return(activityLifecycle));

        m_currentActivities = std::make_shared<CurrentActivities>();
        auto controlAccessKeys = std::make_shared<control::ControlAccessKeys>();
        auto controlStore = std::make_shared<control::ControlStore>(controlAccessKeys);
        auto controlRegistryFactory =
            std::make_shared<control::ControlRegistryFactory>(controlAccessKeys, controlStore);
        m_observer = std::make_shared<ChannelToActivityObserver>(
            m_mockCurrentActivityRequests,
            m_currentActivities,
            control::ControlPriority::CONTENT,
            controlRegistryFactory,
            currentActivityRequestID);
    }
};

TEST_F(ChannelToActivityObserverTest, test_first_entering_foreground_grants_the_given_request) {
    EXPECT_CALL(*m_mockCurrentActivityRequests, grant(_));
    m_observer->onFocusChanged(FocusState::FOREGROUND, noopMixingBehavior);
}

TEST_F(ChannelToActivityObserverTest, test_first_entering_foreground_grants_the_activity) {
    ASSERT_EQ(ActivityID(-1), m_mockActivity->getID());
    m_observer->onFocusChanged(FocusState::FOREGROUND, noopMixingBehavior);
    ASSERT_NE(ActivityID(-1), m_mockActivity->getID());
}

TEST_F(ChannelToActivityObserverTest, test_first_entering_foreground_makes_the_activity_active) {
    m_observer->onFocusChanged(FocusState::FOREGROUND, noopMixingBehavior);
    ASSERT_TRUE(m_currentActivities->isCurrent(m_mockActivity->getID()));
}

TEST_F(ChannelToActivityObserverTest, test_first_entering_foreground_gives_the_activity_a_control_registry) {
    EXPECT_CALL(*m_mockActivity, onControlRegistryAvailable(_));
    m_observer->onFocusChanged(FocusState::FOREGROUND, noopMixingBehavior);
}

TEST_F(ChannelToActivityObserverTest, test_entering_foreground_puts_the_activity_in_foreground) {
    EXPECT_CALL(*m_mockActivity, onForeground());
    m_observer->onFocusChanged(FocusState::FOREGROUND, noopMixingBehavior);
}

TEST_F(ChannelToActivityObserverTest, test_entering_a_granted_state_again_does_not_regrant) {
    setupObserver(true);

    EXPECT_CALL(*m_mockCurrentActivityRequests, grant(_));
    EXPECT_CALL(*m_mockActivity, onControlRegistryAvailable(_));
    EXPECT_CALL(*m_mockActivity, onForeground());
    EXPECT_CALL(*m_mockActivity, onBackground());

    m_observer->onFocusChanged(FocusState::FOREGROUND, noopMixingBehavior);
    m_observer->onFocusChanged(FocusState::BACKGROUND, noopMixingBehavior);

    ASSERT_TRUE(m_currentActivities->isCurrent(m_mockActivity->getID()));

    // expected destructor side effects below as the mocks are strict
    EXPECT_CALL(*m_mockActivity, onStop());
    EXPECT_CALL(*m_mockCurrentActivityRequests, remove(currentActivityRequestID));
}

TEST_F(ChannelToActivityObserverTest, test_first_entering_background_grants_the_given_request) {
    EXPECT_CALL(*m_mockCurrentActivityRequests, grant(_));
    m_observer->onFocusChanged(FocusState::BACKGROUND, noopMixingBehavior);
}

TEST_F(ChannelToActivityObserverTest, test_first_entering_background_grants_the_activity) {
    ASSERT_EQ(ActivityID(-1), m_mockActivity->getID());
    m_observer->onFocusChanged(FocusState::BACKGROUND, noopMixingBehavior);
    ASSERT_NE(ActivityID(-1), m_mockActivity->getID());
}

TEST_F(ChannelToActivityObserverTest, test_first_entering_background_makes_the_activity_active) {
    m_observer->onFocusChanged(FocusState::BACKGROUND, noopMixingBehavior);
    ASSERT_TRUE(m_currentActivities->isCurrent(m_mockActivity->getID()));
}

TEST_F(ChannelToActivityObserverTest, test_first_entering_background_gives_the_activity_a_control_registry) {
    EXPECT_CALL(*m_mockActivity, onControlRegistryAvailable(_));
    m_observer->onFocusChanged(FocusState::BACKGROUND, noopMixingBehavior);
}

TEST_F(ChannelToActivityObserverTest, test_entering_background_puts_the_activity_in_background) {
    EXPECT_CALL(*m_mockActivity, onBackground());
    m_observer->onFocusChanged(FocusState::BACKGROUND, noopMixingBehavior);
}

TEST_F(ChannelToActivityObserverTest, test_first_entering_none_only_denies_the_request) {
    setupObserver(true);
    EXPECT_CALL(*m_mockCurrentActivityRequests, deny(currentActivityRequestID));
    m_observer->onFocusChanged(FocusState::NONE, noopMixingBehavior);
}

TEST_F(ChannelToActivityObserverTest, test_first_entering_foreground_after_none_does_nothing) {
    setupObserver(true);
    EXPECT_CALL(*m_mockCurrentActivityRequests, deny(currentActivityRequestID));
    m_observer->onFocusChanged(FocusState::NONE, noopMixingBehavior);
    m_observer->onFocusChanged(FocusState::FOREGROUND, noopMixingBehavior);
}
TEST_F(ChannelToActivityObserverTest, test_first_entering_background_after_none_does_nothing) {
    setupObserver(true);
    EXPECT_CALL(*m_mockCurrentActivityRequests, deny(currentActivityRequestID));
    m_observer->onFocusChanged(FocusState::NONE, noopMixingBehavior);
    m_observer->onFocusChanged(FocusState::BACKGROUND, noopMixingBehavior);
}

TEST_F(ChannelToActivityObserverTest, test_entering_none_focus_while_in_foreground_stops_the_activity) {
    EXPECT_CALL(*m_mockActivity, onStop());
    m_observer->onFocusChanged(FocusState::FOREGROUND, noopMixingBehavior);
    m_observer->onFocusChanged(FocusState::NONE, noopMixingBehavior);
}

TEST_F(ChannelToActivityObserverTest, test_entering_none_focus_while_in_bacgkround_stops_the_activity) {
    EXPECT_CALL(*m_mockActivity, onStop());
    m_observer->onFocusChanged(FocusState::BACKGROUND, noopMixingBehavior);
    m_observer->onFocusChanged(FocusState::NONE, noopMixingBehavior);
}

TEST_F(ChannelToActivityObserverTest, test_entering_none_focus_while_in_foreground_removes_the_request) {
    EXPECT_CALL(*m_mockCurrentActivityRequests, remove(currentActivityRequestID)).Times(2);
    m_observer->onFocusChanged(FocusState::FOREGROUND, noopMixingBehavior);
    m_observer->onFocusChanged(FocusState::NONE, noopMixingBehavior);
}

TEST_F(ChannelToActivityObserverTest, test_entering_none_focus_while_in_bacgkround_removes_the_request) {
    EXPECT_CALL(*m_mockCurrentActivityRequests, remove(currentActivityRequestID)).Times(2);
    m_observer->onFocusChanged(FocusState::BACKGROUND, noopMixingBehavior);
    m_observer->onFocusChanged(FocusState::NONE, noopMixingBehavior);
}

TEST_F(ChannelToActivityObserverTest, test_entering_none_focus_while_in_foreground_removes_the_activity) {
    m_observer->onFocusChanged(FocusState::FOREGROUND, noopMixingBehavior);
    m_observer->onFocusChanged(FocusState::NONE, noopMixingBehavior);
    ASSERT_FALSE(m_currentActivities->isCurrent(m_mockActivity->getID()));
}

TEST_F(ChannelToActivityObserverTest, test_entering_none_focus_while_in_bacgkround_removes_the_activity) {
    m_observer->onFocusChanged(FocusState::BACKGROUND, noopMixingBehavior);
    m_observer->onFocusChanged(FocusState::NONE, noopMixingBehavior);
    ASSERT_FALSE(m_currentActivities->isCurrent(m_mockActivity->getID()));
}

TEST_F(ChannelToActivityObserverTest, test_destructor_cleans_up_granted_requests) {
    {
        auto controlAccessKeys = std::make_shared<control::ControlAccessKeys>();
        auto controlStore = std::make_shared<control::ControlStore>(controlAccessKeys);
        auto controlRegistryFactory =
            std::make_shared<control::ControlRegistryFactory>(controlAccessKeys, controlStore);
        auto observer = std::make_shared<ChannelToActivityObserver>(
            m_mockCurrentActivityRequests,
            m_currentActivities,
            control::ControlPriority::DIALOG,
            controlRegistryFactory,
            currentActivityRequestID);

        EXPECT_CALL(*m_mockActivity, onStop());
        EXPECT_CALL(*m_mockCurrentActivityRequests, remove(currentActivityRequestID));
        observer->onFocusChanged(FocusState::FOREGROUND, noopMixingBehavior);
    }

    ASSERT_FALSE(m_currentActivities->isCurrent(m_mockActivity->getID()));
}

}  // namespace test
}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience
