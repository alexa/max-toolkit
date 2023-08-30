/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_DEVICERESTRICTREQUESTSHELPER_H
#define MULTIAGENTEXPERIENCE_DEVICERESTRICTREQUESTSHELPER_H

#include <mutex>

#include "MultiAgentExperience/Actor/ActorId.h"

namespace multiAgentExperience {
namespace library {
namespace device {

class DeviceRestrictRequestsHelper {
public:
    DeviceRestrictRequestsHelper();
    virtual ~DeviceRestrictRequestsHelper() = default;
    virtual void restrictRequestsToActor(const actor::ActorId& actorId);
    virtual void stopRestrictingRequests();
    bool canRequestBeGrantedForActor(const actor::ActorId& actorId);

private:
    std::mutex m_requestMutex;
    bool m_areRequestsRestricted;
    actor::ActorId m_actorExempted;
};

}  // namespace device
}  // namespace library
}  // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_DEVICERESTRICTREQUESTSHELPER_H
