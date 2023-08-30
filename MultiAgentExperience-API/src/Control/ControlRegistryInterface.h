/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
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
