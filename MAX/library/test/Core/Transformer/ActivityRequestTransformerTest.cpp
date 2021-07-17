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

#include "Core/Transformer/ActivityRequestTransformer.h"
#include "Core/Transformer/ActivityTransformer.h"

#include "Activity/ActivityType.h"
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

using namespace multiAgentExperience::library::utils;
using namespace ::testing;

class ActivityRequestTransformerTest : public ::testing::Test {};

TEST_F(ActivityRequestTransformerTest, test_denying_request_forwards_to_handler) {
    auto experienceManager =
        std::make_shared<library::experience::ExperienceManager>(std::make_shared<threading::Executor>(false));

    auto controlAccessKeys = std::make_shared<control::ControlAccessKeys>();
    auto controlStore = std::make_shared<control::ControlStore>(controlAccessKeys);
    auto currentControls =
        std::make_shared<control::CurrentControls>(controlAccessKeys->requestAccessKey(), controlStore);
    auto controlRegistryFactory = std::make_shared<control::ControlRegistryFactory>(controlAccessKeys, controlStore);

    auto activityManager =
        multiAgentExperience::library::activity::ActivityManagerFactory::create(controlRegistryFactory, false);

    auto experienceController = experienceManager->getController(multiAgentExperience::actor::ActorId("agent"));
    auto handler =
        std::make_shared<StrictMock<multiAgentExperience::library::activity::test::MockActivityHandlerInterface>>();
    auto activityTransformer = std::make_shared<ActivityTransformer>(activityManager, handler, experienceController);

    auto transformer = std::make_shared<ActivityRequestTransformer>(
        multiAgentExperience::library::activity::ActivityType::CONTENT, activityTransformer, handler);

    EXPECT_CALL(*handler, onDenied());

    transformer->onDenied();
}

}  // namespace test
}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
