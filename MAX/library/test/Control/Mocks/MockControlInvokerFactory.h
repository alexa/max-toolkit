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

#ifndef VII_CONTROL_TEST_MOCK_CONTROL_INVOKER_FACTORY_H_
#define VII_CONTROL_TEST_MOCK_CONTROL_INVOKER_FACTORY_H_

#include "Control/ControlInvokerFactory.h"
#include "Control/ControlInvoker.h"

#include "MockControlStore.h"

#include <gmock/gmock.h>
#include <memory>

namespace multiAgentExperience {
namespace library {
namespace control {
namespace test {

class MockControlInvokerFactory : public ControlInvokerFactory {
public:
    MockControlInvokerFactory() : ControlInvokerFactory(0, std::make_shared<MockControlStore>()) {
    }

    MOCK_METHOD0(create, std::shared_ptr<ControlInvoker>());
};

}  // namespace test
}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience

#endif  // VII_CONTROL_TEST_MOCK_CONTROL_INVOKER_FACTORY_H_
