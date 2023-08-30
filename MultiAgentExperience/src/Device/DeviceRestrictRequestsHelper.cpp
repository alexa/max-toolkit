/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <mutex>

#include "Device/DeviceRestrictRequestsHelper.h"

namespace multiAgentExperience {
namespace library {
namespace device {


DeviceRestrictRequestsHelper::DeviceRestrictRequestsHelper():
    m_areRequestsRestricted{false},
    m_actorExempted{actor::ActorId("")}{
}

void DeviceRestrictRequestsHelper::restrictRequestsToActor(const actor::ActorId& actorId) {
    std::unique_lock<std::mutex> requestLock(m_requestMutex);
    m_areRequestsRestricted = true;
    m_actorExempted = actorId;
}

void DeviceRestrictRequestsHelper::stopRestrictingRequests() {
    std::unique_lock<std::mutex> requestLock(m_requestMutex);
    m_areRequestsRestricted = false;
    m_actorExempted = actor::ActorId("");
}

bool DeviceRestrictRequestsHelper::canRequestBeGrantedForActor(const actor::ActorId& actorId) {
    std::unique_lock<std::mutex> requestLock(m_requestMutex);
    return !m_areRequestsRestricted || (m_actorExempted == actorId);
}

}  // namespace device
}  // namespace library
}  // namespace multiAgentExperience
