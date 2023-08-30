/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_DIALOG_DIALOGSTATE_H
#define MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_DIALOG_DIALOGSTATE_H

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace dialog {

// for example
enum class DialogState {
    UNKNOWN, LISTENING, THINKING, SPEAKING, STOPPED
};

inline std::string dialogStateToString(DialogState dialogState) {
    switch (dialogState) {
        case DialogState::UNKNOWN:
            return "UNKNOWN";
        case DialogState::LISTENING:
            return "LISTENING";
        case DialogState::THINKING:
            return "THINKING";
        case DialogState::SPEAKING:
            return "SPEAKING";
        case DialogState::STOPPED:
            return "STOPPED";
        default:
            return "NONE";
    }
}

} // namespace dialog
} // namespace multiAgentExperience
} // namespace alexaClientSDK

#endif //MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_DIALOG_DIALOGSTATE_H
