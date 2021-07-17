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

#ifndef VII_CORE_DIALOG_MOCKCONTROLREGISTRYINTERFACE_H
#define VII_CORE_DIALOG_MOCKCONTROLREGISTRYINTERFACE_H

#include <MultiAgentExperience/Control/Control.h>
#include <MultiAgentExperience/Control/ControlRegistryInterface.h>

#include <gmock/gmock.h>
#include <memory>
#include <set>

namespace multiAgentExperience {
namespace control {
namespace test {

class MockControlRegistryInterface : public ControlRegistryInterface {
public:
    MOCK_METHOD1(update, void(std::set<std::shared_ptr<Control>>));
};

}  // namespace test
}  // namespace control
}  // namespace multiAgentExperience

#endif  // VII_CORE_DIALOG_MOCKCONTROLREGISTRYINTERFACE_H
