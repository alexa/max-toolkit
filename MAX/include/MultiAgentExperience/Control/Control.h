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

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_CONTROL_CONTROL_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_CONTROL_CONTROL_H_

#include <functional>

namespace multiAgentExperience {
namespace control {

/// An identifier alias for controls.
using ControlId = unsigned int;

/**
 * The ControlType enumerate the set of controls sharable across multiple Agent's Dialogs and Activities.
 */
enum class ControlType {
    /// Value for stop controls.
    STOP
};

using ControlTask = std::function<void()>;

/**
 * A Control couples a ControlType with a task to execute if another actor invokes the available Control.
 */
struct Control {
    /**
     * Constructs the Control with the given type and task.
     * @param type The type of the control.
     * @param task The task to execute if the control is invoked.
     */
    Control(ControlType type, ControlTask task) : id{0}, type{type}, task{task} {
    }

    /// The identifier of this control.
    ControlId id;
    /// The type of this control.
    ControlType type;
    /// The task to execute if the control is invoked.
    ControlTask task;
};

}  // namespace control
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_CONTROL_CONTROL_H_
