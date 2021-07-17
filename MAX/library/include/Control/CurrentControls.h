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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CURRENTCONTROLS_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CURRENTCONTROLS_H_

#include <memory>
#include <unordered_set>

#include "ControlAccessKey.h"
#include "ControlName.h"
#include "ControlStore.h"

namespace multiAgentExperience {
namespace library {
namespace control {

class CurrentControls {
public:
    CurrentControls(const ControlAccessKey controlAccessKey, std::shared_ptr<ControlStore> controlStore);

    ~CurrentControls();

    std::unordered_set<ControlName> getCurrentControls();

private:
    const ControlAccessKey m_controlAccessKey;
    std::shared_ptr<ControlStore> m_controlStore;
};

}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CURRENTCONTROLS_H_
