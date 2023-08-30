/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CONTROLREGISTRY_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CONTROLREGISTRY_H_

#include <memory>
#include <unordered_set>

#include "Control.h"
#include "ControlStore.h"
#include "ControlAccessKey.h"
#include "ControlPriority.h"

namespace multiAgentExperience {
namespace library {
namespace control {

class ControlRegistry {
public:
    ControlRegistry(
        const ControlAccessKey controlAccessKey,
        const ControlPriority controlPriority,
        std::shared_ptr<ControlStore> store);

    ~ControlRegistry();

    void update(
        activity::ActivityID activityId,
        std::unordered_set<std::shared_ptr<Control>> controls);

    void cleanup();

private:
    const ControlAccessKey m_controlAccessKey;
    const ControlPriority m_controlPriority;
    std::shared_ptr<ControlStore> m_store;
};

}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CONTROLREGISTRY_H_
