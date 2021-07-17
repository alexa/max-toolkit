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
#include "Control/Control.h"
#include "Control/ControlAccessKeys.h"
#include "Control/ControlRegistry.h"
#include "Control/ControlStore.h"

#include "Mocks/MockActivity.h"

namespace multiAgentExperience {
namespace library {
namespace activity {
namespace test {

using testing::_;

class ActivityLifecycleTest : public ::testing::Test {
protected:
    std::shared_ptr<MockActivity> m_wrappedActivity;
    std::shared_ptr<ActivityLifecycle> m_activityLifecycle;

    virtual void SetUp() override {
        m_wrappedActivity = std::make_shared<testing::NiceMock<MockActivity>>();
        m_activityLifecycle = std::make_shared<ActivityLifecycle>(m_wrappedActivity);
    }
};

class StoresSomeControlsActivity : public Activity {
public:
    void onControlRegistryAvailable(std::shared_ptr<control::ControlRegistry> controlRegistry) override {
        auto controls = std::unordered_set<std::shared_ptr<control::Control>>();
        auto control = control::Control::create(control::ControlName::STOP, []() {});
        controls.insert(control);
        controlRegistry->update(controls);
    }

    void onForeground() override {
    }

    void onBackground() override {
    }

    void onStop() override {
    }

