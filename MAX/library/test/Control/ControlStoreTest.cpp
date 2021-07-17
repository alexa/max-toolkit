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

#include "Control/Control.h"
#include "Control/ControlAccessKeys.h"
#include "Control/ControlStore.h"

#include "Mocks/MockControlStoreObserver.h"
#include "Verifiers/ControlNameSetVerifier.h"

namespace multiAgentExperience {
namespace library {
namespace control {
namespace test {

using testing::_;

class ControlStoreTest : public ::testing::Test {
protected:
    std::shared_ptr<ControlAccessKeys> m_controlAccessKeys;

    virtual void SetUp() override {
        m_controlAccessKeys = std::make_shared<ControlAccessKeys>();
    }

    std::unordered_set<std::shared_ptr<Control>> createStopControl() {
        auto controlNames = std::unordered_set<ControlName>();
        controlNames.insert(ControlName::STOP);
        return createControlsFor(controlNames);
    }

    std::unordered_set<std::shared_ptr<Control>> createControlsFor(std::unordered_set<ControlName> controlNames) {
        auto set = std::unordered_set<std::shared_ptr<Control>>();
        for (auto controlName : controlNames) {
            auto control = Control::create(controlName, []() {});
            set.insert(control);
        }
        return set;
    }
};

TEST_F(ControlStoreTest, test_store_retains_sets_of_controls_by_control_access_key) {
    auto controlAccessKey = m_controlAccessKeys->requestAccessKey();
    ControlStore controlStore(m_controlAccessKeys);
    controlStore.store(controlAccessKey, ControlPriority::CONTENT, createStopControl());

    ASSERT_TRUE(controlStore.contains(controlAccessKey));
}

TEST_F(
    ControlStoreTest,
    test_store_ignores_empty_sets_of_controls_provided_by_control_access_key_without_existing_controls) {
    auto controlAccessKey = m_controlAccessKeys->requestAccessKey();
    ControlStore controlStore(m_controlAccessKeys);
    controlStore.store(controlAccessKey, ControlPriority::CONTENT, {});

    ASSERT_FALSE(controlStore.contains(controlAccessKey));
}

TEST_F(ControlStoreTest, test_store_removes_sets_of_controls_provided_by_control_access_key_with_existing_controls) {
    auto controlAccessKey = m_controlAccessKeys->requestAccessKey();
    ControlStore controlStore(m_controlAccessKeys);
    controlStore.store(controlAccessKey, ControlPriority::CONTENT, createStopControl());
    controlStore.store(controlAccessKey, ControlPriority::CONTENT, {});

    ASSERT_FALSE(controlStore.contains(controlAccessKey));
}

TEST_F(ControlStoreTest, test_remove_removes_sets_of_controls_by_control_access_key) {
    auto controlAccessKey = m_controlAccessKeys->requestAccessKey();
    ControlStore controlStore(m_controlAccessKeys);
    controlStore.store(controlAccessKey, ControlPriority::CONTENT, createStopControl());
    controlStore.remove(controlAccessKey);

    ASSERT_FALSE(controlStore.contains(controlAccessKey));
}

TEST_F(ControlStoreTest, test_revokeAccess_removes_sets_of_controls_by_control_access_key) {
    auto controlAccessKey = m_controlAccessKeys->requestAccessKey();
    ControlStore controlStore(m_controlAccessKeys);
    controlStore.store(controlAccessKey, ControlPriority::CONTENT, createStopControl());
    controlStore.revokeAccess(controlAccessKey);

    ASSERT_FALSE(controlStore.contains(controlAccessKey));
}

TEST_F(ControlStoreTest, test_revokeAccess_disallows_adding_controls_by_control_access_key) {
    auto controlAccessKey = m_controlAccessKeys->requestAccessKey();
    ControlStore controlStore(m_controlAccessKeys);

    controlStore.revokeAccess(controlAccessKey);
    controlStore.store(controlAccessKey, ControlPriority::CONTENT, createStopControl());

    ASSERT_FALSE(controlStore.contains(controlAccessKey));
}

TEST_F(ControlStoreTest, test_stores_multiple_sets_of_controls_by_control_access_key) {
    ControlStore controlStore(m_controlAccessKeys);
    auto controlAccessKey1 = m_controlAccessKeys->requestAccessKey();
    controlStore.store(controlAccessKey1, ControlPriority::CONTENT, createStopControl());
    auto controlAccessKey2 = m_controlAccessKeys->requestAccessKey();
    controlStore.store(controlAccessKey2, ControlPriority::CONTENT, createStopControl());
    auto controlAccessKey3 = m_controlAccessKeys->requestAccessKey();
    controlStore.store(controlAccessKey3, ControlPriority::CONTENT, createStopControl());

    ASSERT_TRUE(controlStore.contains(controlAccessKey1));
    ASSERT_TRUE(controlStore.contains(controlAccessKey2));
    ASSERT_TRUE(controlStore.contains(controlAccessKey3));
}

TEST_F(ControlStoreTest, test_remove_with_multiple_sets_of_controls_only_removes_the_desired_controls) {
    ControlStore controlStore(m_controlAccessKeys);
    auto controlAccessKey1 = m_controlAccessKeys->requestAccessKey();
    controlStore.store(controlAccessKey1, ControlPriority::CONTENT, createStopControl());
    auto controlAccessKey2 = m_controlAccessKeys->requestAccessKey();
    controlStore.store(controlAccessKey2, ControlPriority::CONTENT, createStopControl());
    auto controlAccessKey3 = m_controlAccessKeys->requestAccessKey();
    controlStore.store(controlAccessKey3, ControlPriority::CONTENT, createStopControl());

    controlStore.remove(controlAccessKey2);

    ASSERT_TRUE(controlStore.contains(controlAccessKey1));
    ASSERT_TRUE(controlStore.contains(controlAccessKey3));

    ASSERT_FALSE(controlStore.contains(controlAccessKey2));
}

TEST_F(ControlStoreTest, test_getUnionOfControlNames_returns_a_single_sets_of_controls) {
    ControlStore controlStore(m_controlAccessKeys);
    auto controlAccessKey = m_controlAccessKeys->requestAccessKey();
    auto controlNames = std::unordered_set<ControlName>();
    controlNames.insert(ControlName::STOP);

    controlStore.store(controlAccessKey, ControlPriority::CONTENT, createControlsFor(controlNames));

    auto requestAccessKey = m_controlAccessKeys->requestAccessKey();
    auto unionOfNames = controlStore.getUnionOfControlNames(requestAccessKey);

    ASSERT_EQ(size_t(1), unionOfNames.size());
    ASSERT_TRUE(unionOfNames.find(ControlName::STOP) != unionOfNames.end());
}

TEST_F(ControlStoreTest, test_getUnionOfControlNames_returns_the_union_of_multiple_sets_of_controls_same) {
    ControlStore controlStore(m_controlAccessKeys);
    auto controlAccessKey1 = m_controlAccessKeys->requestAccessKey();
    auto controlNames1 = std::unordered_set<ControlName>();
    controlNames1.insert(ControlName::STOP);
    controlStore.store(controlAccessKey1, ControlPriority::CONTENT, createControlsFor(controlNames1));

    auto controlAccessKey2 = m_controlAccessKeys->requestAccessKey();
    auto controlNames2 = std::unordered_set<ControlName>();
    controlNames2.insert(ControlName::STOP);
    controlStore.store(controlAccessKey2, ControlPriority::CONTENT, createControlsFor(controlNames2));

    auto controlAccessKey3 = m_controlAccessKeys->requestAccessKey();
    auto controlNames3 = std::unordered_set<ControlName>();
    controlNames3.insert(ControlName::STOP);
    controlStore.store(controlAccessKey3, ControlPriority::CONTENT, createControlsFor(controlNames3));

    auto requestAccessKey = m_controlAccessKeys->requestAccessKey();
    auto unionOfNames = controlStore.getUnionOfControlNames(requestAccessKey);

    ASSERT_EQ(size_t(1), unionOfNames.size());
    ASSERT_TRUE(unionOfNames.find(ControlName::STOP) != unionOfNames.end());
}

TEST_F(ControlStoreTest, test_getHighestPriorityControlByName_returns_nullptr_when_empty) {
    ControlStore controlStore(m_controlAccessKeys);
    auto requestAccessKey = m_controlAccessKeys->requestAccessKey();
    ASSERT_EQ(nullptr, controlStore.getHighestPriorityControlByName(requestAccessKey, ControlName::STOP));
}

TEST_F(ControlStoreTest, test_getHighestPriorityControlByName_returns_nullptr_when_the_control_doesnt_exist) {
    ControlStore controlStore(m_controlAccessKeys);
    auto controlAccessKey = m_controlAccessKeys->requestAccessKey();
    std::unordered_set<std::shared_ptr<Control>> controls;

    auto expectedName = ControlName::STOP;
    auto control = Control::create(expectedName, []() {});
    controls.insert(control);

    controlStore.store(controlAccessKey, ControlPriority::DIALOG, controls);

    auto requestAccessKey = m_controlAccessKeys->requestAccessKey();
    ASSERT_EQ(nullptr, controlStore.getHighestPriorityControlByName(requestAccessKey, ControlName::UNDEFINED));
}

TEST_F(ControlStoreTest, test_getHighestPriorityControlByName_return_the_only_control_when_there_is_one) {
    ControlStore controlStore(m_controlAccessKeys);
    auto controlAccessKey = m_controlAccessKeys->requestAccessKey();
    std::unordered_set<std::shared_ptr<Control>> controls;

    auto expectedName = ControlName::STOP;
    auto control = Control::create(expectedName, []() {});
    controls.insert(control);

    controlStore.store(controlAccessKey, ControlPriority::DIALOG, controls);

    auto requestAccessKey = m_controlAccessKeys->requestAccessKey();
    ASSERT_EQ(control, controlStore.getHighestPriorityControlByName(requestAccessKey, expectedName));
}

TEST_F(
    ControlStoreTest,
    test_getHighestPriorityControlByName_return_the_highest_priority_control_when_there_is_more_than_one_provider) {
    ControlStore controlStore(m_controlAccessKeys);
    auto controlAccessKey1 = m_controlAccessKeys->requestAccessKey();
    std::unordered_set<std::shared_ptr<Control>> controls1;
    auto contentStopResult = false;
    auto contentStop = Control::create(ControlName::STOP, [&contentStopResult]() { contentStopResult = true; });
    controls1.insert(contentStop);
    controlStore.store(controlAccessKey1, ControlPriority::CONTENT, controls1);

    auto controlAccessKey2 = m_controlAccessKeys->requestAccessKey();
    std::unordered_set<std::shared_ptr<Control>> controls2;
    auto stopResult = false;
    auto controlStop = Control::create(ControlName::STOP, [&stopResult]() { stopResult = true; });
    controls2.insert(controlStop);
    controlStore.store(controlAccessKey2, ControlPriority::DIALOG, controls2);

    auto requestAccessKey = m_controlAccessKeys->requestAccessKey();
    auto highestStopControl = controlStore.getHighestPriorityControlByName(requestAccessKey, ControlName::STOP);
    ASSERT_FALSE(stopResult);
    highestStopControl->operator()();
    ASSERT_TRUE(stopResult);
}

TEST_F(ControlStoreTest, test_registered_observer_is_notified_when_registered) {
    ControlStore controlStore(m_controlAccessKeys);
    auto mockObserver = std::make_shared<testing::StrictMock<MockControlStoreObserver>>();
    // first with an empty set when registered, then with the controls.
    EXPECT_CALL(*mockObserver, onControlsUpdated(_)).Times(1);

    controlStore.addObserver(mockObserver);
}

TEST_F(ControlStoreTest, test_registered_observer_is_notified_with_an_empty_set_when_there_are_no_controls_stored) {
    ControlStore controlStore(m_controlAccessKeys);
    auto mockObserver = std::make_shared<testing::StrictMock<MockControlStoreObserver>>();
    // first with an empty set when registered, then with the controls.

    library::test::verifiers::ControlNameSetVerifier controlsVerifier;

    EXPECT_CALL(*mockObserver, onControlsUpdated(_))
        .WillOnce(testing::Invoke([&controlsVerifier](std::unordered_set<control::ControlName> availableControls) {
            controlsVerifier.captureControls(availableControls);
        }));

    controlStore.addObserver(mockObserver);
}

TEST_F(ControlStoreTest, test_registered_observer_is_notified_when_a_control_is_stored_after_registration) {
    ControlStore controlStore(m_controlAccessKeys);
    auto mockObserver = std::make_shared<testing::StrictMock<MockControlStoreObserver>>();
    // for registration.
    EXPECT_CALL(*mockObserver, onControlsUpdated(_)).Times(1);
    controlStore.addObserver(mockObserver);

    // after update.
    EXPECT_CALL(*mockObserver, onControlsUpdated(_)).Times(1);
    auto key = m_controlAccessKeys->requestAccessKey();
    controlStore.store(key, ControlPriority::CONTENT, createStopControl());
}

TEST_F(
    ControlStoreTest,
    test_registered_observer_is_notified_with_the_new_control_when_a_control_is_stored_after_registration) {
    ControlStore controlStore(m_controlAccessKeys);
    auto mockObserver = std::make_shared<testing::StrictMock<MockControlStoreObserver>>();
    // first with an empty set when registered, then with the controls.
    EXPECT_CALL(*mockObserver, onControlsUpdated(_)).Times(1);
    controlStore.addObserver(mockObserver);

    library::test::verifiers::ControlNameSetVerifier controlsVerifier;

    EXPECT_CALL(*mockObserver, onControlsUpdated(_))
        .WillOnce(testing::Invoke([&controlsVerifier](std::unordered_set<control::ControlName> availableControls) {
            controlsVerifier.captureControls(availableControls);
        }));

    controlsVerifier.setExpectedControlNames({ControlName::STOP});

    auto key = m_controlAccessKeys->requestAccessKey();
    controlStore.store(key, ControlPriority::CONTENT, createStopControl());
}

TEST_F(
    ControlStoreTest,
    test_registered_observer_is_not_notified_when_a_control_is_stored_whos_type_already_is_stored) {
    ControlStore controlStore(m_controlAccessKeys);
    auto mockObserver = std::make_shared<testing::StrictMock<MockControlStoreObserver>>();
    // for registration.
    EXPECT_CALL(*mockObserver, onControlsUpdated(_)).Times(1);
    controlStore.addObserver(mockObserver);

    // after update.
    EXPECT_CALL(*mockObserver, onControlsUpdated(_)).Times(1);
    auto firstKey = m_controlAccessKeys->requestAccessKey();
    controlStore.store(firstKey, ControlPriority::CONTENT, createStopControl());

    // duplicate type added by another consumer.
    EXPECT_CALL(*mockObserver, onControlsUpdated(_)).Times(0);
    auto secondKey = m_controlAccessKeys->requestAccessKey();
    controlStore.store(secondKey, ControlPriority::CONTENT, createStopControl());
}

TEST_F(ControlStoreTest, test_registered_observer_is_notified_when_a_control_is_stored_before_registration) {
    ControlStore controlStore(m_controlAccessKeys);
    auto mockObserver = std::make_shared<testing::StrictMock<MockControlStoreObserver>>();

    EXPECT_CALL(*mockObserver, onControlsUpdated(_)).Times(1);

    auto key = m_controlAccessKeys->requestAccessKey();
    controlStore.store(key, ControlPriority::CONTENT, createStopControl());
    controlStore.addObserver(mockObserver);
}

TEST_F(ControlStoreTest, test_registered_observer_is_notified_when_access_active_controls_are_updated_to_empty) {
    ControlStore controlStore(m_controlAccessKeys);
    auto mockObserver = std::make_shared<testing::StrictMock<MockControlStoreObserver>>();

    // for registration.
    EXPECT_CALL(*mockObserver, onControlsUpdated(_)).Times(1);
    controlStore.addObserver(mockObserver);

    // after add.
    EXPECT_CALL(*mockObserver, onControlsUpdated(_)).Times(1);
    auto key = m_controlAccessKeys->requestAccessKey();
    controlStore.store(key, ControlPriority::CONTENT, createStopControl());

    // update to empty controls.
    EXPECT_CALL(*mockObserver, onControlsUpdated(_)).Times(1);
    controlStore.store(key, ControlPriority::CONTENT, {});
}

TEST_F(ControlStoreTest, test_registered_observer_is_notified_when_access_is_removed_for_active_controls) {
    ControlStore controlStore(m_controlAccessKeys);
    auto mockObserver = std::make_shared<testing::StrictMock<MockControlStoreObserver>>();

    // for registration.
    EXPECT_CALL(*mockObserver, onControlsUpdated(_)).Times(1);
    controlStore.addObserver(mockObserver);

    // after add.
    EXPECT_CALL(*mockObserver, onControlsUpdated(_)).Times(1);
    auto key = m_controlAccessKeys->requestAccessKey();
    controlStore.store(key, ControlPriority::CONTENT, createStopControl());

    // after access revoked.
    EXPECT_CALL(*mockObserver, onControlsUpdated(_)).Times(1);
    controlStore.remove(key);
}

TEST_F(
    ControlStoreTest,
    test_registered_observer_is_not_notified_when_access_is_removed_for_duplicate_active_controls) {
    ControlStore controlStore(m_controlAccessKeys);
    auto mockObserver = std::make_shared<testing::StrictMock<MockControlStoreObserver>>();
    // for registration.
    EXPECT_CALL(*mockObserver, onControlsUpdated(_)).Times(1);
    controlStore.addObserver(mockObserver);

    // after update.
    EXPECT_CALL(*mockObserver, onControlsUpdated(_)).Times(1);
    auto firstKey = m_controlAccessKeys->requestAccessKey();
    controlStore.store(firstKey, ControlPriority::CONTENT, createStopControl());

    // duplicate type added and removed by another consumer.
    EXPECT_CALL(*mockObserver, onControlsUpdated(_)).Times(0);
    auto secondKey = m_controlAccessKeys->requestAccessKey();
    controlStore.store(secondKey, ControlPriority::CONTENT, createStopControl());
    controlStore.revokeAccess(secondKey);
}

TEST_F(
    ControlStoreTest,
    test_registered_observer_is_notified_when_access_is_removed_for_all_active_controls_from_multiple_consumers) {
    ControlStore controlStore(m_controlAccessKeys);
    auto mockObserver = std::make_shared<testing::StrictMock<MockControlStoreObserver>>();
    // for registration.
    EXPECT_CALL(*mockObserver, onControlsUpdated(_)).Times(1);
    controlStore.addObserver(mockObserver);

    // after update.
    EXPECT_CALL(*mockObserver, onControlsUpdated(_)).Times(1);
    auto firstKey = m_controlAccessKeys->requestAccessKey();
    controlStore.store(firstKey, ControlPriority::CONTENT, createStopControl());

    auto secondKey = m_controlAccessKeys->requestAccessKey();
    controlStore.store(secondKey, ControlPriority::CONTENT, createStopControl());

    // access for all controls are revoked and therefore removed.
    EXPECT_CALL(*mockObserver, onControlsUpdated(_)).Times(1);
    controlStore.revokeAccess(secondKey);
    controlStore.revokeAccess(firstKey);
}

TEST_F(
    ControlStoreTest,
    test_registered_observer_is_notified_with_empty_set_when_access_is_removed_for_all_active_controls_from_multiple_consumers) {
    ControlStore controlStore(m_controlAccessKeys);
    auto mockObserver = std::make_shared<testing::StrictMock<MockControlStoreObserver>>();
    // for registration.
    EXPECT_CALL(*mockObserver, onControlsUpdated(_)).Times(1);
    controlStore.addObserver(mockObserver);

    // after update.
    EXPECT_CALL(*mockObserver, onControlsUpdated(_)).Times(1);
    auto firstKey = m_controlAccessKeys->requestAccessKey();
    controlStore.store(firstKey, ControlPriority::CONTENT, createStopControl());

    auto secondKey = m_controlAccessKeys->requestAccessKey();
    controlStore.store(secondKey, ControlPriority::CONTENT, createStopControl());

    library::test::verifiers::ControlNameSetVerifier controlsVerifier;

    EXPECT_CALL(*mockObserver, onControlsUpdated(_))
        .WillOnce(testing::Invoke([&controlsVerifier](std::unordered_set<control::ControlName> availableControls) {
            controlsVerifier.captureControls(availableControls);
        }));

    controlStore.revokeAccess(secondKey);
    controlStore.revokeAccess(firstKey);
}

TEST_F(
    ControlStoreTest,
    test_registered_observer_is_notified_with_an_empty_control_set_when_access_is_removed_for_all_active_controls) {
    ControlStore controlStore(m_controlAccessKeys);
    auto mockObserver = std::make_shared<testing::StrictMock<MockControlStoreObserver>>();

    // for registration.
    EXPECT_CALL(*mockObserver, onControlsUpdated(_)).Times(1);
    controlStore.addObserver(mockObserver);

    // after add.
    EXPECT_CALL(*mockObserver, onControlsUpdated(_)).Times(1);
    auto key = m_controlAccessKeys->requestAccessKey();
    controlStore.store(key, ControlPriority::CONTENT, createStopControl());

    // after access revoked.
    library::test::verifiers::ControlNameSetVerifier controlsVerifier;
    EXPECT_CALL(*mockObserver, onControlsUpdated(_))
        .WillOnce(testing::Invoke([&controlsVerifier](std::unordered_set<control::ControlName> availableControls) {
            controlsVerifier.captureControls(availableControls);
        }));
    controlStore.remove(key);
}

TEST_F(
    ControlStoreTest,
    test_registered_observer_is_notified_with_an_empty_control_set_when_access_is_removed_for_all_active_controls_from_multiple_consumers) {
    ControlStore controlStore(m_controlAccessKeys);
    auto mockObserver = std::make_shared<testing::StrictMock<MockControlStoreObserver>>();

    // for registration.
    EXPECT_CALL(*mockObserver, onControlsUpdated(_)).Times(1);
    controlStore.addObserver(mockObserver);

    // after add.
    EXPECT_CALL(*mockObserver, onControlsUpdated(_)).Times(1);
    auto firstKey = m_controlAccessKeys->requestAccessKey();
    controlStore.store(firstKey, ControlPriority::CONTENT, createStopControl());
    auto secondKey = m_controlAccessKeys->requestAccessKey();
    controlStore.store(secondKey, ControlPriority::CONTENT, createStopControl());

    // after access revoked.
    library::test::verifiers::ControlNameSetVerifier controlsVerifier;
    EXPECT_CALL(*mockObserver, onControlsUpdated(_))
        .WillOnce(testing::Invoke([&controlsVerifier](std::unordered_set<control::ControlName> availableControls) {
            controlsVerifier.captureControls(availableControls);
        }));
    controlStore.revokeAccess(secondKey);
    controlStore.revokeAccess(firstKey);
}

}  // namespace test
}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience
