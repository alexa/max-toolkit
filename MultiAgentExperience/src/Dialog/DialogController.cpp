/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Dialog/DialogController.h"

#include "Dialog/DialogLifecycle.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {

static const std::string MODULE_TAG("DialogController");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

DialogController::DialogController(std::shared_ptr<DialogLifecycle> dialogLifecycle) :
        m_dialogLifecycle(dialogLifecycle) {
}

void DialogController::startListening() {
    m_dialogLifecycle->startListening();
}

void DialogController::startThinking() {
    m_dialogLifecycle->startThinking();
}

void DialogController::startOtherState(const DialogState otherState) {
    m_dialogLifecycle->startOtherState(otherState);
}

void DialogController::finishDialog() {
    m_dialogLifecycle->finishDialog();
}

void DialogController::markUninterruptible() {
    m_dialogLifecycle->markUninterruptible();
}

std::weak_ptr<control::Control> DialogController::getHighestPriorityControlFromName(const control::ControlName& controlName) {
    LX(DEBUG3, "");
    return m_dialogLifecycle->getHighestPriorityControlFromName(controlName);
}

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience
