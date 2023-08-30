/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_CONTROL_STOPCONTROLFACTORY_H
#define MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_CONTROL_STOPCONTROLFACTORY_H

#include <set>
#include <memory>

#include <MultiAgentExperience/Control/Control.h>

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace control {

inline std::set<std::shared_ptr<::multiAgentExperience::control::Control>> createStopControl(
        const std::shared_ptr<::multiAgentExperience::activity::ActivityControllerInterface>& activityController) {
    auto stopCallback = [activityController]() {
        activityController->stop();
    };
    return {std::make_shared<::multiAgentExperience::control::Control>(::multiAgentExperience::control::ControlType::STOP, stopCallback)};
}

} // namespace control
} // namespace multiAgentExperience
} // namespace alexaClientSDK

#endif //MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_CONTROL_STOPCONTROLFACTORY_H
