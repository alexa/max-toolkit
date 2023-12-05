/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_ACTIVITYREQUESTMODEL_H
#define MULTIAGENTEXPERIENCE_IPC_ACTIVITYREQUESTMODEL_H

#include <memory>
#include <string>

#include <MultiAgentExperience/IPC/Messaging/Types/TypeUtils.h>
#include <MultiAgentExperience/Activity/ActivityRequestInterface.h>

namespace multiAgentExperience {
namespace ipc {
namespace models {
namespace activity {
//TODO: standardize a way to resolve functions with same parameters within a type. This solutions uses multiple enums.
enum class ActivityRequestGetType {
    FUNCTION
};

enum class ActivityRequestGetHandler {
    FUNCTION
};

enum class ActivityRequestGetMixabilityType {
    FUNCTION
};

enum class ActivityRequestFunctionReturns {
    GET_TYPE,
    GET_HANDLER,
    GET_MIXABILITY_TYPE
};

} // namespace activity
} // namespace models
} // namespace ipc
} // namespace multiAgentExperience

template<>
inline std::string multiAgentExperience::ipc::messaging::types::getNamespace(const std::shared_ptr<multiAgentExperience::activity::ActivityRequestInterface> &t) {
    return "multiAgentExperience::activity";
}

template<>
inline std::string multiAgentExperience::ipc::messaging::types::getName(const std::shared_ptr<multiAgentExperience::activity::ActivityRequestInterface> &t) {
    return "ActivityRequestInterface";
}

#endif //MULTIAGENTEXPERIENCE_IPC_ACTIVITYREQUESTMODEL_H
