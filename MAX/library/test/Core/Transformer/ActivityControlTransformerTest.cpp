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

#include "Core/Transformer/ActivityControllerTransformer.h"

#include <gmock/gmock.h>

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {
namespace test {

class ActivityControllerTransformerTest : public ::testing::Test {};

TEST_F(ActivityControllerTransformerTest, test_stop_call_stop_callback) {
    bool result = false;
    auto stopCallback = [&result]() { result = true; };
    ActivityControllerTransformer transformer(stopCallback);
    transformer.stop();
    ASSERT_TRUE(result);
}

}  // namespace test
}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
