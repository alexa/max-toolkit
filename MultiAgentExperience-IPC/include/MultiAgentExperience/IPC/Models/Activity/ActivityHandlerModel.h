/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/


#ifndef MULTIAGENTEXPERIENCE_IPC_ACTIVITYHANDLERMODEL_H
#define MULTIAGENTEXPERIENCE_IPC_ACTIVITYHANDLERMODEL_H

#include <memory>
#include <string>
#include <MultiAgentExperience/IPC/Messaging/Types/TypeUtils.h>
#include <MultiAgentExperience/Activity/ActivityHandlerInterface.h>

namespace multiAgentExperience {
namespace ipc {
namespace models {
namespace activity {

enum class ActivityHandlerFunctions {
    ON_DENIED,
    ON_GRANTED,
    ON_FOCUS_CHANGED,
    ON_STOP
};

} // namespace activity
} // namespace models
} // namespace ipc
} // namespace multiAgentExperience


template<>
inline std::string multiAgentExperience::ipc::messaging::types::getNamespace(const std::shared_ptr<::multiAgentExperience::activity::ActivityHandlerInterface> &t) {
    return "multiAgentExperience::activity";
}

template<>
inline std::string multiAgentExperience::ipc::messaging::types::getName(const std::shared_ptr<::multiAgentExperience::activity::ActivityHandlerInterface> &t) {
    return "ActivityHandlerInterface";
}

#endif //MULTIAGENTEXPERIENCE_IPC_ACTIVITYHANDLERMODEL_H
