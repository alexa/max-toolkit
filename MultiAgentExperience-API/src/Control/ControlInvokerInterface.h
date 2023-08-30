/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_CONTROL_CONTROLINVOKERINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_CONTROL_CONTROLINVOKERINTERFACE_H_

#include "Control.h"

namespace multiAgentExperience {
namespace control {

/**
 * An interface used by the integrator to take action on available controls.
 */
class ControlInvokerInterface {
public:
    /**
     * Destructor.
     */
    virtual ~ControlInvokerInterface() = default;

    /**
     *
     * Invokes a Universal Device Command (if it is valid).
     *
     * @param controlType - The type of Universal Device Command to invoke. If it is not a control which is available
     *                      then the invocation does nothing.
     */
    virtual void invokeControl(const multiAgentExperience::control::ControlType& controlType) = 0;
};

}  // namespace control
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_CONTROL_CONTROLINVOKERINTERFACE_H_
