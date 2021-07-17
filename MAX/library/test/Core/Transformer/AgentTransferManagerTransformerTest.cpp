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


#include "Core/Transformer/AgentTransferManagerTransformer.h"

#include "Agent/AgentTransferManager.h"
#include "MultiAgentExperience/Agent/Agent.h"

#include "Core/Mocks/MockAgentStoreInterface.h"

#include "Integration/TestAgent.h"

#include <gmock/gmock.h>
#include <memory>

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {
namespace test {

using namespace ::testing;

class AgentTransferManagerTransformerTest : public ::testing::Test {
protected:
    std::shared_ptr<AgentTransferManagerTransformer> m_transformer;
    std::shared_ptr<MockAgentStoreInterface> m_mockAgentStore;

    virtual void SetUp() override {
        m_mockAgentStore = std::make_shared<NiceMock<MockAgentStoreInterface>>();
        auto agentTransferManager = std::make_shared<agent::AgentTransferManager>();
        m_transformer = std::make_shared<AgentTransferManagerTransformer>(
            multiAgentExperience::actor::ActorId("agent"), agentTransferManager, m_mockAgentStore);
    }
};

TEST_F(AgentTransferManagerTransformerTest, test_invoke_agent_invokes_the_agent) {
    auto id = actor::ActorId("id");
    auto agent = std::make_shared<library::test::TestAgent>(id);
    EXPECT_CALL(*m_mockAgentStore, getAgentById(id)).WillRepeatedly(Return(agent));

    m_transformer->invokeAgent(agent->getId());

    ASSERT_TRUE(agent->wasTransferredTo());
}

}  // namespace test
}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience