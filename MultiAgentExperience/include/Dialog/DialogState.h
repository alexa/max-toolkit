/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGSTATE_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGSTATE_H_

#include <string>

namespace multiAgentExperience {
namespace library {
namespace dialog {

using DialogState = std::string;

class DialogStateFactory {
public:
    static DialogState create(std::string value) {
        return DialogState(value);
    }

    static const DialogState idle() {
        return DialogStateFactory::create("idle");
    }

    static const DialogState listening() {
        return DialogStateFactory::create("listening");
    }

    static const DialogState thinking() {
        return DialogStateFactory::create("thinking");
    }

    static const DialogState speaking() {
        return DialogStateFactory::create("speaking");
    }

    static const DialogState finished() {
        return DialogStateFactory::create("finished");
    }

    static const bool isNotIdle(const DialogState& dialogState) {
        return dialogState != idle();
    }

    static const bool isNotListeningOrThinking(const DialogState& dialogState) {
        return dialogState != listening() && dialogState != thinking();
    }
};

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGSTATE_H_
