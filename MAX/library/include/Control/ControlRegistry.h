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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CONTROLREGISTRY_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CONTROLREGISTRY_H_

#include <memory>
#include <unordered_set>

#include "Control.h"
#include "ControlStore.h"
#include "ControlAccessKey.h"
#include "ControlPriority.h"

namespace multiAgentExperience {
namespace library {
namespace control {

class ControlRegistry {
public:
    ControlRegistry(
        const ControlAccessKey controlAccessKey,
        const ControlPriority controlPriority,
        std::shared_ptr<ControlStore> store);

    ~ControlRegistry();

    void update(std::unordered_set<std::shared_ptr<Control>> controls);

    void cleanup();

private:
    const ControlAccessKey m_controlAccessKey;
    const ControlPriority m_controlPriority;
    std::shared_ptr<ControlStore> m_store;
};

}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CONTROLREGISTRY_H_
