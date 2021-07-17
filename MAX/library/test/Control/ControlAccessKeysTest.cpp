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

#include "Control/ControlAccessKeys.h"

namespace multiAgentExperience {
namespace library {
namespace control {
namespace test {

using testing::_;

class ControlAccessKeysTest : public ::testing::Test {
protected:
};

TEST_F(ControlAccessKeysTest, test_requestAccessKey_creates_a_key_with_access) {
    auto controlAccessKeys = std::make_shared<ControlAccessKeys>();

    auto key = controlAccessKeys->requestAccessKey();

    ASSERT_TRUE(controlAccessKeys->hasAccess(key));
}

TEST_F(ControlAccessKeysTest, test_requestAccessKey_creates_multiple_unique_keys_with_access) {
    auto controlAccessKeys = std::make_shared<ControlAccessKeys>();

    auto key1 = controlAccessKeys->requestAccessKey();
    auto key2 = controlAccessKeys->requestAccessKey();

    ASSERT_NE(key1, key2);
    ASSERT_TRUE(controlAccessKeys->hasAccess(key1));
    ASSERT_TRUE(controlAccessKeys->hasAccess(key2));
}

TEST_F(ControlAccessKeysTest, test_revokeAccess_removes_access_for_key) {
    auto controlAccessKeys = std::make_shared<ControlAccessKeys>();
    auto key = controlAccessKeys->requestAccessKey();

    controlAccessKeys->revokeAccess(key);

    ASSERT_FALSE(controlAccessKeys->hasAccess(key));
}

TEST_F(ControlAccessKeysTest, test_revokeAccess_removes_access_for_only_the_given_key) {
    auto controlAccessKeys = std::make_shared<ControlAccessKeys>();
    auto key1 = controlAccessKeys->requestAccessKey();
    auto key2 = controlAccessKeys->requestAccessKey();

    controlAccessKeys->revokeAccess(key1);

    ASSERT_FALSE(controlAccessKeys->hasAccess(key1));
    ASSERT_TRUE(controlAccessKeys->hasAccess(key2));
}

}  // namespace test
}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience
