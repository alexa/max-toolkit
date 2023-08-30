/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Dialog/DialogRequest.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {

static DialogRequestID generateID() {
    static DialogRequestID id = 1;
    return id++;
}

DialogRequest::DialogRequest(
    std::shared_ptr<Dialog> dialog,
    const multiAgentExperience::dialog::DialogBargeInPriority& dialogBargeInPriority) :
    m_id(generateID()),
    m_dialog(dialog),
    m_dialogBargeInPriority(dialogBargeInPriority){
}

std::shared_ptr<Dialog> DialogRequest::getDialog() {
    return m_dialog;
}

const DialogRequestID DialogRequest::getID() const {
    return m_id;
}

multiAgentExperience::dialog::DialogBargeInPriority DialogRequest::getDialogBargeInPriority() const {
    return m_dialogBargeInPriority;
}

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience
