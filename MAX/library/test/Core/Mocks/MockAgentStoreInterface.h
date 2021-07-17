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


#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_TEST_CORE_MOCKS_MOCKAGENTSTOREINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_TEST_CORE_MOCKS_MOCKAGENTSTOREINTERFACE_H_

#include "Core/Transformer/AgentStoreInterface.h"

#include <gmock/gmock.h>
#include <memory>

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {
namespace test {

class MockAgentStoreInterface : public multiAgentExperience::library::core::transformer::AgentStoreInterface {
public:
    MOCK_METHOD1(
        getAgentById,
        std::shared_ptr<multiAgentExperience::agent::Agent>(const multiAgentExperience::actor::ActorId&));
};

}  // namespace test
}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_TEST_CORE_MOCKS_MOCKAGENTSTOREINTERFACE_H_