    ~StoresSomeControlsActivity() override {
    }
};

TEST_F(ActivityLifecycleTest, test_an_activity_lifecycle_does_nothing_on_create) {
    auto strictMockActivity = std::make_shared<testing::StrictMock<MockActivity>>();
    auto lifecycle = std::make_shared<ActivityLifecycle>(strictMockActivity);
    // This test will fail if any lifecycle methods are called during contruction
}

TEST_F(ActivityLifecycleTest, test_an_activity_lifecycle_sets_activity_id_on_request_granted) {
    ActivityID expectedId = 123;
    m_activityLifecycle->markGranted(expectedId);
    ASSERT_EQ(expectedId, m_activityLifecycle->getID());
}

TEST_F(ActivityLifecycleTest, test_an_activity_lifecycle_forwards_the_control_registry) {
    auto controlAccessKeys = std::make_shared<control::ControlAccessKeys>();
    auto store = std::make_shared<control::ControlStore>(controlAccessKeys);
    auto registry = std::make_shared<control::ControlRegistry>(1, control::ControlPriority::CONTENT, store);

    EXPECT_CALL(*m_wrappedActivity, onControlRegistryAvailable(registry));

    m_activityLifecycle->markGranted(1);
    m_activityLifecycle->makeControlRegistryAvailable(registry);
}

TEST_F(ActivityLifecycleTest, test_an_activity_lifecycle_sets_activity_on_foreground_when_entering_foreground) {
    EXPECT_CALL(*m_wrappedActivity, onForeground());

    m_activityLifecycle->markGranted(1);
    m_activityLifecycle->enterForeground();
}

TEST_F(ActivityLifecycleTest, test_an_activity_lifecycle_sets_activity_on_background_when_entering_background) {
    EXPECT_CALL(*m_wrappedActivity, onBackground());

    m_activityLifecycle->markGranted(1);
    m_activityLifecycle->enterBackground();
}

TEST_F(ActivityLifecycleTest, test_an_activity_lifecycle_sets_activity_on_stop_when_stopping) {
    EXPECT_CALL(*m_wrappedActivity, onStop());

    m_activityLifecycle->markGranted(1);
    m_activityLifecycle->stop();
}

TEST_F(
    ActivityLifecycleTest,
    test_an_activity_lifecycle_can_transition_back_and_forth_through_foreground_and_background) {
    EXPECT_CALL(*m_wrappedActivity, onForeground()).Times(2);
    EXPECT_CALL(*m_wrappedActivity, onBackground()).Times(2);

    m_activityLifecycle->markGranted(1);
    m_activityLifecycle->enterForeground();
    m_activityLifecycle->enterBackground();
    m_activityLifecycle->enterForeground();
    m_activityLifecycle->enterBackground();
}

TEST_F(
    ActivityLifecycleTest,
    test_an_activity_lifecycle_does_not_transition_through_foreground_and_background_if_stopped) {
    EXPECT_CALL(*m_wrappedActivity, onForeground()).Times(0);
    EXPECT_CALL(*m_wrappedActivity, onBackground()).Times(0);

    m_activityLifecycle->markGranted(1);
    m_activityLifecycle->stop();
    m_activityLifecycle->enterForeground();
    m_activityLifecycle->enterBackground();
}

TEST_F(
    ActivityLifecycleTest,
    test_an_activity_lifecycle_does_not_call_foreground_more_than_once_without_entering_background) {
    EXPECT_CALL(*m_wrappedActivity, onForeground());

    m_activityLifecycle->markGranted(1);
    m_activityLifecycle->enterForeground();
    m_activityLifecycle->enterForeground();
}

TEST_F(
    ActivityLifecycleTest,
    test_an_activity_lifecycle_does_not_call_background_more_than_once_without_entering_background) {
    EXPECT_CALL(*m_wrappedActivity, onBackground());

    m_activityLifecycle->markGranted(1);
    m_activityLifecycle->enterBackground();
    m_activityLifecycle->enterBackground();
}

TEST_F(ActivityLifecycleTest, test_an_activity_lifecycle_does_not_call_stop_more_than_once) {
    EXPECT_CALL(*m_wrappedActivity, onStop());

    m_activityLifecycle->markGranted(1);
    m_activityLifecycle->stop();
    m_activityLifecycle->stop();
}

TEST_F(ActivityLifecycleTest, test_an_activity_lifecycle_does_not_stop_if_cleaned_up) {
    m_activityLifecycle->markGranted(1);
    m_activityLifecycle->cleanup();

    EXPECT_CALL(*m_wrappedActivity, onStop()).Times(0);

    m_activityLifecycle->stop();
}

TEST_F(ActivityLifecycleTest, test_an_activity_lifecycle_does_not_enter_foreground_if_cleaned_up) {
    m_activityLifecycle->markGranted(1);
    m_activityLifecycle->cleanup();

    EXPECT_CALL(*m_wrappedActivity, onForeground()).Times(0);

    m_activityLifecycle->enterForeground();
}

TEST_F(ActivityLifecycleTest, test_an_activity_lifecycle_does_not_enter_background_if_cleaned_up) {
    m_activityLifecycle->markGranted(1);
    m_activityLifecycle->cleanup();

    EXPECT_CALL(*m_wrappedActivity, onBackground()).Times(0);

    m_activityLifecycle->enterBackground();
}

TEST_F(ActivityLifecycleTest, test_an_activity_lifecycle_removes_all_controls_if_cleaned_up) {
    auto strictMockActivity = std::make_shared<StoresSomeControlsActivity>();
    auto lifecycle = std::make_shared<ActivityLifecycle>(strictMockActivity);

    lifecycle->markGranted(1);

    auto controlAccessKeys = std::make_shared<control::ControlAccessKeys>();
    auto key = controlAccessKeys->requestAccessKey();
    auto store = std::make_shared<control::ControlStore>(controlAccessKeys);
    auto registry = std::make_shared<control::ControlRegistry>(key, control::ControlPriority::CONTENT, store);

    lifecycle->makeControlRegistryAvailable(registry);

    ASSERT_TRUE(store->contains(key));

    lifecycle->cleanup();

    ASSERT_FALSE(store->contains(key));
}

TEST_F(ActivityLifecycleTest, test_an_activity_lifecycle_cleans_up_when_destroyed) {
    auto controlAccessKeys = std::make_shared<control::ControlAccessKeys>();
    auto key = controlAccessKeys->requestAccessKey();
    auto store = std::make_shared<control::ControlStore>(controlAccessKeys);
    auto registry = std::make_shared<control::ControlRegistry>(key, control::ControlPriority::CONTENT, store);

    {
        auto strictMockActivity = std::make_shared<StoresSomeControlsActivity>();
        auto lifecycle = std::make_shared<ActivityLifecycle>(strictMockActivity);

        lifecycle->markGranted(1);

        lifecycle->makeControlRegistryAvailable(registry);

        ASSERT_TRUE(store->contains(key));
    }

    ASSERT_FALSE(store->contains(key));
}

}  // namespace test
}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience
