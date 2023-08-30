/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOG_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOG_H_

#include <memory>
#include <unordered_set>

#include <MultiAgentExperience/Actor/ActorId.h>

#include "Activity/ActivityID.h"
#include "DialogState.h"
#include "DialogController.h"
#include "Control/ControlInvoker.h"
#include "Control/ControlRegistry.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {

// TODO: Forward declare to address a circular dependency.
class DialogController;

class Dialog {
public:
    virtual ~Dialog() = default;

    virtual void onDialogStarted(std::shared_ptr<DialogController> dialogController) = 0;

    virtual void onListening(std::unordered_set<library::control::ControlName> availableControls) = 0;

    virtual void onThinking() = 0;

    virtual void onOtherState(
        const DialogState otherState,
        std::shared_ptr<library::control::ControlRegistry> controlRegistry,
        std::shared_ptr<library::control::ControlInvoker> controlInvoker) = 0;

    virtual void onDialogFinished() = 0;

    virtual multiAgentExperience::actor::ActorId getActorId() const = 0;

    /// method provided to set the activityId corresponding to the dialog
    virtual void setDialogActivityId(const activity::ActivityID dialogActivityId) = 0;
};

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOG_H_
