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

#include "Control/ControlRegistry.h"

#include "Control/Control.h"
#include "Control/ControlStore.h"

namespace multiAgentExperience {
namespace library {
namespace control {

ControlRegistry::ControlRegistry(
    ControlAccessKey controlAccessKey,
    ControlPriority controlPriority,
    std::shared_ptr<ControlStore> store) :
        m_controlAccessKey{controlAccessKey},
        m_controlPriority{controlPriority},
        m_store{store} {
}

void ControlRegistry::update(std::unordered_set<std::shared_ptr<Control>> controls) {
    m_store->store(m_controlAccessKey, m_controlPriority, controls);
}

void ControlRegistry::cleanup() {
    m_store->revokeAccess(m_controlAccessKey);
}

ControlRegistry::~ControlRegistry() {
    cleanup();
}

}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience
