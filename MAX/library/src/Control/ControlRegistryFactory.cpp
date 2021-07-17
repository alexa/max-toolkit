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

#include "Control/ControlRegistryFactory.h"

#include "Control/ControlAccessKeys.h"
#include "Control/ControlRegistry.h"

namespace multiAgentExperience {
namespace library {
namespace control {

ControlRegistryFactory::ControlRegistryFactory(
    std::shared_ptr<ControlAccessKeys> controlAccessKeys,
    std::shared_ptr<ControlStore> controlStore) :
        m_controlAccessKeys{controlAccessKeys},
        m_controlStore{controlStore} {
}

std::shared_ptr<ControlRegistry> ControlRegistryFactory::create(const ControlPriority controlPriority) {
    auto key = m_controlAccessKeys->requestAccessKey();
    return std::make_shared<ControlRegistry>(key, controlPriority, m_controlStore);
}

}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience
