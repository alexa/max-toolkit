/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
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

    /**
     * Stop all ongoing alerts across all agents
     */
    virtual void stopAllAlerts() = 0;
};

}  // namespace control
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_CONTROL_CONTROLMANAGERINTERFACE_H_
