/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_CONTROLREGISTRYTRANSFORMER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_CONTROLREGISTRYTRANSFORMER_H_

#include <memory>
#include <set>

#include <MultiAgentExperience/Control/ControlRegistryInterface.h>

#include "Control/ControlRegistry.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

class ControlRegistryTransformer : public multiAgentExperience::control::ControlRegistryInterface {
public:
    ControlRegistryTransformer(
        const activity::ActivityID activityId,
        std::shared_ptr<control::ControlRegistry> controlRegistry);

    /// @name ControlRegistryInterface method overrides.
    /// @{
    void update(std::set<std::shared_ptr<multiAgentExperience::control::Control>> controls) override;
    /// @}

private:
    const activity::ActivityID m_activityId;
    std::shared_ptr<control::ControlRegistry> m_controlRegistry;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_CONTROLREGISTRYTRANSFORMER_H_
