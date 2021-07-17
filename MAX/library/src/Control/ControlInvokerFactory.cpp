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

#include "Control/ControlInvokerFactory.h"

#include "Control/ControlAccessKeys.h"
#include "Control/ControlInvoker.h"

namespace multiAgentExperience {
namespace library {
namespace control {

ControlInvokerFactory::ControlInvokerFactory(
    std::shared_ptr<ControlAccessKeys> controlAccessKeys,
    std::shared_ptr<ControlStore> controlStore) :
        m_controlAccessKeys(controlAccessKeys),
        m_controlStore(controlStore) {
}

std::shared_ptr<ControlInvoker> ControlInvokerFactory::create() {
    auto key = m_controlAccessKeys->requestAccessKey();
    return std::make_shared<ControlInvoker>(key, m_controlStore);
}

}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience
