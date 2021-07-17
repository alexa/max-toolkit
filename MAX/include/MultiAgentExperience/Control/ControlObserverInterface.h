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

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_CONTROL_CONTROLOBSERVERINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_CONTROL_CONTROLOBSERVERINTERFACE_H_

#include "Control.h"

#include <set>

namespace multiAgentExperience {
namespace control {

/**
 * @brief An interface used to receive notifications when the active control(s) change.
 */
class ControlObserverInterface {
public:
    /**
     * Destructor.
     */
    virtual ~ControlObserverInterface() = default;

    /**
     * When available controls change for active features, this callback delivers the new set of available ControlTypes.
     *
     * @param controls A set of the currently available ControlTypes for the user to take action on.
     */
    virtual void onControlChange(const std::set<ControlType>& controls) = 0;
};

}  // namespace control
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_CONTROL_CONTROLOBSERVERINTERFACE_H_
