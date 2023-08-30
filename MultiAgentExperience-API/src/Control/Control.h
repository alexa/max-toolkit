/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
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
