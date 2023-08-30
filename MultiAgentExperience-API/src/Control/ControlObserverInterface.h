/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
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
