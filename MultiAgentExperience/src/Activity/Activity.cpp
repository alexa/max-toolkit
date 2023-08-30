/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Activity/Activity.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

Activity::Activity() : m_id(-1) {
}

void Activity::onRequestGranted(const ActivityID id) {
    m_id = id;
}

void Activity::onControlRegistryAvailable(std::shared_ptr<control::ControlRegistry> controlRegistry) {
}

const ActivityID Activity::getID() {
    return m_id;
}

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience
