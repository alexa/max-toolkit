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

#include "Activity/ActivityRequestLifecycle.h"

#include "Mocks/MockActivity.h"
#include "Mocks/MockActivityRequest.h"

namespace multiAgentExperience {
namespace library {
namespace activity {
namespace test {

using testing::_;

class ActivityRequestLifecycleTest : public ::testing::Test {
protected:
    const ActivityType m_activityType = ActivityType::CONTENT;
    std::shared_ptr<MockActivity> m_activity;
    std::shared_ptr<MockActivityRequest> m_wrappedActivityRequest;
    std::shared_ptr<ActivityRequestLifecycle> m_activityRequestLifecycle;

    virtual void SetUp() override {
        m_activity = std::make_shared<testing::NiceMock<MockActivity>>();
        m_wrappedActivityRequest = std::make_shared<testing::NiceMock<MockActivityRequest>>(m_activityType, m_activity);
        m_activityRequestLifecycle = std::make_shared<ActivityRequestLifecycle>(m_wrappedActivityRequest);
    }
};

TEST_F(ActivityRequestLifecycleTest, test_an_activity_request_lifecycle_does_nothing_on_create) {
    auto strictMockRequest = std::make_shared<testing::StrictMock<MockActivityRequest>>(
        m_activityType, std::make_shared<testing::StrictMock<MockActivity>>());
    auto lifecycle = std::make_shared<ActivityRequestLifecycle>(strictMockRequest);
    // This test will fail if any lifecycle methods are called during construction
}

TEST_F(ActivityRequestLifecycleTest, test_getID_returns_a_valid_value) {
    ASSERT_NE(ActivityRequestID(-1), m_activityRequestLifecycle->getID());
}

TEST_F(ActivityRequestLifecycleTest, test_getID_returns_the_same_value_as_the_wrapped_request) {
    ASSERT_EQ(m_wrappedActivityRequest->getID(), m_activityRequestLifecycle->getID());
}

TEST_F(ActivityRequestLifecycleTest, test_getActivityType_returns_the_expected_value) {
    ASSERT_EQ(m_activityType, m_activityRequestLifecycle->getActivityType());
}

TEST_F(ActivityRequestLifecycleTest, test_getActivityType_returns_the_same_value_as_the_wrapped_request) {
    ASSERT_EQ(m_wrappedActivityRequest->getActivityType(), m_activityRequestLifecycle->getActivityType());
}

TEST_F(ActivityRequestLifecycleTest, test_getActivityID_returns_the_expected_value) {
    ASSERT_EQ(m_activity->getID(), m_activityRequestLifecycle->getActivityID());
}

TEST_F(ActivityRequestLifecycleTest, test_getActivityID_returns_the_same_value_as_the_wrapped_request) {
    ASSERT_EQ(m_wrappedActivityRequest->getActivity()->getID(), m_activityRequestLifecycle->getActivityID());
}

TEST_F(ActivityRequestLifecycleTest, test_an_activity_request_lifecycle_sets_request_on_granted_when_granted) {
    EXPECT_CALL(*m_wrappedActivityRequest, onGranted());

    m_activityRequestLifecycle->grant();
}

TEST_F(
    ActivityRequestLifecycleTest,
    test_an_activity_request_lifecycle_which_is_not_willing_to_wait_is_denied_on_enqueue) {
    EXPECT_CALL(*m_wrappedActivityRequest, onDenied());

    m_activityRequestLifecycle->enqueue();
}

TEST_F(ActivityRequestLifecycleTest, test_an_activity_request_lifecycle_which_is_willing_to_wait_is_enqueued) {
    auto strictMockRequest = std::make_shared<testing::StrictMock<MockActivityRequest>>(
        m_activityType, std::make_shared<testing::StrictMock<MockActivity>>(), true);
    auto lifecycle = std::make_shared<ActivityRequestLifecycle>(strictMockRequest);
    EXPECT_CALL(*strictMockRequest, onWaiting());

    lifecycle->enqueue();
}

TEST_F(ActivityRequestLifecycleTest, test_an_activity_request_lifecycle_can_grant_if_enqueued) {
    auto strictMockRequest = std::make_shared<testing::StrictMock<MockActivityRequest>>(
        m_activityType, std::make_shared<testing::StrictMock<MockActivity>>(), true);
    auto lifecycle = std::make_shared<ActivityRequestLifecycle>(strictMockRequest);
    EXPECT_CALL(*strictMockRequest, onWaiting());
    EXPECT_CALL(*strictMockRequest, onGranted());

    lifecycle->enqueue();
    lifecycle->grant();
}

TEST_F(ActivityRequestLifecycleTest, test_an_activity_request_lifecycle_can_deny_if_enqueued) {
    auto strictMockRequest = std::make_shared<testing::StrictMock<MockActivityRequest>>(
        m_activityType, std::make_shared<testing::StrictMock<MockActivity>>(), true);
    auto lifecycle = std::make_shared<ActivityRequestLifecycle>(strictMockRequest);
    EXPECT_CALL(*strictMockRequest, onWaiting());
    EXPECT_CALL(*strictMockRequest, onDenied());

    lifecycle->enqueue();
    lifecycle->deny();
}

TEST_F(ActivityRequestLifecycleTest, test_an_activity_request_lifecycle_only_grants_once) {
    EXPECT_CALL(*m_wrappedActivityRequest, onGranted());

    m_activityRequestLifecycle->grant();
    m_activityRequestLifecycle->grant();
}

TEST_F(ActivityRequestLifecycleTest, test_an_activity_request_lifecycle_can_be_removed_after_granted) {
    EXPECT_CALL(*m_wrappedActivityRequest, onRemoved());

    m_activityRequestLifecycle->grant();
    m_activityRequestLifecycle->remove();
}

TEST_F(ActivityRequestLifecycleTest, test_an_activity_request_lifecycle_can_be_finished_after_granted) {
    EXPECT_CALL(*m_wrappedActivityRequest, onFinished());

    m_activityRequestLifecycle->grant();
    m_activityRequestLifecycle->finish();
}

TEST_F(ActivityRequestLifecycleTest, test_an_activity_request_lifecycle_cannot_be_removed_twice_after_granted) {
    EXPECT_CALL(*m_wrappedActivityRequest, onRemoved());

    m_activityRequestLifecycle->grant();
    m_activityRequestLifecycle->remove();
    m_activityRequestLifecycle->remove();
}

TEST_F(ActivityRequestLifecycleTest, test_an_activity_request_lifecycle_cannot_be_finished_twice_after_granted) {
    EXPECT_CALL(*m_wrappedActivityRequest, onFinished());

    m_activityRequestLifecycle->grant();
    m_activityRequestLifecycle->finish();
    m_activityRequestLifecycle->finish();
}

TEST_F(ActivityRequestLifecycleTest, test_an_activity_request_lifecycle_cannot_be_granted_after_removal) {
    EXPECT_CALL(*m_wrappedActivityRequest, onGranted());
    EXPECT_CALL(*m_wrappedActivityRequest, onRemoved());

    m_activityRequestLifecycle->grant();
    m_activityRequestLifecycle->remove();
    m_activityRequestLifecycle->grant();
}

TEST_F(ActivityRequestLifecycleTest, test_an_activity_request_lifecycle_cannot_be_granted_after_finished) {
    EXPECT_CALL(*m_wrappedActivityRequest, onGranted());
    EXPECT_CALL(*m_wrappedActivityRequest, onFinished());

    m_activityRequestLifecycle->grant();
    m_activityRequestLifecycle->finish();
    m_activityRequestLifecycle->grant();
}

TEST_F(ActivityRequestLifecycleTest, test_an_activity_request_lifecycle_cannot_be_enqueued_after_denial) {
    auto strictMockRequest = std::make_shared<testing::StrictMock<MockActivityRequest>>(
        m_activityType, std::make_shared<testing::StrictMock<MockActivity>>(), true);
    auto lifecycle = std::make_shared<ActivityRequestLifecycle>(strictMockRequest);
    EXPECT_CALL(*strictMockRequest, onDenied());

    lifecycle->deny();
    lifecycle->enqueue();

    // This test will fail because of the strict mocks if onWaiting is called
}

TEST_F(ActivityRequestLifecycleTest, test_an_activity_request_lifecycle_cannot_be_enqueued_after_removal) {
    auto strictMockRequest = std::make_shared<testing::StrictMock<MockActivityRequest>>(
        m_activityType, std::make_shared<testing::StrictMock<MockActivity>>(), true);
    auto lifecycle = std::make_shared<ActivityRequestLifecycle>(strictMockRequest);
    EXPECT_CALL(*strictMockRequest, onGranted());
    EXPECT_CALL(*strictMockRequest, onRemoved());

    lifecycle->grant();
    lifecycle->remove();
    lifecycle->enqueue();

    // This test will fail because of the strict mocks if onWaiting is called
}

TEST_F(ActivityRequestLifecycleTest, test_an_activity_request_lifecycle_cannot_be_enqueued_after_finished) {
    auto strictMockRequest = std::make_shared<testing::StrictMock<MockActivityRequest>>(
        m_activityType, std::make_shared<testing::StrictMock<MockActivity>>(), true);
    auto lifecycle = std::make_shared<ActivityRequestLifecycle>(strictMockRequest);
    EXPECT_CALL(*strictMockRequest, onGranted());
    EXPECT_CALL(*strictMockRequest, onFinished());

    lifecycle->grant();
    lifecycle->finish();
    lifecycle->enqueue();

    // This test will fail because of the strict mocks if onWaiting is called
}

TEST_F(ActivityRequestLifecycleTest, test_an_activity_request_lifecycle_sets_request_on_denied_when_denied) {
    EXPECT_CALL(*m_wrappedActivityRequest, onDenied());

    m_activityRequestLifecycle->deny();
}

TEST_F(ActivityRequestLifecycleTest, test_an_activity_request_lifecycle_only_denies_once) {
    EXPECT_CALL(*m_wrappedActivityRequest, onDenied());

    m_activityRequestLifecycle->deny();
    m_activityRequestLifecycle->deny();
}

TEST_F(ActivityRequestLifecycleTest, test_an_activity_request_lifecycle_does_not_grant_after_a_denial) {
    auto strictMockRequest = std::make_shared<testing::StrictMock<MockActivityRequest>>(
        m_activityType, std::make_shared<testing::StrictMock<MockActivity>>());
    auto lifecycle = std::make_shared<ActivityRequestLifecycle>(strictMockRequest);
    EXPECT_CALL(*strictMockRequest, onDenied());

    lifecycle->deny();
    lifecycle->grant();

    // This test will fail because of the strict mocks if onGranted is called
}

TEST_F(ActivityRequestLifecycleTest, test_an_activity_request_lifecycle_does_not_remove_after_a_denial) {
    auto strictMockRequest = std::make_shared<testing::StrictMock<MockActivityRequest>>(
        m_activityType, std::make_shared<testing::StrictMock<MockActivity>>());
    auto lifecycle = std::make_shared<ActivityRequestLifecycle>(strictMockRequest);
    EXPECT_CALL(*strictMockRequest, onDenied());

    lifecycle->deny();
    lifecycle->remove();

    // This test will fail because of the strict mocks if onRemoved is called
}

TEST_F(ActivityRequestLifecycleTest, test_an_activity_request_lifecycle_does_not_finish_after_a_denial) {
    auto strictMockRequest = std::make_shared<testing::StrictMock<MockActivityRequest>>(
        m_activityType, std::make_shared<testing::StrictMock<MockActivity>>());
    auto lifecycle = std::make_shared<ActivityRequestLifecycle>(strictMockRequest);
    EXPECT_CALL(*strictMockRequest, onDenied());

    lifecycle->deny();
    lifecycle->finish();

    // This test will fail because of the strict mocks if onFinished is called
}

TEST_F(ActivityRequestLifecycleTest, test_an_activity_request_lifecycle_does_not_wait_after_a_denial) {
    auto strictMockRequest = std::make_shared<testing::StrictMock<MockActivityRequest>>(
        m_activityType, std::make_shared<testing::StrictMock<MockActivity>>(), true);
    auto lifecycle = std::make_shared<ActivityRequestLifecycle>(strictMockRequest);
    EXPECT_CALL(*strictMockRequest, onDenied());

    lifecycle->deny();
    lifecycle->enqueue();

    // This test will fail because of the strict mocks if onFinished is called
}

}  // namespace test
}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience
