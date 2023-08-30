/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Control/ControlRegistry.h"

#include "Control/Control.h"
#include "Control/ControlStore.h"

namespace multiAgentExperience {
namespace library {
namespace control {

ControlRegistry::ControlRegistry(
    ControlAccessKey controlAccessKey,
    ControlPriority controlPriority,
    std::shared_ptr<ControlStore> store) :
        m_controlAccessKey{controlAccessKey},
        m_controlPriority{controlPriority},
        m_store{store} {
}

void ControlRegistry::update(
    activity::ActivityID activityId,
    std::unordered_set<std::shared_ptr<Control>> controls) {
    m_store->store(m_controlAccessKey, activityId, m_controlPriority, controls);
}

void ControlRegistry::cleanup() {
    m_store->revokeAccess(m_controlAccessKey);
}

ControlRegistry::~ControlRegistry() {
    cleanup();
}

}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience
