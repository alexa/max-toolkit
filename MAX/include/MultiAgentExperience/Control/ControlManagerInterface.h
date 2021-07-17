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

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_CONTROL_CONTROLMANAGERINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_CONTROL_CONTROLMANAGERINTERFACE_H_

#include "ControlObserverInterface.h"

#include <memory>

namespace multiAgentExperience {
namespace control {

/**
 * An interface used to register observers of control changes.
 */
class ControlManagerInterface {
public:
    /**
     * Destructor.
     */
    virtual ~ControlManagerInterface() = default;

    /**
     * "Register" an observers to be notified when the active controls change.
     * @param observer the ControlObserverInterface implementation
     */
    virtual void addObserver(std::weak_ptr<ControlObserverInterface> observer) = 0;

    /**
     * "De-register" all observers of control changes
     */
    virtual void clearObservers() = 0;
};

}  // namespace control
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_CONTROL_CONTROLMANAGERINTERFACE_H_
