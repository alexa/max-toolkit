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

#include "Core/Transformer/ControlInvokerTransformer.h"

#include <MultiAgentExperience/Control/Control.h>

#include "Control/ControlInvokerFactory.h"
#include "Control/ControlStore.h"
#include "Control/CurrentControls.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {
namespace test {

class ControlInvokerTransformerTest : public ::testing::Test {
protected:
    std::shared_ptr<control::ControlAccessKeys> m_controlAccessKeys;
    std::shared_ptr<control::ControlStore> m_controlStore;
    std::shared_ptr<ControlInvokerTransformer> m_transformer;

    void SetUp() override {
        m_controlAccessKeys = std::make_shared<control::ControlAccessKeys>();
        m_controlStore = std::make_shared<control::ControlStore>(m_controlAccessKeys);
        auto currentControls =
            std::make_shared<control::CurrentControls>(m_controlAccessKeys->requestAccessKey(), m_controlStore);

        auto controlInvokerFactory =
            std::make_shared<control::ControlInvokerFactory>(m_controlAccessKeys, m_controlStore);
        auto invoker = controlInvokerFactory->create();
        m_transformer = std::make_shared<ControlInvokerTransformer>(actor::ActorId("test"), invoker);
    }
};

TEST_F(ControlInvokerTransformerTest, test_invoke_control_does_nothing_if_there_are_no_controls) {
    m_transformer->invokeControl(multiAgentExperience::control::ControlType::STOP);
}

TEST_F(ControlInvokerTransformerTest, test_invoke_control_invokes_a_control_if_it_exists) {
    auto key = m_controlAccessKeys->requestAccessKey();
    bool wasInvoked = false;
    auto controls = std::unordered_set<std::shared_ptr<control::Control>>();
    auto control = control::Control::create(control::ControlName::STOP, [&wasInvoked]() { wasInvoked = true; });
    controls.insert(control);

    m_controlStore->store(key, control::ControlPriority::CONTENT, controls);

    m_transformer->invokeControl(multiAgentExperience::control::ControlType::STOP);

    ASSERT_TRUE(wasInvoked);
}

}  // namespace test
}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience