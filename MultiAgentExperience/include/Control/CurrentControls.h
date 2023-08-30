/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CURRENTCONTROLS_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CURRENTCONTROLS_H_

#include <memory>
#include <unordered_set>

#include "ControlAccessKey.h"
#include "ControlName.h"
#include "ControlStore.h"

namespace multiAgentExperience {
namespace library {
namespace control {

class CurrentControls {
public:
    CurrentControls(const ControlAccessKey controlAccessKey, std::shared_ptr<ControlStore> controlStore);

    ~CurrentControls();

    std::unordered_set<ControlName> getCurrentControls();

    std::unordered_map<ControlName, std::weak_ptr<Control>> getControlsOfActivity(const activity::ActivityID& activityId);

private:
    const ControlAccessKey m_controlAccessKey;
    std::shared_ptr<ControlStore> m_controlStore;
};

}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CURRENTCONTROLS_H_
