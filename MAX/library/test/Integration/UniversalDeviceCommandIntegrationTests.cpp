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
#include <memory>

#include <MultiAgentExperience/Application/MAXFactory.h>

#include "TestActivityHandler.h"
#include "TestAgent.h"
#include "TestControlWrapper.h"
#include "TestDialog.h"

#include "Utils/Threading/Executor.h"

namespace multiAgentExperience {
namespace library {
namespace test {

using testing::_;

class UniversalDeviceCommandIntegrationTests : public ::testing::Test {
protected:
    const actor::ActorId INTEGRATOR = actor::ActorId("TestApplication");
    const actor::ActorId AGENT_ONE = actor::ActorId("AgentOne");
    const actor::ActorId AGENT_TWO = actor::ActorId("AgentTwo");
};

TEST_F(
    UniversalDeviceCommandIntegrationTests,
    test_an_agent_with_dialog_can_invoke_an_available_control_from_an_agent) {
    auto max = multiAgentExperience::application::MAXFactory::create(INTEGRATOR);
    auto testAgentOne = std::make_shared<TestAgent>(AGENT_ONE);
    auto testAgentTwo = std::make_shared<TestAgent>(AGENT_TWO);
    max->getAgentManager()->registerAgent(testAgentOne);
    max->getAgentManager()->registerAgent(testAgentTwo);
    auto executor = std::make_shared<utils::threading::Executor>();

    auto activity = std::make_shared<TestActivityHandler>();
    auto activityRequest = std::make_shared<multiAgentExperience::activity::ActivityRequestInterface>(
        activity::ActivityType::CONTENT, activity);
    executor->submit([&testAgentOne, &activityRequest]() { testAgentOne->startActivity(activityRequest); });

    auto invokeControlType = control::ControlType::STOP;

    // register control for activity
    auto testControl = std::make_shared<TestControlWrapper>();
    auto control = testControl->getControl(invokeControlType);

    executor->submit([&activity, &control]() { activity->addControl(control); });

    // start a dialog from the other agent
    auto dialog = std::make_shared<TestDialog>();

    executor->submit([&dialog, &testAgentTwo]() { testAgentTwo->startDialog(dialog); });

    // emulate processing a request
    executor->submit([&dialog]() { dialog->startListening(); });
    executor->submit([&dialog]() { dialog->startThinking(); });

    // invoke control
    executor->submit([&dialog, &invokeControlType]() { dialog->invokeControl(invokeControlType); });
    executor->waitForSubmittedTasks();

    ASSERT_TRUE(testControl->wasInvoked());
}

TEST_F(
    UniversalDeviceCommandIntegrationTests,
    test_an_agent_with_dialog_can_invoke_an_available_control_from_an_integrator) {
    auto max = multiAgentExperience::application::MAXFactory::create(INTEGRATOR);
    auto testAgentOne = std::make_shared<TestAgent>(AGENT_ONE);
    auto testAgentTwo = std::make_shared<TestAgent>(AGENT_TWO);
    max->getAgentManager()->registerAgent(testAgentOne);
    max->getAgentManager()->registerAgent(testAgentTwo);
    auto executor = std::make_shared<utils::threading::Executor>();

    auto activity = std::make_shared<TestActivityHandler>();
    auto activityRequest = std::make_shared<multiAgentExperience::activity::ActivityRequestInterface>(
        activity::ActivityType::CONTENT, activity);
    executor->submit([&max, &activityRequest]() { max->getActivityManager()->request(activityRequest); });

    auto invokeControlType = control::ControlType::STOP;

    // register control for activity
    auto testControl = std::make_shared<TestControlWrapper>();
    auto control = testControl->getControl(invokeControlType);

    executor->submit([&activity, &control]() { activity->addControl(control); });

    // start a dialog from the other agent
    auto dialog = std::make_shared<TestDialog>();

    executor->submit([&testAgentTwo, &dialog]() { testAgentTwo->startDialog(dialog); });

    // emulate processing a request
    executor->submit([&dialog]() { dialog->startListening(); });
    executor->submit([&dialog]() { dialog->startThinking(); });

    // invoke control
    executor->submit([&dialog, &invokeControlType]() { dialog->invokeControl(invokeControlType); });

    executor->waitForSubmittedTasks();

    ASSERT_TRUE(testControl->wasInvoked());
}

TEST_F(UniversalDeviceCommandIntegrationTests, test_an_integrator_can_invoke_an_available_control_from_an_agent) {
    auto max = multiAgentExperience::application::MAXFactory::create(INTEGRATOR);
    auto testAgentOne = std::make_shared<TestAgent>(AGENT_ONE);
    auto testAgentTwo = std::make_shared<TestAgent>(AGENT_TWO);
    max->getAgentManager()->registerAgent(testAgentOne);
    max->getAgentManager()->registerAgent(testAgentTwo);
    auto executor = std::make_shared<utils::threading::Executor>();

    auto activity = std::make_shared<TestActivityHandler>();
    auto activityRequest = std::make_shared<multiAgentExperience::activity::ActivityRequestInterface>(
        activity::ActivityType::CONTENT, activity);
    executor->submit([&testAgentOne, &activityRequest]() { testAgentOne->startActivity(activityRequest); });

    auto invokeControlType = control::ControlType::STOP;

    // register control for activity
    auto testControl = std::make_shared<TestControlWrapper>();
    auto control = testControl->getControl(invokeControlType);

    executor->submit([&activity, &control]() { activity->addControl(control); });

    // invoke control from integrrator
    executor->submit([&max, &invokeControlType]() { max->getControlInvoker()->invokeControl(invokeControlType); });

    executor->waitForSubmittedTasks();

    ASSERT_TRUE(testControl->wasInvoked());
}

}  // namespace test
}  // namespace library
}  // namespace multiAgentExperience