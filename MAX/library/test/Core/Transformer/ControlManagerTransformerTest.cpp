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

#include "Core/Transformer/ControlManagerTransformer.h"
#include "Core/Transformer/ControlStoreObserverTransformer.h"

#include <MultiAgentExperience/Control/Control.h>

#include "Control/ControlStore.h"
#include "Control/CurrentControls.h"

#include "Mocks/MockControlObserverInterface.h"
#include "Verifiers/ControlTypeSetVerifier.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {
namespace test {

using namespace ::testing;

class ControlManagerTransformerTest : public ::testing::Test {
protected:
    std::shared_ptr<control::ControlAccessKeys> m_controlAccessKeys;
    std::shared_ptr<control::ControlStore> m_controlStore;
    std::shared_ptr<ControlManagerTransformer> m_transformer;

    void SetUp() override {
        m_controlAccessKeys = std::make_shared<control::ControlAccessKeys>();
        m_controlStore = std::make_shared<control::ControlStore>(m_controlAccessKeys);
        auto currentControls =
            std::make_shared<control::CurrentControls>(m_controlAccessKeys->requestAccessKey(), m_controlStore);

        m_transformer = std::make_shared<ControlManagerTransformer>(actor::ActorId("test"), m_controlStore);
    }
};

TEST_F(ControlManagerTransformerTest, test_clear_observers_does_nothing_when_none_are_added) {
    m_transformer->clearObservers();
}

TEST_F(ControlManagerTransformerTest, test_adding_an_observer_gets_control_updates) {
    auto mockObserver = std::make_shared<testing::StrictMock<MockControlObserverInterface>>();

    // notified of the start state.
    EXPECT_CALL(*mockObserver, onControlChange(_)).Times(1);
    m_transformer->addObserver(mockObserver);

    auto controls = std::unordered_set<std::shared_ptr<control::Control>>();
    auto control = control::Control::create(control::ControlName::STOP, []() {});
    controls.insert(control);

    // notified when the controls are added.
    EXPECT_CALL(*mockObserver, onControlChange(_)).Times(1);
    auto key = m_controlAccessKeys->requestAccessKey();
    m_controlStore->store(key, control::ControlPriority::CONTENT, controls);
}

TEST_F(ControlManagerTransformerTest, test_adding_an_observer_gets_control_updates_of_matching_type) {
    auto mockObserver = std::make_shared<testing::StrictMock<MockControlObserverInterface>>();

    // notified of the start state.
    EXPECT_CALL(*mockObserver, onControlChange(_)).Times(1);
    m_transformer->addObserver(mockObserver);

    auto controls = std::unordered_set<std::shared_ptr<control::Control>>();
    auto control = control::Control::create(control::ControlName::STOP, []() {});
    controls.insert(control);

    // notified when the controls are added.
    library::test::verifiers::ControlTypeSetVerifier controlsVerifier;
    EXPECT_CALL(*mockObserver, onControlChange(_))
        .WillOnce(testing::Invoke(
            [&controlsVerifier](std::set<multiAgentExperience::control::ControlType> availableControls) {
                controlsVerifier.captureControls(availableControls);
            }));
    std::set<multiAgentExperience::control::ControlType> expectedControls;
    expectedControls.insert(multiAgentExperience::control::ControlType::STOP);
    controlsVerifier.setExpectedControlNames(expectedControls);

    auto key = m_controlAccessKeys->requestAccessKey();
    m_controlStore->store(key, control::ControlPriority::CONTENT, controls);
}

TEST_F(ControlManagerTransformerTest, test_adding_an_observer_which_goes_out_of_scope_and_not_callback) {
    {
        auto mockObserver = std::make_shared<testing::StrictMock<MockControlObserverInterface>>();
        // notified of the start state.
        EXPECT_CALL(*mockObserver, onControlChange(_)).Times(1);
        m_transformer->addObserver(mockObserver);
    }

    auto controls = std::unordered_set<std::shared_ptr<control::Control>>();
    auto control = control::Control::create(control::ControlName::STOP, []() {});
    controls.insert(control);
    auto key = m_controlAccessKeys->requestAccessKey();
    m_controlStore->store(key, control::ControlPriority::CONTENT, controls);
}

}  // namespace test
}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
