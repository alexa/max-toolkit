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

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_CONTROL_CONTROLREGISTERINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_CONTROL_CONTROLREGISTERINTERFACE_H_

#include <memory>
#include <set>

#include "Control.h"

namespace multiAgentExperience {
namespace control {

/**
 * The ControlRegistryInterface is used to register controls. Registered controls are made conditionally available to
 * other actors in the multi-agent experience to invoke these actions.
 */
class ControlRegistryInterface {
public:
    /**
     * Destructor.
     */
    virtual ~ControlRegistryInterface() = default;

    /**
     * Updates the currently available set of controls registered for the associated feature. Any previously registered
     * controls with this control registry instance will be overridden. No other registry instances will be affected.
     *
     * @param controls The set of controls to make available to other actors.
     */
    virtual void update(std::set<std::shared_ptr<Control>> controls) = 0;
};

}  // namespace control
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_CONTROL_CONTROLREGISTERINTERFACE_H_
