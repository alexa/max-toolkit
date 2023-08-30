/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/


#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CONTROLSTOREOBSERVERINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CONTROLSTOREOBSERVERINTERFACE_H_

#include "Control.h"

#include <unordered_set>

namespace multiAgentExperience {
namespace library {
namespace control {

class ControlStoreObserverInterface {
public:
    virtual ~ControlStoreObserverInterface() = default;

    virtual void onControlsUpdated(const std::unordered_set<ControlName>& controlNames) = 0;
};

}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CONTROLSTOREOBSERVERINTERFACE_H_
