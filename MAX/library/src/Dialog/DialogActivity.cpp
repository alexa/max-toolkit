/*
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
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

void DialogActivity::onBackground() {
}

void DialogActivity::onStop() {
    m_dialog->finishDialog();
}

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience
