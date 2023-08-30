/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGREQUEST_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGREQUEST_H_

#include <memory>

#include <MultiAgentExperience/Actor/ActorId.h>
#include <MultiAgentExperience/Dialog/DialogBargeInPriority.h>

#include "DialogRequestID.h"
#include "Dialog.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {

class DialogRequest {
public:
    DialogRequest(
        std::shared_ptr<Dialog> dialog,
        const multiAgentExperience::dialog::DialogBargeInPriority& dialogBargeInPriority);

    virtual ~DialogRequest() = default;

    std::shared_ptr<Dialog> getDialog();

    const DialogRequestID getID() const;

    multiAgentExperience::dialog::DialogBargeInPriority getDialogBargeInPriority() const;

    virtual multiAgentExperience::actor::ActorId getActorId() const = 0;

    virtual void onGranted() = 0;

    virtual void onDenied() = 0;

private:
    const DialogRequestID m_id;
    std::shared_ptr<Dialog> m_dialog;
    const multiAgentExperience::dialog::DialogBargeInPriority m_dialogBargeInPriority;
};

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGREQUEST_H_
