/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <sstream>
#include <unordered_set>

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Control/Control.h"
#include "Control/ControlRegistry.h"
#include "Core/Transformer/ControlRegistryTransformer.h"
#include "Core/Transformer/TransformerUtils.h"

#include "Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

static const std::string MODULE_TAG("ControlRegistryTransformer");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

static bool isValidControlType(const multiAgentExperience::control::ControlType type) {
    return type == multiAgentExperience::control::ControlType::STOP;
}

ControlRegistryTransformer::ControlRegistryTransformer(
    const activity::ActivityID activityId,
    std::shared_ptr<control::ControlRegistry> controlRegistry) :
    m_activityId{activityId},
    m_controlRegistry{controlRegistry} {
    std::stringstream ss;
    ss << "details:"
       << " activityId=" << activityId;
    LX(DEBUG0, ss.str());
}

void ControlRegistryTransformer::update(std::set<std::shared_ptr<multiAgentExperience::control::Control>> controls) {
    std::stringstream ss;
    ss << "details:"
       << " activityId=" << m_activityId
       << " controls=" << multiAgentExperience::library::utils::toString(controls);
    LX(DEBUG0, ss.str());

    std::unordered_set<std::shared_ptr<library::control::Control>> transformedControls;

    for (const auto& externalControl : controls) {
        if (isValidControlType(externalControl->type)) {
            auto convertedControlType = TransformerUtils::convertControlTypeToControlName(externalControl->type);
            auto control = library::control::Control::create(convertedControlType, [externalControl]() { externalControl->task(); });
            transformedControls.insert(control);
        }
    }

    m_controlRegistry->update(m_activityId, transformedControls);
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
