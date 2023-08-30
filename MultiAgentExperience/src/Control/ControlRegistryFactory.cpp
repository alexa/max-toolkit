/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Control/ControlRegistryFactory.h"

#include "Control/ControlAccessKeys.h"
#include "Control/ControlRegistry.h"

namespace multiAgentExperience {
namespace library {
namespace control {

ControlRegistryFactory::ControlRegistryFactory(
    std::shared_ptr<ControlAccessKeys> controlAccessKeys,
    std::shared_ptr<ControlStore> controlStore) :
        m_controlAccessKeys{controlAccessKeys},
        m_controlStore{controlStore} {
}

std::shared_ptr<ControlRegistry> ControlRegistryFactory::create(const ControlPriority controlPriority) {
    auto key = m_controlAccessKeys->requestAccessKey();
    return std::make_shared<ControlRegistry>(key, controlPriority, m_controlStore);
}

}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience
