/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Dialog/DialogActivity.h"

#include "Control/ControlRegistry.h"
#include "Dialog/DialogLifecycle.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {

DialogActivity::DialogActivity(std::shared_ptr<DialogLifecycle> dialog) : m_dialog(dialog) {
}

void DialogActivity::onControlRegistryAvailable(std::shared_ptr<control::ControlRegistry> controlRegistry) {
    // Dialogs wont use this registry. Instead registries lifespan should be limited to interruptible states only.
    controlRegistry->cleanup();
}

void DialogActivity::onForeground() {
    m_dialog->startDialog();
}

void DialogActivity::onBackground(multiAgentExperience::library::activity::MixingBehavior behavior) {
}

void DialogActivity::onStop() {
    m_dialog->finishDialog();
}

actor::ActorId DialogActivity::getActorId() const {
    return m_dialog->getActorId();
}

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience
