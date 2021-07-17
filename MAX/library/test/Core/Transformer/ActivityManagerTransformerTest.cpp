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

#include "Core/Transformer/ActivityManagerTransformer.h"
#include "Core/Transformer/ActivityRequestTransformerFactory.h"
#include "MultiAgentExperience/Activity/ActivityRequestInterface.h"

#include "Activity/ActivityManagerFactory.h"

#include "Control/ControlAccessKeys.h"
#include "Control/ControlRegistryFactory.h"
#include "Control/ControlStore.h"
#include "Control/CurrentControls.h"

#include "Experience/ExperienceManager.h"

#include <Mocks/MockActivityHandlerInterface.h>

#include <gmock/gmock.h>
#include <memory>

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {
namespace test {

using namespace ::testing;

class ActivityManagerTransformerTest : public ::testing::Test {
protected:
    std::shared_ptr<ActivityManagerTransformer> m_transformer;

    virtual void SetUp() override {
        auto experienceManager = std::make_shared<library::experience::ExperienceManager>(
            std::make_shared<utils::threading::Executor>(false));

        auto controlAccessKeys = std::make_shared<control::ControlAccessKeys>();
        auto controlStore = std::make_shared<control::ControlStore>(controlAccessKeys);
        auto currentControls =
            std::make_shared<control::CurrentControls>(controlAccessKeys->requestAccessKey(), controlStore);
        auto controlRegistryFactory =
            std::make_shared<control::ControlRegistryFactory>(controlAccessKeys, controlStore);

        auto activityManager = activity::ActivityManagerFactory::create(controlRegistryFactory, false);

        auto requestTransformerFactory =
            std::make_shared<ActivityRequestTransformerFactory>(activityManager, experienceManager);
        m_transformer = std::make_shared<ActivityManagerTransformer>(
            multiAgentExperience::actor::ActorId("agent"), activityManager, requestTransformerFactory);
    }
};

TEST_F(ActivityManagerTransformerTest, test_request_successfully_registers_the_handler) {
    auto handler = std::make_shared<StrictMock<activity::test::MockActivityHandlerInterface>>();
    auto request = std::make_shared<multiAgentExperience::activity::ActivityRequestInterface>(
        multiAgentExperience::activity::ActivityType::CONTENT, handler);

    EXPECT_CALL(*handler, onReady(_, _, _, _));
    EXPECT_CALL(*handler, onFocusStateChange(multiAgentExperience::activity::ActivityFocus::FOREGROUND));

    m_transformer->request(request);

    // destructor consequence
    EXPECT_CALL(*handler, onStop());
}

TEST_F(ActivityManagerTransformerTest, test_stop_removes_the_request_and_stops_the_handler) {
    auto handler = std::make_shared<StrictMock<activity::test::MockActivityHandlerInterface>>();
    auto request = std::make_shared<multiAgentExperience::activity::ActivityRequestInterface>(
        multiAgentExperience::activity::ActivityType::CONTENT, handler);

    // request side effects
    EXPECT_CALL(*handler, onReady(_, _, _, _));
    EXPECT_CALL(*handler, onFocusStateChange(multiAgentExperience::activity::ActivityFocus::FOREGROUND));
    m_transformer->request(request);

    // test expectation
    EXPECT_CALL(*handler, onStop());

    m_transformer->stop(request);
}

TEST_F(ActivityManagerTransformerTest, test_stop_removes_only_the_requested_request) {
    auto handler = std::make_shared<StrictMock<activity::test::MockActivityHandlerInterface>>();
    auto request = std::make_shared<multiAgentExperience::activity::ActivityRequestInterface>(
        multiAgentExperience::activity::ActivityType::CONTENT, handler);
    auto handlerTwo = std::make_shared<StrictMock<activity::test::MockActivityHandlerInterface>>();
    auto requestTwo = std::make_shared<multiAgentExperience::activity::ActivityRequestInterface>(
        multiAgentExperience::activity::ActivityType::ALERTS, handlerTwo);

    // request side effects
    EXPECT_CALL(*handler, onReady(_, _, _, _));
    EXPECT_CALL(*handler, onFocusStateChange(_)).Times(AnyNumber());

    EXPECT_CALL(*handlerTwo, onReady(_, _, _, _));
    EXPECT_CALL(*handlerTwo, onFocusStateChange(_));
    m_transformer->request(request);
    m_transformer->request(requestTwo);

    // test expectation
    EXPECT_CALL(*handler, onStop());

    m_transformer->stop(request);

    // destructor consequences
    EXPECT_CALL(*handlerTwo, onStop());
}

}  // namespace test
}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
