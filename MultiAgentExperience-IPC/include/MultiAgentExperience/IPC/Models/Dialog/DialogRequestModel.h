/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_IPC_MODELS_DIALOG_DIALOGREQUESTMODEL_H
#define MULTIAGENTEXPERIENCE_IPC_MODELS_DIALOG_DIALOGREQUESTMODEL_H

#include <memory>
#include <string>

#include <MultiAgentExperience/IPC/Messaging/Types/TypeUtils.h>
#include <MultiAgentExperience/Dialog/DialogRequestInterface.h>

namespace multiAgentExperience {
namespace ipc {
namespace models {
namespace dialog {

enum class DialogRequestFunctions {
    ON_DENIED,
    ON_DIALOG_STARTED,
    ON_ERROR,
    ON_DIALOG_STOPPED
};

/**
 * This method - @c DialogRequestInterface::getDialogBargeInPriority needs its own enum class. This is because
 * the method does not return void, but instead returns an enum @c DialogBargeInPriority.
 *
 * Hence, the corresponding @c TransportSenderInterface::send method for this needs to return a
 * @c Message of @c EnumPayload type. However, the @c send method cannot be overloaded with the same argument (DialogRequestFunctions)
 * and different return type.
 *
 * Hence, we must overload the @c send method by using a different argument - DialogRequestFunctionGetDialogBargeInPriority.
 */
enum class DialogRequestFunctionGetDialogBargeInPriority {
    FUNCTION
};

enum class DialogRequestFunctionReturns {
    GET_DIALOG_BARGE_IN_PRIORITY
};

} // namespace dialog
} // namespace models
} // namespace ipc
} // namespace multiAgentExperience

template<>
inline std::string multiAgentExperience::ipc::messaging::types::getNamespace(const std::shared_ptr<multiAgentExperience::dialog::DialogRequestInterface> &t) {
    return "multiAgentExperience::dialog";
}

template<>
inline std::string multiAgentExperience::ipc::messaging::types::getName(const std::shared_ptr<multiAgentExperience::dialog::DialogRequestInterface> &t) {
    return "DialogRequestInterface";
}

#endif //MULTIAGENTEXPERIENCE_IPC_MODELS_DIALOG_DIALOGREQUESTMODEL_H
