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

#include "Core/Transformer/ActivityTransformer.h"

#include "Activity/ActivityManagerFactory.h"

#include "Control/ControlAccessKeys.h"
#include "Control/ControlRegistryFactory.h"
#include "Control/ControlStore.h"
#include "Control/CurrentControls.h"
#include "Experience/ExperienceManager.h"

#include <Mocks/MockActivityHandlerInterface.h>
#include <Mocks/MockExperienceControlInterface.h>

#include <gmock/gmock.h>
#include <memory>

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {
namespace test {

using namespace ::testing;

class ActivityTransformerTest : public ::testing::Test {
protected:
    std::shared_ptr<control::ControlRegistry> m_controlRegistry;
    std::shared_ptr<activity::test::MockActivityHandlerInterface> m_mockHandler;
    std::shared_ptr<ActivityTransformer> m_transformer;
    std::shared_ptr<multiAgentExperience::experience::test::MockExperienceControlInterface> m_experienceController;
    void SetUp() override {
        auto experienceManager =
            std::make_shared<experience::ExperienceManager>(std::make_shared<utils::threading::Executor>(false));

        auto controlAccessKeys = std::make_shared<control::ControlAccessKeys>();
        auto controlStore = std::make_shared<control::ControlStore>(controlAccessKeys);
        auto currentControls =
            std::make_shared<control::CurrentControls>(controlAccessKeys->requestAccessKey(), controlStore);
        auto controlRegistryFactory =
            std::make_shared<control::ControlRegistryFactory>(controlAccessKeys, controlStore);

        auto activityManager = activity::ActivityManagerFactory::create(controlRegistryFactory, false);

        m_experienceController =
            std::make_shared<NiceMock<multiAgentExperience::experience::test::MockExperienceControlInterface>>();
        m_controlRegistry = controlRegistryFactory->create(control::ControlPriority::CONTENT);
        m_mockHandler = std::make_shared<StrictMock<activity::test::MockActivityHandlerInterface>>();
        m_transformer = std::make_shared<ActivityTransformer>(activityManager, m_mockHandler, m_experienceController);

        m_transformer->onControlRegistryAvailable(m_controlRegistry);
    }
};

TEST_F(ActivityTransformerTest, test_the_first_state_change_to_foreground_calls_on_ready) {
    EXPECT_CALL(*m_mockHandler, onReady(_, multiAgentExperience::activity::ActivityFocus::FOREGROUND, _, _));
    EXPECT_CALL(*m_mockHandler, onFocusStateChange(multiAgentExperience::activity::ActivityFocus::FOREGROUND));

    m_transformer->onForeground();
}

TEST_F(ActivityTransformerTest, test_the_first_state_change_to_background_calls_on_ready) {
    EXPECT_CALL(*m_mockHandler, onReady(_, multiAgentExperience::activity::ActivityFocus::BACKGROUND, _, _));
    EXPECT_CALL(*m_mockHandler, onFocusStateChange(multiAgentExperience::activity::ActivityFocus::BACKGROUND));

    m_transformer->onBackground();
}

TEST_F(ActivityTransformerTest, test_the_second_state_change_to_foreground_does_not_call_on_ready) {
    EXPECT_CALL(*m_mockHandler, onReady(_, multiAgentExperience::activity::ActivityFocus::BACKGROUND, _, _));
    EXPECT_CALL(*m_mockHandler, onFocusStateChange(multiAgentExperience::activity::ActivityFocus::BACKGROUND));

    m_transformer->onBackground();

    EXPECT_CALL(*m_mockHandler, onFocusStateChange(multiAgentExperience::activity::ActivityFocus::FOREGROUND));

    m_transformer->onForeground();

    // test will fail because of strict mocks if onReady is called again
}

TEST_F(ActivityTransformerTest, test_the_second_state_change_to_background_does_not_call_on_ready) {
    EXPECT_CALL(*m_mockHandler, onReady(_, multiAgentExperience::activity::ActivityFocus::FOREGROUND, _, _));
    EXPECT_CALL(*m_mockHandler, onFocusStateChange(multiAgentExperience::activity::ActivityFocus::FOREGROUND));

    m_transformer->onForeground();

    EXPECT_CALL(*m_mockHandler, onFocusStateChange(multiAgentExperience::activity::ActivityFocus::BACKGROUND));

    m_transformer->onBackground();

    // test will fail because of strict mocks if onReady is called again
}

TEST_F(ActivityTransformerTest, test_on_stop_does_nothing_if_never_started) {
    m_transformer->onStop();

    // test will fail if any interaction with the handler happens as a result
}

TEST_F(ActivityTransformerTest, test_on_stop_stops_a_foreground_activity) {
    EXPECT_CALL(*m_mockHandler, onReady(_, multiAgentExperience::activity::ActivityFocus::FOREGROUND, _, _));
    EXPECT_CALL(*m_mockHandler, onFocusStateChange(multiAgentExperience::activity::ActivityFocus::FOREGROUND));

    m_transformer->onForeground();

    EXPECT_CALL(*m_mockHandler, onStop());

    m_transformer->onStop();
}

TEST_F(ActivityTransformerTest, test_on_stop_stops_a_background_activity) {
    EXPECT_CALL(*m_mockHandler, onReady(_, multiAgentExperience::activity::ActivityFocus::BACKGROUND, _, _));
    EXPECT_CALL(*m_mockHandler, onFocusStateChange(multiAgentExperience::activity::ActivityFocus::BACKGROUND));

    m_transformer->onBackground();

    EXPECT_CALL(*m_mockHandler, onStop());

    m_transformer->onStop();
}

TEST_F(ActivityTransformerTest, test_on_stop_invalidates_experience_controller) {
    EXPECT_CALL(*m_mockHandler, onReady(_, multiAgentExperience::activity::ActivityFocus::FOREGROUND, _, _));
    EXPECT_CALL(*m_mockHandler, onFocusStateChange(multiAgentExperience::activity::ActivityFocus::FOREGROUND));

    m_transformer->onForeground();

    EXPECT_CALL(*m_mockHandler, onStop());

    EXPECT_CALL(*m_experienceController, invalidate());
    m_transformer->onStop();
}

}  // namespace test
}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
