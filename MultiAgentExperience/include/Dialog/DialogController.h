/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGCONTROLLER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGCONTROLLER_H_

#include <memory>

#include "DialogState.h"
#include "DialogLifecycle.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {

// TODO: Forward declare to address a circular dependency.
class DialogLifecycle;

class DialogController {
public:
    DialogController(std::shared_ptr<DialogLifecycle> m_dialogLifecycle);

    void startListening();

    void startThinking();

    void startOtherState(const DialogState otherState);

    void finishDialog();

    void markUninterruptible();

    std::weak_ptr<control::Control> getHighestPriorityControlFromName(const control::ControlName& controlName);

private:
    std::shared_ptr<DialogLifecycle> m_dialogLifecycle;
};

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGCONTROLLER_H_
