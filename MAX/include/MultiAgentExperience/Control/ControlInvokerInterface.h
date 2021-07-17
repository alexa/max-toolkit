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
