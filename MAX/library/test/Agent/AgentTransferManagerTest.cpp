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

#include "Agent/AgentTransferManager.h"

#include "Integration/TestAgent.h"

namespace multiAgentExperience {
namespace library {
namespace agent {
namespace test {

using testing::_;

class AgentTransferManagerTest : public ::testing::Test {};

TEST_F(AgentTransferManagerTest, test_agent_manager_invoke_agent_invokes_the_given_agent) {
    static auto id = actor::ActorId("test");
    auto testAgent = std::make_shared<library::test::TestAgent>(id);
    auto transferManager = std::make_shared<AgentTransferManager>();
    transferManager->invokeAgent(testAgent);
    ASSERT_TRUE(testAgent->wasTransferredTo());
}

}  // namespace test
}  // namespace agent
}  // namespace library
}  // namespace multiAgentExperience