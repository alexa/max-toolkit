/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Control/CurrentControls.h"

#include "Control/ControlName.h"
#include "Control/ControlStore.h"

namespace multiAgentExperience {
namespace library {
namespace control {

CurrentControls::CurrentControls(const ControlAccessKey controlAccessKey, std::shared_ptr<ControlStore> controlStore) :
        m_controlAccessKey(controlAccessKey),
        m_controlStore(controlStore) {
}

std::unordered_set<ControlName> CurrentControls::getCurrentControls() {
    return m_controlStore->getUnionOfControlNames(m_controlAccessKey);
}

std::unordered_map<ControlName, std::weak_ptr<Control>> CurrentControls::getControlsOfActivity(const activity::ActivityID& activityId) {
    return m_controlStore->getControlsOfActivity(m_controlAccessKey, activityId);
}

CurrentControls::~CurrentControls() {
    m_controlStore->revokeAccess(m_controlAccessKey);
}

}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience
